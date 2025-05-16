#include <stdlib.h>
#include <stdio.h>

int main(){
    //з правами root виводиться фміст файлу, де лежать зашифровані паролі користувачів
    int status = system("sudo cat /etc/master.passwd");
    //при невдачі повертається -1
    if(status == -1){
        printf("Didn't execute");
        return 1;
    }
}
