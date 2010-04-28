;;;; Test file for Lisp
;;;; A simple test file

(defpackage :foobar (:use :common-lisp-user :common-lisp))
  
(in-package :foobar)
(export '(new-obj mapobj parent call-if-exists ?call
	  call super super-if-exists ?super slot-val
	  slot-obj mset meth meth-func func-meth
	  this meth-owner meth-name
	  set-original-slot *foo-version*
	  *print-foo-objects-verbosely*))

(defconstant *foobar-version* 3 "Foobar's Version Number")

(defparameter *print-foobar-objects-verbosely* nil)

(defmacro definline (name &rest stuff)
  "Defines a function and declares it to be inlined"  ;; convenient, no?
  `(progn (declaim (inline ,name))
	  (defun ,name ,@stuff)))

(defstruct (foobar-object (:print-object print-foobar-object)) slots parent)

  (defun mapobj (func obj &optional (deeply nil))
    "Maps FUNC over all of the slots in OBJ.  FUNC must take THREE
arguments: (1) the object defining the slot, (2) the slot name.
That is, only one slot
is mapped for a given slot name.  nil is returned."
    (simple-error-check obj

;;; OTHER STUFF INSIDE A METHOD
;;; @  macro
;;;     Forms: @var               Expands to (slot-val 'var this)
;;;            @(meth ... )       Expands to (call 'meth this ... )
;;; @? macro
;;;     Form:  @?(meth ... )      Expands to (?call 'meth this ... )
;;; #@ macro
;;;     Form:  #@meth             Expands to (meth-func 'meth this)

