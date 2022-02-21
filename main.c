#include<sys/stat.h>
#include<sys/mman.h>
#include<fcntl.h> 
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#include<immintrin.h>
#include<time.h>
#include<pthread.h>
#include"memaccess.h"

#define PAGE_SIZE 4096
#define BUFFER_SIZE 64
#define FILE_SIZE 0x800000000 // 64GB   
#define THREAD_NUM 1

struct thread_data{
    __uint64_t* mem;
    int thread_id;
    double iops;
};

void* WriteMem(void* thread_arg){

    struct thread_data* arg = (struct thread_data*)thread_arg;
    __uint64_t* mem = arg->mem;
    printf("thread %d, memaddr=%p\n", arg->thread_id, mem);
    
    __m512 va;
    float af[16] __attribute__ ((aligned (64)));
    clock_t start_time, end_time;  

    int i = 0;
    for(i = 0; i < 16; i++)
        af[i] = (float)i;
    va = _mm512_load_ps(af);

    double overall_time = 0;
    i = 0;

    // set registers for writing memory
    // %r15 for array address offset, %r14 for base address
    __asm__("xor %%r15, %%r15\n\t"
            "mov %0, %%r14\n\t"
            :
            :"r"(mem)
            :"%r15", "%r14"
    );
    
    //warm up for creating page table
    while(i < 100000){
        __asm__ volatile(
            SIZEBTSTFLUSH_64_AVX512
            "sfence\n\t"
            :::"%r14", "%r15", "memory"
        );
        i = i + 1;
    } 

    // start testing
    start_time = clock();
    while(i < 10000000){
        __asm__ volatile(
            SIZEBTSTFLUSH_512_AVX512
            "sfence\n\t"
            :::"%r14", "%r15", "memory"
        );
        i = i + 1;
    }
    end_time = clock();
    overall_time = (double)(end_time-start_time)/CLOCKS_PER_SEC;
    arg->iops = (double)i/overall_time;

    printf("thread %d: IOPS = %fK, time = %lfs\n", arg->thread_id, arg->iops/1000, overall_time);
    pthread_exit(NULL);

}

int main(){
    int fd = 0;
    __uint64_t* p_map;
    pthread_t threads[THREAD_NUM];
    struct thread_data td[THREAD_NUM];

    // open the test file
    fd = open("/mnt/pm0/test", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR, 0666);
    printf("fd = %d\n", fd);
    ftruncate(fd, FILE_SIZE);

    // mmap the file
    p_map = (__uint64_t*)mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(p_map == MAP_FAILED){
        printf("mmap failed.\n");
        munmap(p_map, FILE_SIZE);
        assert(0);
    } 
    printf("mmap succeeded, at %p.\n", p_map);

    // create multiple threads to do the PM I/O test
    // manually modify THREAD_NUM and IO granularity and record, haven't written any automatic script yet
    int i = 1;
    double sum_iops = 0;
    for(i = 0; i < THREAD_NUM; i++){
        printf("main(): creating thread %d\n", i);
        td[i].thread_id = i;
        td[i].mem = p_map + FILE_SIZE/THREAD_NUM/8*i; 
        td[i].iops = 0;
        int ret = pthread_create(&threads[i], NULL, WriteMem, (void*)&(td[i]));
        if(ret != 0){
            printf("pthread_create error: error_code = %d\n", ret);
            assert(0);
        }
    }

    // block the main func, calculate sum IOPS
    int ret = 0;
    for(i = 0; i < THREAD_NUM; i++){
        ret = pthread_join(threads[i], NULL);
        if(ret != 0) {
            printf("pthread_join error\n");
            assert(0);
        }
        sum_iops += td[i].iops;
    }
    printf("Sum IOPS = %dK\n", (int)(sum_iops/1000));

    munmap(p_map, FILE_SIZE);

    return 0;
}
