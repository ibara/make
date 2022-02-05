/*
MIT License

Copyright (c) 2005-2018 Luc Van Oostenryck

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

****

taken from https://github.com/lucvoo/slibc/blob/master/include/sys/cdefs.h

added additional ifdefs for all definitions, useful when using musl
libc

*/

#ifndef _CDEFS_LOCAL_H
#define _CDEFS_LOCAL_H

#ifndef __GNUC_VERSION
#define __GNUC_VERSION (__GNUC__*100 + __GNUC_MINOR__)
#endif

#ifdef __cplusplus
#ifndef __THROW
#define __THROW throw ()
#endif
#ifndef __BEGIN_DECLS
#define __BEGIN_DECLS extern "C" {
#endif
#ifndef __END_DECLS
#define __END_DECLS }
#endif
#else /* __cplusplus */
#ifndef __THROW
#define __THROW
#endif
#ifndef __BEGIN_DECLS
#define __BEGIN_DECLS
#endif
#ifndef __END_DECLS
#define __END_DECLS
#endif
#endif /* __cplusplus */

#ifndef __CONST
#define __CONST		__attribute__((__const__))
#endif

#ifndef __MALLOC
#define __MALLOC	__attribute__((__malloc__))
#endif

#ifndef __NORETURN
#define __NORETURN	__attribute__((__noreturn__))
#endif

#ifndef __PURE
#define __PURE		__attribute__((__pure__))
#endif

#endif
