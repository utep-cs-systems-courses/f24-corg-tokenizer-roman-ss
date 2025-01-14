#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h" 
#include "history.h"  

int main() {
    char input[200];  // where we store user input
    char **tokens;    // where will we put tokens
    List *history = init_history(); // where history will start

    while (1) {
        // will exit loop if user enters exit, otherwise calls to function to output tokens or history
        printf("Type a string, 'history' to view history, or 'exit' for a surprise: ");
        fgets(input, sizeof(input), stdin);
        
        // newline remove
        input[strcspn(input, "\n")] = '\0';

        
        if (strcmp(input, "exit") == 0) {
            break;
        }

       

	if (input[0] == '!' && input[1]>= '0' && input[1] <= '9') {
            int id = atoi(&input[1]); 
            char *history_item = get_history(history, id);

            if (history_item) {
                printf("Accessing history item %d: %s\n", id, history_item);
                continue;
            } else {
                printf("Not a valid id\n");
                continue; // start of while loop
            }
        } else if (strcmp(input, "history") == 0) {
            print_history(history); 
            continue;
        }

        // tokenize function from tokenizer
        tokens = tokenize(input);

        // error print 
        if (tokens == NULL) {
            printf("No tokens found.\n");
            continue;
        }

        // use function from history file
        add_history(history, input);

        
        printf("Tokens:\n");
        for (int i = 0; tokens[i] != NULL; i++) {
            printf("Token %d: %s\n", i, tokens[i]);
        }

        // free tokens til its backwards
        free_tokens(tokens);
    }

    // free historylist
    free_history(history);

    return 0;
}
