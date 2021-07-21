/*
 * Portability goo.
 * Please see each function for licensing details.
 */

#include <stdint.h>
#include "defines.h"
#include "lst.h"
#include "portable.h"


/*
 * This minimal asprintf routine written by Brian Callahan <bcallah@devio.us>
 * and released into the Public Domain.
 */

#ifdef NEED_ASPRINTF

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int
asprintf(char **ret, const char *format, ...)
{
        int retval;
        va_list ap;

        va_start(ap, format);

        if ((*ret = malloc(32)) == NULL) {
                retval = -1;
                goto out;
        }

        retval = vsnprintf(*ret, 32, format, ap);

out:
        va_end(ap);

        return retval;
}

#endif /* NEED_ASPRINTF */

#ifdef NEED_REALLOCARRAY

/*	$OpenBSD: reallocarray.c,v 1.3 2015/09/13 08:31:47 guenther Exp $	*/
/*
 * Copyright (c) 2008 Otto Moerbeek <otto@drijf.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/types.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

/*
 * This is sqrt(SIZE_MAX+1), as s1*s2 <= SIZE_MAX
 * if both s1 < MUL_NO_OVERFLOW and s2 < MUL_NO_OVERFLOW
 */
#define MUL_NO_OVERFLOW	((size_t)1 << (sizeof(size_t) * 4))

void *
reallocarray(void *optr, size_t nmemb, size_t size)
{
	if ((nmemb >= MUL_NO_OVERFLOW || size >= MUL_NO_OVERFLOW) &&
	    nmemb > 0 && SIZE_MAX / nmemb < size) {
		errno = ENOMEM;
		return NULL;
	}
	return realloc(optr, size * nmemb);
}

#endif /* NEED_REALLOCARRAY */
#ifdef NEED_STRLCPY
/*	$OpenBSD: strlcpy.c,v 1.16 2019/01/25 00:19:25 millert Exp $	*/

/*
 * Copyright (c) 1998, 2015 Todd C. Miller <millert@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/types.h>
#include <string.h>

/*
 * Copy string src to buffer dst of size dsize.  At most dsize-1
 * chars will be copied.  Always NUL terminates (unless dsize == 0).
 * Returns strlen(src); if retval >= dsize, truncation occurred.
 */
size_t
strlcpy(char *dst, const char *src, size_t dsize)
{
	const char *osrc = src;
	size_t nleft = dsize;

	/* Copy as many bytes as will fit. */
	if (nleft != 0) {
		while (--nleft != 0) {
			if ((*dst++ = *src++) == '\0')
				break;
		}
	}

	/* Not enough room in dst, add NUL and traverse rest of src. */
	if (nleft == 0) {
		if (dsize != 0)
			*dst = '\0';		/* NUL-terminate dst */
		while (*src++)
			;
	}

	return(src - osrc - 1);	/* count does not include NUL */
}

#endif /* NEED_STRLCPY */
#ifdef NEED_STRTONUM
/*	$OpenBSD: strtonum.c,v 1.8 2015/09/13 08:31:48 guenther Exp $	*/

/*
 * Copyright (c) 2004 Ted Unangst and Todd Miller
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <errno.h>
#include <limits.h>
#include <stdlib.h>

#define	INVALID		1
#define	TOOSMALL	2
#define	TOOLARGE	3

long long
strtonum(const char *numstr, long long minval, long long maxval,
    const char **errstrp)
{
	long long ll = 0;
	int error = 0;
	char *ep;
	struct errval {
		const char *errstr;
		int err;
	} ev[4] = {
		{ NULL,		0 },
		{ "invalid",	EINVAL },
		{ "too small",	ERANGE },
		{ "too large",	ERANGE },
	};

	ev[0].err = errno;
	errno = 0;
	if (minval > maxval) {
		error = INVALID;
	} else {
		ll = strtoll(numstr, &ep, 10);
		if (numstr == ep || *ep != '\0')
			error = INVALID;
		else if ((ll == LLONG_MIN && errno == ERANGE) || ll < minval)
			error = TOOSMALL;
		else if ((ll == LLONG_MAX && errno == ERANGE) || ll > maxval)
			error = TOOLARGE;
	}
	if (errstrp != NULL)
		*errstrp = ev[error].errstr;
	errno = ev[error].err;
	if (error)
		ll = 0;

	return (ll);
}

#endif /* NEED_STRTONUM */
#ifdef NEED_SYS_SIGNAME
/*	$OpenBSD: signame.c,v 1.7 2015/09/19 04:02:21 guenther Exp $ */
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <signal.h>
#include <unistd.h>

const char *const sys_signame[NSIG] = {
	"Signal 0",
	"HUP",		/* SIGHUP */
	"INT",		/* SIGINT */
	"QUIT",		/* SIGQUIT */
	"ILL",		/* SIGILL */
	"TRAP",		/* SIGTRAP */
	"ABRT",		/* SIGABRT */
	"EMT",		/* SIGEMT */
	"FPE",		/* SIGFPE */
	"KILL",		/* SIGKILL */
	"BUS",		/* SIGBUS */
	"SEGV",		/* SIGSEGV */
	"SYS",		/* SIGSYS */
	"PIPE",		/* SIGPIPE */
	"ALRM",		/* SIGALRM */
	"TERM",		/* SIGTERM */
	"URG",		/* SIGURG */
	"STOP",		/* SIGSTOP */
	"TSTP",		/* SIGTSTP */
	"CONT",		/* SIGCONT */
	"CHLD",		/* SIGCHLD */
	"TTIN",		/* SIGTTIN */
	"TTOU",		/* SIGTTOU */
	"IO",		/* SIGIO */
	"XCPU",		/* SIGXCPU */
	"XFSZ",		/* SIGXFSZ */
	"VTALRM",	/* SIGVTALRM */
	"PROF",		/* SIGPROF */
	"WINCH",	/* SIGWINCH */
	"INFO",		/* SIGINFO */
	"USR1",		/* SIGUSR1 */
	"USR2",		/* SIGUSR2 */
	"THR",		/* SIGTHR */
};
#if 0

#endif
#endif /* NEED_SYS_SIGNAME */
#ifdef NEED_FGETLN 
/*
 * Copyright (c) 2015 Joerg Jung <jung@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * portable fgetln() version, NOT reentrant
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "compat.h"


char *
fgetln(FILE *fp, size_t *len)
{
    static char *buf = NULL;
    static size_t bufsz = 0;
    size_t r = 0;
    char *p;
    int c, e;

    if (!fp || !len) {
        errno = EINVAL;
        return NULL;
    }
    if (!buf) {
        if (!(buf = calloc(1, BUFSIZ)))
            return NULL;
        bufsz = BUFSIZ;
    }
    while ((c = getc(fp)) != EOF) {
        buf[r++] = c;
        if (r == bufsz) {
            if (!(p = reallocarray(buf, 2, bufsz))) {
                e = errno;
                free(buf);
                errno = e;
                buf = NULL, bufsz = 0;
                return NULL;
            }
            buf = p, bufsz = 2 * bufsz;
        }
        if (c == '\n')
            break;
    }
    return (*len = r) ? buf : NULL;
}
#endif /* NEED_FGETLN */
#ifdef NEED_ARC4RANDOM_UNIFORM
#endif /* NEED_ARC4RANDOM_UNIFORM */
