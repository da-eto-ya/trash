module Fib3 (
  main
) where

fibs :: Int -> [Int]
fibs m = 0 : 1 : next (fibs m) where
  next (x : p@(y : _)) = (x + y) `mod` m : next p

main :: IO ()
main = do
  x <- readLn :: IO Int
  m <- readLn :: IO Int
  mapM_ print $ take x $ fibs m
