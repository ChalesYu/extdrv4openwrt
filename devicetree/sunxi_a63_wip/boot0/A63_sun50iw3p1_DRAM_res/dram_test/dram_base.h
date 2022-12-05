
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
#define LOBYTE(w)           ((BYTE)((DWORD)(w) & 0xff))
#define HIBYTE(w)           ((BYTE)((DWORD)(w) >> 8))

//Find and replace
//#define (u_nsigned __int16) (WORD)
//#define (u_nsigned __int8) (BYTE)

#include "dram_para.h"

#include "func.h"
