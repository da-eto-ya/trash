import Data.List
import Data.Function

main :: IO ()
main = interact (run . map read . words)

run :: [Int] -> String
run (n:xs) = out (solve (pairs xs)) where
  -- show result
  out :: [Int] -> String
  out ys = unlines [show (length ys), unwords (map show ys)]
  -- form input
  pairs :: [Int] -> [(Int, Int)]
  pairs []       = []
  pairs (x:y:zs) = (x, y) : pairs zs
  -- solution
  solve :: [(Int, Int)] -> [Int]
  solve ps = solve' (sortBy (compare `on` snd) ps) [] where
    solve' []          acc = acc
    solve' ((_, s):us) acc = solve' (filter (\u -> fst u > s || snd u < s) us) (s:acc)
