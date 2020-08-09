/*
 * linker.h - Linker script mapping information
 *
 * Machine generated for CPU 'nios2_gen2_0' in SOPC Builder design 'wasca'
 * SOPC Builder design path: ../../wasca.sopcinfo
 *
 * Generated: Thu Apr 04 19:08:23 JST 2019
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __LINKER_H_
#define __LINKER_H_


/*
 * BSP controls alt_load() behavior in crt0.
 *
 */

#define ALT_LOAD_EXPLICITLY_CONTROLLED


/*
 * Base address and span (size in bytes) of each linker region
 *
 */

#define EXTERNAL_SDRAM_CONTROLLER_REGION_BASE 0x4000000
#define EXTERNAL_SDRAM_CONTROLLER_REGION_SPAN 33554432
#define ONCHIP_FLASH_0_DATA_REGION_BASE 0x20
#define ONCHIP_FLASH_0_DATA_REGION_SPAN 235488
#define ONCHIP_MEMORY2_0_BEFORE_EXCEPTION_REGION_BASE 0x100000
#define ONCHIP_MEMORY2_0_BEFORE_EXCEPTION_REGION_SPAN 32
#define ONCHIP_MEMORY2_0_REGION_BASE 0x100020
#define ONCHIP_MEMORY2_0_REGION_SPAN 32736
#define RESET_REGION_BASE 0x0
#define RESET_REGION_SPAN 32


/*
 * Devices associated with code sections
 *
 */

#define ALT_EXCEPTIONS_DEVICE ONCHIP_MEMORY2_0
#define ALT_RESET_DEVICE ONCHIP_FLASH_0_DATA
#define ALT_RODATA_DEVICE ONCHIP_MEMORY2_0
#define ALT_RWDATA_DEVICE ONCHIP_MEMORY2_0
#define ALT_TEXT_DEVICE ONCHIP_MEMORY2_0

#endif /* __LINKER_H_ */
