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

int file_exists(const char* filename){
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1; // O arquivo existe
    }
    return 0; // O arquivo não existe
}

char* concatena(const char* a, const char* b){
    char* ret = malloc((strlen(a) + strlen(b) + 2) * sizeof(char));
    int i = 0, j = 0;

    for(i = 0; i < strlen(a); i++)
        ret[i] = a[i];
    ret[i] = '/';

    for(j = 0; j < strlen(b); j++)
        ret[i + 1 + j] = b[j];
    ret[i + j + 1] = '\0';
    
    return ret;
}

int main(int argc, char* argv[]) {
    char* diretorios_raw = argv[1];

    int dir_cnt;
    char** diretorios = split(diretorios_raw, ':', &dir_cnt); 

    int cmd_cnt;
    char** comandos;
    comandos = read_command(&cmd_cnt);
    
    int flag = 0;

    for(int i = 0; i < dir_cnt; i++){
        char* aux = concatena(diretorios[i], comandos[0]); // diretorios[i] + / + comandos[0]
        if(file_exists(aux)){
            execv(aux, comandos + 1);
            free(aux);
            flag = 1;
            break;
        }
        free(aux);
    }

    if(flag == 0)
        printf("O programa nao existe\n");

    for (int i = 0; i < dir_cnt; ++i)
        free(diretorios[i]);
    free(diretorios);

    for (int i = 0; i < cmd_cnt; ++i)
        free(comandos[i]);
    free(comandos);

    return 0;
}