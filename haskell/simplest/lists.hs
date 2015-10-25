main :: IO ()
main = putStrLn "lists"

addTwoElements :: a -> a -> [a] -> [a]
addTwoElements x y = (x :) . (y :)
