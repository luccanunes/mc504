/*
MC504 - Experimento 2

Feito por
- Lucca Miranda Nunes 230554
- Yvens Ian Prado Porto 184031
*/
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TRUE 1
#define FALSE 0

/**
 * @brief Particiona uma string em um vetor de acordo com um caractere separador
 *
 * @param[in] s String a ser particionada
 * @param[in] sep Caractere separador
 * @param[out] size Tamanho do vetor resultante
 * @return Vetor resultante
 */
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

/**
 * @brief Lê um comando da entrada padrão e retorna um vetor com o comando e a lista de argumentos
 *
 * @param[out] sz Tamanho do vetor resultante
 * @return Vetor resultante
 */
char** read_command(int* sz) {
    printf("simple-shell$: ");
    char* comando_raw = NULL;
    size_t size;
    getline(&comando_raw, &size, stdin);
    return split(comando_raw, ' ', sz);
}

/**
 * @brief Diz se um arquivo existe
 *
 * @param[in] filename Caminho para o arquivo
 * @return 1, se existe; 0, do contrário
 */
int file_exists(const char* filename){
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

/**
 * @brief Concatena duas strings com o caractere '/' entre elas
 *
 * @param[in] a String à esquerda do '/'
 * @param[in] b String à direita do '/'
 * @return String resultante
 */
char* concatena(const char* a, const char* b){
    char* ret = malloc((strlen(a) + strlen(b) + 2) * sizeof(char));
    int i = 0, j = 0;

    for (i = 0; i < strlen(a); i++)
        ret[i] = a[i];
    ret[i] = '/';

    for (j = 0; j < strlen(b); j++)
        ret[i + 1 + j] = b[j];
    ret[i + j + 1] = '\0';
    
    return ret;
}

void libera(char** lista, int n){
    for (int i = 0; i < n; ++i)
        free(lista[i]);
    free(lista);
}

int main(int argc, char* argv[]) {
    char* diretorios_raw = argv[1];

    int dir_cnt;
    char** diretorios = split(diretorios_raw, ':', &dir_cnt); 

    int cmd_cnt;
    char** comandos;

    while(TRUE){
        comandos = read_command(&cmd_cnt);

        if(strcmp(comandos[0], "exit") == 0){
            libera(comandos, cmd_cnt);
            break;
        }

        if(cmd_cnt == 0) continue;

        // codigo pai
        if (fork() != 0) { 
            if(strcmp(comandos[cmd_cnt - 1], "&") != 0){
                int status;
                waitpid(-1, &status, 0);
            }
        }
        // codigo filho
        else {
            int flag = 0;

            if(strcmp(comandos[cmd_cnt - 1], "&") == 0)
                comandos[cmd_cnt - 1] = NULL;

            for(int i = 0; i < dir_cnt; i++){
                char* aux = concatena(diretorios[i], comandos[0]); // diretorios[i] + / + comandos[0]
                if(file_exists(aux)){
                    execv(aux, comandos);
                    free(aux);
                    flag = 1;
                    break;
                }
                free(aux);
            }

            if(flag == 0)
                printf("Comando não encontrado.\n");

            return 0;
        }

        libera(comandos, cmd_cnt);
    }

    libera(diretorios, dir_cnt);

    return 0;
}