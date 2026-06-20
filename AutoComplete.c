#include <stdio.h>
#include "AutoComplete.h"

TrieNode *CreateNodeTrie()
{
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    if (node == NULL)
    {
        printf("Error: Gagal alokasi memori.\n");
        exit(1);
    }

    for (int i = 0; i < 26; i++)
        node->Anak[i] = NULL;

    node->AkhirKata = false;
    node->Bobot = 0;

    return node;
}