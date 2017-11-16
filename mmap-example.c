
// Programming by stackexchange copy-and-paste

#include <sys/mman.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>

#include "defs.h"

typedef struct
{
  int a;
  int b;
} myStruct;

// must be at least 32bits
uintptr_t suggested_mem_region_a = 0x80000000;
uintptr_t mem_region_a = 0;

int alocate_memory(void* suggested_mem_location) {
  uintptr_t mem_location =
    (uintptr_t)mmap(suggested_mem_location, 1024 * sizeof(lval),
		    PROT_READ|PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  if ((void*)mem_location == MAP_FAILED) {
    printf("Map failed.\n");
  } else {
    if (mem_location != suggested_mem_location) {
      printf("Allocated memory had to be shifted: %li .\n",
	     (long)mem_region_a);
    }
    lval* entry = (lval*)mem_region_a;
    entry[0] = 4;
    printf("Success: entry=%p, entry->a = %d\n", entry, entry[0]);
  }
}

int main() {
  mem_region_a = (uintptr_t)alocate_memory((void*)suggested_mem_location);
  return 0;
}
