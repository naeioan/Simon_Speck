
#ifndef SIMON
#define SIMON

/*
 SIMON_WORD_SIZE n = word size (16, 24, 32, 48, or 64)
 */ 
 
#define SIMON_WORD_SIZE (64)

/*
SIMON_KEY_WORDS m = number of key words (must be 4 if n = 16,
                                          3 or 4 if n = 24 or 32,
                                          2 or 3 if n = 48,
                                          2, 3, or 4 if n = 64)
*/
#define SIMON_KEY_WORDS (2)

#define SIMON_BLOCK_SIZE (SIMON_WORD_SIZE*2) 

#define SIMON_KEY_SIZE (SIMON_WORD_SIZE*SIMON_KEY_WORDS)

#define SIMON_CONST_C (0xfffffffc) // ??


/*
T = SIMON_ROUNDS,
j = SIMON_SEQUENCE_NUMBER

(T, j) = (32,0) if n = 16
       = (36,0) or (36,1) if n = 24, m = 3 or 4
       = (42,2) or (44,3) if n = 32, m = 3 or 4
       = (52,2) or (54,3) if n = 48, m = 2 or 3
       = (68,2), (69,3), or (72,4) if n = 64, m = 2, 3, or 4

*/

/* please reffer to Table 3.1: SIMON parameters, 
 * page 10 from "The Simon and Speck Families of Lightweight Block Ciphers"  
 */

#define SIMON_ROUNDS (68)
#define SIMON_SEQUENCE_NUMBER (2)


#endif

