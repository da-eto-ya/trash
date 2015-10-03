import Data.Char

twoDigits2Int :: Char -> Char -> Int
twoDigits2Int x y = if isDigit x && isDigit y then digitToInt x * 10 + digitToInt y else 100

dist :: (Double, Double) -> (Double, Double) -> Double
dist x y = sqrt $ (fst x - fst y) ^ (2 :: Int) + (snd x - snd y) ^ (2 :: Int)

doubleFact :: Integer -> Integer
doubleFact 1 = 1
doubleFact 2 = 2
doubleFact n = n * doubleFact (n - 2)

fibonacci :: Integer -> Integer
fibonacci = fibonacci' 0 1 where
  fibonacci' :: Integer -> Integer -> Integer -> Integer
  fibonacci' f1 _  0 = f1
  fibonacci' _  f2 1 = f2
  fibonacci' f1 f2 n | n > 0     = fibonacci' f2 (f1 + f2) (n - 1)
                     | otherwise = fibonacci' (f2 - f1) f1 (n + 1)

seqA :: Integer -> Integer
seqA n = let
    seqA' a0 _  _  0 = a0
    seqA' _  a1 _  1 = a1
    seqA' _  _  a2 2 = a2
    seqA' a0 a1 a2 k = seqA' a1 a2 (a2 + a1 - 2 * a0) (k - 1)
  in seqA' 1 2 3 n

sum'n'count :: Integer -> (Integer, Integer)
sum'n'count = sum'n'count' 0 1 where
  sum'n'count' s c n | n < 0     = sum'n'count' s c (-n)
                     | n >= 10   = sum'n'count' (s + n `mod` 10) (c + 1) (n `div` 10)
                     | otherwise = (s + n, c)

integration :: (Double -> Double) -> Double -> Double -> Double
integration f a b | a > b     = -integration f b a
                  | a == b    = 0
                  | otherwise = sum' 0 n where
  n = 1000
  sum' acc 0 = acc
  sum' acc k = sum' (acc + f xi * dx) (k - 1) where
    xi = (x k + x (k - 1)) / 2
    dx = x k - x (k - 1)
    x m = a + (m / n) * (b - a)

main :: IO ()
main = putStrLn "hello"
