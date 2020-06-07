//server program

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr


void func_chat(int sockfd)
{
char buff[MAX];
int n;

for (;;) {
bzero(buff, MAX);


read(sockfd, buff, sizeof(buff));
// print buffer which contains the client content
printf("From client: %s\t To client : ", buff);
bzero(buff, MAX);
n = 0;
// copy server message in the buffer
while ((buff[n++] = getchar()) != '\n')
;

// and send that buffer to client
write(sockfd, buff, sizeof(buff));

if (strncmp("exit", buff, 4) == 0) {
printf("Server Exit...\n");
break;
}
}
}

//for  Driver
int main()
{
int sockfd, connfd, len;
struct sockaddr_in servaddr, cli;

// creating socket
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd == -1) {
printf("socket creation not successful...\n");
exit(0);
}
else
printf("Socket created successfully..\n");
bzero(&servaddr, sizeof(servaddr));

// assign IP, PORT
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(PORT);

// Binding of socket
if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
printf("socket bind failed...\n");
exit(0);
}
else
printf("Socket successfully binded..\n");


if ((listen(sockfd, 5)) != 0) {
printf("Listen failed...\n");
exit(0);
}
else
printf("Server listening..\n");
len = sizeof(cli);


connfd = accept(sockfd, (SA*)&cli, &len);
if (connfd < 0) {
printf("server acccept failed...\n");
exit(0);
}
else
printf("server acccept the client...\n");


func_chat(connfd);


close(sockfd);
}


