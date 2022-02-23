#include "memaccess.h"

#define PAGE_SIZE 4096
#define BUFFER_SIZE 64
#define FILE_SIZE 0x2000000000  // 256GB
#define THREAD_NUM thread_num
#define MAX_THREAD_NUM 32
#define TEST_SIZE 8000000

struct thread_data {
    __uint64_t* mem;
    int thread_id;
    double iops;
} __attribute__((aligned(64)));

inline double time_diff_ms(timespec time1, timespec time2) {
    return (time2.tv_sec - time1.tv_sec) * 1000 +
           (double)(time2.tv_nsec - time1.tv_nsec) / 1000000;
}

static int thread_num = 1;
static int access_size = 64;
static bool is_seq = 1;

void* WriteMem(void* thread_arg){
    struct thread_data* arg = (struct thread_data*)thread_arg;
    __uint64_t* mem = arg->mem;
    printf("thread %d, memaddr=%p\n", arg->thread_id, mem);
    bindCore(arg->thread_id);

    __m512 va;
    float af[16] __attribute__((aligned(64)));
    timespec start_time, end_time;

    uint64_t i = 0;
    for (i = 0; i < 16; i++)
        af[i] = (float)i;
    va = _mm512_load_ps(af);

    double overall_time = 0;
    i = 0;
    // set registers for writing memory
    // %r15 for array address offset, %r14 for base address
    __asm__(
        "xor %%r15, %%r15\n\t"
        "mov %0, %%r14\n\t"
        :: "r"(mem) : "%r15", "%r14");
    while (i < 100000) {
        __asm__ volatile(SIZEBTNT_64_AVX512 "sfence\n\t" ::
                             : "%r14", "%r15", "memory");
        i++;
    }

    // create an array for random or sequential offsets
    uint64_t csize = TEST_SIZE;
    uint64_t* cindex = (uint64_t*)malloc(sizeof(uint64_t) * csize);
    init_chasing_index(cindex, csize, is_seq, access_size);

    i = 0;
    __asm__(
        "xor %%r15, %%r15\n\t"
        "mov %0, %%r14\n\t"
        :: "r"(mem) : "%r15", "%r14");

    // start testing
    clock_gettime(CLOCK_REALTIME, &start_time);
    while(i < TEST_SIZE){
        __asm__ volatile(
            SIZEBTNT_256_AVX512
            "movq (%0, %1, 8), %%r15\n\t"
            "sfence\n\t"
            :
            :"r"(cindex), "r"(i)
            :"%r15", "%r14", "memory"
        );
        i++;
    }
    clock_gettime(CLOCK_REALTIME, &end_time);
    overall_time = time_diff_ms(start_time, end_time) / 1000;
    arg->iops = (double)i / overall_time;

    printf("thread %d: IOPS = %fK, time = %lfs\n", arg->thread_id,
           arg->iops / 1000, overall_time);
    pthread_exit(NULL);

}

int main(int argc, char* argv[]) {
    // argv[1] is thread num, 
    // argv[2] is access size/B, 
    // argv[3] is "seq" for sequential or others for random write;
    thread_num = std::stoi(argv[1], nullptr, 10);
    access_size = std::stoi(argv[2], nullptr, 10);
    is_seq = 1 ? strcmp(argv[3], "seq\n") : 0;
    printf("Test with %d threads, %dB granularity, %sly\n", thread_num, access_size, is_seq? "sequential": "random");

    int fd = 0;
    __uint64_t* p_map;
    pthread_t threads[MAX_THREAD_NUM];
    struct thread_data td[MAX_THREAD_NUM];

    // open the test file
    fd = open("/mnt/pm0/test", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR,
              0666);
    printf("fd = %d\n", fd);
    ftruncate(fd, 0);
    ftruncate(fd, FILE_SIZE);

    // mmap the file
    p_map = (__uint64_t*)mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE,
                              MAP_SHARED, fd, 0);
    if (p_map == MAP_FAILED) {
        printf("mmap failed.\n");
        munmap(p_map, FILE_SIZE);
        assert(0);
    }
    printf("mmap succeeded, at %p.\n", p_map);

    // create multiple threads to do the PM I/O test
    // manually modify THREAD_NUM and IO granularity and record, haven't written
    // any automatic script yet
    int i = 1;
    double sum_iops = 0;
    for (i = 0; i < THREAD_NUM; i++) {
        printf("main(): creating thread %d\n", i);
        td[i].thread_id = i;
        td[i].mem = p_map + FILE_SIZE / THREAD_NUM / 8 * i;
        td[i].iops = 0;
        int ret = pthread_create(&threads[i], NULL, WriteMem, (void*)&(td[i]));
        if (ret != 0) {
            printf("pthread_create error: error_code = %d\n", ret);
            assert(0);
        }
    }

    // block the main func, calculate sum IOPS
    int ret = 0;
    for (i = 0; i < THREAD_NUM; i++) {
        ret = pthread_join(threads[i], NULL);
        if (ret != 0) {
            printf("pthread_join error\n");
            assert(0);
        }
        sum_iops += td[i].iops;
    }
    printf("Sum IOPS = %dK\n", (int)(sum_iops / 1000));

    munmap(p_map, FILE_SIZE);

    return 0;
}
