#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    const char *user = "max";
    const char *file = "/tmp/testperm.txt";
    //чтворення від імені користувача max (звичайний)
    printf("Creating as user...\n");
    system("echo 'Testing' > /tmp/testperm.txt");
    system("ls -l /tmp/testperm.txt");
    //зміна власника на root 640 (6 - власник читає/редагує, 4 - група читає, 0 - інші нічого)
    printf("Making root owner, perms 640...\n");
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "sudo chown root:wheel %s && sudo chmod 640 %s", file, file);
    system(cmd);
    system("ls -l /tmp/testperm.txt");
    //перевірка читання
    printf("Checking read as user %s...\n", user);
    snprintf(cmd, sizeof(cmd), "sudo -u %s sh -c 'cat %s >/dev/null && echo Read ok || echo No read'", user, file);
    system(cmd);
    //перевірка запису
    printf("Checking write as user %s...\n", user);
    snprintf(cmd, sizeof(cmd), "sudo -u %s sh -c 'echo test >> %s 2>/dev/null && echo Write ok || echo No write'", user, file);
    system(cmd);
}
