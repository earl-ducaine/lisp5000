
// Programming by stackexchange: copy-and-paste

#include <sys/mman.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <error.h>

#include "defs.h"

// must be at least 32bits
uintptr_t SUGGESTED_MEM_LOCATION_REGION_A = 0x80000000;
uintptr_t mem_region_a = 0;



// malloc based memory allocation
void* alocate_region_malloc(long size_in_bytes) {
  void* mem_location = malloc(size_in_bytes);
  if (!mem_location) {
    int error_save = errno;
    printf("Map failed with error code: %i\n", error_save);
  }
  return mem_location;
}

// malloc based memory allocation
void* alocate_memory_mmap(void* suggested_mem_location, uintptr_t size_in_bytes) {
  void* mem_location =
    (void*)mmap(suggested_mem_location, size_in_bytes * sizeof(lval),
		    PROT_READ|PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (mem_location == MAP_FAILED) {
    int error_save = errno;
    printf("Map failed with error code: %i\n", error_save);
  } else {
    if (mem_location != suggested_mem_location) {
      printf("Allocated memory had to be shifted: %li .\n",
	     (long)mem_location);
    }
  }
  return mem_location;
}



 /* if (somecall() == -1) { */
 /*               int errsv = errno; */
 /*               printf("somecall() failed\n"); */
 /*               if (errsv == ...) { ... } */
 /*           } */
 /*    lval* entry = (lval*)mem_location; */
 /*    entry[0] = 4; */
 /*    printf("Success: entry=%p, entry->a = %d\n", entry, entry[0]); */
