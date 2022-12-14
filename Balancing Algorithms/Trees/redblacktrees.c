/*
Rudolf Bayer
1972
-	Self-balancing
-	Sorted Keys
-	Colored Nodes
Root = Black
Black property Leaf = Black (NULL) root and null leaves are always black
Red Property Node can only have Black Child
Depth Property = must have the same number of Count Black in path
New Node = Red

RULES
New nodes starts as red
all NULL Nodes are black; have a nil node with elem=0, color=black, left=right=NULL to act as the null node
Root is always black
No consecutive reds

Insertion
Case 1: If the root node is red then change it to black 

Case 2: Z uncle is red then recolor them which suffice the properties

Case 3: Z uncle is black then do a avl rotation and match the color of parent and granparent which suffice the property

Deletion


Time complexity
Amortized Access: O(log n) for accessing, searching and O(1) for insertions and deletion
Worst: O(log n) in all cases

Space Complexity
O(n)


*/