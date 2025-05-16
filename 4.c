#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("---whoami---:\n");
    //виконання whoami (who am I? - "хто я?": показує ім'я поточного юзера)
    system("whoami");
    //id показує UID, GID та список груп разом з ім'ям
    printf("\n---id---:\n");
    system("id");
}
