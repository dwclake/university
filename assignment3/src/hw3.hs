module Main where

import FLang

main :: IO ()
main = putStrLn "Hello, Haskell!"


{-

ghci> Compact ex412re
aa*(bbb*a(b+1)+bab+ba+b)+bb*a(b+1)
ghci> m@(qs, s, fs, d) = minimize $ reachable $ nfsm_to_fsm $ glushkov ex412re
ghci> qs
[[[]],[[0,13]],[[1,2,7,10,12]],[[3,8,11,17]],[[4,5],[14,15]],[[6,17],[9,17],[16,17]],[[17]]]
ghci> length qs
7
ghci> (j, k, l, i) = intify m
ghci> j
[0,1,2,3,4,5,6]
ghci> i 1 'a'
2
ghci> i 2 'a'
2
ghci> i 2 'b'
3
ghci> i 3 'b'
4
ghci> i 4 'a'
5
ghci> i 4 'b'
4
ghci> i 5 'b'
6
ghci> i 6 'a'
0
ghci> r = fsm_to_re' (j, k, l, i)
ghci> Compact $ fromRE' r
aa*b+aa*ba+aa*bab+aa*bbb*a+aa*bbb*ab+bb*a+bb*ab

-}
ex412re :: RegExp
ex412re = toRE "aa*.bb.b*.a.b1+.ba.b.+ba.+b+.bb*.a.b1+.+"