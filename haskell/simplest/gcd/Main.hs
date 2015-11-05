module Main (main) where

import Prelude hiding (gcd)

gcd :: [Int] -> Int
gcd []           = 0
gcd [x]          = x
gcd (x : y : xs) = gcd $ gcd' x y : xs where
  gcd' 0 b = b
  gcd' a 0 = a
  gcd' a b  | a >= b    = gcd' (a `mod` b) b
            | otherwise = gcd' a (b `mod` a)

main :: IO ()
main = interact (show . gcd . map read . words)
