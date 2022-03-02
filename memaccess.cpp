#include "memaccess.h"
#include <algorithm>
#include <random>

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
        // _mm256_store_epi64(pDest, loaded);
        // _mm_clwb(pDest);
    }
    _mm_sfence();
}

int init_chasing_index(uint64_t* cindex,
                       uint64_t csize,
                       bool is_seq,
                       int access_size) {
    uint64_t curr_pos = 0;
    uint64_t i = 0;
    if (access_size % 64)
        assert(0);

    memset(cindex, 0, sizeof(uint64_t) * csize);

    for (i = 0; i < csize - 1; i++) {
        cindex[i] = i * access_size / 64;
    }

    if (!is_seq) {
        static std::random_device rd;
        static std::mt19937 rng(rd());
        std::shuffle(cindex, cindex + csize, rd);
    }

    return 0;
}