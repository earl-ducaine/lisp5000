

#ifndef DEFS_H
#define DEFS_H

// typedef uint32_t lval;
typedef int32_t lval;

// a type coordinated with lval to be the same size that holds pure c
// values only. (Not always clear what 'pure c values' means.
typedef lval cint_platform;

struct symbol_init {
  const char *name;
  lval(*fun) ();
  cint_platform argc;
  lval(*setfun) ();
  cint_platform setargc;
  lval sym;
};

void* allocate_region_malloc(long size_in_bytes);
void* allocate_region_mmap(long size_in_bytes);

#define allocate_region allocate_region_mmap

#endif
