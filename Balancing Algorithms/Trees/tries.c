/*
Axel Thue-1912	
Rene de la Briandais-1959	
Edward Fredkin-1960
-	Each node has max 26 pointers
-	Each represent a character of the English alphabet
-	Trie is also called Digital Tree
-	Strings only | Characters only
Trie Time Complexity:
O(K) in all cases where K is the length of string
Space Complexity:
O(1) in all cases
*/

#include<stdio.h>
#include<stdlib.h>
#define CHILDREN_SIZE 26

typedef struct trieNode{
    struct trieNode *children[CHILDREN_SIZE];
    int isEndWord;
}*triePtr;

void initTrie(triePtr *trie);
void insertTrie(triePtr trie, char word[]);
int searchWord(triePtr trie, char word[]);
triePtr createTrie();
int main(){
    triePtr trie;
    initTrie(&trie);
    insertTrie(trie, "age");
    insertTrie(trie, "ages");
    printf("%d", searchWord(trie, "ages"));
    printf("%d", searchWord(trie, "agesd"));
    return 0;
}


void initTrie(triePtr *trie){
    (*trie) = (triePtr)calloc(1, sizeof(struct trieNode));
}

int getIndex(char word){
    return word - 'a';
}

triePtr createTrie(){
    triePtr trie = (triePtr)calloc(sizeof(struct trieNode), 1);
    return trie;
}

void insertTrie(triePtr trie, char word[]){
    triePtr trav;
    int x, index = 0;

    for(x=0, trav=trie; word[x] != '\0'; x++, trav = trav->children[index]){
        index = getIndex(word[x]);

        if(trav->children[index] == NULL){
            trav->children[index] = createTrie();
        }
    }

    trav->isEndWord = 1;
}

int searchWord(triePtr trie, char word[]){
    int x, index;
    triePtr trav;
    for(x=0, trav = trie; word[x] != '\0'; x++, trav = trav->children[index]){
        index = getIndex(word[x]);

        if(trav->children[index] == NULL){
            return 0;
        }
    }
    return (trav->isEndWord != 1 ) ? 0 : 1;
}