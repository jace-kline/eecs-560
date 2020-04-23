{-# Language InstanceSigs #-}

module Leftist where

import Heap
import BinTree

newtype Leftist a = Leftist { toTree :: BinTree a }
    deriving (Eq, Show)

instance Heap Leftist where
    empty :: (Ord a) => Leftist a
    empty = Leftist Empty

    singleton :: (Ord a) => a -> Leftist a
    singleton x = Leftist (Node x Empty Empty)

    add :: (Ord a) => a -> Leftist a -> Leftist a
    add x h = merge (singleton x) h

    merge :: (Ord a) => Leftist a -> Leftist a -> Leftist a
    merge (Leftist t1) (Leftist t2) = Leftist $ 
                                        case t1 of
                                            Empty -> t2
                                            Node x1 l1 r1 -> case t2 of
                                                Empty -> t1
                                                Node x2 l2 r2 -> swapOnRank $
                                                                    if min x1 x2 == x1 
                                                                    then Node x1 l1 $ toTree $ merge (Leftist r1) (Leftist t2)
                                                                    else Node x2 l2 $ toTree $ merge (Leftist r2) (Leftist t1)
        where 
            swapOnRank :: BinTree a -> BinTree a
            swapOnRank Empty = Empty
            swapOnRank (Node x l r) = if rank r > rank l 
                                      then Node x r l 
                                      else Node x l r

    peek :: (Ord a) => Leftist a -> Maybe a
    peek (Leftist Empty) = Nothing
    peek (Leftist (Node x _ _)) = Just x

    pop :: (Ord a) => Leftist a -> Maybe (Leftist a)
    pop (Leftist Empty) = Nothing
    pop (Leftist (Node x l r)) = Just $ merge (Leftist l) (Leftist r)
                                                    
fromList :: (Ord a) => [a] -> Leftist a
fromList xs = foldl merge empty (map singleton xs)