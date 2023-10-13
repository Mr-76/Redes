#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
void mensagemFinal(char *mensagem_servidor, char *mensagem_cliente) {

  // servidor
  char nomeServidor[40];
  char valorServidor[40];

  // nomeServidor clioente nomeServidor servidor valorServidor cliente
  // valorServidor servidor e a soma

  char delimitador[] = " ";
  char *nomeServer = strtok(mensagem_servidor, delimitador);

  strncpy(nomeServidor, nomeServer, sizeof(nomeServidor));

  char *valorServer = strtok(NULL, delimitador);

  strncpy(valorServidor, valorServer, sizeof(nomeServidor));
  int valor_server = atoi(valorServidor);

  char nomeCliente[40];
  char valorCliente[40];

  // cliente
  char *nomeClientetok = strtok(mensagem_cliente, delimitador);

  strncpy(nomeCliente, nomeClientetok, sizeof(nomeCliente));


  char *valorClientetok = strtok(NULL, delimitador);

  strncpy(valorCliente, valorClientetok, sizeof(valorCliente));

  int valor_cliente = atoi(valorCliente);

  int soma = valor_server + valor_cliente;

  printf("nome cliente: %s | nome server: %s | valor cliente: %d | valor "
         "servidor %d| soma %d\n",
         nomeCliente, nomeServidor, valor_cliente, valor_server, soma);
}

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

  mensagemFinal(mensagem_servidor, mensagem_cliente);

  close(meu_socket);

  return 0;
}
