main :: IO ()
main = putStrLn "lists"

addTwoElements :: a -> a -> [a] -> [a]
addTwoElements x y = (x :) . (y :)

nTimes:: a -> Int -> [a]
nTimes x c = take c xs where xs = x : xs

oddsOnly :: Integral a => [a] -> [a]
oddsOnly []       = []
oddsOnly (x : xs) = if odd x then x : oddsOnly xs else oddsOnly xs

sum3 :: Num a => [a] -> [a] -> [a] -> [a]
sum3 xs ys zs = sum2 (sum2 xs ys) zs where
  sum2 (x:xs) (y:ys) = (x + y) : sum2 xs ys
  sum2 []     ys     = ys
  sum2 xs     []     = xs

groupElems :: Eq a => [a] -> [[a]]
groupElems xs = reverse $ map reverse $ groupElems' xs [] where
  groupElems' []     gs = gs
  groupElems' (x:xs) [] = groupElems' xs [[x]]
  groupElems' (x:xs) (g:gs) =
    if head g == x
      then groupElems' xs ((x:g) : gs)
      else groupElems' xs ([x] : g : gs)

