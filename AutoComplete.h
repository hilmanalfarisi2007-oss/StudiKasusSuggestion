#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include <stdbool.h>

// Struktur Data Trie
typedef struct TrieNode
{
    struct TrieNode *Anak[26];
    bool AkhirKata;
    int Bobot;
} TrieNode;

// Struktur Data Linked List
typedef struct RekomendasiNode
{
    char Kata[100];
    int Bobot;
    struct RekomendasiNode *Next;
} RekomendasiNode;

typedef struct
{
    RekomendasiNode *First;
} LinkedList;

// Fungsi ADT Trie
TrieNode *CreateNodeTrie();
void InsertKata(TrieNode *root, char *kata, int bobot);
void LoadKata(TrieNode *root, char *namaFile);
TrieNode *SearchInput(TrieNode *root, char *input);
void AmbilRekomendasi(TrieNode *node, char *bufferKata, int depth, LinkedList *listRekomen);

// Fungsi Linked List
void InitList(LinkedList *list);
void InsertList(LinkedList *list, char *kata, int bobot);
void SortList(LinkedList *list);
void PrintTop10(LinkedList *list);
void HapusList(LinkedList *list);

#endif