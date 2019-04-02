#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <malloc.h>


int is_file(const char*);

int main() {
    char dirname[200];

    printf("Enter the path to directory you want to change files' names:\n");
    scanf("%s", dirname);


    if(is_file(dirname) != 0) {
        printf("%s is not a directory\n", dirname);
        return 0;
    }

    printf("Selected Directory: %s\n", dirname);

    DIR *d;

    struct dirent *dir;

    d = opendir(dirname);

    if(d) {
        while((dir = readdir(d)) != NULL) {
            if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                char* d_name = malloc(strlen(dir->d_name) + 1);
                strcpy(d_name, dir->d_name);

                char* d_name_upr = malloc(strlen(dir->d_name) + 1);

                strcpy(d_name_upr, dir->d_name);
                strupr(d_name_upr);

                char* new_path = malloc(strlen(dir->d_name) + 1);

                strcpy(new_path, dirname);

                char* old_path = strcat(strcat(new_path, "/"), d_name);
                char* nn_path = strcat(strcat(dirname, "/"), d_name_upr);
                printf("Renaming %s to %s\n", old_path, nn_path);

                if(rename(old_path, nn_path) == 0) {
                    printf("Renamed");
                } else {
                    printf("Could not rename files");
                }
            }
        }
        closedir(d);
    } else {
        printf("Dir %s could not be opened", dirname);
    }


    free(d);

    return 0;
}


int is_file(const char* name) {
    DIR *directory = opendir(name);

    if(directory != NULL) {
        closedir(directory);
        return 0;
    }

    if(errno == ENOTDIR) {
        return 1;
    }

    return -1;
}

