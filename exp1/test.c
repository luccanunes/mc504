#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char** split(char* s, char sep, int* size) {
    int len = 0, n = 1;
    while (s[len] != '\0' && s[len] != '\n') {
        if (s[len] == sep)
            n++;
        len++;
    }
    *size = n;

    char** arr = malloc((n + 1) * sizeof(char *));
    int cur_str = 0, cur_str_size = 0;

    for (int i = 0; i <= len; ++i) {
        if (s[i] == sep || s[i] == '\0' || s[i] == '\n') {
            arr[cur_str] = malloc((cur_str_size + 1) * sizeof(char)); 
            cur_str++;
            cur_str_size = 0;
        } else {
            cur_str_size++;
        }
    }

    arr[n] = NULL;

    cur_str = 0, cur_str_size = 0;
    for (int i = 0; i <= len; ++i) {
        if (s[i] == sep || s[i] == '\0' || s[i] == '\n') {
            arr[cur_str][cur_str_size] = '\0'; 
            cur_str++;
            cur_str_size = 0;
        } else {
            arr[cur_str][cur_str_size] = s[i]; 
            cur_str_size++;
        }
    }

    return arr;
}

char** read_command(int* sz) {
    printf("simple-shell$: ");
    char* comando_raw = NULL;
    size_t size;
    ssize_t len = getline(&comando_raw, &size, stdin);
    return split(comando_raw, ' ', sz);
}

void printv(char *const cmds[]){
    int i = 0;
    while(cmds[i] != NULL){
        printf("%s\n", cmds[i]);
        i++;
    }
}

int main() {
    int cmd_cnt;
    char** comandos;
    comandos = read_command(&cmd_cnt);

    printv(comandos + 1);

    for (int i = 0; i < cmd_cnt; ++i)
        free(comandos[i]);
    free(comandos);

    return 0;
}