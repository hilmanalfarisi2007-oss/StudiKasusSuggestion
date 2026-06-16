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

void SortList(LinkedList *list) {
    if (list->First == NULL) return;

    int swapped;
    RekomendasiNode *ptr1;
    RekomendasiNode *lptr = NULL; // Menandai batas akhir yang sudah terurut
    
    // Variabel sementara untuk swap (sesuai spesifikasi tugasmu)
    char tempKata[100];
    int tempBobot;

    do {
        swapped = 0;
        ptr1 = list->First;

        while (ptr1->Next != lptr) {
            // Urutkan secara descending (Bobot kecil digeser ke belakang)
            if (ptr1->Bobot < ptr1->Next->Bobot) { 
                // 1. Swap Bobot
                tempBobot = ptr1->Bobot;
                ptr1->Bobot = ptr1->Next->Bobot;
                ptr1->Next->Bobot = tempBobot;

                // 2. Swap Kata
                strcpy(tempKata, ptr1->Kata);
                strcpy(ptr1->Kata, ptr1->Next->Kata);
                strcpy(ptr1->Next->Kata, tempKata);

                swapped = 1;
            }
            ptr1 = ptr1->Next;
        }
        lptr = ptr1;
    } while (swapped);
}