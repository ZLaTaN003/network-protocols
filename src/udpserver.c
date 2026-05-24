#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


void udpserver(){

  int server = socket(AF_INET,SOCK_DGRAM,0);
  
  struct sockaddr_in addr,client_addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(1234);
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(server,(struct sockaddr*)&addr,sizeof(addr));
  
  
  char cmsg[100];
  char msg[100];
  socklen_t adrlen = sizeof(client_addr);
  printf("Enter the Message\n");
  while(1){
  
  int n = recvfrom(server,cmsg,sizeof(cmsg),0,(struct sockaddr*)&client_addr,&adrlen);
  cmsg[n] = '\0';

  fgets(msg, sizeof(msg), stdin);
  size_t len = strlen(msg);
  
  if (msg[len - 1] == '\n'){
      msg[len - 1] = '\0';
    }
    
  sendto(server,msg,strlen(msg),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
  printf("You said: %s\n",msg);
  printf("Client said: %s\n",cmsg);
  
  }
 
  
  close(server);

} 
