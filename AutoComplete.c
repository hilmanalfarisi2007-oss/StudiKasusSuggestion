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
    
}

//Fungsi Linked list
void InitList(LinkedList *list) {
    list->First = NULL;
}

void InsertList(LinkedList *list, char *kata, int bobot) {
    // Alokasi memori untuk node baru
    RekomendasiNode *newNode = (RekomendasiNode*) malloc(sizeof(RekomendasiNode));
    
    // Isi data node baru
    strcpy(newNode->Kata, kata);
    newNode->Bobot = bobot;
    
    // Sambungkan ke list->First
    newNode->Next = list->First;
    list->First = newNode;
}