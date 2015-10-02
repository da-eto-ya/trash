import Data.Char

twoDigits2Int :: Char -> Char -> Int
twoDigits2Int x y = if isDigit x && isDigit y then digitToInt x * 10 + digitToInt y else 100

dist :: (Double, Double) -> (Double, Double) -> Double
dist x y = sqrt $ (fst x - fst y) ^ 2 + (snd x - snd y) ^ 2

doubleFact :: Integer -> Integer
doubleFact 1 = 1
doubleFact 2 = 2
doubleFact n = n * doubleFact (n - 2)

fibonacci :: Integer -> Integer
fibonacci = fibonacci' 0 1 where
  fibonacci' :: Integer -> Integer -> Integer -> Integer
  fibonacci' f1 _  0 = f1
  fibonacci' _  f2 1 = f2
  fibonacci' f1 f2 n | n > 0 = fibonacci' f2 (f1 + f2) (n - 1)
                     | n < 0 = fibonacci' (f2 - f1) f1 (n + 1)

main :: IO ()
main = putStrLn "hello"
