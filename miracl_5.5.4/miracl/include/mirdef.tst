/*
 *   MIRACL compiler/hardware definitions - mirdef.h
 *   Copyright (c) 1988-2006 Shamus Software Ltd.
 */

#define MR_LITTLE_ENDIAN
#define MIRACL 32
#define mr_utype int
#define MR_IBITS 32
#define MR_LBITS 32
#define mr_unsign32 unsigned int
#define mr_dltype long long
#define mr_unsign64 unsigned long long
#define MR_NOASM
#define MR_FLASH 52
#define MR_ALWAYS_BINARY
#define MAXBASE ((mr_small)1<<(MIRACL-1))
#define MR_BITSINCHAR 8
