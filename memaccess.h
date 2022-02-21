#define SIZEBTNT_64_AVX512		\
				"vmovntdq  %%zmm0,  0x0(%%r14, %%r15) \n\t" \
				"add $0x40, %%r15 \n\t"

#define SIZEBTNT_128_AVX512		\
				"vmovntdq  %%zmm0,  0x0(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x40(%%r14, %%r15) \n\t" \
				"add $0x80, %%r15 \n\t"

#define SIZEBTNT_256_AVX512		\
				"vmovntdq  %%zmm0,  0x0(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x40(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x80(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0xc0(%%r14, %%r15) \n\t" \
				"add $0x100, %%r15 \n\t"

#define SIZEBTNT_512_AVX512		\
				"vmovntdq  %%zmm0,  0x0(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x40(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x80(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0xc0(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x100(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x140(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x180(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x1c0(%%r14, %%r15) \n\t" \
				"add $0x200, %%r15 \n\t"

#define SIZEBTNT_1024_AVX512	\
				"vmovntdq  %%zmm0,  0x0(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x40(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x80(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0xc0(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x100(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x140(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x180(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x1c0(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x200(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x240(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x280(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x2c0(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x300(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x340(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x380(%%r14, %%r15) \n\t" \
				"vmovntdq  %%zmm0,  0x3c0(%%r14, %%r15) \n\t" \
				"add $0x400, %%r15 \n\t"

#define SIZEBTSTFLUSH_64_AVX512		\
				"vmovdqa64  %%zmm0,  0x0(%%r14, %%r15) \n\t" \
				"clwb  0x0(%%r14, %%r15) \n\t" \
				"add $0x40, %%r15 \n\t"

#define SIZEBTSTFLUSH_128_AVX512		\
				"vmovdqa64  %%zmm0,  0x0(%%r14, %%r15) \n\t" \
				"clwb  0x0(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x40(%%r14, %%r15) \n\t" \
				"clwb  0x40(%%r14, %%r15) \n\t" \
				"add $0x80, %%r15 \n\t"

#define SIZEBTSTFLUSH_256_AVX512		\
				"vmovdqa64  %%zmm0,  0x0(%%r14, %%r15) \n\t" \
				"clwb  0x0(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x40(%%r14, %%r15) \n\t" \
				"clwb  0x40(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x80(%%r14, %%r15) \n\t" \
				"clwb  0x80(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0xc0(%%r14, %%r15) \n\t" \
				"clwb  0xc0(%%r14, %%r15) \n\t" \
				"add $0x100, %%r15 \n\t"

#define SIZEBTSTFLUSH_512_AVX512		\
				"vmovdqa64  %%zmm0,  0x0(%%r14, %%r15) \n\t" \
				"clwb  0x0(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x40(%%r14, %%r15) \n\t" \
				"clwb  0x40(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x80(%%r14, %%r15) \n\t" \
				"clwb  0x80(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0xc0(%%r14, %%r15) \n\t" \
				"clwb  0xc0(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x100(%%r14, %%r15) \n\t" \
				"clwb  0x100(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x140(%%r14, %%r15) \n\t" \
				"clwb  0x140(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x180(%%r14, %%r15) \n\t" \
				"clwb  0x180(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x1c0(%%r14, %%r15) \n\t" \
				"clwb  0x1c0(%%r14, %%r15) \n\t" \
				"add $0x200, %%r15 \n\t"

#define SIZEBTSTFLUSH_1024_AVX512	\
				"vmovdqa64  %%zmm0,  0x0(%%r14, %%r15) \n\t" \
				"clwb  0x0(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x40(%%r14, %%r15) \n\t" \
				"clwb  0x40(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x80(%%r14, %%r15) \n\t" \
				"clwb  0x80(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0xc0(%%r14, %%r15) \n\t" \
				"clwb  0xc0(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x100(%%r14, %%r15) \n\t" \
				"clwb  0x100(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x140(%%r14, %%r15) \n\t" \
				"clwb  0x140(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x180(%%r14, %%r15) \n\t" \
				"clwb  0x180(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x1c0(%%r14, %%r15) \n\t" \
				"clwb  0x1c0(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x200(%%r14, %%r15) \n\t" \
				"clwb  0x200(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x240(%%r14, %%r15) \n\t" \
				"clwb  0x240(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x280(%%r14, %%r15) \n\t" \
				"clwb  0x280(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x2c0(%%r14, %%r15) \n\t" \
				"clwb  0x2c0(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x300(%%r14, %%r15) \n\t" \
				"clwb  0x300(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x340(%%r14, %%r15) \n\t" \
				"clwb  0x340(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x380(%%r14, %%r15) \n\t" \
				"clwb  0x380(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x3c0(%%r14, %%r15) \n\t" \
				"clwb  0x3c0(%%r14, %%r15) \n\t" \
				"add $0x400, %%r15 \n\t"

#define SIZEBTST_64_AVX512		\
				"vmovdqa64  %%zmm0,  0x0(%%r14, %%r15) \n\t" \
				"add $0x40, %%r15 \n\t"

#define SIZEBTST_128_AVX512		\
				"vmovdqa64  %%zmm0,  0x0(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x40(%%r14, %%r15) \n\t" \
				"add $0x80, %%r15 \n\t"

#define SIZEBTST_256_AVX512		\
				"vmovdqa64  %%zmm0,  0x0(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x40(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x80(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0xc0(%%r14, %%r15) \n\t" \
				"add $0x100, %%r15 \n\t"

#define SIZEBTST_512_AVX512		\
				"vmovdqa64  %%zmm0,  0x0(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x40(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x80(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0xc0(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x100(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x140(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x180(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x1c0(%%r14, %%r15) \n\t" \
				"add $0x200, %%r15 \n\t"

#define SIZEBTST_1024_AVX512	\
				"vmovdqa64  %%zmm0,  0x0(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x40(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x80(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0xc0(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x100(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x140(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x180(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x1c0(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x200(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x240(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x280(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x2c0(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x300(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x340(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x380(%%r14, %%r15) \n\t" \
				"vmovdqa64  %%zmm0,  0x3c0(%%r14, %%r15) \n\t" \
				"add $0x400, %%r15 \n\t"

#define SIZEBTLD_64_AVX512	\
				"vmovntdqa 0x0(%%r14, %%r15), %%zmm0 \n\t" \
				"add $0x40, %%r15 \n\t"

#define SIZEBTLD_128_AVX512	\
				"vmovntdqa  0x0(%%r14, %%r15), %%zmm0 \n\t" \
				"vmovntdqa  0x40(%%r14, %%r15), %%zmm1 \n\t" \
				"add $0x80, %%r15 \n\t"

#define SIZEBTLD_256_AVX512	\
				"vmovntdqa  0x0(%%r14, %%r15), %%zmm0 \n\t" \
				"vmovntdqa  0x40(%%r14, %%r15), %%zmm1 \n\t" \
				"vmovntdqa  0x80(%%r14, %%r15), %%zmm2 \n\t" \
				"vmovntdqa  0xc0(%%r14, %%r15), %%zmm3 \n\t" \
				"add $0x100, %%r15 \n\t"

#define SIZEBTLD_512_AVX512	\
				"vmovntdqa  0x0(%%r14, %%r15), %%zmm0 \n\t" \
				"vmovntdqa  0x40(%%r14, %%r15), %%zmm1 \n\t" \
				"vmovntdqa  0x80(%%r14, %%r15), %%zmm2 \n\t" \
				"vmovntdqa  0xc0(%%r14, %%r15), %%zmm3 \n\t" \
				"vmovntdqa  0x100(%%r14, %%r15), %%zmm4 \n\t" \
				"vmovntdqa  0x140(%%r14, %%r15), %%zmm5 \n\t" \
				"vmovntdqa  0x180(%%r14, %%r15), %%zmm6 \n\t" \
				"vmovntdqa  0x1c0(%%r14, %%r15), %%zmm7 \n\t" \
				"add $0x200, %%r15 \n\t"

#define SIZEBTLD_1024_AVX512	\
				"vmovntdqa  0x0(%%r14, %%r15), %%zmm0 \n\t" \
				"vmovntdqa  0x40(%%r14, %%r15), %%zmm1 \n\t" \
				"vmovntdqa  0x80(%%r14, %%r15), %%zmm2 \n\t" \
				"vmovntdqa  0xc0(%%r14, %%r15), %%zmm3 \n\t" \
				"vmovntdqa  0x100(%%r14, %%r15), %%zmm4 \n\t" \
				"vmovntdqa  0x140(%%r14, %%r15), %%zmm5 \n\t" \
				"vmovntdqa  0x180(%%r14, %%r15), %%zmm6 \n\t" \
				"vmovntdqa  0x1c0(%%r14, %%r15), %%zmm7 \n\t" \
				"vmovntdqa  0x200(%%r14, %%r15), %%zmm8 \n\t" \
				"vmovntdqa  0x240(%%r14, %%r15), %%zmm9 \n\t" \
				"vmovntdqa  0x280(%%r14, %%r15), %%zmm10 \n\t" \
				"vmovntdqa  0x2c0(%%r14, %%r15), %%zmm11 \n\t" \
				"vmovntdqa  0x300(%%r14, %%r15), %%zmm12 \n\t" \
				"vmovntdqa  0x340(%%r14, %%r15), %%zmm13 \n\t" \
				"vmovntdqa  0x380(%%r14, %%r15), %%zmm14 \n\t" \
				"vmovntdqa  0x3c0(%%r14, %%r15), %%zmm15 \n\t" \
				"add $0x400, %%r15 \n\t"

#define SIZEBT_NT_64	"movnti %[random], 0x0(%%r14, %%r15) \n\t" \
			"movnti %[random], 0x8(%%r14, %%r15) \n\t" \
			"movnti %[random], 0x10(%%r14, %%r15) \n\t" \
			"movnti %[random], 0x18(%%r14, %%r15) \n\t" \
			"movnti %[random], 0x20(%%r14, %%r15) \n\t" \
			"movnti %[random], 0x28(%%r14, %%r15) \n\t" \
			"movnti %[random], 0x30(%%r14, %%r15) \n\t" \
			"movnti %[random], 0x38(%%r14, %%r15) \n\t" \
			"add $0x40, %%r15 \n\t"

#define SIZEBT_LOAD_64	"mov 0x0(%%r14, %%r15),  %%r13  \n\t" \
			"mov 0x8(%%r14, %%r15),  %%r13  \n\t" \
			"mov 0x10(%%r14, %%r15), %%r13  \n\t" \
			"mov 0x18(%%r14, %%r15), %%r13  \n\t" \
			"mov 0x20(%%r14, %%r15), %%r13  \n\t" \
			"mov 0x28(%%r14, %%r15), %%r13  \n\t" \
			"mov 0x30(%%r14, %%r15), %%r13  \n\t" \
			"mov 0x38(%%r14, %%r15), %%r13  \n\t" 
