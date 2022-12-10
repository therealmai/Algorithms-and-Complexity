/*
Donald R. Morisson
1968
-	Each node has at least 2 children with N-1 pointers
-	Also called a compressed trie
-	1 node can store at max 3 letters if possible
Time Complexity:
O(k) = Average and Worst where K is the length of string
Space Complexity:
O(1) in all access, searching and deletion
O(k*m) in Insertion where K is the string length and m is the alphabet size
*/
