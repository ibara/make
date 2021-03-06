[![Build Status](https://travis-ci.org/ibara/make.svg?branch=master)](https://travis-ci.org/ibara/make)
make
====
`make`, or `omake`, is a portable version of the OpenBSD Make program.

It is suitable for ensuring standard Make compliance, for older Unix machines
that do not have a free Make or have a very old Make, or for users that do not
need the bells and whistles of `bmake` or `GNU Make`.

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

Get a tarball
-------------
https://devio.us/~bcallah/make/make-20170124.tar.gz
