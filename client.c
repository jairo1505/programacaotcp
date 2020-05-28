#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    int socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_desc == -1)
    {
        printf("Não foi possivel ciar o socket");
        return 1;
    }
    
    return 0;
}