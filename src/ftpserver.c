#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void ftpserver(){
  int server = socket(AF_INET,SOCK_STREAM,0);

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(1234);
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(server,(struct sockaddr*)&addr,sizeof(addr));
  
  listen(server,0);
  int client = accept(server,NULL,NULL);
  
  char str[100];
  recv(client,str,sizeof(str),0);
  printf("Client message\nFile Name : %s\n",str);
  
  FILE *f1;
  f1 = fopen(str,"r");
  if (f1 == NULL){
    printf("File don't exist");
    close(server);
    close(client);
  }
  
  char msg[100];
  while(fgets(msg,sizeof(msg),f1) != NULL){
    send(client,msg,sizeof(msg),0);
  }
  
 fclose(f1);
 printf("File Transferred\n");
 close(server);
 close(client);
 

}
