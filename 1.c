#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Need 1 arg: lower UID\n");
        exit(1);
    }
    int lower_UID = atoi(argv[1]);
    FILE *pipe;
    char line[100];
    char curr_username[100] = "";
    //ім'я поточного користувача
    int my_uid = getuid();
    struct passwd *my_pass = getpwuid(my_uid);
    if(my_pass != NULL) {
        strncpy(curr_username, my_pass->pw_name, sizeof(curr_username) - 1);
    }
    //відкриття pipe та виконання getent passwd
    pipe = popen("getent passwd", "r");
    if(pipe == NULL){
        printf("Didn't popen");
        exit(1);
    }
    //читання кожного рядка виводу
    while(fgets(line, sizeof(line), pipe) != NULL){
        //ім'я користувача (перше поле) (пусті рядки пропускаються)
        char *username = strtok(line, ":");
        if(username == NULL) continue;
        //поле пароля (друге) пропускається
        char *field_ptr = strtok(NULL, ":");
        if(field_ptr == NULL) continue;
        //uid (третє поле)
        char *uid_str = strtok(NULL, ":");
        if(uid_str == NULL) continue;
        int uid = atoi(uid_str);
        // чи це звичайний користувач, а не цей
        if(uid >= lower_UID){ //користувачі починаються десь з 1000
            if(curr_username[0] == '\0' || strcmp(username, curr_username) != 0){
                printf("%s\n", username);
            }
        }
    }
    pclose(pipe);
}
