// File Gurad
#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef signed char s8;   /* 1byte=8bit  */
typedef unsigned char u8; /* 1byte=8bit  */

typedef signed short int s16;   /* 2bytes=16bit */
typedef unsigned short int u16; /* 2bytes=16bit */

typedef signed long int s32;   /* 4bytes=32bit */
typedef unsigned long int u32; /* 4bytes=32bit */  // uint23_t

typedef signed long long int s64;   /* 8bytes=64bit */
typedef unsigned long long int u64; /* 8bytes=64bit */

typedef float f32;  /* 4bytes=32bit */
typedef double f64; /* 8bytes=64bit */

typedef long double f128; /* 16bytes=128bit */

#define NULL_PTR ((void*)0)

#define STD_TYPES_NOK 0
#define STD_TYPES_OK 1

#endif /* STD_TYPES_H_ */