{-# Language InstanceSigs #-}

module Skew where

import Heap
import BinTree

newtype Skew a = Skew { toTree :: BinTree a }
    deriving (Eq, Show)

instance Heap Skew where
    empty :: (Ord a) => Skew a
    empty = Skew Empty

    singleton :: (Ord a) => a -> Skew a
    singleton x = Skew (Node x Empty Empty)

    add :: (Ord a) => a -> Skew a -> Skew a
    add x h = merge (singleton x) h

    merge :: (Ord a) => Skew a -> Skew a -> Skew a
    merge (Skew t1) (Skew t2) = Skew $ 
                                    case t1 of
                                        Empty -> t2
                                        Node x1 l1 r1 -> case t2 of
                                            Empty -> t1
                                            Node x2 l2 r2 -> if min x1 x2 == x1 
                                                                then Node x1 (toTree $ merge (Skew r1) (Skew t2)) l1
                                                                else Node x2 (toTree $ merge (Skew r2) (Skew t1)) l2

    peek :: (Ord a) => Skew a -> Maybe a
    peek (Skew Empty) = Nothing
    peek (Skew (Node x _ _)) = Just x

    pop :: (Ord a) => Skew a -> Maybe (Skew a)
    pop (Skew Empty) = Nothing
    pop (Skew (Node x l r)) = Just $ merge (Skew l) (Skew r)
                                                    
fromList :: (Ord a) => [a] -> Skew a
fromList xs = foldl merge empty (map singleton xs)