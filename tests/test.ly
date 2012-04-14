\version "2.14.2"

#(define (naturalize-pitch p)
  "Strings should be read"
   (let ((o (ly:pitch-octave p))
         (a (* 4 (ly:pitch-alteration p)))
         ;; alteration, a, in quarter tone steps,
         ;; for historical reasons
         (n (ly:pitch-notename p)))
     (cond
      ((and (> a 1) (or (eq? n 6) (eq? n 2)))
       (set! a (- a 2))
       (set! n (+ n 1)))
      ((and (< a -1) (or (eq? n 0) (eq? n 3)))
       (set! a (+ a 2))
       (set! n (- n 1))))
     (cond
      ((> a 2) (set! a (- a 4)) (set! n (+ n 1)))
      ((< a -2) (set! a (+ a 4)) (set! n (- n 1))))
     (if (< n 0) (begin (set! o (- o 1)) (set! n (+ n 7))))
     (if (> n 6) (begin (set! o (+ o 1)) (set! n (- n 7))))
     (ly:make-pitch o n (/ a 4))))

\header {
  title = "Maple Leaf Rag"
  composer = "Scott Joplin"
  piece = "Tempo di marcia"
  tagline =
    \markup {
      \override #'(box-padding . 1.0) \override #'(baseline-skip . 2.7) \box
      \center-column {
        \small \line { Sheet music from \with-url #"http://www.MutopiaProject.org"
          \line { \teeny www. \hspace #-0.5 MutopiaProject \hspace #-0.5 \teeny .org \hspace #0.5 } 
        }
      }
    }
}

\paper {
  top-margin = 15
  ragged-right = ##t
  system-system-spacing #'padding = #8
  score-system-spacing =
    #'((basic-distance . 12)
       (minimum-distance . 6)
       (padding . 1)
       (stretchability . 12))
}

top =  \relative c' {
 \override TextScript   #'padding = #2
 
 \key as \major
 \time 2/4
 \clef treble
 \partial 8
 r8 \f |
 \repeat volta 2 {
  r16 as' <es' es,> as, c <es es,>8 g,16 |
  <es' es,>16 g, bes <es es,> ~ <es es,>4 |
  r16 as, <es' es,> as, c <es es,>8 g,16 |
  <es' es,>16 g, bes <es es,> ~ <es es,>8 r16 <es es,> |
  r16 as, ces <fes fes,> r16 <es es,> r16 <es es,> |
  r16 as, ces <fes fes,> r16 <es es,> r8 |
  \change Staff = "down"
   \stemUp r16^\p as,,,-( ces as'-) r as-( ces as'-) \stemNeutral |
  \change Staff = "up"
  r16 as-( ces as'-) r as-( ces as'-) |
  }
}

bottom =  \relative c {
 \key as \major
 \time 2/4
 \clef bass
 \partial 8
 <es es,>8 |
 \repeat volta 2 {
  <as as,> <c as es> <c as es> <a a,> |
  <bes bes,> <des g, es> <des g, es> <es, es,> |
  <as as,> <c as es> <c as es> <a a,> |
  <bes bes,> <des g, es> <des g, es> <es, es,> |
  <fes fes,>4 <es es,>8 <es es,> |
  <fes fes,>4 <es es,>8 r |
  \stemDown as,, r as' r \stemNeutral |
  as' r as' r \clef treble |
  }
}

\score {
  \context PianoStaff <<
  \context Staff = "up"
   \applyMusic #unfold-repeats \top 
  \context Staff = "down"
   \applyMusic #unfold-repeats \bottom
 >>
 
  \midi {
    \context {
      \Score tempoWholesPerMinute = #(ly:make-moment 120 4)
    }
    \context {
      \Voice
      \remove Dynamic_performer
    }
  }
  \layout{}
}

