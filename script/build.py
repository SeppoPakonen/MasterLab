#!/usr/bin/env python3

import os
import re
import shutil
import subprocess
import sys
from pathlib import Path


def read_mainconfigs(upp_path):
    if not upp_path.exists():
        return []
    text = upp_path.read_text(encoding="utf-8", errors="replace")
    lines = text.splitlines()
    start = None
    for idx, line in enumerate(lines):
        if line.strip() == "mainconfig":
            start = idx + 1
            break
    if start is None:
        return []
    block_lines = []
    for line in lines[start:]:
        if not line.strip():
            if block_lines:
                break
            continue
        if line[:1].isspace():
            block_lines.append(line)
            continue
        break
    block = "\n".join(block_lines)
    entries = re.findall(r'"([^"]*)"\s*=\s*"([^"]*)"', block)
    return [{"name": name, "flags": flags} for name, flags in entries]


def select_config_by_token(configs, token):
    token = token.strip()
    try:
        index = int(token, 10)
    except ValueError:
        index = None
    if index is not None:
        if index < 0 or index >= len(configs):
            raise ValueError(f"Mainconfig index out of range: {index}")
        return configs[index], index
    for idx, cfg in enumerate(configs):
        if cfg["name"].lower() == token.lower():
            return cfg, idx
    raise ValueError(f"Unknown mainconfig: {token}")


def split_flags(flags):
    return [token.strip(",;") for token in re.split(r"[\s,]+", flags.strip()) if token]


def normalize_flags(flags):
    return ",".join(filter(None, split_flags(flags)))


def parse_jobs(arg):
    try:
        value = int(arg, 10)
    except ValueError as exc:
        raise ValueError(f"Invalid jobs value: {arg}") from exc
    if value <= 0:
        raise ValueError("Jobs must be positive")
    return value


def print_help():
    print(
        "\n".join(
            [
                "Usage: build.py [options] <target>",
                "",
                "Options:",
                "  --android, -Android              Select Android build method (BUILDER=ANDROID)",
                "  --bootstrap, -Bootstrap, -bs     Bootstrap-build umk via Makefile",
                "  --smoketest, -Smoketest          Build a single source file smoke target",
                "  --clean, -Clean, -c              Clean build (rebuild all)",
                "  --release, -Release, -r          Use release build flags in umk",
                "  --mainconf X, -mc X              Select mainconfig by index or name",
                "  --list-conf P, -lc P             List mainconfigs for a package",
                "  --method X, -m X                 Select build method by index, name, or path",
                "  --list-methods, -ListMethods     List build methods and exit",
                "  --jobs N, -j N, -jN              Parallel jobs",
                "  --verbose, -Verbose, -v          Verbose output",
                "  --flags F, -f F                  Extra flags to append",
                "  --output O, -o O                 Custom output filename",
                "  --dump-cmd                       Dump the umk command and exit",
                "  --help, -Help, -h                Show this help",
            ]
        )
    )


def method_dirs(home):
    if os.name == "nt":
        return [home / "upp"]
    return [home / ".config" / "u++" / "theide", home / ".config" / "u++" / "umk", home / "upp"]


def collect_methods(home):
    methods = []
    seen = set()
    for d in method_dirs(home):
        if not d.exists():
            continue
        for bm in sorted(d.glob("*.bm")):
            key = str(bm.resolve())
            if key in seen:
                continue
            seen.add(key)
            methods.append(bm)
    return methods


def list_methods(home):
    methods = collect_methods(home)
    if not methods:
        print("No build methods found.")
        return
    print("\nAvailable build methods:")
    for idx, bm in enumerate(methods):
        print(f"{idx:2}: {bm.stem} ({bm})")
    print("")


def default_method(home):
    for env_name in ("UPP_BM", "UPP_BUILD_MODEL"):
        env_value = os.environ.get(env_name)
        if env_value:
            return env_value
    methods = collect_methods(home)
    for bm in methods:
        if bm.stem.upper() == "CLANG":
            return str(bm)
    if methods:
        return str(methods[0])
    return "CLANG"


def resolve_method(token, home):
    if token is None:
        return default_method(home)
    if token.upper() == "ANDROID":
        return "ANDROID"
    methods = collect_methods(home)
    try:
        idx = int(token, 10)
        if idx < 0 or idx >= len(methods):
            raise ValueError(f"Method index out of range: {idx}")
        return str(methods[idx])
    except ValueError:
        pass
    path_candidate = Path(token).expanduser()
    if path_candidate.exists():
        return str(path_candidate)
    for bm in methods:
        if bm.stem.lower() == token.lower():
            return str(bm)
    raise ValueError(f"Unknown build method: {token}")


def find_umk(repo_root, home):
    env_umk = os.environ.get("UMK")
    candidates = []
    if env_umk:
        candidates.append(Path(env_umk).expanduser())
    if os.name == "nt":
        candidates += [repo_root / "umk.exe", home / "upp" / "umk.exe"]
    else:
        candidates += [repo_root / "umk", home / "bin" / "umk", home / "upp" / "umk"]
    for path in candidates:
        if path.exists():
            return str(path)
    discovered = shutil.which("umk")
    if discovered:
        return discovered
    return None


def resolve_upp_path(repo_root, target):
    target_path = Path(target)
    if target_path.suffix == ".upp":
        return target_path if target_path.is_absolute() else (Path.cwd() / target_path)
    
    # List of directories to search for packages
    search_dirs = [
        repo_root / "src",
        repo_root / "effects",
        repo_root / "instruments",
        repo_root / "midi_effects",
        repo_root / "midi_inserts",
        repo_root / "midi_instruments",
    ]

    for base_dir in search_dirs:
        if not base_dir.exists():
            continue
        direct = base_dir / target / f"{target}.upp"
        if direct.exists():
            return direct
            
    candidates = []
    for base_dir in search_dirs:
        if base_dir.exists():
            candidates.extend(list(base_dir.rglob(f"{target}.upp")))

    if len(candidates) == 1:
        return candidates[0]
    if len(candidates) > 1:
        raise ValueError(f"Multiple .upp files named {target}.upp found in search paths.")
    
    raise ValueError(f"Cannot find target package '{target}' in search paths.")


def list_configs(repo_root, token):
    upp_path = resolve_upp_path(repo_root, token)
    configs = read_mainconfigs(upp_path)
    if not configs:
        print(f"No mainconfig entries in {upp_path}")
        return
    for idx, cfg in enumerate(configs):
        print(f"{idx:2}: {cfg['name']} = \"{cfg['flags']}\"")


def main():
    repo_root = Path(__file__).resolve().parent.parent
    home = Path.home()

    raw_args = sys.argv[1:]
    if not raw_args or any(a in raw_args for a in ("--help", "-Help", "-h")):
        print_help()
        sys.exit(0 if raw_args else 1)

    if "--bootstrap" in raw_args or "-Bootstrap" in raw_args or "-bs" in raw_args:
        subprocess.run(["make"], cwd=str(repo_root), check=False)
        sys.exit(0)

    if "--list-methods" in raw_args or "-ListMethods" in raw_args:
        list_methods(home)
        sys.exit(0)

    target = None
    clean = False
    release = False
    verbose = False
    android = False
    dump_cmd = False
    mainconf = None
    list_conf = None
    method_token = None
    jobs = None
    extra_flags = None
    custom_output = None

    i = 0
    while i < len(raw_args):
        arg = raw_args[i]
        if arg in ("--clean", "-Clean", "-c"):
            clean = True
        elif arg in ("--release", "-Release", "-r"):
            release = True
        elif arg in ("--verbose", "-Verbose", "-v"):
            verbose = True
        elif arg in ("--android", "-Android"):
            android = True
        elif arg in ("--dump-cmd",):
            dump_cmd = True
        elif arg in ("--smoketest", "-Smoketest"):
            target = "daw"
        elif arg in ("--mainconf", "-mc"):
            i += 1
            mainconf = raw_args[i]
        elif arg in ("--list-conf", "-lc"):
            i += 1
            list_conf = raw_args[i]
        elif arg in ("--method", "-m"):
            i += 1
            method_token = raw_args[i]
        elif arg in ("--jobs", "-j"):
            i += 1
            jobs = parse_jobs(raw_args[i])
        elif arg.startswith("-j") and len(arg) > 2:
            jobs = parse_jobs(arg[2:])
        elif arg in ("--flags", "-f"):
            i += 1
            extra_flags = raw_args[i]
        elif arg in ("--output", "-o"):
            i += 1
            custom_output = raw_args[i]
        elif not arg.startswith("-"):
            target = arg
        else:
            print(f"Error: Unknown option: {arg}")
            sys.exit(1)
        i += 1

    if list_conf:
        list_configs(repo_root, list_conf)
        sys.exit(0)

    if not target:
        print("Error: target is required.")
        sys.exit(1)

    umk_path = find_umk(repo_root, home)
    if not umk_path:
        print("Error: umk not found.")
        sys.exit(1)

    try:
        upp_path = resolve_upp_path(repo_root, target).resolve()
    except ValueError as e:
        print(f"Error: {e}")
        sys.exit(1)

    target_name = upp_path.stem
    method = "ANDROID" if android else resolve_method(method_token, home)

    search_dirs = [
        repo_root / "src",
        repo_root / "effects",
        repo_root / "instruments",
        repo_root / "midi_effects",
        repo_root / "midi_inserts",
        repo_root / "midi_instruments",
    ]

    roots_candidates = [d.resolve() for d in search_dirs]
    roots_candidates += [
        (repo_root / "uppsrc").resolve(),
        (repo_root.parent / "ai-upp" / "uppsrc").resolve(),
        (home / "ai-upp" / "uppsrc").resolve(),
        (home / "upp" / "uppsrc").resolve(),
    ]
    
    roots = []
    seen_roots = set()
    for root in roots_candidates:
        key = str(root)
        if key in seen_roots or not root.exists():
            continue
        seen_roots.add(key)
        roots.append(key)
    roots_arg = ";".join(roots) if os.name == "nt" else ",".join(roots)

    configs = read_mainconfigs(upp_path)
    custom_flags = extra_flags if extra_flags else None
    if not custom_flags and mainconf:
        try:
            cfg, _ = select_config_by_token(configs, mainconf)
        except ValueError as exc:
            print(f"Error: {exc}")
            sys.exit(1)
        custom_flags = normalize_flags(cfg["flags"])
    elif not custom_flags and configs:
        custom_flags = normalize_flags(configs[0]["flags"])

    flags_list = split_flags(custom_flags) if custom_flags else []
    flags_list = [f for f in flags_list if f.upper() != "DEBUG_FULL"]
    if not release:
        flags_list.append("DEBUG_FULL")
    custom_flags = ",".join(dict.fromkeys(flags_list)) if flags_list else None

    build_flags = "-bsH1r" if release else "-bsdH1"
    if clean:
        build_flags += "a"
    if verbose:
        build_flags += "v"
    if jobs:
        build_flags = re.sub(r"H\d+", f"H{jobs}", build_flags)

    output_name = custom_output if custom_output else target_name
    output_path = repo_root / "bin" / output_name
    if os.name == "nt" and output_path.suffix.lower() != ".exe":
        output_path = output_path.with_suffix(".exe")
    output_path.parent.mkdir(parents=True, exist_ok=True)

    cmd = [umk_path, roots_arg, target_name, method, build_flags]
    if custom_flags:
        cmd.append(f"+{custom_flags}")
    cmd.append(str(output_path))

    print(f"Executing: {' '.join(cmd)}")
    if dump_cmd:
        sys.exit(0)

    result = subprocess.run(cmd)
    sys.exit(result.returncode)


if __name__ == "__main__":
    main()
