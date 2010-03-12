This is a test
of Haskel literate programming;
Bird style

> fact :: Integer -> Integer
> fact 0 = 1
> fact n = n * fact (n-1)

while this is not considered code
fact :: Integer -> Integer

This is the Latex style

\begin{code}
tsort []     = []
tsort (x:xs) = tsort [y | y<-xs, y>x] ++ [x] ++ tsort [y | y<-xs, y<=x]
\end{code}

and the code will be formatted as you requested.
