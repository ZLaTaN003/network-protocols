#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <string.h>


void tcpserver(){

  int server = socket(AF_INET,SOCK_STREAM,0);

  
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(1235);
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(server,(struct sockaddr*)&addr,sizeof(addr));
  
  listen(server,0);
  int client = accept(server,NULL,NULL);
  
  char cmsg[100];
  char msg[100];
  printf("Enter the Message\n");
  while(1){
    int n = recv(client,cmsg,sizeof(cmsg),0);
    cmsg[n] = '\0';
  
    fgets(msg, sizeof(msg), stdin);
    size_t len = strlen(msg);
    
    if (msg[len - 1] == '\n'){
        msg[len - 1] = '\0';
    }
    send(client,msg,strlen(msg),0);
    
    printf("You said: %s\n",msg);
    printf("Client said: %s\n",cmsg);
  }

} 
