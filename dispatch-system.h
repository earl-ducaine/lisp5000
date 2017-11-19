

#ifndef DISPATCH_SYSTEM_H
#define DISPATCH_SYSTEM_H

// Note the enums here have to be coordinated with the initial_symbols
// table.  In particular the second element of items on that table
// must correspond with the enumeration below.  Eventually this will
// be worked out, but for now we have to suffer with it.
enum initial_dispatchable_enum {
  PLACEHOLDER_DONT_USE,
  QUOTE,
  LET,
  LET_STAR,
  FLET,
  LABELS,
  MACROLET,
  SYMBOL_MACROLET,
  SETQ,
  FUNCTION,
  TAGBODY,
  GO,
  BLOCK,
  RETURN_FROM,
  CATCH,
  THROW,
  UNWIND_PROTECT,
  IF,
  MULTIPLE_VALUE_CALL,
  MULTIPLE_VALUE_PROG1,
  PROGN,
  PROGV,
  SETF,
  FINISH_FILE_STREAM,
  MAKEI,
  DPB,
  LDB,
  BACKQUOTE,
  UNQUOTE,
  UNQUOTE_SPLICING,
  IBOUNDP,
  LISTEN_FILE_STREAM,
  LIST,
  VALUES,
  FUNCALL,
  APPLY,
  EQ,
  CONS,
  CAR,
  CDR,
  SIGN_EQUALS,
  SIGN_LESS_THAN,
  SIGN_PLUS,
  SIGN_MINUS,
  SIGN_MULTIPLICATION,
  SIGN_DIVISION,
  MAKE_FILE_STREAM,
  HASH,
  IERROR,
  GENSYM,
  STRING,
  FASL,
  MAKEJ,
  MAKEF,
  FREF,
  PRINT,
  GC,
  CLOSE_FILE_STREAM,
  IVAL,
  FLOOR,
  READ_FILE_STREAM,
  WRITE_FILE_STREAM,
  LOAD,
  IREF,
  LAMBDA,
  CODE_CHAR,
  CHAR_CODE,
  STANDARD_INPUT,
  STANDARD_OUTPUT,
  ERROR_OUTPUT,
  PACKAGES,
  STRING_EQUALS,
  IMAKUNBOUND,
  EVAL,
  JREF,
  RUN_PROGRAM,
  UNAME,
  SETFCAR,
  SETFCDR,
  SETFIREF,
  SETFJREF
};

// Structure used to build a table of symbols used to build the
// initial system.
struct initial_symbol {
  const char *name;
  int function_index;
  cint_platform argc;
  int setf_function_index;
  cint_platform setargc;
  lval sym;
};

// Structure used to build a table of function dispatched, not that
// unlike almost all other data values used, the second column
// (dispatch address) depends on architecture (i.e. 32bit vs
// 64bit).

// The index into initial_dispatchables should correspond with the
// enum, initial_dispatchable_enums. E.g., the entry indexed by
// UNQUOTE_SPLICING has, as its second column, a pointer to the
// c function llisten_fs and corresponds to the lisp symbol
// 'UNQUOTE-SPLICING
/* struct initial_dispatchable { */
/*   enum initial_dispatchable_enum index; */
/*   // We will make this explicitly an int of the appropriate size to */
/*   // hopefully make things more clear.  But it should be remembered */
/*   // that it needs to be cast as: */
/*   // */
/*   // lval(*fun) () */
/*   // */
/*   // to be used as a function. */
/*   lval uintptr_t address; */
/* }; */

extern struct initial_symbol initial_symbols[];

// Odd looking.  Means get_initial_symbols returns a pointer to a
// function which takes no arguments and returns an lval.
lval (*get_initial_dispatchable(enum initial_dispatchable_enum index))(lval* g, lval n,...);

#endif
