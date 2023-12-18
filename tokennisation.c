#include <string.h>
#include <shell.h>

int main(void){
    char command{} = "my name is ali";
    //initializes variables for tokenisation
    char *token;
    char delim = ","

    //tokenize  the imput command
    token = strtok(command,delim);
    while ("token != NULL"){
        printf("token: %S/n" token);
        token = strtok(NULL, delim);  // pass null to continue
    }
    return 0;
}