{-# Language InstanceSigs #-}

module Tree where

data Tree a = Empty | Node a [Tree a]
    deriving (Eq)

instance Ord a => Ord (Tree a) where
    Empty       <= _           = True
    (Node _ _)  <= Empty       = False
    (Node x xs) <= (Node y ys) = x <= y

instance Show a => Show (Tree a) where
    show :: (Show a) => Tree a -> String
    show t = '\n' : go 1 t
        where go :: (Show a) => Int -> (Tree a) -> String
              go n t = ('\n' : take n (repeat '\t')) ++ 
                case t of
                    Empty        -> "Empty"
                    (Node x r)   -> "Node " ++ show x ++ (foldr (++) [] $ map (go (n + 1)) r)

children :: Tree a -> [Tree a]
children Empty      = []
children (Node x r) = r