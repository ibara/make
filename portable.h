/*
 * This file is was written by Brian Callahan <bcallah@devio.us>
 * and released into the Public Domain.
 */

#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include "ohash.h"

#ifdef NEED_ASPRINTF
int     asprintf(char **, const char *, ...);
#endif

#ifdef NEED_FGETLN
char   *fgetln(FILE *, size_t *);
#endif

#ifdef NEED_REALLOCARRAY
void   *reallocarray(void *, size_t, size_t);
#endif

#ifdef NEED_STRLCPY
size_t  strlcpy(char *, const char *, size_t);
#endif

#ifdef NEED_STRTONUM
long long strtonum(const char *, long long, long long, const char **);
#endif

#ifdef NEED_OPTRESET
static int optreset;
#endif

#ifdef NEED_PLEDGE
#define pledge(foo, bar) (0)
#endif

#ifdef NEED_PROGNAME
char *__progname;
#endif

#ifndef __only_inline
#define __only_inline
#endif

#ifndef _NSIG
#define _NSIG 65
#endif

#ifdef NEED_SYS_SIGNAME
extern const char *const sys_signame[65];
#endif

#ifndef SIGINFO
#define SIGINFO 29
#endif

#ifdef NEED_ARC4RANDOM_UNIFORM
uint32_t arc4random_uniform(uint32_t);
#endif /* NEED_ARC4RANDOM_UNIFORM */

/* From OpenBSD sys/time.h */
#ifndef timespeccmp
#define timespeccmp(tsp, usp, cmp)              \
    (((tsp)->tv_sec == (usp)->tv_sec) ?         \
        ((tsp)->tv_nsec cmp (usp)->tv_nsec) :   \
        ((tsp)->tv_sec cmp (usp)->tv_sec))
#endif
