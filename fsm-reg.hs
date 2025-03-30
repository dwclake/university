module Fsm_Reg where

-- Regular Expression functions

import Data.List (sort, inits, tails, stripPrefix, foldl', -- for my code
                  isPrefixOf, isSuffixOf, isInfixOf)       -- for your code

-- Fixed alphabet, but everything below should work for any sigma!
sigma :: [Char]
sigma = "ab"

---------------- General list functions

-- Normalize a list: sort and remove duplicates
norm :: Ord a => [a] -> [a]
norm xs = rad $ sort xs where
  rad :: Eq a => [a] -> [a]  -- Remove adjacent duplicates
  rad [] = []
  rad [x] = [x]
  rad (x:ys@(y:zs)) | x == y = rad ys
                    | otherwise = x : rad ys

-- Cartesian product, preserves normalization
cart :: [a] -> [b] -> [(a,b)]
cart xs ys = [(x,y) | x <- xs, y <- ys]

-- Powerset, preserves normalization
power :: [a] -> [[a]]
power [] = [[]]
power (x:xs) = let ys = power xs
               in [] : map (x:) ys ++ tail ys

-- Check whether two lists overlap
overlap :: Eq a => [a] -> [a] -> Bool
overlap [] ys = False
overlap (x:xs) ys = elem x ys || overlap xs ys

-- splits xs = list of all possible splits of xs, in order. For example,
-- splits "abc" = [("","abc"), ("a","bc"), ("ab","c"), ("abc","")]
splits :: [a] -> [([a], [a])]
splits xs = zip (inits xs) (tails xs)



---------------- Length-ordered lists

-- Length-Ordered Lists over "character type" a (aka "strings")
-- Invariant: In LOL n xs, n == length xs
data LOL a = LOL Int [a] deriving (Eq,Ord)

-- Show instance doesn't print LOL constructor or length
instance Show a => Show (LOL a) where
  show (LOL n xs) = show xs

-- Empty list (epsilon)
eps :: LOL a
eps = LOL 0 []

-- Smart constructor for LOL a, establishes invariant
lol :: [a] -> LOL a
lol xs = LOL (length xs) xs

-- Concatenation of LOLs, preserves invariant
dot :: LOL a -> LOL a -> LOL a
dot xs (LOL 0 _) = xs                            -- special case, for efficiency
dot (LOL n xs) (LOL m ys) = LOL (n+m) (xs++ys)   -- general case

-- Reverse of LOLs, preserves invariant
rev :: LOL a -> LOL a
rev (LOL n xs) = LOL n (reverse xs)


---------------- Languages

-- Normalized lists of LOLs (aka "languages"), possibly infinite
-- Invariant: xs :: Lang a implies xs is sorted with no duplicates
type Lang a = [LOL a]


-- Smart constructor for (finite) languages, establishes invariant
lang :: Ord a => [[a]] -> Lang a
lang xs = norm $ map lol xs

-- Membership for languages (infinite lists satisfying invariant included)
memb :: Ord a => LOL a -> Lang a -> Bool
memb _ [] = False
memb x (y:ys) =
  case compare x y of
    LT -> False
    EQ -> True
    GT -> memb x ys
                           
-- Merge of langages (aka "union")
merge :: Ord a => Lang a -> Lang a -> Lang a
merge [] ys = ys
merge xs [] = xs
merge xs@(x:xr) ys@(y:yr) =
  case compare x y of
    LT -> x : merge xr ys
    EQ -> x : merge xr yr
    GT -> y : merge xs yr

-- Concatenation of languages
cat :: Ord a => Lang a -> Lang a -> Lang a
cat [] _ = []
cat _ [] = []
cat (x:xr) ys@(y:yr) = dot x y : merge (map (dot x) yr) (cat xr ys)

-- Kleene star of a language
kstar :: Ord a => Lang a -> Lang a
kstar [] = [eps]
kstar (LOL 0 []:xr) = kstar xr
kstar xs = eps : cat xs (kstar xs)

-- Left quotient of a language by a string
leftq :: Ord a => LOL a -> Lang a -> Lang a
leftq _ [] = []
leftq w@(LOL n xs) (LOL m ys:yss)
  | n <= m = case stripPrefix xs ys of
      Nothing -> leftq w yss
      Just zs -> LOL (m-n) zs : leftq w yss
  | otherwise = leftq w yss
        
-- Nonempty part of a language
nep [] = []
nep (LOL 0 [] : xs) = xs  -- remove empty string, which must be first
nep xs = xs


-- All strings of length <= n over an alphabet sigma, in LOL order
-- Useful for testing
strings :: Int -> [Char] -> [String]
strings n sigma = concat [strs i | i <- [0..n]] where
  strs 0 = [""]
  strs n = [a:xs | a <- sort sigma, xs <- strs (n-1)]


---- Regular expressions and the languages they denote 
data RegExp = Empty                -- Empty language
            | Let Char             -- Single letter language
            | Union RegExp RegExp  -- Union
            | Cat RegExp RegExp    -- Concatenation
            | Star RegExp          -- Kleene star
            deriving (Show, Eq)

-- Compact display form for RegExp
newtype Compact = Compact RegExp

instance (Show Compact) where    -- use precedence to minimize parentheses
  showsPrec d (Compact r) = sp d r where
    sp d Empty         = showString "0"
    sp d (Let c)       = showString [c]
    sp d (Union r1 r2) = showParen (d > 6) $  -- prec(Union) = 6
                         sp 6 r1 .
                         showString "+" .
                         sp 6 r2
    sp d (Cat r1 r2)   = showParen (d > 7) $  -- prec(Cat) = 7
                         sp 7 r1 .
                         sp 7 r2
    sp d (Star Empty)  = showString "1"
    sp d (Star r1)     = sp 9 r1 .     -- prec(Star) = 8
                         showString "*"


-- Quick and dirty postfix RegExp parser, gives non-exaustive match on error
-- Allows 1 to be used as an input form for 0*
toRE :: String -> RegExp
toRE w = go w [] where
  go [] [r]              = r
  go ('+':xs) (r2:r1:rs) = go xs (Union r1 r2:rs)
  go ('.':xs) (r2:r1:rs) = go xs (Cat r1 r2:rs)
  go ('*':xs) (r:rs)     = go xs (Star r:rs)
  go ('0':xs) rs         = go xs (Empty:rs)
  go ('1':xs) rs         = go xs (Star Empty:rs)
  go (x:xs) rs           = go xs (Let x:rs)   -- everything else is a letter


-- The language associated to (aka denotation of) a regular expression: [[r]]
lang_of :: RegExp -> Lang Char
lang_of Empty = []
lang_of (Let a) = lang [[a]]
lang_of (Union r1 r2) = merge (lang_of r1) (lang_of r2)
lang_of (Cat r1 r2) = cat (lang_of r1) (lang_of r2)
lang_of (Star r1) = kstar (lang_of r1)


-- The one-string and finite languages of Theorem 3.2.
onestr :: String -> RegExp
onestr [] = Star Empty
onestr [x] = Let x
onestr (x:xs) = Cat (Let x) (onestr xs)

finite :: [String] -> RegExp
finite [] = Empty
finite [w] = onestr w
finite (w:ws) = Union (onestr w) (finite ws)


-- Some recursive functions on regular expressions

-- Empty
emptyr :: RegExp -> Bool
emptyr Empty = True
emptyr (Let _) = False
emptyr (Union r1 r2) = emptyr r1 && emptyr r2
emptyr (Cat r1 r2) = emptyr r1 || emptyr r2
emptyr (Star r1) = False
  
-- Unitary
unitr :: RegExp -> Bool
unitr Empty = False
unitr (Let _) = False
unitr (Union r1 r2) =
  unitr r1 && (emptyr r2 || unitr r2) || emptyr r1 && unitr r2
unitr (Cat r1 r2) = unitr r1 && unitr r2
unitr (Star r1) = emptyr r1 || unitr r1
  
-- Bypassable
bypr :: RegExp -> Bool
bypr Empty = False
bypr (Let _) = False
bypr (Union r1 r2) = bypr r1 || bypr r2
bypr (Cat r1 r2) = bypr r1 && bypr r2
bypr (Star r1) = True
  
-- Infinite
infr :: RegExp -> Bool
infr Empty = False
infr (Let _) = False
infr (Union r1 r2) = infr r1 || infr r2
infr (Cat r1 r2) =
  infr r1 && not (emptyr r2) || not (emptyr r1) && infr r2
infr (Star r1) = not (emptyr r1) && not (unitr r1)
  
-- Reverse
revr :: RegExp -> RegExp
revr Empty = Empty
revr (Let c) = Let c
revr (Union r1 r2) = Union (revr r1) (revr r2)
revr (Cat r1 r2) = Cat (revr r2) (revr r1)
revr (Star r1) = Star (revr r1)
  
-- Left quotient (by a letter)
leftqr :: Char -> RegExp -> RegExp
leftqr s Empty = Empty
leftqr s (Let c) = if s == c then Star Empty else Empty
leftqr s (Union r1 r2) = Union (leftqr s r1) (leftqr s r2)
leftqr s (Cat r1 r2) | bypr r1 = Union (Cat (leftqr s r1) r2) (leftqr s r2)
                     | otherwise = Cat (leftqr s r1) r2
leftqr s (Star r1) = Cat (leftqr s r1) (Star r1)

-- Non-empty part
nepr :: RegExp -> RegExp
nepr Empty = Empty
nepr (Let c) = Let c
nepr (Union r1 r2) = Union (nepr r1) (nepr r2)
nepr (Cat r1 r2) = Union (Cat (nepr r1) r2) (Cat r1 (nepr r2))
nepr (Star r1) = Cat (nepr r1) (Star r1)


-- Matching algorithm 1
match1 :: RegExp -> String -> Bool
match1 Empty _ = False
match1 (Let c) w = w == [c]
match1 (Union r1 r2) w = match1 r1 w || match1 r2 w
match1 (Cat r1 r2) w = any (\(w1,w2) -> match1 r1 w1 && match1 r2 w2) (splits w)
match1 (Star r) w = null w ||
  any (\(w1,w2) -> match1 r w1 && match1 (Star r) w2) (tail $ splits w)

-- Matching algorithm 2
match2 :: RegExp -> String -> Bool
match2 r w = m [r] False w where
  m :: [RegExp] -> Bool -> String -> Bool  -- for c, False is 0, True is 1
  m [] c w = not c && null w
  m (Empty : rs) c w = False
  m (Let a : rs) c [] = False
  m (Let a : rs) c (x:xs) = a == x && m rs False xs
  m (Union r1 r2 : rs) c w = m (r1:rs) c w || m (r2:rs) c w
  m (Cat r1 r2 : rs) c w = m (r1:r2:rs) c w || c && bypr r1 && m (r2:rs) c w
  m (Star r1 : rs) c w = not c && m rs c w || m (r1:Star r1:rs) True w
