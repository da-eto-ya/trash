module Main (main) where

import Prelude hiding (gcd)

gcd :: [Int] -> Int
gcd []       = 0
gcd [x]      = x
gcd (x:y:xs) = gcd $ gcd' (abs x) (abs y) : xs where
  gcd' 0 b = b
  gcd' a 0 = a
  gcd' a b = gcd' b (a `rem` b)

main :: IO ()
main = interact (show . gcd . map read . words)
