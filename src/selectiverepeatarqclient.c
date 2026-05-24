#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

typedef struct frame{
    int type;
    int seqno;

  }Frame;

static int base=0,seq =0;
static int windowsize = 3;
static int client;
static int acked[100] = {0};

void *srsenddata(){
  while(1){
    while((seq - base) < windowsize){  // keep sending everything in window
      Frame frame;
      frame.type = 1;
      frame.seqno = seq;
      send(client,&frame,sizeof(frame),0);
      printf("Sent frame %d\n",frame.seqno);
      seq++;
  }
  }
}

void *srreceivedata(){
  while(1){
    Frame ack;
    recv(client,&ack,sizeof(ack),0);
    
    if(ack.type == 0){ // store the acked frames slide the window cumulatively
      printf("ACK %d received\n",ack.seqno);
      acked[ack.seqno] = 1;

      while(acked[base]){
        base++;
      }
      sleep(1);
      
   }
   else if (ack.type == -1){ // on nack selectively resend the corrupted frame
     Frame frame;
     printf("Select and Repeat the frame %d\n", ack.seqno);
     frame.type = 1;
     frame.seqno= ack.seqno;
     send(client,&frame,sizeof(frame),0);
     
    }
     }

}
void selectiverepeatarqclient(){
  client = socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(1235);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  connect(client,(struct sockaddr*)&addr,sizeof(addr));
  
  Frame frame,ack;
  
  pthread_t sender,receiver;
  pthread_create(&sender,NULL,srsenddata,NULL);
  sleep(1);
  pthread_create(&receiver,NULL,srreceivedata,NULL);
  sleep(1);

  while(1);
  

  close(client);

}
