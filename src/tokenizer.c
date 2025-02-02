#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
//returns 1 if whitespace
int space_char(char c) {
    return (c == ' ' || c == '\t' || c == '0') ? 1 : 0;
}

//returns 1 if not whitespace
int non_space_char(char c) {
    return (c != ' ' && c != '\t' && c != '0') ? 1 : 0;
}

char *token_start(char *str) {
    if (str == NULL) {
        return NULL; 
    }

    // use space function to get to start
    while (space_char(*str)) {
        str++;
    }

    // if no token
    if (*str == '\0') {
        return NULL;
    }

    
    return str;
}


char *token_terminator(char *token) {
    if (token == NULL) {
        return NULL; 
    }

    //while moves until we find whitespace/end of token
    while (*token != '\0' && !space_char(*token)) {
        token++;
    }

    //if token points to value \0, end of string no more tokens
    return (*token == '\0') ? NULL : token;
}

int count_tokens(char *str) {
    int count = 0;
    char *token;

    // use token_start to find first token
    token = token_start(str);
    while (token != NULL) {
        count++; // for token
        
        // move pointer to end of token
        token = token_terminator(token);
        
        
        if (token != NULL) {
            token++; 
            token = token_start(token); // token is now pointer to start of next token
        }
    }

    return count; 
}

// couldn't find easier way to access length of string, will be used to know how much space allocated for strings we need to copy, i used string.h after this because I kept getting errors when trying to call this function in history.c
int str_length(char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}


char *copy_str(char *inStr, short len) {
    if (inStr == NULL || len < 1) {
        return NULL; // check for NULL pointer or empty length
    }

    //making memory for copy, not sure if need NULL check due to last check 
    char *newStr = (char *)malloc(len + 1);
    if (newStr == NULL) {
        return NULL; 
    }

    // copy into newStr
    for (short i = 0; i < len; i++) {
        newStr[i] = inStr[i];
    }
    newStr[len] = '\0'; //zero terminator

    return newStr;
}


char **tokenize(char *str) {
    int count = count_tokens(str);
    char **tokens = (char **)malloc((count + 1) * sizeof(char *)); // **tokens is pointers to pointers of chars, this is where we'll keep them
    if (tokens == NULL) {
        return NULL; 
    }

    char *token = token_start(str);
    int index = 0;

    while (token != NULL) {
        char *terminator = token_terminator(token);
        
        // str_length cameo, length of individual token
        short len = (terminator != NULL) ? (terminator - token) : str_length(token);
        
        // token goes in copy array
        tokens[index] = copy_str(token, len);
        if (tokens[index] == NULL) {
            // malloc
            for (int j = 0; j < index; j++) {
                free(tokens[j]); // free previously allocated tokens
            }
            free(tokens);
            return NULL;
        }
        index++;
        
        // Move to the next token if applicable
        token = (terminator != NULL) ? terminator + 1 : NULL; 
        token = token_start(token); 
    }

    tokens[index] = NULL; // end of token list
    return tokens;
}


void print_tokens(char **tokens) {
    if (tokens == NULL) {
        return;
    }

    for (int i = 0; tokens[i] != NULL; i++) {
        printf("Token[%d]: %s\n", i, tokens[i]);
    }
}

//free tokens
void free_tokens(char **tokens) {
    if (tokens == NULL) {
        return; 
    }

    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]); 
    }
    free(tokens); 
}

