
#ifndef RANKBV_H
#define RANKBV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

    /* count the bits in a bunch of junk and time it */

    typedef struct rankbv {
        uint64_t n;
        uint32_t s;
        uint64_t ones;
        uint8_t factor;
        uint64_t S[0];
    } rankbv_t;

    /** bit operations */
#define rankbv_mask63       0x00000000000003F
#define RBVW				64
#define RBVW32              32

    /* misc */
    static inline void
    rankbv_setbit(rankbv_t* rbv,size_t i)
    {
        size_t bs = i/rbv->s;
        size_t block = bs + i/RBVW + 1;
        rbv->S[block] |= (1LL<<(i%RBVW));
    }

    static inline int
    rankbv_getbit(rankbv_t* rbv,size_t i)
    {
        size_t bs = i/rbv->s;
        size_t block = bs + i/RBVW + 1;
        return ((rbv->S[block] >> (i%RBVW)) & 1LL);
    }

    static inline size_t
    rankbv_length(rankbv_t* rbv)
    {
        return rbv->n;
    }
    void*     rankbv_safecalloc(size_t n);
    uint32_t  rankbv_bits(size_t n);
    uint32_t  rankbv_popcount8(const uint32_t x);
    size_t    rankbv_numsblocks(rankbv_t* rbv);
    uint64_t* rankbv_getdata(rankbv_t* rbv);

    /* rankbv functions */
    rankbv_t* rankbv_init(size_t n,uint32_t f);
    rankbv_t* rankbv_create(uint64_t* A,size_t n,uint32_t f);
    void      rankbv_free(rankbv_t* rbv);
    void      rankbv_build(rankbv_t* rbv);
    int       rankbv_access(rankbv_t* rbv,size_t i);
    size_t    rankbv_rank1(rankbv_t* rbv,size_t i);
    size_t    rankbv_select0(rankbv_t* rbv,size_t x);
    size_t    rankbv_select1(rankbv_t* rbv,size_t x);
    size_t    rankbv_ones(rankbv_t* rbv);
    void      rankbv_print(rankbv_t* rbv);


    /* save/load */
    size_t    rankbv_spaceusage(rankbv_t* rbv);
    rankbv_t* rankbv_load(FILE* f);
    size_t    rankbv_save(rankbv_t* rbv,FILE* f);



#ifdef __cplusplus
}
#endif

#endif

