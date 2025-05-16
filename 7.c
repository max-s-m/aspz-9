#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main(){
    //тимчасовий файл
    char temp_name[] = "/tmp/secretXXX";
    int fd = mkstemp(temp_name); //замінює XXX на випадкові символи та повертає дескриптор
    if(fd == -1){
        printf("Didn't get descriptor\n");
        exit(1);
    }
    close(fd); //mkstemp відкриває файл, можна закрити close(fd)
    printf("Created: %s\n", temp_name);
    //записуються дані
    FILE *fp = fopen(temp_name, "w");
    if(fp == NULL){
        printf("Didn't open\n");
        unlink(temp_name);
        exit(1);
    }
    fprintf(fp, "This is top secret\n"); //конфіденційна інформація у тимчасовому файлі
    fclose(fp);
    printf("Data written\n");
    //обмеження доступу
    char cmd[100];
    snprintf(cmd, sizeof(cmd), "chmod 600 %s", temp_name); //обмеження - тільки користувач має доступ
    printf("Perms %s limited (600).\n", temp_name);
    //читання даних через cat
    printf("\nReading (cat):\n");
    snprintf(cmd, sizeof(cmd), "cat %s", temp_name);
    system(cmd);
    //видалення файлу
    unlink(temp_name);
    printf("\nFile %s deleted\n", temp_name);
}
