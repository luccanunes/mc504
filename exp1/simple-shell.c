#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    assert(argc == 2); // TODO: remove

    char* diretorios_raw = argv[1];

    int len = 0, dir_cnt = 1, cur_dir_size = 0, max_dir_size = 0;
    while (diretorios_raw[len] != '\0') {
        cur_dir_size++;
        if (max_dir_size < cur_dir_size)
            max_dir_size = cur_dir_size;
        if (diretorios_raw[len] == ':') {
            cur_dir_size = 0;
            dir_cnt++;
        }
        len++;
    }
    max_dir_size++;

    char** diretorios = malloc(dir_cnt * sizeof(char *));

    for (int i = 0; i < dir_cnt; ++i)
        diretorios[i] = malloc(max_dir_size * sizeof(char));


    int cur_dir = 0, cur_dir_pos = 0;
    for (int i = 0; i <= len; ++i) {
        if (diretorios_raw[i] == ':' || diretorios_raw[i] == '\0') {
            diretorios[cur_dir][cur_dir_pos] = '\0';
            cur_dir++;
            cur_dir_pos = 0;
        } else {
            diretorios[cur_dir][cur_dir_pos] = diretorios_raw[i];
            cur_dir_pos++;
        }
    }
    
    for (int i = 0; i < dir_cnt; i++){
        printf("%s\n", diretorios[i]);
    }


    for (int i = 0; i < dir_cnt; ++i)
        free(diretorios[i]);
    free(diretorios);
    // printf("%d\n", argc);
    // printf("%s\n", diretorios);
    return 0;
}