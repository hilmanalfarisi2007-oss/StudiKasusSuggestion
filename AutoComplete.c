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

void InsertKata(TrieNode *root, char *kata, int bobot)
{
    TrieNode *current = root;

    for (int i = 0; kata[i] != '\0'; i++)
    {
        int indeks = tolower(kata[i]) - 'a';

        if (indeks < 0 || indeks > 25)
            return;

        if (current->Anak[indeks] == NULL)
            current->Anak[indeks] = CreateNodeTrie();

        current = current->Anak[indeks];
    }

    current->AkhirKata = true;
    current->Bobot = bobot;
}