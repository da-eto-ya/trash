module Main where

fib :: Int -> Int
fib x = fib' 0 0 1 where
  fib' c f0 f1  | c == x    = f0
                | otherwise = fib' (c+1) f1 ((f0 + f1) `mod` 10)

main :: IO ()
main = do
  x <- readLn :: IO Int
  print $ fib x
