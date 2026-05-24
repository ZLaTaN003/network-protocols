#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>

void ftpclient(char ip[], char fname[]){

 
  int server = socket(AF_INET,SOCK_STREAM,0);

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(1234);
  addr.sin_addr.s_addr = inet_addr(ip);
  connect(server,(struct sockaddr*)&addr,sizeof(addr));
  

  send(server,fname,strlen(fname)+1,0);
  
  int n;
  char content[100];
  while(1){
    n = recv(server,content,sizeof(content),0);
    if (n <= 0){
      break;
    }
    content[n] = '\0';
    printf("%s",content);
  }
 printf("\nFile transfer complete.\n");
 close(server);

}
