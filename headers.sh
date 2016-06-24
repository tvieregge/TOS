#!/bin/sh
set -e

for PROJECT in $SYSTEM_HEADER_PROJECTS; do
  DESTDIR="$PWD/sysroot" $MAKE -C $PROJECT install-headers
done
