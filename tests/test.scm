#|
multiline
comment
|#

"string with special \n \t chars"

; comment
(define (fn a)
  (let* ((b (+ a 1)))
    (if (= a 1)
        #t
        #f))) ;; another comment

(define c (lambda (x)
            (let loop ((i 0))
              (unless (= i 10)
                      ;; print some chars
                      (display #\' #\#)
                      (loop (+ i 1))))))

((if (= 0 0) * +) 5 2)

;; numbers
(define pi 3.14159)

(define circle-area
    (lambda (radius)
      (* pi radius radius)))

(define (circle-area radius)
    (* pi radius radius))

(define (blah)
  (define (foo) 55)
  (define (woo) 42)
  (+ (foo) (woo)))

(define (repeat-forever)
  (display "I will not play with Scheme in class.")
  (repeat-forever))

(define (all-atoms-are-numeric? tree)
  (call-with-current-continuation
   (lambda (return)                     ;bind RETURN to the current cont

     (define (walk tree)
       (cond ((null? tree))
             ((pair? tree)              ;pair? is like consp
              (walk (car tree))
              (walk (cdr tree)))
             ((number? tree))
             (else (return #f))))       ;found a non-number -- return false

     (walk tree)
     #t)))                              ;else return true


(cond ((number? x) "A number.")
      ((string? x) "A string.")
      (else "Beats me!"))

(cond ((assoc key a-list) => cdr)
      (else #f))


(letrec ((even? (lambda (n) (if (= n 0) #t (odd? (- n 1)))))
         (odd?  (lambda (n) (if (= n 0) #f (even? (- n 1))))))
  (even? 42))


(let counting ((n 10))
  (cond ((< 0 n)
         (write n)
         (counting (- n 1)))))


(define (list . arguments) arguments)

(define-syntax my-or
  (syntax-rules ()
    ((my-or) #f)
    ((my-or e) e)
    ((my-or e1 e2 ...)
     (let ((temp e1))
       (if temp temp (my-or e2 ...))))))

(define-syntax syntax-rules
  (lambda (x)
    (syntax-case x ()
      ((_ (i ...) ((keyword . pattern) template) ...)
       (syntax (lambda (x)
                 (syntax-case x (i ...)
                   ((dummy . pattern) (syntax template))
                   ...)))))))
