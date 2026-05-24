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
  
void gobackarqserver(){
  int server = socket(AF_INET,SOCK_STREAM,0);

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(1235);
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(server,(struct sockaddr*)&addr,sizeof(addr));
  
  listen(server,0);
  int client = accept(server,NULL,NULL);
  
  Frame frame,ack;
  int expected = 0; // The next frame seq that receiver expects
  while(1){
    recv(client,&frame,sizeof(frame),0);
    
    if (rand() % 4 == 0){
      printf("Corrupted frame seqno=%d\n",frame.seqno); // on corruption send nack
      ack.seqno = frame.seqno;
      ack.type = -1;
      send(client,&ack,sizeof(ack),0);
      sleep(2);
      continue;
    }
    else if (frame.seqno == expected){
       printf("Frame %d received\n",frame.seqno); // send ack and incement expected frame seq
       ack.seqno = frame.seqno;
       ack.type = 0;
       send(client,&ack,sizeof(ack),0);
       expected++; 
       
    }
    else {
      printf("Discarded Frame %d\n",frame.seqno); // reject out of order frames
      sleep(2);
      }  
  }
  
  close(server);
  close(client);
}
