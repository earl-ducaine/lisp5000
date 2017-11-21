

#ifndef DEFS_H
#define DEFS_H

// typedef uint32_t lval;
typedef int32_t lval;

// a type coordinated with lval to be the same size that holds pure c
// values only. (Not always clear what 'pure c values' means.
typedef lval cint_platform;

void* allocate_region_malloc(long size_in_bytes);
void* allocate_region_mmap(long size_in_bytes);
void debug_write(char* debug_string, long arg);
void debug_write_local(char* debug_string, long arg);

lval get_function_pointer(int index);
lval set_function_pointer(int index);

/* struct initial_symbol { */
/*   const char *name; */
/*   lval(*fun) (); */
/*   cint_platform argc; */
/*   lval(*setfun) (); */
/*   cint_platform setargc; */
/*   lval sym; */
/* }; */

#define allocate_region allocate_region_mmap

#if DEBUG
#define debug_write(x, f) debug_write_local((x), (f))
#else
#define debug_write(x, f)
#endif

lval eval_declare(lval* f, lval ex);
lval liboundp(lval* f);
lval eval_quote(lval* g, lval ex);
lval eval_let(lval* f, lval ex);
lval eval_letm(lval* f, lval ex);
lval eval_flet(lval* f, lval ex);
lval eval_labels(lval* f, lval ex);
lval eval_macrolet(lval* f, lval ex);
lval eval_symbol_macrolet(lval* f, lval ex);
lval eval_setq(lval* f, lval ex);
lval eval_function(lval* f, lval ex);
lval eval_tagbody(lval* f, lval ex);
lval eval_go(lval* f, lval ex);
lval eval_block(lval* f, lval ex);
lval eval_return_from(lval* f, lval ex);
lval eval_catch(lval* f, lval ex);
lval eval_throw(lval* f, lval ex);
lval eval_unwind_protect(lval* f, lval ex);
lval eval_if(lval* f, lval ex);


#endif
