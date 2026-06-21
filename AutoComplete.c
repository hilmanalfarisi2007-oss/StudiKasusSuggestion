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

void InitList(LinkedList *list)
{
    list->First = NULL;
}

void InsertList(LinkedList *list, char *kata, int bobot)
{
    RekomendasiNode *newNode = (RekomendasiNode *)malloc(sizeof(RekomendasiNode));

    strcpy(newNode->Kata, kata);
    newNode->Bobot = bobot;

    newNode->Next = list->First;
    list->First = newNode;
}

void SortList(LinkedList *list)
{
    if (list->First == NULL)
        return;

    int swapped;
    RekomendasiNode *ptr1;
    RekomendasiNode *lptr = NULL;

    char tempKata[100];
    int tempBobot;

    do
    {
        swapped = 0;
        ptr1 = list->First;

        while (ptr1->Next != lptr)
        {
            if (ptr1->Bobot < ptr1->Next->Bobot)
            {

                tempBobot = ptr1->Bobot;
                ptr1->Bobot = ptr1->Next->Bobot;
                ptr1->Next->Bobot = tempBobot;

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

void PrintTop10(LinkedList *list)
{
    RekomendasiNode *node = list->First;
    int count = 0;

    printf("\n--- Top 10 Rekomendasi ---\n");
    while (node != NULL && count < 10)
    {
        printf("%d. %s (Bobot: %d)\n", count + 1, node->Kata, node->Bobot);
        node = node->Next;
        count++;
    }

    if (count == 0)
    {
        printf("Tidak ada rekomendasi yang ditemukan.\n");
    }
}

void HapusList(LinkedList *list)
{
    RekomendasiNode *node = list->First;
    RekomendasiNode *next;

    while (node != NULL)
    {
        next = node->Next;
        free(node);
        node = next;
    }
    list->First = NULL;
}