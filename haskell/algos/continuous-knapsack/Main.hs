import Text.Printf
import Data.List
import Data.Ord

main :: IO ()
main = interact (printf "%.3f" . run . map read . words)

run :: [Double] -> Double
run (_ : w : xs) = solve w (sortBy (comparing (\(ci, wi) -> - ci / wi)) (pairs xs [])) 0 where
  -- (ci, wi) pairs
  pairs []           acc = acc
  pairs (x : y : ys) acc = pairs ys ((x, y) : acc)
  -- solution
  solve 0  _               acc = acc
  solve _  []              acc = acc
  solve wc ((ci, wi) : ys) acc | wc <= wi  = solve 0 ys (acc + ci * wc / wi)
                               | otherwise = solve (wc - wi) ys (acc + ci)
