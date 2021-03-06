About
=====
TOS is a hobby operating system written in C and assembly (GAS).

*If you're looking for the code I've written, most of it is in kernel/arch/i386 and kernel/kernel*

The currently implemented features are
* Bringing up the CPU (GDT, IDT)
* Setting up the rest of x86 (PIC, PIT)
* Interrupts
* Basic Keyboard support
* (very) Basic kernel mode shell

The next features up are
* Physical memory manger
* Virtual memory manager
* Fancy visual stuff when I get bored

Building
========
A GCC cross compiler for i686-elf is required, as well as QEMU or some other way of running an i686 binary.   
Building can be done with ./build and simuation with ./qemu (if using QEMU).

The complete process can be found in the resources section.

For Manjaro
-----------
If you happen to be building on Manjaro (as I am) this is exactly what you need to do:

* get the newest binutils from here: ftp://ftp.gnu.org/gnu/binutils/
* get the newest gcc from here: ftp://ftp.gnu.org/gnu/gcc/
* exstract them both into HOME/src
* Follow these instruction starting at "The Build" : http://wiki.osdev.org/GCC_Cross-Compiler
* install: qemu, xorriso, mtools

Resources
=========
These are the resources I used for learning and examples
* OSDev.org wiki, specifically the Meaty Skeleton
tutorial was used as the bases for the build system,
file layout and very basic libc requirments
* The OS Development Series from brokenthorn.com for
most of the knowledge, especially on the CPU bring up
* Bran's Kernel Development Tutorial from www.osdever.net
for the interrupt set up and some very repetitive assembly
