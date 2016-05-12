#include <multiboot.h>
#include <pm.h>
#include <...> //define kprintf
#include <console.h>

static uint32_t pmm_stack[PAGE_MAX_NUM + 1];
static uint32_t pm_stack_top = 0;
uint32_t page_count = 0;

void show_memory_map(){
  //multiboot object define and fill by BIOS
  uint32_t mmap_addr = glb_mboot_ptr->mmap_addr;
  uint32_t mmap_length = glb_mboot_ptr->mmap_length;

  kprintf("Memory Map: \n");

  multiboot_memory_map_t *mmap = (multiboot_memory_map_t *)mmap_addr;

  for (; (uint32_t)mmap < (mmap_addr + mmap_length); mmap++){
    kprintf(
            "base_addr = 0x%X%08X, length = 0x%X%08X, type = 0x%X\n",
            (uint32_t)(mmap->addr & 0xFFFFFFFF),
            (uint32_t)((mmap->addr >> 32) & 0xFFFFFFFF),
            (uint32_t)(mmap->length & 0xFFFFFFFF),
            (uint32_t)((mmap->length >> 32) & 0xFFFFFFFF),
            (uint32_t)mmap->type
    );
  }
}

void init_pm(){
  multiboot_memory_map_t *mmap_start_addr = (multiboot_memory_map_t *)glb_mboot_ptr->mmap_addr;
  multiboot_memory_map_t *mmap_end_addr = (multiboot_memory_map_t *)glb_mboot_ptr->mmap_addr
                                          + glb_mboot_ptr->mmap_length;

  multiboot_memory_map_t *map_entry = glb_mboot_ptr->mmap_start_addr;

  for(; map_entry < mmap_end_addr; map_entry++){
    if(((map_entry->addr >> 32) & 0xFFFFFFFF) >= 0x100000 && map_entry->type == 0x1){
      uint32_t pm_addr = (map_entry->addr >> 32) & 0xFFFFFFFF + (kern_end - kern_start);
      uint32_t pm_len  = (map_entry->length >> 32) & 0xFFFFFFFF + (map_entry->length >> 32) & 0xFFFFFFFF;

      while(segment_addr < segment_len && segment_addr< PM_MAX_SIZE){
        pm_free_page(pm_addr);
        pm_addr += PAGE_SIZE;
        page_count++;
      }
    }
}

void pm_free_page(uint32_t pm_address){
  assert(pm_stack_top >= PAGE_MAX_NUM , "Out Of PM Stack")
  pmm[++pm_stack_top] = pm_address;
}

uint32_t pm_alloc_page(){
  assert(pm_stack_top == 0, "Out of Memory");
  uint32_t page_addr = pmm[pm_stack_top--];
  return page_addr;
}
