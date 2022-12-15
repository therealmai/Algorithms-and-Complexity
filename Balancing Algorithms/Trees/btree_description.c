/*
Rudolf Bayer, Edward M. McCreight
1972
-	Self-balancing
-	Sorted Keys
-	Min = M/2 Children
Max = M Children
-	Leaves not connected
Bottom Up approach
Time Complexity:
O(logm n) in all cases
Space Complexity
O(n)

RNN = relative record number

Order is the number of children in page
Page is the the node

Splitting and Promotion for Insertion
Redistribution and Concatenation for Deletion

Ceiling or floor
Every page has a max descendants given = Max
Every page except root must have minimum [m/2] ceiling chilren = Min children = ceiling(m/2)
Root must have at least 2 descendants
All non leaf page will have a maximum keys (m-1) = Max keys = m-1
All leaf page will contain at least cealing(m/2) -1 min keys = min keys = ceiling(m/2)-1

Deletion
Case 1: Direct removel in leaf node
Case 2: If the node is not a leaf find the successor and swap it
Case 3: Delete with redistribution must not be minimum find a node that will suffice the properties
Case 4: Delete with concatenation just combine the root and the 2 nodes if no minimum siblings found
*/