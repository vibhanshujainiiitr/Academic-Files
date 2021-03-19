(princ "Please enter the number: ")
(setq a (read))
  (princ "Number  ") (princ "Square  ") (princ "Square root") 
(dotimes (n a)
  (print n)  (princ "       ")  (prin1 (* n n)) (princ"        ") (princ (sqrt n))
  )


