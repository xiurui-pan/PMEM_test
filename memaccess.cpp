#include "memaccess.h"

void bindCore(uint16_t core) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core, &cpuset);
    int rc = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
    if (rc != 0) {
        printf("can't bind core %d!", core);
        exit(-1);
    }
}

void fastMemcpy(void* pvDest, void* pvSrc, size_t nBytes) {
    assert(nBytes % 32 == 0);
    assert((intptr_t(pvDest) & 31) == 0);
    assert((intptr_t(pvSrc) & 31) == 0);
    const __m256i* pSrc = reinterpret_cast<const __m256i*>(pvSrc);
    __m256i* pDest = reinterpret_cast<__m256i*>(pvDest);
    int64_t nVects = nBytes / sizeof(*pSrc);
    for (; nVects > 0; nVects--, pSrc++, pDest++) {
        const __m256i loaded = _mm256_stream_load_si256(pSrc);
        _mm256_stream_si256(pDest, loaded);
    }
    _mm_sfence();
}

static inline int get_rand(uint64_t* rd, uint64_t range){
    uint8_t ok;
    int i = 0;
    for (i = 0; i < RDRAND_MAX_RETRY; i++) {
        asm volatile("rdrand %0; setc %1\n\t" : "=r"(*rd), "=qm"(ok));

        if (ok) {
            *rd = *rd % range;
            return 0;
        }
    }

    return 1;
}

int init_chasing_index(uint64_t* cindex, uint64_t csize, bool is_seq, int access_size){
    uint64_t curr_pos = 0;
    uint64_t i = 0;
    int ret = 0;
    if(access_size % 64)
        assert(0);

    memset(cindex, 0, sizeof(uint64_t) * csize);

    for (i = 0; i < csize - 1; i++) {
        if(!is_seq){
            ret = get_rand(&curr_pos, csize);
        }
        else {
            curr_pos = i;
        }
        cindex[i] = curr_pos * access_size / 64;
        if (ret != 0)
            return 1;
    }

    return 0;
}