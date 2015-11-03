module Main where

fib :: Integer -> Integer
fib x = fib' 0 0 1 where
  fib' c f0 f1  | c == x    = f0
                | otherwise = fib' (c+1) f1 (f0 + f1)

main :: IO ()
main = do
  x <- readLn :: IO Integer
  print $ fib x
