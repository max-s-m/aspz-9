#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void test_access(const char *, const char *);

int main(){
    const char *user = "max";
    printf("-----home:-----\n");
    system("ls -l ~");
    //далі елементів дуже багато, тому виводяться 10
    printf("\n-----/usr/bin:-----\n");
    system("ls -l /usr/bin | head -n 10");
    printf("\n-----/etc:-----\n");
    system("ls -l /etc | head -n 10");
    //перевірка різних файлів
    test_access(user, "/etc/passwd");
    test_access(user, "/usr/bin/ls");
    test_access(user, "/usr/bin/top");
    //файл у домашній папці (644: 6 - власник редагує/читає, 4 - група читає, 4 - інші читають)
    system("echo 'home file' > ~/mytestfile && chmod 644 ~/mytestfile");
    test_access(user, "/home/max/mytestfile");
}
//отримання прав доступу
void test_access(const char *user, const char *path) {
    printf("\n%s:\nUser max can:\n", path);
    char cmd[200];
    //задання команди перевірки прав у масив cmd
    snprintf(cmd, sizeof(cmd), "sudo -u %s sh -c '[ -r %s ] && echo + read || echo - read; "
        "[ -w %s ] && echo + write || echo - write; "
        "[ -x %s ] && echo + exec || echo - exec'", user, path, path, path);
    //виконання перевірки
    system(cmd);
}
