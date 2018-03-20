/*
 *   MIRACL Comba's method for ultimate speed binary polynomial
 *   mrcomba2.tpl 
 *
 *   Here the inner loops of the basic multiplication, and squaring  
 *   algorithms are completely unravelled, and  reorganised for maximum possible speed. 
 *
 *   This approach is recommended for maximum speed where parameters
 *   are fixed and compute resources are constrained. The processor MUST 
 *   support a special binary polynomial multiplication instruction
 *
 *   This file is a template. To fill in the gaps and create mrcomba2.c, 
 *   you must run the mex.c program to insert the C or assembly language 
 *   macros from the appropriate .mcs file. 
 *
 *   This method would appear to be particularly useful for implementing 
 *   fast Elliptic Curve Cryptosystems over GF(2^m) 
 *
 *   The #define MR_COMBA2 in mirdef.h determines the FIXED size of 
 *   modulus to be used. This *must* be determined at compile time. 
 *
 *   Note that this module can generate a *lot* of code for large values 
 *   of MR_COMBA2. This should have a maximum value of 8-20.
 *
 *   Note that on some processors it is *VITAL* that arrays be aligned on 
 *   4-byte boundaries
 *
 * *  **** This code does not like -fomit-frame-pointer using GCC  ***********
 *
 *   Copyright (c) 2006 Shamus Software Ltd.
 */

#include "miracl.h"    

#ifdef MR_COMBA2

#ifdef MR_WIN64
#if _MSC_VER>=1500
#define MR_PCLMULQDQ
#include <wmmintrin.h>
#endif
#endif

/* NOTE! z must be distinct from x and y */

void comba_mult2(_MIPD_ big x,big y,big z) 
{ /* comba multiplier */
    int i;
    mr_small *a,*b,*c;
    big w;
#ifdef MR_PCLMULQDQ
    __m128i m1,m2,sum;
#endif
#ifdef MR_OS_THREADS
    miracl *mr_mip=get_mip();
#endif
    w=mr_mip->w0; 
    for (i=2*MR_COMBA2;i<(int)(w->len&MR_OBITS);i++) w->w[i]=0;
    w->len=2*MR_COMBA2-1;
    a=x->w; b=y->w; c=w->w;
/*** MULTIPLY2 ***/      /* multiply a by b, result in c */
	
    mr_lzero(w);
    if (w!=z) copy (w,z); 
}   
 
#endif
