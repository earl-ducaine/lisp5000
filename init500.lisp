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

(defmacro defun (name lambda-list &rest body)
  (list 'progn
	(list 'funcall '#'(setf fdefinition)
	      (list 'function
		    (list 'lambda lambda-list
			  (cons 'block (cons (if (consp name)
						 (car (cdr name))
						 name)
					     body))))
	      (list 'quote name))
	(list 'quote name)))

(defmacro setf (place new-value)
  (if (consp place)
      (cons 'funcall (cons (list 'function (list 'setf (car place)))
			   (cons new-value (cdr place))))
      (list 'setq place new-value)))

(defun append (&rest lists)
  (if (cdr lists)
      (let ((list (car lists))
	    (result nil)
	    (end nil))
	(if list
	    (tagbody
	     start
	       (if list
		   (progn
		     (setf end (if end
				   (setf (cdr end) (list (car list)))
				   (setf result (list (car list)))))
		     (setf list (cdr list))
		     (go start)))
	       (setf (cdr end) (apply #'append (cdr lists)))
	       (return-from append result))
	    (apply #'append (cdr lists))))
      (car lists)))

(defun backquote-expand (list level)
  (if (consp list)
      (if (eq 'backquote (car list))
	  (list 'list ''backquote
		(backquote-expand (car (cdr list)) (+ level 1)))
	  (if (eq 'unquote (car list))
	      (if (= level 0)
		  (car (cdr list))
		  (list 'list ''unquote
			(backquote-expand (car (cdr list)) (- level 1))))
	      (if (eq 'unquote-splicing (car list))
		  (if (= level 0)
		      (values (car (cdr list)) t)
		      (list 'list ''unquote-splicing
			    (backquote-expand (car (cdr list)) (- level 1))))
		  (labels ((collect (list)
			     (if (consp list)
				 (cons (multiple-value-call
					   #'(lambda (value
						      &optional splicingp)
					       (if splicingp
						   value
						   (list 'list value)))
				       (backquote-expand (car list) level))
				     (collect (cdr list)))
				 (list (list 'quote list)))))
		    (cons 'append (collect list))))))
      (list 'quote list)))

(defmacro backquote (form)
  (backquote-expand form 0))

(defun macro-function (symbol &optional environment)
  "(dolist (binding environment)
    (when (and (consp (car binding))
	       (= (floor (ival (cdar binding)) 16) 1)
	       (eq (caar binding) symbol))
      (return-from macro-function
	(when (= (ldb '(1 . 4) (ival (cdr binding))) 1)
	  (cdr binding)))))"
  (if (= (ldb '(1 . 1) (iref symbol 8)) 1)
      (iref symbol 5)))

(defun macroexpand-1 (form &optional env)
  (if (consp form)
      (let ((definition (macro-function (car form) env)))
	(if definition
	    (values (apply definition (cdr form)) t)
	    (values form nil)))
      (if (and form (symbolp form) (= (ldb '(1 . 0) (iref form 8)) 1))
	  (values (iref form 4) t)
	  (values form nil))))

(defun macroexpand (form &optional env)
  (multiple-value-bind (form expanded-p)
      (macroexpand-1 form env)
    (if expanded-p
	(tagbody
	 start
	   (multiple-value-bind (expansion expanded-p)
	       (macroexpand-1 form env)
	     (if expanded-p
		 (progn
		   (setq form expansion)
		   (go start))
		 (return-from macroexpand (values expansion t)))))
	(values form nil))))

(defmacro define-symbol-macro (symbol expansion)
  `(progn
    (setf (iref ',symbol 4) ',expansion)
    (setf (iref ',symbol 8) (dpb 1 (cons 1 0) (iref ',symbol 8)))
    ',symbol))

(defun special-operator-p (symbol)
  (member symbol '(block catch eval-when flet function go if labels let let*
		   load-time-value locally macrolet multiple-value-call
		   multiple-value-prog1 progn progv quote return-from setq
		   symbol-macrolet tagbody the throw unwind-protect)))

(defun constantp (form &optional environment)
  (not (or (and (symbolp form)
		(zerop (ldb '(1 . 4) (iref form 8))))
	   (and (consp form)
		(not (eq (car form) 'quote))))))

(defun null (object) (if object nil t))

(defun not (object) (if object nil t))

(defun length (sequence)
  (let ((tag (ldb '(2 . 0) (ival sequence))))
    (if (= tag 0)
	0
	(if (= tag 1)
	    (let ((i 0)) (dolist (elem sequence i) (setf i (+ 1 i))))
	    (if (= tag 2)
		(let ((subtag (iref sequence 1)))
		  (if (= subtag 3)
		      (/ (ival (iref sequence 0)) 256)
		      (if (= subtag 4)
			  (let ((dimensions/fill (iref sequence 3)))
			    (if (consp dimensions/fill)
				(error "not a sequence")
				(or dimensions/fill
				    (length (iref sequence 4)))))
			  0)))
		(let ((subtag (jref sequence 1)))
		  (if (= subtag 20)
		      (- (/ (jref sequence 0) 64) 4)
		      (if (= subtag 116)
			  (- (/ (jref sequence 0) 8) 31)
			  (error "not a sequence")))))))))

(defun mod (x y) (multiple-value-call #'(lambda (q r) r) (floor x y)))

(defun functionp (object) (eq (type-of object) 'function))

(defun coerce (object result-type)
  (if (typep object result-type)
      object
      (case result-type
	((t) object)
	(character (character object))
	(function (if (and (consp object) (eq (car object) 'lambda))
		      (eval (list 'function object))
		      (if (fboundp object)
			  (fdefinition object))
			  (error 'type-error :datum object
				 :expected-type result-type)))
	(t (error 'type-error :datum object :expected-type result-type)))))

(defun ensure-type (name expander)
  (let ((cons (assoc name *type-expanders*)))
    (if cons
	(setf (cdr cons) expander)
	(push (cons name expander) *type-expanders*))
    name))

(defmacro deftype (name lambda-list &rest forms)
  `(ensure-type ',name #'(lambda ,lambda-list (block ,name ,@forms))))

(defun *= (cons number)
  (or (not cons) (eq (car cons) '*) (= (car cons) number)))

(defun typep (object type-specifier &optional environment)
  (let ((tag (ldb '(2 . 0) (ival object))))
    (case type-specifier
      ((nil extended-char) nil)
      ((t *) t)
      (null (not object))
      (list (or (not object) (= tag 1)))
      (fixnum (and (= tag 0) (= (ldb '(5 . 0) (ival object)) 16)))
      (package (and (= tag 2) (= (iref object 1) 5)))
      (symbol (or (not object) (and (= tag 2) (= (iref object 1) 0))))
      ((character base-char)
       (and (= tag 0) (= (ldb '(5 . 0) (ival object)) 24)))
      (standard-char (and (= tag 0)
			  (= (ldb '(5 . 0) (ival object)) 24)
			  (let ((code (char-code object)))
			    (or (= code 10)
				(< 31 code 127)))))
      (bit (member object '(0 1)))
      (t (setq type-specifier (designator-list type-specifier))
	 (case (car type-specifier)
	   (cons (and (= tag 1)
		      (or (not (cdr type-specifier))
			  (typep (car object) (cadr type-specifier)))
		      (or (not (cddr type-specifier))
			  (typep (car object) (caddr type-specifier)))))
	   ((string base-string) (and (stringp object)
				      (*= (cdr type-specifier)
					  (length object))))
	   (satisfies (funcall (cadr type-specifier) object))
	   (member (member object (cdr type-specifier)))
	   (not (not (typep object (cadr type-specifier))))
	   (and (every #'(lambda (spec) (typep object spec))
		       (cdr type-specifier)))
	   (or (some #'(lambda (spec) (typep object spec))
		     (cdr type-specifier)))
	   (eql (eql object (cadr type-specifier)))
	   (t (when (= tag 2)
		(let ((class (iref object 1)))
		  (when (= (ldb '(2 . 0) (ival class)) 2)
		    (member (car type-specifier)
			    (mapcar #'class-name
				    (class-precedence-list class))))))))))))

(defun fboundp (function-name)
  (if (consp function-name)
      (iboundp (cadr function-name) 6)
      (iboundp function-name 5)))

(defun fdefinition (function-name)
  (if (consp function-name)
      (if (iboundp (cadr function-name) 6)
	  (iref (cadr function-name) 6)
	  (error 'undefined-error :name function-name))
      (if (iboundp function-name 5)
	  (iref function-name 5)
	  (error 'undefined-error :name function-name))))

(defun function-lambda-expression (function)
  (values (list* 'lambda (iref function 4) (iref function 5))
	  (iref function 3)
	  (iref function 6)))

(defmacro defconstant (name initial-value &optional documentation)
  `(progn
    (setf (iref ',name 4) ,initial-value)
    (setf (iref ',name 8) (dpb 1 '(1 . 4) (iref ',name 8)))
    ',name))

(defmacro defparameter (name initial-value &optional documentation)
  `(progn
    (setf (iref ',name 4) ,initial-value)
    (setf (iref ',name 8) (dpb 1 (cons 1 2) (iref ',name 8)))
    ',name))

(defparameter *type-expanders* nil)
