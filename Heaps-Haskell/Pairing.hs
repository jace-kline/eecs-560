{-# Language InstanceSigs #-}

module Pairing where

import Heap
import Tree

data Pairing a = Pairing (Tree a)
    deriving (Eq, Show)

fromPairing :: Pairing a -> Tree a
fromPairing (Pairing t) = t

instance Heap Pairing where
    empty :: (Ord a) => Pairing a
    empty = Pairing Empty

    singleton :: (Ord a) => a -> Pairing a
    singleton x = Pairing (Node x [])

    add :: (Ord a) => a -> Pairing a -> Pairing a
    add x p = merge (singleton x) p

    merge :: (Ord a) => Pairing a -> Pairing a -> Pairing a
    merge (Pairing Empty) p = p
    merge p (Pairing Empty) = p
    merge (Pairing (Node x xs)) (Pairing (Node y ys)) = Pairing $ 
                                                            if x <= y 
                                                            then Node x $ (Node y ys) : xs
                                                            else Node y $ (Node x xs) : ys

    peek :: (Ord a) => Pairing a -> Maybe a
    peek (Pairing Empty) = Nothing
    peek (Pairing (Node x _)) = Just x

    pop :: (Ord a) => Pairing a -> Maybe (Pairing a)
    pop (Pairing Empty) = Nothing
    pop (Pairing (Node x xs)) = Just $ mergeMulti $ map Pairing xs

fromList :: (Ord a) => [a] -> Pairing a
fromList xs = mergeMulti $ map singleton xs

mergeMulti :: (Ord a) => [Pairing a] -> Pairing a
mergeMulti ps = go ps
    where go :: (Ord a) => [Pairing a] -> Pairing a
          go [] = Pairing Empty
          go [p] = p
          go (p:q:qs) = go (qs ++ [merge p q])
          
          
