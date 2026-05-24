#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


void udpclient(){

  int client = socket(AF_INET,SOCK_DGRAM,0);

  
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(1234);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  
  char msg[100];
  char smsg[100];
  socklen_t adrlen = sizeof(addr);
  printf("Enter the Message\n");
  while(1){
  
  fgets(msg, sizeof(msg), stdin);
  size_t len = strlen(msg);
  
  if (msg[len - 1] == '\n'){
      msg[len - 1] = '\0';
    }
  sendto(client,msg,strlen(msg),0,(struct sockaddr*)&addr,sizeof(addr));

  int n = recvfrom(client,smsg,sizeof(smsg),0,(struct sockaddr*)&addr,&adrlen);
  smsg[n] = '\0';

  
  printf("You said: %s\n",msg);
  printf("Server said: %s\n",smsg);
    
  }

  close(client);
  }
 



