#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    const char *user = "max";
    const char *filename = "/tmp/original.txt";
    const char *copy_path = "/home/max/copied.txt";
    printf("Creating as user...\n");
    system("echo 'User goblin mode' > /tmp/original.txt");
    system("ls -l /tmp/original.txt");
    //копіювання адміном до домашньої папки юзера
    printf("Copying to max's home as root...\n");
    char cmd1[256];
    snprintf(cmd1, sizeof(cmd1),
             "sudo cp %s %s && sudo chown root:wheel %s && sudo chmod 444 %s",
             filename, copy_path, copy_path, copy_path);
    system(cmd1);
    system("ls -l /home/max/copied.txt");
    //спроба змінити копійований файл
    printf("Editing as user...\n");
    char cmd2[512];
    snprintf(cmd2, sizeof(cmd2), "sudo -u %s sh -c 'echo Change >> %s'", user, copy_path);
    int edit_result = system(cmd2);
    //не має вийти, оскільки файл належить root
    if(edit_result != 0)
        printf("Didn't edit\n");
    else
        printf("Edited\n");
    //спроба видалення як простий користувач
    printf("Deleting as user...\n");
    char cmd3[256];
    snprintf(cmd3, sizeof(cmd3), "sudo -u %s rm %s", user, copy_path);
    int rm_result = system(cmd3);
    //має вийти, оскільки права на видалення визначаються правами на директорію
    if(rm_result != 0)
        printf("Didn't delete'\n");
    else
        printf("Deleted\n");
}
