
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

#define DBG
//#define printf debug
#define mctl_read_w readl
#define mctl_write_w writel
#define _usdelay udelay


#define WORD uint16_t
#define DWORD uint32_t
#define _DWORD uint32_t
#define BYTE uint8_t
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

//Find and replace
//#define (u_nsigned __int16) (WORD)
//#define (u_nsigned __int8) (BYTE)

#include "dram_para.h"

#include "func.h"
