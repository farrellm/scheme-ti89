
# Scheme 68k
Scheme for the TI-89
versions .1

This is the beginnings of a Scheme interpreter for TI-89 and TI-92+ calculators.  Current support is limited, but more will be coming soon.

If you are unfamiliar with Scheme, it is a dialect of LISP and is probably best known for being the language taught in 6.001, the intro computer science course at MIT.  For more information on Scheme, see:
 http://sicp.ai.mit.edu/Spring-2004/handouts-and-documentation.html
 http://mitpress.mit.edu/sicp/full-text/book/book.html

To use: send appropriate files to your calculator (in the bin directory), write a Scheme program in a calculator text file named "scmprog" and run scheme()
Note that nothing is displayed automatically, you must use the "print" procedure to display results.

Features:
- Definition and reassignment of variables.
- lambda
- sugared lambda definitions (see example 3)
- integer, floating point, and string data types
- let
- quote (' quoting coming soon)
- if and cond
- begin
- primitives: +, -, *, =, print, newline

Limitations:
- No cons, car, cdr (yet, coming soon)
- Very few primitive procedures
- No rational number support
- Initialization and parsing are slow

Warning: Testing is limited to my TI-89, which is AMS 2.05, HW 1, and
overclocked.  Furthermore, dynamic memory is used extensively.
Therefore, you should back-up your calculator before trying Scheme.
Please let me know of any problems you encounter so I can try to fix
them.  Finally, I am not responsible for any damage to your calculator
or loss of information.

Example programs:

1.

```
(print "6001 at mit")
(newline)
(define x (+ 2 3))
(print x)
```

2.

```
(define x ((lambda (z)(+ 1 z)) 6000))
(print x)
```

3.

```
(define (square x)(* x x))
(define y (square 5))
(print (- y 2))
```

## Acknowledgements:

Thank you to Professor Eric Grimson and everyone who
contributed to the source code for the meta-circular evaluator, I
could not have written this without you.