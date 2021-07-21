/*	$OpenBSD: generate.c,v 1.18 2016/10/14 09:27:21 natano Exp $ */

/*
 * Copyright (c) 2001 Marc Espie.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE OPENBSD PROJECT AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OPENBSD
 * PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <portable.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ohash.h>

#include "stats.h"
#include "cond_int.h"
#include "var_int.h"
#include "node_int.h"

#define M(x)	x, #x
char *table_var[] = {
	M(TARGET),
	M(OODATE),
	M(ALLSRC),
	M(IMPSRC),
	M(PREFIX),
	M(ARCHIVE),
	M(MEMBER),
	M(LONGTARGET),
	M(LONGOODATE),
	M(LONGALLSRC),
	M(LONGIMPSRC),
	M(LONGPREFIX),
	M(LONGARCHIVE),
	M(LONGMEMBER),
	M(FTARGET),
	M(DTARGET),
	M(FPREFIX),
	M(DPREFIX),
	M(FARCHIVE),
	M(DARCHIVE),
	M(FMEMBER),
	M(DMEMBER),
	M(FIMPSRC),
	M(DIMPSRC),
	NULL
};

char *table_cond[] = {
	M(COND_IF),
	M(COND_IFDEF),
	M(COND_IFNDEF),
	M(COND_IFMAKE),
	M(COND_IFNMAKE),
	M(COND_ELSE),
	M(COND_ELIF),
	M(COND_ELIFDEF),
	M(COND_ELIFNDEF),
	M(COND_ELIFMAKE),
	M(COND_ELIFNMAKE),
	M(COND_ENDIF),
	M(COND_FOR),
	M(COND_ENDFOR),
	M(COND_INCLUDE),
	M(COND_UNDEF),
	M(COND_POISON),
	NULL
};

char *table_nodes[] = {
	M(NODE_DEFAULT),
	M(NODE_EXEC),
	M(NODE_IGNORE),
	M(NODE_INCLUDES),
	M(NODE_INVISIBLE),
	M(NODE_JOIN),
	M(NODE_LIBS),
	M(NODE_MADE),
	M(NODE_MAIN),
	M(NODE_MAKE),
	M(NODE_MAKEFLAGS),
	M(NODE_MFLAGS),
	M(NODE_NOTMAIN),
	M(NODE_NOTPARALLEL),
	M(NODE_NO_PARALLEL),
	M(NODE_NULL),
	M(NODE_OPTIONAL),
	M(NODE_ORDER),
	M(NODE_PARALLEL),
	M(NODE_PATH),
	M(NODE_PHONY),
	M(NODE_PRECIOUS),
	M(NODE_RECURSIVE),
	M(NODE_SILENT),
	M(NODE_SINGLESHELL),
	M(NODE_SUFFIXES),
	M(NODE_USE),
	M(NODE_WAIT),
	M(NODE_BEGIN),
	M(NODE_END),
	M(NODE_INTERRUPT),
	M(NODE_CHEAP),
	M(NODE_EXPENSIVE),
	M(NODE_POSIX),
	M(NODE_SCCS_GET),
	NULL
};


char **table[] = {
	table_var,
	table_cond,
	table_nodes
};

int
main(int argc, char *argv[])
{
	uint32_t i;
	uint32_t v;
	uint32_t h;
	uint32_t slots;
	const char *errstr;
	const char *e;
	char **occupied;
	char **t;
	int tn;

	Init_Stats();
	if (argc != 3)
		exit(1);

	tn = strtonum(argv[1], 1, INT_MAX, &errstr);
	if (errstr)
		exit(1);
	t = table[tn-1];
	slots = strtonum(argv[2], 0, INT_MAX, &errstr);
	if (errstr)
		exit(1);
	if (slots) {
		occupied = calloc(slots, sizeof(char *));
		if (!occupied)
			exit(1);
	} else
		occupied = NULL;

	printf("/* File created by generate %d %d, do not edit */\n",
	    tn, slots);
	for (i = 0; t[i] != NULL; i++) {
		e = NULL;
		v = ohash_interval(t[i], &e);
		if (slots) {
			h = v % slots;
			if (occupied[h]) {
				fprintf(stderr,
				    "Collision: %s / %s (%d)\n", occupied[h],
				    t[i], h);
				exit(1);
			}
			occupied[h] = t[i];
		}
		i++;
		printf("#define K_%s %u\n", t[i], v);
	}
	if (slots)
		printf("#define MAGICSLOTS%d %u\n", tn, slots);
	exit(0);
}
