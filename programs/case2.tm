; case2: accept an expression string like 1^mx1^n=1^mn
;
; Thinking:
; 1: copy the substring before 'x' to the 2nd tape
; 2: copy the substring between 'x' and '=' to the 3rd tape
; 3: move the 1st head and the 2nd head, if the 2nd head meets 
;    a block, then the 3rd head move one square and the 2nd 
;    head goes to the left.=

#Q = {0,cp1,cp1tocp2,cp2,mh_all,cmp,mh2,before_ac,accept_ml,accept,accept2,accept3,accept4,halt_accept,reject_ml,reject_mr,reject,reject2,reject3,reject4,reject5,halt_reject}

#S = {1,x,=}

#G = {1,x,=,_,t,r,u,e,f,a,l,s}

#q0 = 0

#B = _

#F = {halt_accept}

#N = 3

; the transition functions

; State 0: start state 
0 1__ 1__ *** cp1
0 x__ x__ *** reject_mr
0 =__ =__ *** reject_mr
0 ___ ___ *** reject_mr

; State cp1: copy the first term to the 2nd tape
cp1 1__ _1_ rr* cp1
cp1 x__ ___ r** cp1tocp2
cp1 =__ ___ rl* reject_ml
cp1 ___ ___ *l* reject_ml

; State cp1tocp2: a temp state from cp1 to cp2
cp1tocp2 1__ 1__ *** cp2
cp1tocp2 =__ ___ rl* reject_ml
cp1tocp2 x__ ___ rl* reject_ml
cp1tocp2 ___ ___ *l* reject_ml

; State cp2: copy the second term to the 3rd tape
cp2 1__ __1 r*r cp2
cp2 =__ ___ rll mh_all
cp2 x__ ___ rll reject_ml
cp2 ___ ___ *ll reject_ml

; State mh_all: move all tape heads to the left
mh_all 111 111 lll mh_all
mh_all _11 _11 *ll mh_all
mh_all 1_1 1_1 l*l mh_all
mh_all 11_ 11_ ll* mh_all
mh_all __1 __1 **l mh_all
mh_all _1_ _1_ *l* mh_all
mh_all 1__ 1__ l** mh_all
mh_all ___ ___ rrr cmp
mh_all x11 x11 *** reject_ml
mh_all x1_ x1_ *** reject_ml
mh_all =11 =11 *** reject_ml
mh_all =1_ =1_ *** reject_ml

; State cmp: compare the number of 1's
cmp 111 _11 rr* cmp
cmp 1_1 1_1 *lr mh2
cmp __1 __1 **r before_ac
cmp _11 _11 *** reject_ml
cmp x11 _11 r** reject_ml
cmp x_1 __1 rl* reject_ml
cmp =11 _11 r** reject_ml
cmp =_1 __1 rl* reject_ml

; State mh2: move 2nd tape head to the left
mh2 111 111 *l* mh2
mh2 1_1 1_1 *r* cmp
mh2 11_ 11_ lll reject_ml

; State before_ac: a temp state before accept
before_ac ___ ___ *ll accept_ml
before_ac __1 __1 *ll reject_ml

; State accept_ml: move to the left and replace the symbol with block
accept_ml _11 ___ *ll accept_ml
accept_ml __1 ___ **l accept_ml
accept_ml _1_ ___ *l* accept_ml
accept_ml ___ ___ *** accept

; State accept*: write 'true' on 1st tape
accept ___ t__ r** accept2
accept2 ___ r__ r** accept3
accept3 ___ u__ r** accept4
accept4 ___ e__ *** halt_accept

; State reject_ml: move all tape heads to the left
reject_ml 111 111 lll reject_ml
reject_ml _11 _11 *ll reject_ml
reject_ml 1_1 1_1 l*l reject_ml
reject_ml 11_ 11_ ll* reject_ml
reject_ml __1 __1 **l reject_ml
reject_ml _1_ _1_ *l* reject_ml
reject_ml 1__ 1__ l** reject_ml
reject_ml x11 x11 lll reject_ml
reject_ml x_1 x_1 l*l reject_ml
reject_ml x1_ x1_ ll* reject_ml
reject_ml x__ x__ l** reject_ml
reject_ml =11 =11 lll reject_ml
reject_ml =_1 =_1 l*l reject_ml
reject_ml =1_ =1_ ll* reject_ml
reject_ml =__ =__ l** reject_ml
reject_ml ___ ___ rrr reject_mr

; State reject_mr: move to the right and empty the tapes
reject_mr 111 ___ rrr reject_mr
reject_mr _11 ___ *rr reject_mr
reject_mr 1_1 ___ r*r reject_mr
reject_mr 11_ ___ rr* reject_mr
reject_mr __1 ___ **r reject_mr
reject_mr _1_ ___ *r* reject_mr
reject_mr 1__ ___ r** reject_mr
reject_mr x11 ___ rrr reject_mr
reject_mr x_1 ___ r*r reject_mr
reject_mr x1_ ___ rr* reject_mr
reject_mr x__ ___ r** reject_mr
reject_mr =11 ___ rrr reject_mr
reject_mr =_1 ___ r*r reject_mr
reject_mr =1_ ___ rr* reject_mr
reject_mr =__ ___ r** reject_mr
reject_mr ___ ___ *** reject

; State reject*: write 'false' on 1st tape
reject ___ f__ r** reject2
reject2 ___ a__ r** reject3
reject3 ___ l__ r** reject4
reject4 ___ s__ r** reject5
reject5 ___ e__ *** halt_reject
