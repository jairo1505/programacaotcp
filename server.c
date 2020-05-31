#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int socket_desc, c, new_socket;
    struct sockaddr_in server, client;
    char *message, client_reply[2000];

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_desc == -1)
    {
        printf("Não foi possivel ciar o socket!\n");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if (bind(socket_desc, (struct sockaddr *) &server,sizeof(server)) < 0)
    {
        printf("Erro ao fazer o bind!\n");
        return 1;
    }

    printf("Bind efetuado.\n");

    listen(socket_desc, 3);

    printf("Aguardando conexões...\n");

    c = sizeof(struct sockaddr_in);
    while((new_socket = accept(socket_desc, (struct sockaddr *) &client, (socklen_t *) &c)))
    {
        char *client_ip = inet_ntoa(client.sin_addr);
        int client_port = ntohs(client.sin_port);

        printf("Conexão aceita do cliente %s:%d\n", client_ip, client_port);

        message = "Olá cliente!";
        if (recv(new_socket, client_reply, 2000, 0) < 0 ){
            printf("Falha no recv!\n");
            return 1;
        }
        printf("Resposta Recebida.\n");
        printf("%s\n", client_reply);

        write(new_socket, message, strlen(message));
    }
    
    if (new_socket < 0)
    {
        printf("Erro ao aceitar conexão!\n");
        return 1;
    }

    return 0;
}