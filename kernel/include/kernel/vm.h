#ifndef _VM_H_
#define _VM_H_

#include <types.h>
#include <idt.h>

#define PAGE_OFFSET     0xC0000000

/*
  bit 0 = Present bit
  P = 1 valid
  P = 0 not valid
*/
#define PAGE_PRESENT    0x1

/*
  bit 1 R/W bit
  R/W = 1 read, write, and execute
  R/W = 0 read only or execute
  kernel mode bit1 not in option
*/
#define PAGE_WRITE      0x2

/*
  bit 2  U/S flag
  U/S = 1 user page
  U/S = 0 superuser page
*/
#define PAGE_USER       0x4

#define PAGING_SIZE     4096

/*
  [31:22] -> entry in PGT -> a page table address
*/
#define PGD_INDEX(X)    (((x) >> 22) & 0x3FF)

/*
  [21:12] -> entry in page table -> first 20 bits pm address
*/
#define PTE_INDEX(x)    (((x) >> 12) & 0x3FF)

/*
  [11:0] -> offset
*/
#define OFFSET_INDEX(x) (((x)) 0xFFFF)

typedef uint32_t pgd_t;
typedef uint32_t pte_t;

//num of pgd entries
//each mapping need 4 byte to manage
#define PGD_SIZE (PAGING_SIZE/sizeof(uint32_t))
#define PTE_SIZE (PAGING_SIZE/sizeof(uint32_t))

//512 MB RAM support
#define PTE_COUNT     128

extern pgd_t pgd_kern[PGD_SIZE];

void init_vm(void);
void switch_pgd(uint32_t);

//map pma to vma with flag
void map(pdg_t *, uint32_t, uint32_t, uint32_t);
void unmap(pgt_t *, uint32_t);

uint32_t get_mapping(pgd_t *, uint32_t, uint32_t);

void page_fault(pt_regs *);

#endif
