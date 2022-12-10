#include <stdio.h>
#include <stdbool.h>

/*

#include <common.h>
#include <init.h>
#include <log.h>
#include <asm/io.h>
#include <asm/arch/clock.h>
#include <asm/arch/dram.h>
#include <asm/arch/cpu.h>
#include <asm/arch/prcm.h>
#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/kconfig.h>

*/


#define DBG
//#define printf debug
#define mctl_read_w readl
#define mctl_write_w writel
#define _usdelay udelay

// Drop this
// ONLY FOR CHECK PASS COMPILE !!!
////////////////
#if 1
#define uint8_t int
#define int16_t int
#define uint16_t int
#define uint32_t int
#define uint64_t long int
#endif
////////////////


#define __int16 int16_t
#define WORD uint16_t
#define _WORD uint16_t
#define DWORD uint32_t
#define _DWORD uint32_t
#define _QWORD uint64_t
#define BYTE uint8_t
#define _BYTE uint8_t
#define LOWORD(l)           ((WORD)((DWORD)(l) & 0xffff))
#define HIWORD(l)           ((WORD)((DWORD)(l) >> 16))

//#define LOBYTE(w)           ((BYTE)(((DWORD)(w)) & 0xff))
//#define HIBYTE(w)           ((BYTE)((((DWORD)(w)) >> 8) & 0xff))

// data 0x12345678  32-bit
#define BYTE0(w)		((BYTE)(((DWORD)(w)) & 0xff))		// byte 0  0x78
#define BYTE1(w)		((BYTE)((((DWORD)(w)) >> 8) & 0xff))	// byte 1  0x56
#define BYTE2(w)		((BYTE)((((DWORD)(w)) >> 16) & 0xff))	// byte 2  0x34
#define BYTE3(w)		((BYTE)((((DWORD)(w)) >> 24) & 0xff))	// byte 3  0x12

#define LOBYTE(w)  BYTE0(w)
#define HIBYTE(w)  BYTE3(w)

//#define readb(c)	({ u8  __v = __arch_getb(c); __iormb(); __v; }) // BYTE 0xff
//#define readw(c)	({ u16 __v = __arch_getw(c); __iormb(); __v; }) // WORD 0xffff
//#define readl(c)	({ u32 __v = __arch_getl(c); __iormb(); __v; }) // DWORD 0xffff ffff
//#define readq(c)	({ u64 __v = __arch_getq(c); __iormb(); __v; }) // QWORD 0xffff ffff ffff ffff

//Find and replace
//#define (u_nsigned __int16) (uint16_t)
//#define (u_nsigned __int8) (uint8_t)

static int write_level_flag ;

#include "dram_para.h"

#include "func.h"
