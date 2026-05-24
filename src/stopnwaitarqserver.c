#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <string.h>

typedef struct frame{
    int type; // data=1 ack=0 corrupt=-1
    int seqno;
    char data[100];
  }Frame;
  
void stopwaitserver(){
  int server = socket(AF_INET,SOCK_STREAM,0);

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(1235);
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(server,(struct sockaddr*)&addr,sizeof(addr));
  
  listen(server,0);
  int client = accept(server,NULL,NULL);
  
  Frame frame,ack;
  // Get incoming frame and send back ack
  while(1){
    recv(client,&frame,sizeof(frame),0);
    printf("Frame Received of seq=%d data=%s",frame.seqno,frame.data);
    
    if (frame.type == 1){ 
      ack.type = 0;
      ack.seqno = frame.seqno;
      send(client,&ack,sizeof(ack),0);
      printf("ACK is sent for the seq %d \n",ack.seqno);
      
    }
    
  }
  
  close(server);
  close(client);
}
