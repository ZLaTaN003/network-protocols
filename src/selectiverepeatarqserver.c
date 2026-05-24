#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct frame{
    int type;
    int seqno;

  }Frame;
  
int selectiverepeatarqserver(){
  int server = socket(AF_INET,SOCK_STREAM,0);
  int received[100] = {0};

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(1235);
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(server,(struct sockaddr*)&addr,sizeof(addr));
  
  listen(server,0);
  int client = accept(server,NULL,NULL);

  Frame frame,ack;
  while(1){
    recv(client,&frame,sizeof(frame),0);
    
    if(rand() % 4 == 0){  // send nack for corrupted
      printf("Corrupted frame seqno=%d\n",frame.seqno);
      ack.seqno = frame.seqno;
      ack.type = -1;
      send(client,&ack,sizeof(ack),0);
      sleep(2);
      continue;
    }
    else{
       if (!received[frame.seqno]){ // accept the frame which have not been accepted yet in any order and send ack
          printf("Frame %d received\n",frame.seqno);
          received[frame.seqno] = 1;
       }
       else{
          printf("Duplicate frame : %d\n", frame.seqno);
          sleep(2);
       }
       ack.seqno = frame.seqno;
       ack.type = 0;

       send(client,&ack,sizeof(ack),0);
       printf("ACK sent : %d\n", frame.seqno);    
    }
  }
  
  close(server);
  close(client);
}
