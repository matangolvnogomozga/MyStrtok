#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<iostream>
#include<assert.h>

#define MAXNUM 100

char** MyStrtok(char string[], const char* delim, int* num);
bool IsSymbol(char symb, const char* delim);

int main()
{
    char string[] = "  \n\nHello,  dear   Intel (intel)\n\t\t users\n \t from   MIPT (or mipt)";

    int num = 0;
    char** pointers = MyStrtok(string, " \n\t()", &num);
    if(pointers == NULL)
    {
        printf("Check your phrase\n");
        return 1;
    }

    for(int i = 0; i < num; ++i)
        puts(pointers[i]);

    const char line[] = "Intel";
    const char line2[] = "MIPT";

    for(int i = 0; i < num; ++i)
    {
        if(strcmp(pointers[i], line) == 0)
            printf("\nNot AMD\n");
        if(strcmp(pointers[i], line2) == 0)
            printf("\nThe first university\n");
    }

    printf("\nNumber of words is %d\n", num);
    return 0;
}

//-------------------------------------------------------------------
//! Function "MyStrtok" breaks line to tokens
//!
//!@param [in] string Line we are working with
//!@param [in] delim Array, contains separators
//!
//!@param [out] num Number of tokens in line
//!
//!@return Array with pointers to start of tokens
//!
//!@note If there is more tokens that defined, function returned NULL
//!      or there isn't any tokens
//!
//!@note
//-------------------------------------------------------------------
char** MyStrtok(char string[], const char* delim, int* num)
{
    assert(string != NULL);
    assert(delim != NULL);

    char** array = (char **)calloc(MAXNUM, sizeof(char*));
    int i = 0; /// counter in "string"
    int j = 0; /// counter in "array"
    int len = strlen(string);

    /// Ignoring separators in the beginning
    for(i; IsSymbol(string[i], delim) && string[i] != '\0'; ++i)
        continue;

    /// If there are only separators in line
    if(i == len)
        return NULL;

    /// The first token
    array[0] = &string[i];
    ++i;
    ++j;

    for(i; string[i] != '\0'; ++i)
    {
        if(j > MAXNUM)
            return NULL;
        if(IsSymbol(string[i], delim) && i + 1 <= len)
            string[i] = '\0';
        else if(string[i-1] == '\0')
        {
            array[j++] = &string[i];
        }
    }
    *num = j;
    return array;
}

//------------------------------------------------------
//! Function "IsSymbol" checks existing symbol in line
//!
//!@param [in] symb Symbol to check
//!@param [in] delim Line to check
//!
//!@return true, if symbol exist in line
//!        false, if not
//!
//------------------------------------------------------
bool IsSymbol(char symb, const char* delim)
{
    assert(delim != NULL);

    int len = strlen(delim);
    for(int i = 0; i < len; ++i)
    {
        if(symb != delim[i])
            continue;
        else
            return true;
    }
    return false;
}
