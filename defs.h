

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
lval eval_block(lval* f, lval l);
lval eval_body(lval* f, lval l);
lval eval_catch(lval* f, lval l);
lval eval_flet(lval* f, lval l);
lval eval_function(lval* f, lval l);
lval eval_go(lval* f, lval l);
lval eval_if(lval* f, lval l);
lval eval_labels(lval* f, lval l);
lval eval_let(lval* f, lval l);
lval eval_letm(lval* f, lval l);
lval eval_macrolet(lval* f, lval l);
lval eval_multiple_value_call(lval* f, lval l);
lval eval_multiple_value_prog1(lval* f, lval l);
lval eval_progv(lval* f, lval l);
lval eval_quote(lval* f, lval l);
lval eval_return_from(lval* f, lval l);
lval eval_setf(lval* f, lval l);
lval eval_setq(lval* f, lval l);
lval eval_symbol_macrolet(lval* f, lval l);
lval eval_tagbody(lval* f, lval l);
lval eval_throw(lval* f, lval l);
lval eval_unwind_protect(lval* f, lval l);
lval gc(lval* f, lval l);
lval lapply(lval* f, lval l);
lval lcar(lval* f, lval l);
lval lcdr(lval* f, lval l);
lval lchar_code(lval* f, lval l);
lval lclose_fs(lval* f, lval l);
lval lcons(lval* f, lval l);
lval ldivi(lval* f, lval l);
lval ldpb(lval* f, lval l);
lval leq(lval* f, lval l);
lval lequ(lval* f, lval l);
lval leval(lval* f, lval l);
lval lfasl(lval* f, lval l);
lval lfinish_fs(lval* f, lval l);
lval lfloor(lval* f, lval l);
lval lfref(lval* f, lval l);
lval lfuncall(lval* f, lval l);
lval lhash(lval* f, lval l);
lval liboundp(lval* f, lval l);
lval limakunbound(lval* f, lval l);
lval liref(lval* f, lval l);
lval lival(lval* f, lval l);
lval ljref(lval* f, lval l);
lval lldb(lval* f, lval l);
lval lless(lval* f, lval l);
lval llist(lval* f, lval l);
lval llisten_fs(lval* f, lval l);
lval lload(lval* f, lval l);
lval lmake_fs(lval* f, lval l);
lval lmakef(lval* f, lval l);
lval lmakei(lval* f, lval l);
lval lmakej(lval* f, lval l);
lval lminus(lval* f, lval l);
lval lplus(lval* f, lval l);
lval lprint(lval* f, lval l);
lval lread_fs(lval* f, lval l);
lval lrp(lval* f, lval l);
lval lstring(lval* f, lval l);
lval lstring_equal(lval* f, lval l);
lval ltimes(lval* f, lval l);
lval luname(lval* f, lval l);
lval lvalues(lval* f, lval l);
lval lwrite_fs(lval* f, lval l);
lval setfcar(lval* f, lval l);
lval setfcdr(lval* f, lval l);
lval setfiref(lval* f, lval l);
lval setfjref(lval* f, lval l);



#endif
