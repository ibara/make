/*
 * This file is was written by Brian Callahan <bcallah@devio.us>
 * and released into the Public Domain.
 */

#include <stdio.h>
#include "ohash.h"

#ifdef NEED_ASPRINTF
int	asprintf(char **, const char *, ...);
#endif

#ifdef NEED_FGETLN
char   *fgetln(FILE *, size_t *);
#endif

#ifdef NEED_REALLOCARRAY
void   *reallocarray(void *, size_t, size_t);
#endif

#ifdef NEED_STRLCPY
size_t	strlcpy(char *, const char *, size_t);
#endif

#ifdef NEED_STRTONUM
long long strtonum(const char *, long long, long long, const char **);
#endif

#ifdef NEED_PROGNAME
char *__progname;
#endif

#ifndef _NSIG
#define _NSIG 33
#endif

#ifdef NEED_SYS_SIGNAME
extern const char *const sys_signame[];
#endif

#ifndef SIGINFO
#define SIGINFO 29
#endif

/* From OpenBSD sys/time.h */
#ifndef timespeccmp
#define timespeccmp(tsp, usp, cmp)		\
    (((tsp)->tv_sec == (usp)->tv_sec) ?		\
	((tsp)->tv_nsec cmp (usp)->tv_nsec) :	\
	((tsp)->tv_sec cmp (usp)->tv_sec))
#endif
