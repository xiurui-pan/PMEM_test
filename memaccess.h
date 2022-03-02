#include <assert.h>
#include <fcntl.h>
#include <immintrin.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <string>

void bindCore(uint16_t core);
void fastMemcpy(void* pvDest, void* pvSrc, size_t nBytes);

int init_chasing_index(uint64_t* cindex, uint64_t csize, bool is_seq, int access_size);