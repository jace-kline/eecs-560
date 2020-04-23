{-# Language InstanceSigs #-}

module BinTree where

data BinTree a = Empty | Node a (BinTree a) (BinTree a)
    deriving (Eq)

instance Show a => Show (BinTree a) where
    show :: (Show a) => BinTree a -> String
    show t = '\n' : go 1 t
        where go :: (Show a) => Int -> (BinTree a) -> String
              go n t = ('\n' : take n (repeat '\t')) ++ 
                case t of
                    Empty        -> "Empty"
                    (Node x l r) -> "Node " ++ show x ++ (go (n + 1) l) ++ (go (n + 1) r)

rank :: BinTree a -> Int
rank Empty        = 0
rank (Node x l r) = (rank r) + 1