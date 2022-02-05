/* public domain */

#ifndef _ARC4RANDOM_LOCAL_H
#define _ARC4RANDOM_LOCAL_H

#ifdef __linux__
void arc4random_stir(void);
void arc4random_addrandom(unsigned char *dat, int datlen);
uint32_t arc4random(void);
void arc4random_buf(void *buf, size_t n);
uint32_t arc4random_uniform(uint32_t upper_bound);
#endif

#endif
