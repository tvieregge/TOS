#!/bin/sh
set -e
. ./iso.sh

qemu-system-x86_64 -cdrom tos.iso $1
