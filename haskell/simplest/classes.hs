class Printable a where
  toString :: a -> String

instance Printable Bool where
  toString True  = "true"
  toString False = "false"

instance Printable () where
  toString () = "unit type"

instance (Printable a, Printable b) => Printable (a, b) where
  toString (x, y) = "(" ++ toString x ++ "," ++ toString y ++ ")"

class (Enum a, Eq a, Bounded a) => SafeEnum a where
  ssucc :: a -> a
  ssucc x | x == maxBound = minBound
          | otherwise     = succ x

  spred :: a -> a
  spred x | x == minBound = maxBound
          | otherwise     = pred x

instance SafeEnum Char

avg :: Int -> Int -> Int -> Double
avg x y z = (/3) $ sum $ map fromIntegral [x, y, z]

main :: IO ()
main = putStrLn (
  toString True ++ " : " ++
  toString False ++ " : " ++
  toString () ++ " : " ++
  toString ((), False) ++ " : " ++
  show (spred '\NUL') ++ " : " ++
  show (avg 3 4 5)
  )
