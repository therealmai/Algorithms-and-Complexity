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
O(1) in all access, searching and deletion
O(k*m) in Insertion where K is the string length and m is the alphabet size
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define CHILDREN_SIZE 26

typedef struct trieNode{
    struct trieNode *children[CHILDREN_SIZE];
    int isEndWord;
}*triePtr;

void initTrie(triePtr *trie);
void insertTrie(triePtr trie, char word[]);
int searchWord(triePtr trie, char word[]);
triePtr createTrie();
void deleteWord(triePtr *trie, char word[], int letter);

int main(){
    triePtr trie;
    initTrie(&trie);
    insertTrie(trie, "age");
    // insertTrie(trie, "hello");
    
    printf("%d\n", searchWord(trie, "age"));
    deleteWord(&trie, "age", 0);
    printf("%d\n", searchWord(trie, "age"));
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
// return 1 if node has children, otherwise return 0
int isPrefix(triePtr node){
    int x = 0;
    
    if(node != NULL)
      for(; node->children[x] == NULL && x < CHILDREN_SIZE; x++){}

    return (x < CHILDREN_SIZE) ? 1 : 0;
}

void deleteWord(triePtr *trie, char word[], int letter){
    triePtr *trav, temp;
    if(letter == strlen(word) + 1 || (*trie) == NULL){
        return;
    }
    int index = getIndex(word[letter]);
    deleteWord(&(*trie)->children[index], word, letter+1);

    trav = trie;
    temp = *trav;
    if(letter == strlen(word) && temp->isEndWord == 1){
        temp->isEndWord = 0;

        // if the node has no children, just delete it
        if(isPrefix(temp) == 0){
            *trav = NULL;
            free(temp);
            temp = NULL;
        }
    }

    // if the node has no children and it is not the end of the word, delete it
    if(isPrefix(temp) == 0 && temp->isEndWord == 0){
        *trav = NULL;
        free(temp);
        temp = NULL;
    }
}