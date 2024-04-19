#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{    
    int isWord;
    struct Trie *next[26];
};

// Initializes a trie structure
struct Trie* createTrie()
{
    struct Trie* trie =malloc(sizeof(struct Trie));

    trie->isWord = 0;

    for(int i = 0; i<26; i++)
    {
        trie->next[i] = NULL;
    }

    return trie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *current = pTrie;
    for(int i = 0; i < strlen(word); ++i)
    {
        int index = word[i] - 'a';
        if(current->next[index] == NULL)
        {
            current->next[index] = createTrie();
        }
        current = current->next[index];
    }
    current->isWord += 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    for(int i = 0; i < strlen(word); ++i)
    {
        int index = word[i] - 'a';
        if(pTrie->next[index] != NULL)
        {
            pTrie = pTrie->next[index];
        }
    }
    int isWord = pTrie->isWord;

    return isWord;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    int i;
    if(pTrie == NULL)
        return NULL;
    for(i = 0; i < 26; i++)
    {
        pTrie->next[i] = deallocateTrie(pTrie->next[i]);
    }

    free(pTrie);
    return NULL;
}



// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* input = fopen(filename, "r");

    int n;
    fscanf(input, "%d", &n);
    for(int i = 0; i < n; i++)
    {
        pInWords[i] = malloc(256 * sizeof(char));
        fscanf(input,"%s",pInWords[i]);
    }


    fclose(input);
    return n;

}

int main(void)
{
    char *inWords[256];
    
    //read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i=0;i<numWords;++i)
    {
        printf("%s\n",inWords[i]);
    }
    
    struct Trie *pTrie = createTrie();
    for (int i=0;i<numWords;i++)
    {
        insert(pTrie, inWords[i]);
    }
    // parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i=0;i<5;i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}

