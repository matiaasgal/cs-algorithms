#lang scheme
(define L (list
        (list -33.44003296183172 -70.61985298758073 'B)
        (list -33.43426713209184 -70.62289747871729 'B)
        (list -33.43006349423838 -70.63708488612306 'B)
        (list -33.43803004119132 -70.64337573667652 'B)
        (list -33.44619373563781 -70.64086113904358 'B)
        (list -33.4257103678636 -70.64422322724718 'M)
        (list -33.41923507168084 -70.64103602664417 'M)
        (list -33.43046006207341 -70.62414358121895 'M)
        (list -33.42351439001992 -70.62269166979385 'M)
        (list -33.4168318250916 -70.63589592464307 'M)
        (list -33.4363021804775 -70.65375907580642 'F)
        (list -33.4438710243915 -70.64710750632044 'F)
        (list -33.444237981853355 -70.64034599349185 'F)
        (list -33.44056833738342 -70.63396928220634 'F)
        (list -33.4266222728644 -70.64040096514086 'F)
        (list -33.44373218727798 -70.6559948895669 'A)
        (list -33.454198732825525 -70.66467498831103 'A)
        (list -33.46148718802316 -70.65325085835102 'A)
        (list -33.45443234666258 -70.64356274813983 'A)
        (list -33.44644239614436 -70.64585877425924 'A)))

; para validar que es una coordenada
(define valid_coord?
  (lambda (x)
    (number? x)))

; validar que se recibe un punto valido de tipo lista y que tiene coordenadas X e Y numericas
(define valid_point?
  (lambda (P)
    (and (list? P)
         (not (null? P))
         (not (null? (cdr P)))
         (number? (car P))
         (number? (car (cdr P))))))

; distancia euclidiana solicitada en el enunciado del trabajo
(define euclidian_distance
  (lambda (P Q)
    (cond
      ((not (valid_point? P)) (display "El primer punto dado no cuenta con las coordenadas validas"))
      ((not (valid_point? Q)) (display "El segundo punto dado no cuenta con las coordenadas  validas"))
      (else
       (sqrt (+ (expt (- (car P) (car Q)) 2)
                (expt (- (car (cdr P)) (car (cdr Q))) 2)))))))

; distancia de manhattan, esta es la distancia que consideramos para la resolucion del problema
(define distance
  (lambda (P Q)    
    (cond
      ((not (valid_point? P)) (display "El primer punto dado no cuenta con coordenadas validas"))
      ((not (valid_point? Q)) (display "El segundo punto dado no cuenta con coordenadas validas"))
      (else
       (+ (abs (- (car P) (car Q))) (abs (- (car (cdr P)) (car (cdr Q)))))))))

; crea un punto 
(define create_point
 (lambda (x y)
  (if (and (valid_coord? x)
           (valid_coord? y)) (list x y)
                            (display "Las coordenadas dadas no son validas"))))

; comparar coordenadas de 2 puntos
(define comp
  (lambda (P Q)
    (cond
      ((< (car P) (car Q)) P) ; si el x de P es menor, retorna P
      ((> (car P) (car Q)) Q) ; si el x de P es mayor, retorna Q
      (else ; caso donde ambos puntos son iguales en x. En caso de tener misma y, retorna Q siendo igual al P
       (if (< (car (cdr P)) (car (cdr Q))) P Q)))))
 
; retorna el mejor p0 entre 2 puntos (punto de menor latitud y longitud)
(define best_p0?
  (lambda (P Q)
    (cond
      ((not (valid_point? P)) (display "El primer punto dado no cuenta con las coordenadas validas"))
      ((not (valid_point? Q)) (display "El segundo punto dado no cuenta con las coordenadas validas"))
      (else
       (comp P Q)))))

; recorre la lista y retorna el mejor p0
(define list_loop
  (lambda (L temp-point)
    (cond
      ((null? L) temp-point)
      ((not (valid_point? (car L))) (display "La lista no cuenta con el formato valido"))
      (else
       (let* ((new-p0 (car L))
             (final-p0 (best_p0? temp-point new-p0)))
         (list_loop (cdr L) final-p0))))))

; recibe el mejor p0 de la lista
(define get_p0
  (lambda (L)
    (cond
      ((null? L) (display "La lista se encuentra vacia"))
      ((not (valid_point? (car L))) (display "La lista no cuenta con el formato valido"))
      (else
       (let* ((temp-point (car L))
            (p0 (list_loop (cdr L) temp-point)))
         p0)))))

; evalua la orientacion y retorna un numero positivo si b esta a la izquierda de a 
(define left?
  (lambda (act A B)
    (cond
      ((or (not (valid_point? A))
            (not (valid_point? B))) (display "Existe un error de validez en los puntos de la circunvalacion"))
      (else
       (- (* (- (car A) (car act)) (- (car (cdr B)) (car (cdr act))))
          (* (- (car (cdr A)) (car (cdr act))) (- (car B) (car act))))))))

; busca el punto mas a la izquierda desde la posicion actual
(define search_best
  (lambda (L act best)
    (cond
      ((null? L) best)
      ((equal? (car L) act) (search_best (cdr L) act best))
      (else
       (let ((possible (car L)))
         (if (> (left? act best possible) 0) (search_best (cdr L) act possible)
             (search_best (cdr L) act best)))))))

; funcion auxiliar recursiva para encontrar todos los nodos de la envolvente convexa
(define convexhull_helper
  (lambda (L act p0 result)
    (let* ((initial-best (if (equal? (car L) act) (car (cdr L)) (car L)))
           (next (search_best L act initial-best)))
      (if (equal? next p0)
          (cons (list (car act) (car (cdr act)) (car p0) (car(cdr p0))) result)
          (let ((actual-seg (list (car act) (car (cdr act)) (car next) (car (cdr next)))))
            (convexhull_helper L next p0 (cons actual-seg result)))))))

; ejecuta el algoritmo de jarvis
(define convexhull
  (lambda (L)
    (cond
      ((null? L) (display "La lista se encuentra vacia"))
      ((not (valid_point? (car L))) (display "La lista no cuenta con el formato valido"))
      (else
       (let* ((p0 (get_p0 L)))
         (display "La envolvente convexa esta dada por: ")
         (newline)
         (convexhull_helper L p0 p0 '()))))))


; funcion auxiliar recursiva para encontrar la menor distancia
(define min_dist_helper
  (lambda (L P first-dist first-point)
    (cond
      ((null? L) (list first-point first-dist))
      ((not (valid_point? (car L))) (display "La lista no cuenta con el formato valido"))
      (else
       (let ((new-dist (distance (car L) P))
             (new-point (car L)))
         (if (< new-dist first-dist) (min_dist_helper (cdr L) P new-dist new-point)
             (min_dist_helper (cdr L) P first-dist first-point)))))))

; muestra la menor distancia entre un punto dado y uno existente ademas de mostrar el punto mismo (el existente)
(define min_dist
  (lambda (L x y)
    (cond
      ((null? L) (display "La lista se encuentra vacia"))
      ((not (valid_point? (car L))) (display "La lista no cuenta con el formato valido"))
      ((not (and (valid_coord? x)(valid_coord? y))) (display "Las coordenadas no son validas"))
      (else
       (let* ((P (create_point x y))
              (first-point (car L))
              (first-dist (distance (car L) P))
              (final-list (min_dist_helper (cdr L) P first-dist first-point)))
         (newline)
         (display "La menor distancia es de: ")
         (display (car (cdr final-list)))
         (newline)
         (display "Siendo el punto mas cercano: ")
         (display (car final-list)))))))

;-----------------------------------------------------------------------------------------------------------------------------------

(convexhull L)
(min_dist L -33.44644239614436 -70.64585877425924) ; punto dentro de la lista, debe retornar distancia 0