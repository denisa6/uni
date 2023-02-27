; 1. Write a function to check if an atom is member ofa list (the list is non-liniar)
; nrOcc(x,e) = {
;                1,                                  if x is an atom and x = e
;                + nrOcc(x_i,e) (where i = 1,n), if x is a list
;                0,                                  otherwise
; }

; main1(x,e) = {
;    true,   if nrOcc(x,e) > 0
;    false,  otherwise
; }

(defun nrOcc(x e)
(cond
    ((and (atom x) (equal x e))     1)
    ((listp x)                      (apply #'+ (mapcar #'(lambda (a) (nrOcc a e)) x)))
    (t                              0)
)
)

(defun main1(x e)
(cond
    ((< 0 (nrOcc x e))      t)
    (t                      nil)
)
)

; 2. Write a function that returns the sum of numeric atoms in a list, atany level.
; suma(x) = {
;             x,                            if x is a number
;             0,                            if x is an atom and not a number
;             + suma(x_i) (where i = 1,n),  otherwise
; }

(defun suma(x)
(cond
    ((numberp x)  x)
    ((atom x)     0)
    (t            (apply #'+ (mapcar #'suma x)))
)
)

; 3. Define   a   function   to tests   the   membership   of a node in a n-tree represented
; as   (root list_of_nodes_subtree1 ... list_of_nodes_subtreen)
; Eg. tree is (a (b (c)) (d) (E (f)))  and the node is "b" => true
; same as 1

(defun include(x node)
(cond
    ((and (atom x) (equal x node))   1)
    ((atom x)                        0)
    ((listp x)                       (apply #'+ (mapcar #'(lambda(a) (include a node)) x)))
)
)

(defun main3(x node)
(cond
    ((> (include x node) 0)    t)
    (t                         nil)
)
)

; 4. Write a function that returns the product of numeric atoms in a list,at any level.
;productL(n)={
;               n, n is a number
;               1, n is an atom
;		* i=1,k productL(n_i), otherwise
;}


(defun productL(l)
(cond
    ((numberp l)     l)
    ((atom l)        1)
    (t               (apply  '* (mapcar #'productL l)))
)
)

; 5. Write a function that computes the sum of even numbers and the 
; decrease the sum of odd numbers, at any level of a list.
; func5(x) = {
;               x,                             if x is a number and is even
;               -x,                            if x is a  number and is odd
;               0,                             if x is an atom and not a number
;               + func5(x_i) (where i = 1,n),  if x is a list
; }

(defun func5(x)
(cond
    ((and (numberp x) (equal (mod x 2) 0))   x)
    ((numberp x)                             (- 0 x))
    ((atom x)                                0)
    ((listp x)                               (apply #'+ (mapcar #'func5 x)))
)
)

; 6. Write a function that returns the maximum of numeric atoms in a list, at any level.
; maxFor2(a,b) = {
;                 nil,  if a and b are not numbers
;                 a,    if b is not a number
;                 b,    if a is not a number
;                 a,    if a > b
;                 b,    otherwise
; }
; maxForList(l) = {
;                  nil,                              if l is empty
;                  maxFor2(l1, maxForList(l2...ln)), otherwise
; }
; getMax(x) = {
;              x,                                       if x is a number
;              nil,                                     if x is an atom
;              maxForList(getMax(x_i)) (where i = 1,n), otherwise
; }

(defun maxFor2(a b)
(cond
    ((and (not (numberp a)) (not (numberp b))) nil)
    ((not (numberp b))                         a)
    ((not (numberp a))                         b)
    ((> a b)                                   a)
    (t                                         b)
)
)

(defun maxForList(l)
(cond
    ((null l)       nil)
    (t              (maxFor2 (car l) (maxForList (cdr l))))
)
)

(defun getMax(x)
(cond
    ((numberp x)  x)
    ((atom x)     nil)
    (t            (apply #'maxForList (list (mapcar #'getMax x))))
)
)

; 7. Write a function that substitutes an element E with all elements of a list L1 at all levels of a given list L.
; rep(l,x,nl) = {
;                nl,                             if l is an atom and l = x
;                l,                              if l is an atom
;                rep(l_i,x,nl) (where i = 1,n),  otherwise
; }

(defun rep(l x nl)
(cond
    ((and (atom l) (equal l x))         nl)
    ((atom l)                           l)
    (t                                  (mapcar #'(lambda (a) (rep a x nl)) l))
)
)

; 8. Write a function to determine the number of nodes on the level k from a n-tree represented as follows: 
; (rootlist_nodes_subtree1 ... list_nodes_subtreen) 
; Eg: tree is(a (b (c)) (d) (e (f))) and k=1 => 3 nodes
; nrNodes(x,lvl,k) = {
;                     1,                                    if x is an atom and lvl = k
;                     0,                                    if x is an atom
;                     + nrNodes(x,lvl+1,k) (where i = 1,n), otherwise
; }
; main8(x,k) = nrNodes(x,-1,k)

(defun nrNodes(x lvl k)
(cond
    ((and (atom x) (equal lvl k))  1)
    ((atom x)                      0)
    (t                             (apply #'+ (mapcar #'(lambda(a) (nrNodes a (+ 1 lvl) k)) x)))
)
)

(defun main8(x k)
    (nrNodes x -1 k)
)

; 9. Write a function that removes all occurrences of an atom from any level of a list.
; mapcan = apply #'append (mapcar)
; removeE(x,e) = {
;                 nil,                            if x is an atom and x = e
;                 (x),                            if x is an atom
;                 removeE(x_i,e) (where i = 1,n), otherwise
; }

(defun removeE(x e)
(cond
    ((and (atom x) (equal x e))   nil)
    ((atom x)                     (list x))
    (t                            (mapcan #'(lambda(a) (removeE a e)) x))
)
)


; 10. Define  a  function  that  replaces  one  node  with  another  one  in  a  n-tree
; represented  as:  root list_of_nodes_subtree1... list_of_nodes_subtreen) 
; Eg: tree is (a (b (c)) (d) (e (f))) andnode 'b' will be replace with node 'g' => tree (a (g (c)) (d) (e (f)))}
; same as 7

(defun replaceE(x k e)
(cond
    ((and (atom x) (equal x k))   e)
    ((atom x)                     x)
    (t                            (mapcar #'(lambda(a) (replaceE a k e)) x))
)
)

; 11. Write a function to determine the depth of a list.
; maxFor2 - already implemented at 6
; maxForList - already implemented
; depth(x,lvl) = {
;                 lvl,                                            if x is an atom
;                 maxForList( (depth(x,lvl+1)) ) (where i = 1,n), otherwise
; }
; main11(x) = depth(x,0)

(defun depth(x lvl)
(cond
    ((atom x) lvl)
    (t        (apply #'maxForList (list (mapcar #'(lambda(a) (depth a (+ 1 lvl))) x))))
)
)

(defun main11(x)
    (depth x 0)
)



; 12. Write a function that substitutes an element through another one at all levels of a given list.
; same as 10

; 13. Define  a  function  that  returns  the  depth  of  a  tree  represented  
; as(root  list_of_nodes_subtree1  ... list_of_nodes_subtreen) 
; Eg. the depth of the tree (a (b (c)) (d) (e (f))) is 3
; same as 11

; 14. Write a function that returns the number of atoms in a list, at any level
; nrAtoms(x) = {
;               1,                              if x is an atom
;               + nrAtoms(x_i) (where i = 1,n), otherwise
; }

(defun nrAtoms(x)
(cond
    ((atom x) 1)
    (t        (apply #'+ (mapcar #'nrAtoms x)))
)
)

; 15. Write a function that reverses a list together with all its sublists elements, at any level.


; 16. Write a function that produces the linear list of all atoms of a given list, 
; from all levels, and written in the same order.
; Eg.: (((A B) C) (D E)) --> (A B C D E)
; liniarize(x) = {
;                 (x),                            if x is an atom
;                 liniarize(x_i) (where i = 1,n), otherwise
; }

(defun liniarize(x)
(cond
    ((atom x)   (list x))
    (t          (mapcan #'liniarize x))
)
)

