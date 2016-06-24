#!/bin/sh
set -e

. ./config.sh
mkdir -p sysroot

. ./headers.sh

for PROJECT in $PROJECTS; do
  DESTDIR="$PWD/sysroot" $MAKE -C $PROJECT install
done
