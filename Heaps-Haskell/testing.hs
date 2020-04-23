import Heap
import qualified Leftist as L
import qualified Skew as S
import qualified Pairing as P
import qualified Binomial as B

newtype RPI = RPI { toInt :: Int }
    deriving (Eq)

instance Ord RPI where
    (RPI x) <= (RPI y) = y <= x

instance Show RPI where
    show (RPI x) = show x

s :: [Int]
-- s = [21, 15, 24, 38, 25]
s = [3, 7, 18, 13, 32, 55, 51, 29, 25, 12, 16, 73]

h :: (Ord a) => [a] -> P.Pairing a
h xs = foldl (\r x -> merge (singleton x) r) empty xs