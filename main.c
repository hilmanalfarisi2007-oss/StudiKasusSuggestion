#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "autocomplete.h"

int main()
{
    TrieNode *root = CreateNodeTrie();

    LoadKata(root, "google-10000-english.txt");

    char input[100];

    while (1)
    {
        printf("Input: ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\r\n")] = '\0';

        if (strcmp(input, "!exit") == 0)
        {
            printf("Program selesai.\n");
            break;
        }

        if (strlen(input) == 0)
        {
            printf("Input tidak boleh kosong.\n\n");
            continue;
        }

        for (int i = 0; input[i]; i++)
            input[i] = tolower(input[i]);

        TrieNode *nodePrefiks = SearchInput(root, input);

        LinkedList listRekomen;
        InitList(&listRekomen);

        if (nodePrefiks == NULL)
        {
            printf("Tidak ada kata yang sesuai dengan \"%s\".\n\n", input);
            continue;
        }

        char bufferKata[100];
        strcpy(bufferKata, input);
        AmbilRekomendasi(nodePrefiks, bufferKata, strlen(input), &listRekomen);

        SortList(&listRekomen);
        PrintTop10(&listRekomen);
        printf("\n");

        HapusList(&listRekomen);
    }

    return 0;
}