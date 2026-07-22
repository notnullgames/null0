;;; simple wisp cart for null0 (experimental)
;;;
;;; wisp cannot currently import null0 host functions; this example shows
;;; what a cart would look like. See null0.wisp for the full API surface.

(defn load ()
  (clear BLUE)
  (draw-circle 100 100 50 RED))

(defn update () 0)
