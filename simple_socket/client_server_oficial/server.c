#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
int main(void) {

  int meu_socket, socket_cliente, tamanho_cliente;
  struct sockaddr_in endereco_server, endereco_cliente;

  char string_servidor[500], string_cliente[500];

  memset(string_servidor, '\0', sizeof(string_servidor));
  memset(string_cliente, '\0', sizeof(string_cliente));

  meu_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (meu_socket < 0) {
    printf("criacao de socket falhou\n");
    return -1;
  }

  // precisa para fazer o bind :)
  endereco_server.sin_family = AF_INET;
  endereco_server.sin_port = htons(2000);
  endereco_server.sin_addr.s_addr = inet_addr("127.0.0.1");
  //
  if (bind(meu_socket, (struct sockaddr *)&endereco_server,
           sizeof(endereco_server)) < 0) {
    printf("bind falhou");
    return -1;
  }

  printf("%lu", sizeof(endereco_cliente));
  // somente uma conexao
  if (listen(meu_socket, 1) < 0) { // para esperando por um cliente ate receber
    printf("error escutando\n");
    return -1;
  }

  printf("\ncliente em conexao\n");

  tamanho_cliente = sizeof(endereco_cliente);

  socket_cliente = accept(meu_socket, (struct sockaddr *)&endereco_cliente,
                          (socklen_t *)&tamanho_cliente);

  if (socket_cliente < 0) {
    printf("cant accept\n");
    return -1;
  }
  printf("Client connected at IP: %s and port: %i\n",
         inet_ntoa(endereco_cliente.sin_addr),
         ntohs(endereco_cliente.sin_port));

  // Receive client's message:
  if (recv(socket_cliente, string_cliente, sizeof(string_cliente), 0) < 0) {
    printf("nao foi recebido\n");
    return -1;
  }
  printf("mensagem do cliente %s\n", string_cliente);

  char delimitador[] = " ";

  char nome[40];
  char valor[40];

  char *ptrStringNomeCliente = strtok(string_cliente, delimitador);

  strncpy(nome, ptrStringNomeCliente, sizeof(nome));
  printf("%s\n", nome);

  char *ptrStringNumeroCliente = strtok(NULL, delimitador);
  strncpy(valor, ptrStringNumeroCliente, sizeof(nome));
  int valor_cliente = atoi(valor);

  // printf("%s\n", ptrStringNumeroCliente);
  int random = (rand() % 100);
  int soma = random + valor_cliente;
  printf("valor do cliente %d\n valor do servidor %d\n valor da soma %d\n",
         valor_cliente, random, soma);

  printf("\ndepois de formatar\n");

  char str_retorno[10];
  sprintf(str_retorno, "%d", random);

  strcpy(string_servidor, str_retorno);

  if (send(socket_cliente, string_servidor, strlen(string_servidor), 0) < 0) {
    printf("nao pode mandar\n");
    return -1;
  }

  close(socket_cliente);
  close(meu_socket);

  return 0;
}
