#ifndef _PM_H_
#define _PM_H_

#include <multiboot.h>
#include <types.h>

//kernel stack size
#define STACK_SIZE    8192
#define PM_MAX_SIZE   0x20000000
#define PAGE_SZIE     0x1000
#define PAGE_MAX_NUM  (PM_MAX_SIZE/PAGE_SZIE)

void show_memory_map(void);
void init_pm(void);
void pm_free_page(uint32_t );
uint32_t pm_alloc_page(void);

#endif
