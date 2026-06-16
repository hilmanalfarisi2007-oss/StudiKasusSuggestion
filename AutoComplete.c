#include <stdio.h>
#include <stdlib.h>
#include "AutoComplete.h"

TrieNode *SearchInput(TrieNode *root, char *input){
   TrieNode *current = root;

   for (int i = 0; input[i]; i++){
        int index = input[i] - 'a';

        if(current->Anak[index] == NULL){
            return NULL;
        }
        current = current->Anak[index];
   }
    return current;
}

void AmbilRekomendasi(TrieNode *node, char *bufferKata, int depth, LinkedList *listrekomen){
    if (node == NULL){
        return;
    }

    if (node->AkhirKata){
        bufferKata[depth] = '\0';
        InsertList(listrekomen, bufferKata, node->Bobot);
    }

    for (int i = 0; i < 26; i++){
        if (node->Anak[i] != NULL){
            bufferKata[depth] = i + 'a';
            AmbilRekomendasi(node->Anak[i],bufferKata, depth + 1,listrekomen);
        }
    }
}