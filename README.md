make
====
`make`, or `omake`, is a portable version of the
[OpenBSD](https://www.openbsd.org/)
make program.
It is currently synced with OpenBSD 6.9 -current as of July 22, 2021.

This version of make is suitable for ensuring standard Make compliance, for
older Unix machines that do not have a free Make or have a very old Make, or
for users that do not need the bells and whistles of `bmake` or `GNU Make`.

`make` has no dependencies other than libc. It is known to build and run on all
*BSD flavors, Linux, Mac OS X, Cygwin, AIX, and Solaris. It is very likely to
run on other Unix flavors; please let me know if you are using this on a Unix
not listed here so that I may add it to the list.

Compiling
---------
To build, run:
```
$ ./configure
$ make
# make install
```

Working compilers
-----------------
The following compilers are known to build `make`:
* Clang
* GCC
* PCC
* TinyCC
* CParser
* CompCert
* lacc

It is likely that any C99 compiler will work.

Testing
-------
Tested on Linux and Mac OS X using TravisCI. *BSD, Cygwin, AIX, and Solaris
testing done manually. AIX 5.1L and Solaris 8 are used to help ensure backwards
compatibility.

Licensing
---------
All C files other than `portable.c` are 2- and 3-clause BSD licensed.
`portable.c` has a combination of Public Domain, ISC, and 3-clause BSD
licensed code.
