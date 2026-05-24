#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <string.h>


void tcpclient(){

  int client = socket(AF_INET,SOCK_STREAM,0);

  
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(1235);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  connect(client,(struct sockaddr*)&addr,sizeof(addr));
  
  char msg[100];
  char smsg[100];
  printf("Enter the Message\n");
  while (1){
    fgets(msg, sizeof(msg), stdin);
    size_t len = strlen(msg);
    if (msg[len - 1] == '\n'){
        msg[len - 1] = '\0';
    }
    
    send(client,msg,strlen(msg),0);
    

    int n = recv(client,smsg,sizeof(smsg),0);
    smsg[n] = '\0';
    
    printf("You said: %s\n",msg);
    printf("Server said: %s\n",smsg);

  }

  close(client);
  
}
