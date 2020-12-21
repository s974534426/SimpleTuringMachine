; case1: check if the input string is in the language {a^ib^ja^ib^j | i, j > 0}
;
; Thinking:
; 1: copy all symbols behind the first a^ib^j pair to the 2nd tape
; 2: delete these symbols in the 1st tape and move both points to the leftmost position
; 3: compare the 1st tape and 2nd tape

#Q = {0,mr1,mr2,cp,ml,mh,cmp,accept,accept2,accept3,accept4,halt_accept,reject,reject_ml,reject_mr,reject2,reject3,reject4,reject5,halt_reject}

#S = {a,b}

#G = {a,b,_,t,r,u,e,f,l,s}

#q0 = 0

#B = _

#F = {halt_accept}

#N = 2

; the transition functions

; State 0: start state 
0 a_ a_ ** mr1
0 b_ b_ ** reject_mr
0 __ __ ** reject_mr

; State mr1: move to right until meeting 'b'
mr1 a_ a_ r* mr1
mr1 b_ b_ r* mr2
mr1 __ __ l* reject_ml

; State mr2: move to right until meeting 'a'
mr2 b_ b_ r* mr2
mr2 a_ aa rr cp
mr2 __ __ l* reject_ml

; State cp: copy the symbols to the 2nd tape
cp a_ aa rr cp
cp b_ bb rr cp
cp __ __ ll ml

; State ml: move left and replace symbol in the 1st tape with block until meeting a block in the 2nd tape
ml aa _a ll ml
ml ab _b ll ml
ml ba _a ll ml
ml bb _b ll ml
ml a_ a_ lr mh
ml b_ b_ lr mh

; State mh: move 1st head to the left
mh aa aa l* mh
mh ba ba l* mh
mh _a _a r* cmp

; State cmp: compare two strings
cmp aa __ rr cmp
cmp ab ab ll reject_ml
cmp ba ba ll reject_ml
cmp bb __ rr cmp
cmp a_ a_ ll reject_ml
cmp b_ b_ ll reject_ml
cmp _a _a ll reject_ml
cmp _b _b ll reject_ml
cmp __ __ ** accept

; State accept*: write 'true' on 1st tape
accept __ t_ r* accept2
accept2 __ r_ r* accept3
accept3 __ u_ r* accept4
accept4 __ e_ ** halt_accept

; State reject_ml: move the 2 tapes to the leftmost position
reject_ml aa aa ll reject_ml
reject_ml ab ab ll reject_ml
reject_ml ba ba ll reject_ml
reject_ml bb bb ll reject_ml
reject_ml a_ a_ l* reject_ml
reject_ml b_ b_ l* reject_ml
reject_ml _a _a *l reject_ml
reject_ml _b _b *l reject_ml
reject_ml __ __ rr reject_mr

; State reject_mr: delete all symbols from left to right
reject_mr aa __ rr reject_mr
reject_mr ab __ rr reject_mr
reject_mr ba __ rr reject_mr
reject_mr bb __ rr reject_mr
reject_mr a_ __ r* reject_mr
reject_mr b_ __ r* reject_mr
reject_mr _a __ *r reject_mr
reject_mr _b __ *r reject_mr
reject_mr __ __ ** reject

; State reject*: write 'false' on 1st tape
reject __ f_ r* reject2
reject2 __ a_ r* reject3
reject3 __ l_ r* reject4
reject4 __ s_ r* reject5
reject5 __ e_ ** halt_reject
