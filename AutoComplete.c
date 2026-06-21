#include <stdio.h>
#include <stdlib.h>
#include "AutoComplete.h"

TrieNode *SearchInput(TrieNode *root, char *input)
{
    TrieNode *current = root;

    for (int i = 0; input[i]; i++)
    {
        int index = input[i] - 'a';

        if (current->Anak[index] == NULL)
        {
            return NULL;
        }
        current = current->Anak[index];
    }
    return current;
}

void AmbilRekomendasi(TrieNode *node, char *bufferKata, int depth, LinkedList *listrekomen)
{
    if (node == NULL)
    {
        return;
    }

    if (node->AkhirKata)
    {
        bufferKata[depth] = '\0';
        InsertList(listrekomen, bufferKata, node->Bobot);
    }

    for (int i = 0; i < 26; i++)
    {
        if (node->Anak[i] != NULL)
        {
            bufferKata[depth] = i + 'a';
            AmbilRekomendasi(node->Anak[i], bufferKata, depth + 1, listrekomen);
        }
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AutoComplete.h"

TrieNode *CreateNodeTrie()
{
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    if (node == NULL)
    {
        printf("Gagal alokasi\n");
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
            continue;

        if (current->Anak[indeks] == NULL)
            current->Anak[indeks] = CreateNodeTrie();

        current = current->Anak[indeks];
    }

    current->AkhirKata = true;
    current->Bobot = bobot;
}

void LoadKata(TrieNode *root, char *namaFile)
{
    FILE *file = fopen(namaFile, "r");
    if (file == NULL)
    {
        printf("File tidak ditemukan.\n");
        exit(1);
    }

    char buffer[100];
    int nomorBaris = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        buffer[strcspn(buffer, "\r\n")] = '\0';

        if (strlen(buffer) == 0)
            continue;

        int bobot = 10000 - nomorBaris;
        InsertKata(root, buffer, bobot);
        nomorBaris++;
    }

    fclose(file);
}