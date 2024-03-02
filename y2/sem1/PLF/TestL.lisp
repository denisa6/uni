(defun a (l ll)
  (cond
   ((null l)   ll)
   (t          (cons (car l) (a (cdr l) ll)))
   )
)
(defun rev (l)
(cond
   ((null l)               nil)
   (t   (a (rev (cdr l))   (list (car l))))
)
)

(defun f (l c)
(cond
   ((and (null l) (= c 1))       (list 1))
   ((null l)                     nil)
   ((= (+ (car l) c) 10)         (a (list 0) (f (cdr l) 1)))
   ((= c 1)                      (a (list (+ (car l) 1)) (f (cdr l) 0)))
   (t                            (a (list (car l)) (f (cdr l) 0)))
)
)

(defun main(l)
   (rev (f (rev l) 1))
)