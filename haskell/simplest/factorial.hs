module Main where

factorial :: Integer -> Integer
factorial x = product [1..x]

main :: IO ()
main = do
  x <- readLn :: IO Integer
  print $ factorial x
