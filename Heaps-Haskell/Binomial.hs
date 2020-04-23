{-# Language InstanceSigs #-}

module Binomial where

import Heap
import Tree
import Data.List (sort, sortOn)

newtype BT a = BT { toTree :: Tree a }

instance Show a => Show (BT a) where
    show (BT t) = show t

mkBT :: a -> BT a
mkBT x = BT $ Node x []

order :: BT a -> Int
order (BT Empty)      = -1
order (BT (Node x r)) = length r

newtype Binomial a = Binomial { toBTs :: [BT a] }
    deriving (Eq)

instance Eq (BT a) where
    t == s = order t == order s

instance Ord (BT a) where
    t <= s = order t <= order s

instance Show a => Show (Binomial a) where
    show (Binomial bts) = "Binomial" ++ (foldr (\x r -> ('\n' : show x) ++ r) [] bts)

instance Heap Binomial where
    empty :: (Ord a) => Binomial a
    empty = Binomial []

    singleton :: (Ord a) => a -> Binomial a
    singleton x = Binomial [BT $ Node x []]

    add :: (Ord a) => a -> Binomial a -> Binomial a
    add x h = merge (singleton x) h

    merge :: (Ord a) => Binomial a -> Binomial a -> Binomial a
    merge (Binomial []) h = h
    merge h (Binomial []) = h
    merge (Binomial xs) (Binomial ys) = mergeBTs (xs ++ ys)

    peek :: (Ord a) => Binomial a -> Maybe a
    peek (Binomial []) = Nothing
    peek (Binomial ts) = let (Node x r) = maximum $ map toTree ts
                         in Just x

    pop :: (Ord a) => Binomial a -> Maybe (Binomial a)
    pop (Binomial []) = Nothing
    pop (Binomial ts) =  let (h, rest) = (head (sortOn toTree ts), tail (sortOn toTree ts))
                         in case h of
                                BT Empty       -> Nothing
                                BT (Node x cs) -> Just $ mergeBTs $ (map BT cs) ++ rest
                            
mergeBTs :: (Ord a) => [BT a] -> Binomial a
mergeBTs = Binomial . mergeWrapper

mergeWrapper :: (Ord a) => [BT a] -> [BT a]
mergeWrapper = sort . mergeHelper . sort

mergeHelper :: (Ord a) => [BT a] -> [BT a]
mergeHelper []  = []
mergeHelper [t] = [t]
mergeHelper (t:s:ts) | t == s    = mergeHelper $ propogate (merge2 t s) ts
                     | otherwise = t : mergeHelper (s : ts)
                        where 
                            merge2 (BT t) (BT s) = BT $ 
                                                        case (t, s) of
                                                            (Empty, _) -> s
                                                            (_, Empty) -> t
                                                            ((Node x1 r1), (Node x2 r2)) -> 
                                                                if x1 <= x2 
                                                                then Node x1 (r1 ++ [s])
                                                                else Node x2 (r2 ++ [t])
                            propogate u []     = [u]
                            propogate u (v:vs) = if u <= v 
                                                 then u : v : vs
                                                 else v : (propogate u vs)

fromList :: (Ord a) => [a] -> Binomial a
fromList xs = mergeBTs $ map mkBT xs