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
Instance 1
Case 1: If to be deleted is leaf just free or if to be deleted has one child then promote the child and color it to black
Case 2: If to be deleted has 2 childs, exhange the value to its inorder predecessor then delete it (based it on case 1)

Instance 2
Case 1: If sibling of deleted value is black and has child red then do a simple avl rotation then recolor the child of sibling and 
grandparent to black then color parent the former color of granparent

Case 2: If sibling of deleted value is black and has black child. Color sibling to red if its parent is red then
recolor parent to black. If parent is black already then make it double black

Case 3: If sibling of deleted value is red then make the deleted value to be double black then do a rotation where sibling becomes
the granparent (make them linear) and make it black while the former parent becomes red






Time complexity
Amortized Access: O(log n) for accessing, searching and O(1) for insertions and deletion
Worst: O(log n) in all cases

Space Complexity
O(n)


*/