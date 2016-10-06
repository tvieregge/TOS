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
A GCC cross compiler for i686-elf is required, and QEMU or some other way of running it.
Then just run ./build to build and ./qemu if you have it installed to boot. The complete
process can be found in the resources section.

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
