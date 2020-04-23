module Heap where

class Heap h where
    empty :: (Ord a) => h a
    singleton :: (Ord a) => a -> h a
    add :: (Ord a) => a -> h a -> h a
    merge :: (Ord a) => h a -> h a -> h a
    peek :: (Ord a) => h a -> Maybe a
    pop :: (Ord a) => h a -> Maybe (h a)