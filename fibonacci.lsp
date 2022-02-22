(defglobal sum-of-even-fibonaccis 0)

(defun fibonacci-pair (n)
  (if (= n 3)
      '(1 . 2)
    (let ((prev (fibonacci-pair (- n 1))))
      (cons 
       (cdr prev)
       (+ (car prev) (cdr prev))))))
  
(defun fibonacci (n)
  (let ((pair (fibonacci-pair n)))
    (+ (car pair) (cdr pair))))


(defun naive-fibonacci (n)
  (cond ((= n 1) 1)
        ((= n 2) 2)
        (t (+ (naive-fibonacci (- n 2))
              (naive-fibonacci (- n 1))))))

(defun even (n) (= (mod n 2) 0))

(defun fibonacci-triple (n)
  (if (< n 3) (error "bad"))
  (if (= n 3)
      '(1 2 2)
    (let* ((prev (fibonacci-triple (- n 1)))
           (next-number (+ (first prev) (second prev))))
      (list (second prev)
            next-number
            (+ (third prev)
               (if (even next-number) next-number 0))))))

(defun fibonacci-and-sum-of-evens (n)
  (let* ((triple (fibonacci-triple n))
         (fib (+ (first triple) (second triple))))
    (list fib (if (even fib) (+ fib (third triple)) (third triple)))))

(fibonacci-triple 3)
(fibonacci-triple 4)
(fibonacci-triple 5)



