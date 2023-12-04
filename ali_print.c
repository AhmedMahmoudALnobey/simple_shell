#include "shell.h"

void ali_print(const char *format){
    write (STDOUT_FILENO, format, strlen(format));

}
write(1, &format, strlen(format));