#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int main(void) {
  int meu_socket;
  struct sockaddr_in endereco_server;
  char mensagem_servidor[500], mensagem_cliente[500];

  memset(mensagem_servidor, '\0', sizeof(mensagem_servidor));
  memset(mensagem_cliente, '\0', sizeof(mensagem_cliente));

  meu_socket = socket(AF_INET, SOCK_STREAM, 0);

  if (meu_socket < 0) {
    printf("criacao de socket falhou\n");
    return -1;
  }

  endereco_server.sin_family = AF_INET;
  endereco_server.sin_port = htons(2000);
  endereco_server.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(meu_socket, (struct sockaddr *)&endereco_server,
              sizeof(endereco_server)) < 0) {
    printf("Unable to connect\n");
    return -1;
  }
  printf("Connected with server successfully\n");

  printf("Enter message: ");
  gets(mensagem_cliente);

  if (send(meu_socket, mensagem_cliente, strlen(mensagem_cliente), 0) < 0) {
    printf("Unable to send message\n");
    return -1;
  }

  if (recv(meu_socket, mensagem_servidor, sizeof(mensagem_servidor), 0) < 0) {
    printf("Error while receiving server's msg\n");
    return -1;
  }

  printf("Server's response: %s\n", mensagem_servidor);

  close(meu_socket);

  return 0;
}
