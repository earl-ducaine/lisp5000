

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
void debug_write(char* debug_string, long arg);
void debug_write_local(char* debug_string, long arg);

#define allocate_region allocate_region_mmap

#if DEBUG
#define debug_write(x, f) debug_write_local((x), (f))
#else
#define debug_write(x, f)
#endif

#endif
