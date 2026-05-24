#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <string.h>


typedef struct frame{
    int type;
    int seqno;
    char data[100];
  }Frame;
  
void stopwaitclient(){ 
  int seq = 0;
  
  int client = socket(AF_INET,SOCK_STREAM,0);

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(1235);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  connect(client,(struct sockaddr*)&addr,sizeof(addr));
  
  Frame frame,ack;
  
  struct timeval tv; // Timeout for recv
  tv.tv_sec = 3;
  tv.tv_usec = 0;
  
  setsockopt(client,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));

  while(1){
  
    printf("Enter the message \n");
    fgets(frame.data,sizeof(frame.data),stdin);
    size_t adrlen = strlen(frame.data);
    if (frame.data[adrlen - 1] == '\n'){
        frame.data[adrlen - 1] = '\0';
    }
    frame.type = 1;
    frame.seqno = seq;
    
    // Send the frame and start timer resend on timeout
    while(1){
      send(client,&frame,sizeof(frame),0);
      int n = recv(client,&ack,sizeof(ack),0);
      if (n < 0){
        printf("Timeout Occured Resending it\n");
        continue;
      } 
      if (ack.type == 0 && ack.seqno == seq){
        printf("Ack received sending next frame\n");
        break;
      }    
    }
    seq = 1 - seq;    
    }   
  close(client);
  } 



