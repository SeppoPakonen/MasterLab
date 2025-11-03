#!/bin/sh
if [ "$1" = "--clean" ]; then
    umk src,$HOME/ai-upp/uppsrc daw ~/.config/u++/theide/CLANG.bm -bdsa +GUI,DEBUG_FULL bin/daw
else
    umk src,$HOME/ai-upp/uppsrc daw ~/.config/u++/theide/CLANG.bm -bds +GUI,DEBUG_FULL bin/daw
fi
