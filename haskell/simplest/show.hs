-- 127.224.120.12

ip :: String
ip = show a ++ show b ++ show c ++ show d where
  a = 127.2
  b = 2
  c = 4.1
  d = 20.12

main :: IO ()
main = putStrLn ip
