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

Time complexity
Amortized Access: O(log n) for accessing, searching and O(1) for insertions and deletion
Worst: O(log n) in all cases

Space Complexity
O(n)


*/