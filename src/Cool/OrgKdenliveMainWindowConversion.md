# Conversion Note: `org.kdenlive.MainWindow.xml`

## Source
- `tmp/k/src/org.kdenlive.MainWindow.xml`

## Target
- `src/Cool/OrgKdenliveMainWindowConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
<!DOCTYPE node PUBLIC "-//freedesktop//DTD D-BUS Object Introspection 1.0//EN" "http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd">
<node>
  <interface name="org.kde.kdenlive.rendering">
    <signal name="abortRenderJob">
      <arg name="url" type="s" direction="out"/>
    </signal>
    <method name="setRenderingProgress">
      <arg name="url" type="s" direction="in"/>
      <arg name="progress" type="i" direction="in"/>
      <arg name="frame" type="i" direction="in"/>
    </method>
    <method name="setRenderingFinished">
      <arg name="url" type="s" direction="in"/>
      <arg name="status" type="i" direction="in"/>
      <arg name="error" type="s" direction="in"/>
    </method>
    <method name="addProjectClip">
      <arg name="url" type="s" direction="in"/>
    </method>
    <method name="addTimelineClip">
      <arg name="url" type="s" direction="in"/>
    </method>
    </interface>
</node>

```
