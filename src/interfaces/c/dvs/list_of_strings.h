#ifndef DVS_LIST_OF_STRINGS_H
#define DVS_LIST_OF_STRINGS_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct S_ListOfStrings
{
    char** elements;
    size_t size;
} ListOfStrings;

ListOfStrings createListOfStrings(const size_t size)
{
    ListOfStrings list_of_strings;

    list_of_strings.size = size;
    list_of_strings.elements = (char**)malloc(size * sizeof(char*));

    for (size_t k = 0; k < size; k++)
    {
        list_of_strings.elements[k] = NULL;
    }

    return list_of_strings;
}

void destroyListOfStrings(ListOfStrings* const list_of_strings)
{
    for (size_t k = 0; k < list_of_strings->size; k++)
    {
        if (list_of_strings->elements[k] != NULL)
        {
            free(list_of_strings->elements[k]);
        }
    }

    free(list_of_strings->elements);
    list_of_strings->elements = NULL;
    list_of_strings->size = 0;
}

#endif  // DVS_LIST_OF_STRINGS_H
