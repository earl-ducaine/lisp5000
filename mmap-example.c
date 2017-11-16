
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
uintptr_t mem_region_a_suggested = 0x80000000;
uintptr_t mem_region_a = 0x80000000;

int alocate_memory() {
  mem_region_a =
    (uintptr_t)mmap((void*)mem_region_a_suggested, 1024 * sizeof(lval),
		    PROT_READ|PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  if ((void*)mem_region_a == MAP_FAILED) {
    printf("Map failed.\n");
  } else {
    if (mem_region_a != mem_region_a_suggested) {
      printf("Allocated memory had to be shifted: %li .\n", (long)mem_region_a);
    }
    lval* entry = (lval*)mem_region_a;
    entry[0] = 4;
    printf("Success: entry=%p, entry->a = %d\n", entry, entry[0]);
  }
}

int main() {
  alocate_memory();
  return 0;
}
