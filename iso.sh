#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/tos.kernel isodir/boot/tos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "tos" {
	multiboot /boot/tos.kernel
}
EOF
grub-mkrescue -o tos.iso isodir
