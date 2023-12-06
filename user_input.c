#include "shell.h"

void read_command(char *command, size_t size) {
    if (fgets(command, size, stdin) == NULL) {
        if (fof(stdin))
        ali_print("/n");
    exit(EXIT_SUCCESS);
    } else {
        ali_print("Error while reading input./n");
        exit(EXIT_FAILURE);
    }
}
command[strcpspn(command), "/n"] = '/0';
#endif