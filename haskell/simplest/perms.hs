import Data.List

comb :: Int -> [Int] -> [[Int]]
comb 0 _  = [[]]
comb _ [] = []
comb m xs = concatMap (\x -> map (x:) (comb (m-1) (delete x xs))) xs

readInts :: IO [Int]
readInts = fmap (map read . words) getLine

listToString :: Show a => [a] -> String
listToString xs = unwords (map show xs)

main :: IO ()
main = do
    [n, k] <- readInts
    mapM_ (putStrLn . listToString) (comb k [0..n-1])

