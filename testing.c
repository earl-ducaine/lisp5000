
// evaca
lval ex = car(co);
fn = *binding(f, car(car(co)), 1, &m); [sym:car(car(co))]


((lval*)o2s(o2a(*(o2a(car(car(co))) + 4 + 1))[2]))[2]

// generates the fn that we use to generate the 64 vs 32 mismatch
// although the mismatch occures in call.  We should be able to
// generated it with the following in evaca, post binding call.


p /x o2s(o2a(fn)[2])[2]


// ep: note, expr is read from the stream. So reading is the next
// logical place to look.
p /x ((lval*)o2s(o2a(*(o2a(car(car(cons(g, expr, 0)))) + 4 + 1))[2]))[2]



g
