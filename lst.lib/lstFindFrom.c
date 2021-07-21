/*	$OpenBSD: lstFindFrom.c,v 1.19 2015/10/14 13:50:22 espie Exp $	*/
/*	$NetBSD: lstFindFrom.c,v 1.6 1996/11/06 17:59:40 christos Exp $ */

/*
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
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

/*-
 * LstFindFrom.c --
 *	Find a node on a list from a given starting point. Used by Lst_Find.
 */

#include	"lstInt.h"
#include	<stddef.h>

/*-
 *-----------------------------------------------------------------------
 * Lst_FindFrom --
 *	Search for a node starting and ending with the given one on the
 *	given list using the passed datum and comparison function to
 *	determine when it has been found.
 *
 * Results:
 *	The found node or NULL
 *-----------------------------------------------------------------------
 */
LstNode
Lst_FindFrom(LstNode ln, FindProc cProc, void *d)
{
	LstNode tln;

	for (tln = ln; tln != NULL; tln = tln->nextPtr)
		if (!(*cProc)(tln->datum, d))
			return tln;

	return NULL;
}

