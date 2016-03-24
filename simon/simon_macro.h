#ifndef PRIMITIVES
#define PRIMITIVES

#include "constants.h"

/*
 * rotate shift left x by n bits
 */
#define rol(x, n) ( ((x)<<(n)) | ((x)>>(SIMON_WORD_SIZE-(n))) )

/*
 * rotate shift right x by n bits
 */
#define ror(x, n) ( ((x)>>(n)) | ((x)<<(SIMON_WORD_SIZE-(n))) )

/*
 * function f
 * f(x) = (Sx & S8x) ⊕ S2x
 */
#define f(x) ((rol(x, 1)&rol(x, 8)) ^ rol(x, 2))


/*
 * Round function for encryption
 * be sure to save x to a temp variable
 */

#define roundFunction(x, y, k) \
  x = (y) ^ f(x) ^ (k) ; \
  y = (x)

/*
 * Invert round function for decyption
 */
#define invertRoundFunction(x, y, k) \
  x = y ; \
  y = (x) ^ f(y) ^ k 

#endif
