comb :: Int -> [a] -> [[a]]
comb 0 _      = [[]]
comb _ []     = []
comb m (x:xs) = map (x:) (comb (m-1) xs) ++ comb m xs

readInts :: IO [Int]
readInts = fmap (map read . words) getLine

listToString :: Show a => [a] -> String
listToString xs = unwords (map show xs)

main :: IO ()
main = do
    [k, n] <- readInts
    mapM_ (putStrLn . listToString) (comb k [0..n-1])

