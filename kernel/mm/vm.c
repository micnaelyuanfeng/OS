#include <vm.h>
#include <debug.h>
#include <pm.h>
#include <string.h>

pgt_t pgd_kern[PGD_SIZE] __attribute__((aligned(PAGING_SIZE)));

static pte_t pte_kern[PTE_COUNT][PTE_SIZE] __attribute__((aligned(PAGING_SIZE)));

void init_vm(){
  //first address staring @ 0xC0000000
  uint32_t kern_pte_start = PGD_INDEX(PAGE_OFFSET);

  int i;

  for(i = kern_pte_start, j = 0; i < PTE_COUNT + kern_pte_start; i++, j++){
      pgd_kern[i] = (pte_kern[j] - PAGE_OFFSET) | PAGE_WRITE | PAGE_PRESENT;
  }

  //register is 32 bits width -> pointer has to be 32 bits long
  uint32_t *pte = (uint32_t *)pte_kern
  for(i = 1; i < PTE_COUNT * PTE_SIZE; i++){
    pte[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;
  }

  //register page fault handler
  /**
    code
  **/
  switch_pgd((uint32_t)(pgd_kern - PAGE_OFFSET));
}
