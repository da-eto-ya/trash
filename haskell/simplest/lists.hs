main :: IO ()
main = putStrLn "lists"

addTwoElements :: a -> a -> [a] -> [a]
addTwoElements x y = (x :) . (y :)

nTimes:: a -> Int -> [a]
nTimes x c = take c xs where xs = x : xs
