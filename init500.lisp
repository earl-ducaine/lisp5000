(funcall #'(setf iref)
	 #'(lambda (object) (= (ldb (cons 2 0) (ival object)) 1))
	 'consp 5)

(funcall #'(setf iref)
	 #'(lambda (new-definition function-name)
	     (if (consp function-name)
		 (funcall #'(setf iref) new-definition
			  (car (cdr function-name)) 6)
		 (progn
		   (funcall #'(setf iref) new-definition function-name 5)
		   (funcall #'(setf iref)
			    (dpb 0 '(1 . 1) (iref function-name 8))
			    function-name 8)))
	     new-definition)
	 'fdefinition 6)

(funcall #'(setf iref)
	 #'(lambda (new-function symbol &optional environment)
	     (funcall #'(setf iref) new-function symbol 5)
	     (funcall #'(setf iref) (dpb 1 '(1 . 1) (iref symbol 8))
		      symbol 8)
	     new-function)
	 'macro-function 6)

(funcall #'(setf macro-function)
	 #'(lambda (name lambda-list &rest body)
	     (list 'progn
		   (list 'funcall '#'(setf macro-function)
			 (list 'function
			       (cons 'lambda (cons lambda-list body)))
			 (list 'quote name))
		   (list 'quote name)))
	 'defmacro)
