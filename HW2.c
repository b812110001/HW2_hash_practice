#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 15
#define TABLE_SIZE 30

typedef struct Word_count
{
    char word[MAX_LENGTH];
    int count;
    struct Word_count *next;
} Word_count;

Word_count *hash_table[TABLE_SIZE];

// Hash Function
unsigned int hash(char *word)
{
    unsigned int hash_value = 0;
    while (*word)
    {
        hash_value = (hash_value * 31) + *word;
        word++;
    }
    return hash_value % TABLE_SIZE;
}

// Insert words
void insert_word(char *word, int *unique_count)
{
    unsigned int index = hash(word);

    // 檢查單字是否存在
    Word_count *insert = hash_table[index];
    while (insert != NULL)
    {
        if (strcmp(insert->word, word) == 0)
        {
            insert->count++;
            return;
        }
        insert = insert->next;
    }

    Word_count *new_word = (Word_count *)malloc(sizeof(Word_count));
    strcpy(new_word->word, word);
    new_word->count = 1;
    new_word->next = hash_table[index];
    hash_table[index] = new_word;
    (*unique_count)++;
}

int main()
{
    FILE *file = fopen("hw2_data.txt", "r");
    // 初始化Hash Table
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }

    char word[MAX_LENGTH];
    int unique_count = 0;

    // 讀取文件內容
    while (fscanf(file, "%s", word) == 1)
    {
        insert_word(word, &unique_count);
    }
    fclose(file);

    printf("Times of each word appear:\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Word_count *current = hash_table[i];
        while (current != NULL)
        {
            printf("%s: %d\n", current->word, current->count);
            current = current->next;
        }
    }
    printf("There are %d unique words in total.\n", unique_count);
    return 0;
}
