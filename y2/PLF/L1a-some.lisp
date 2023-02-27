;1. 
;a)Write a function to return the n-th element of a list, or NIL if such an element does not exist.
;b)Write a function to check whether an atom E is amember of a list which is not necessarily linear.
;c)Write a function to determine the list of all sublists of a given list, on any level.
; A sublist is either the list itself, or any element that is a list, at any level.
; Example: (1 2 (3 (4 5)(6 7)) 8 (9 10)) => 5sublists:(  (1 2 (3 (4 5) (6 7)) 8 (9 10))    (3 (4 5) (6 7))     (4 5)   (6 7)   (9 10) )
;d)Write a function to transform a linear list into a set.

;a
(defun func1a (l n p)
(cond
    ((null l)  nil)
    ((= p n)   (car l))
    (t         (func1a (cdr l) n (+ 1 p)))
)
)

(defun main1a (l n)
    (func1a l n 1)
)

;b
(defun func1b (l e)
(cond
    ((null l)                                nil)
    ((and (atom (car l)) (equal (car l) e))  t)
    ((listp (car l))                        (func1b (car l) e))
    (t                                      (func1b (cdr l) e))
)
)

;c
(defun a (l ll)
  (cond
   ((null l) ll)
   (t (cons (car l) (a (cdr l) ll)))
   )
)

(defun func1c (l)
(cond
    ((null l) nil)
    ((listp (car l))   (a (a (list(car l)) (func1c (car l))) (func1c (cdr l))))
    (t                 (func1c (cdr l)))
)
)

(defun main1c (l)
    (func1c (list l))
)

;d
(defun func1d (l v)
    (cond 
        ((null l) v)
        ((not (func1b v (car l)))  (func1d (cdr l) (a v (list (car l)))))
        (t (func1d (cdr l) v))
    )
)

(defun main1d (l)
    (func1d l ())
)


;2. a)Write a function to return the product of two vectors.https://en.wikipedia.org/wiki/Dot_product
;b)Write a function to return the depth of a list. Example: the depth of a linear list is 1.
;c)Write a function to sort a linear list without keeping the double values.
;d)Write a function to return the intersection of two sets

;a
(defun func2a (v1 v2)
(cond
    ((null v1)   0)
    (t           (+ (* (car v1) (car v2)) (func2a (cdr v1) (cdr v2))))
)
)

;b
(defun maxFor2(a b)
(cond
    ((and (not (numberp a)) (not (numberp b))) nil)
    ((not (numberp b))                         a)
    ((not (numberp a))                         b)
    ((> a b)                                   a)
    (t                                         b)
)
)

(defun func2b (l lvl)
(cond
    ((null l)          lvl)
    ((listp (car l))   (maxFor2 (func2b (car l) (+ 1 lvl)) (func2b (cdr l) lvl)))
    (t                 (func2b (cdr l) lvl))
)
)

(defun main2b (l)
    (func2b l 1)
)

;c
(defun checkI (l e)
(cond
    ((null l)           (list e))
    ((equal (car l) e)  l)
    ((< e (car l))      (cons e l))
    (t                  (cons (car l) (checkI (cdr l) e)))
)
)

(defun func2c (l)
(cond
    ((null l)   nil)
    (t          (checkI (func2c (cdr l)) (car l)))
)
)

;d
(defun func2d (s1 s2)
(cond
    ((null s2)            nil)
    ((func1b s1 (car s2)) (cons (car s2) (func2d s1 (cdr s2))))
    (t                    (func2d s1 (cdr s2)))
)
)


;3. a) Write a function that inserts in a linear list a given atom A after the 2nd, 4th, 6th, ... element.
;b) Write a function to get from a given list the list of all atoms, on any level, but reverse order. 
; Example:(((A B) C) (D E)) ==> (E D C B A)
;c) Write a function that returns the greatest common divisor of all numbers in a nonlinear list.
;d) Write a function that determines the number of occurrences of a given atom in a nonlinear list.

;a
(defun func3a (l e p)
(cond
    ((null l)           nil)
    ((= 0 (mod p 2))   (a (list (car l)) (a (list e) (func3a (cdr l) e (+ 1 p)))))
    (t                 (a (list (car l)) (func3a (cdr l) e (+ 1 p))))
)
)

(defun main3a (l e)
    (func3a l e 1)
)

;b
(defun func3b (l)
(cond
    ((null l)          nil)
    ((listp (car l))   (a (func3b (cdr l)) (func3b (car l))))
    (t                 (a (func3b (cdr l)) (list (car l))))
)
)

;c
(defun myGcd (a b)
(cond
    ((and (not (numberp a)) (not (numberp b)))   nil)
    ((not (numberp b))                           a)
    ((not (numberp a))                           b)
    ((or (= a 0) (= b 0))                        nil)
    ((= a b)                                     a)
    ((< a b)                                     (myGcd a (- b a)))
    (t                                           (myGcd (- a b) b))
)
)

(defun func3c (l)
(cond
    ((null l)          nil)
    ((listp (car l))   (myGcd (func3c (car l)) (func3c (cdr l))))
    (t                 (myGcd (car l) (func3c (cdr l))))
)
)

;d
(defun nrOcc (l e)
(cond
    ((null l)  0)
    ((and (atom (car l))   (equal (car l) e)) (+ 1 (nrOcc (cdr l) e)))
    ((listp (car l))       (+ (nrOcc (car l) e) (nrOcc (cdr l) e)))
    (t                     (nrOcc (cdr l) e))      
)
)

;4.a)Write a function to return the sum of two vectors.
;b)Write a function to get from a given list the list of all atoms, on any level, but on the same order. 
; Example:(((A B) C) (D E)) ==> (A B C D E)
;c)Write a function that, with a list given as parameter, inverts only continuoussequences of atoms.
; Example:(a b c (d (e f) g h i)) ==> (c b a (d (f e) i h g))
;d)Write a list to return the maximum value of the numerical atoms from a list, at superficial level.

;a - not sure if i got it right
(defun func4a (v1 v2)
(cond
    ((null v1)   nil)
    (t           (cons (+ (car v1) (car v2)) (func4a (cdr v1) (cdr v2))))
)
)

;b
(defun func4b (l)
(cond
    ((null l)          nil)
    ((listp (car l))   (a (func4b (car l)) (func4b (cdr l))))
    (t                 (a (list (car l)) (func4b (cdr l))))
)
)

;c
; invertCont (l, aux) = {
;   aux , if l is empty
;   aux U invertCont(l1, nil) U invertCont(l2...ln, nil), if l1 is a list
;   invertCont(l2...ln, (l1 U aux)), otherwise

(defun invertCont (l aux)
  (cond
    ((null l) aux)
    ((listp (car l)) (a aux (a (list (invertCont (car l) nil)) (invertCont (cdr l) nil))))
    (t (invertCont (cdr l) (a (list (car l)) aux)))
  )
)

;d maxFor2 + maxForList
(defun maxForList (l)
(cond
    ((null l)       nil)
    (t              (maxFor2 (car l) (maxForList (cdr l))))
)
)

;5.a)Write twice the n-th element of a linear list. 
; Example: for (10 20 30 40 50) and n=3 will produce (10 20 30 30 40 50).
;b)Write a function to return an association list with the two lists given as parameters. 
; Example: (A B C) (X Y Z) --> ((A.X) (B.Y) (C.Z)).
;c)Write a function to determine the number of all sublists of a given list, on any level.
; A sublist is either the list itself, or any element that is a list, at any level. 
; Example: (1 2 (3 (4 5) (6 7)) 8 (9 10)) => 5 lists:(list itself, (3 ...), (4 5), (6 7), (9 10)).
;d)Write a function to return the number of all numerical atoms in a list at superficial level.

;a
(defun func5a (l n p)
(cond
    ((null l)   nil)
    ((equal p n)   (a (list (car l)) (a (list (car l)) (func5a (cdr l) n (+ 1 p)))))
    (t             (a (list (car l)) (func5a (cdr l) n (+ 1 p))))
)
)

(defun main5a(l n)
    (func5a l n 1)
)

;b
(defun func5b (l1 l2)
(cond
    ((and (null l1) (null l2))    nil)
    ((null l1)                    (a (list (cons nil (car l2))) (func5b nil (cdr l2))))
    ((null l2)                    (a (list (cons (car l1) nil)) (func5b (cdr l1) nil)))
    (t                            (a (list (cons (car l1) (car l2))) (func5b (cdr l1) (cdr l2))))
)
)

;c
(defun func5c (l)
(cond
    ((null l)          1)
    ((listp (car l))   (+ (func5c (car l)) (func5c (cdr l))))
    (t                 (func5c (cdr l)))
)
)

;d
(defun func5d (l)
(cond
    ((null l)            0)
    ((numberp (car l))   (+ 1 (func5d (cdr l))))
    ((listp (car l))     (+ (func5d (car l)) (func5d (cdr l))))
    (t                   (func5d (cdr l)))
)
)


;6. a)Write a function to test whether a list is linear.
;b)Write a function to replace the first occurence of an element E in a given listwith an other element O.
;c)Write a function to replace each sublist of a list with its last element.
;A sublist is an element from the first level, which is a list. 
; Example: (a (b c) (d (e (f)))) ==> (a c (e (f))) ==> (a c (f)) 
; ==> (a c f)(a (b c) (d ((e) f))) ==> (a c ((e) f)) ==> (a c f)
;d)Write a function to merge two sorted lists without keeping double values.

;a
(defun main6a (l)
(cond
    ((= (func5c l) 1)   t)
    (t                  nil)
)
)

;b - nu merge pentru liste neliniare
(defun func6b (l e o x)
(cond
    ((null l)   nil)
    ((and (equal (car l) e) (equal x 0))   (a (list o) (func6b (cdr l) e o (+ 1 x))))
    ((listp (car l))                       (a (list (func6b (car l) e o x)) (func6b (cdr l) e o x)))
    (t                                     (a (list (car l)) (func6b (cdr l) e o x)))
)
)

(defun main6b (l e o)
    (func6b l e o 0)
)

;c
(defun lastElem (l)
(cond
    ((null l)                                       nil)
    ((and (= (length l) 1) (not (listp (car l))))   (car l))
    ((and (= (length l) 1) (listp (car l)))         (lastElem (car l)))
    (t                  (lastElem (cdr l)))
)
)

(defun func6c (l)
(cond
    ((null l)          nil)
    ((listp (car l))   (cons (lastElem (car l)) (func6c (cdr l))))
    (t                 (cons (car l) (func6c (cdr l))))
)
)

;d
(defun func6d (l1 l2)
(cond
    ((and (null l1) (null l2))   nil)
    ((null l1)                   (cons (car l2) (func6d nil (cdr l2))))
    ((null l2)                   (cons (car l1) (func6d (cdr l1) nil)))
    ((= (car l1) (car l2))       (cons (car l1) (func6d (cdr l1) (cdr l2))))
    ((< (car l1) (car l2))       (cons (car l1) (func6d (cdr l1) l2)))
    (t                           (cons (car l2) (func6d l1 (cdr l2))))
)
)


;7. a)Write a function to eliminate the n-th element of a linear list.
;b)Write a function to determine the successor of a number represented digit by digit as a list, 
;without transforming the representation of the number from list to number. 
; Example: (1 9 3 5 9 9) --> (1 9 3 6 0 0)
;c)Write a function to return the set of all the atoms of a list.
; Exemplu: (1 (2 (1 3 (2 4) 3) 1) (1 4)) ==> (1 2 3 4)
;d)Write a function to test whether a linear list is a set.

;a
(defun func7a (l n p)
(cond
    ((null l)   nil)
    ((= p n)    (func7a (cdr l) n (+ 1 p)))
    (t          (cons (car l) (func7a (cdr l) n (+ 1 p))))
)
)

(defun main7a (l n)
    (func7a l n 1)
)

;b

;molnar
(defun suma (l)
(cond
    ((null l)                                       0)
    ((and (atom (car l)) (not (numberp (car l))))   (suma (cdr l)))
    (t                                              (+ (car l) (suma (cdr l))))
)
)

(defun suma2 (l)
(cond
    ((null l)            0)
    ((numberp (car l))   (+ (car l) (suma2 (cdr l))))
    (t                   (suma2 (cdr l)))
)
)


(defun rev(l)
(cond
    ((null l) nil)
    ((listp (car l))   (a (rev (cdr l)) (list (rev (car l)))))
    (t    (a (rev (cdr l)) (list (car l))))
)
)
