#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

char** split(char* s, char sep, int* size) {
    int len = 0, n = 1;
    while (s[len] != '\0' && s[len] != '\n') {
        if (s[len] == sep)
            n++;
        len++;
    }
    *size = n;

    char** arr = malloc(n * sizeof(char *));
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

int main(int argc, char* argv[]) {
    char* diretorios_raw = argv[1];

    int dir_cnt;
    char** diretorios = split(diretorios_raw, ':', &dir_cnt); 

    int cmd_cnt;
    char** comandos;
    comandos = read_command(&cmd_cnt);

    for (int i = 0; i < dir_cnt; ++i)
        free(diretorios[i]);
    free(diretorios);

    for (int i = 0; i < cmd_cnt; ++i)
        free(comandos[i]);
    free(comandos);

    return 0;
}