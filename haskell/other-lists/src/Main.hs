module Main where

import Data.Char

squares'n'cubes :: Num a => [a] -> [a]
squares'n'cubes = concatMap (\x -> [x * x, x * x * x])

perms :: [a] -> [[a]]
perms [] = [[]]
perms (x:xs) = concatMap (inserts x) $ perms xs where
    inserts x ys = map (\n -> take n ys ++ [x] ++ drop n ys) [0..length ys]

delAllUpper :: String -> String
delAllUpper = unwords . filter (any isLower) . words

max3 :: Ord a => [a] -> [a] -> [a] -> [a]
max3 = zipWith3 (\x y z -> max (max x y) z)

fibStream :: [Integer]
fibStream = zipWith (+) (0:fibStream) (0:1:fibStream)

repeat' :: a -> [a]
repeat' = iterate repeatHelper where
    repeatHelper = id

data Odd = Odd Integer
    deriving (Eq, Show)

instance Enum Odd where
    succ (Odd x) = Odd (x + 2)
    pred (Odd x) = Odd (x - 2)
    toEnum x = Odd (toInteger x)
    fromEnum (Odd x) = fromIntegral x
    enumFrom n = n : enumFrom (succ n)
    enumFromThen n@(Odd x) th@(Odd t) = n : enumFromThen th (Odd (t + t - x))
    enumFromTo n@(Odd x) (Odd y)
        | x <= y    = takeWhile (\(Odd e) -> e <= y) $ enumFrom n
        | otherwise = []
    enumFromThenTo n@(Odd x) th@(Odd t) (Odd y)
        | x <= y && x <= t = takeWhile (\(Odd e) -> e <= y) $ enumFromThen n th
        | x >= y && x > t  = takeWhile (\(Odd e) -> e >= y) $ enumFromThen n th
        | otherwise        = []

coins :: Num a => [a]
coins = [2, 3, 7]

change :: (Ord a, Num a) => a -> [[a]]
change n | n < 0     = []
         | n == 0    = [[]]
         | otherwise = [c : res | c <- coins, res <- change (n - c)]


concatList :: [[a]] -> [a]
concatList = foldr (++) []


lengthList :: [a] -> Int
lengthList = foldr (const (+1)) 0


sumOdd :: [Integer] -> Integer
sumOdd = foldr (+) 0 . filter odd

evenOnly :: [a] -> [a]
evenOnly = foldr (\(n, x) s -> if even n then x:s else s) [] . zip [1..]

lastElem :: [a] -> a
lastElem = foldl1 (flip const)

main = print $ lastElem [2]
