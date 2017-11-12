

#ifndef DEFS_H

#define DEFS_H
#define TRUE symi[1].sym
#define T g[-2]
#define U g[-3]
#define V g[-4]
#define W g[-5]
#define NF(n) lval *g; g=f+n+3; f[1]=0; g[-1]=(n<<5)|16; *g=*f;
#define E *f
#define NE *g

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

#endif
