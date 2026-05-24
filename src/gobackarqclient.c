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
  
static int client;
static int base = 0,seq=0;
static int windowsize = 4;

void *gobacksenddata(){
  while(1){
    while (seq - base < windowsize){ // keep sending everything inside the window
      Frame frame;
      frame.type = 1;
      frame.seqno = seq;
      send(client,&frame,sizeof(frame),0);
      printf("Sent frame %d\n",frame.seqno);
      seq++;    
    }
  }
}

void *gobackreceivedata(){
  while(1){
    Frame ack;
    recv(client,&ack,sizeof(ack),0);
    if(ack.type == 0){ // on ack increment the base or slide the window forward
      printf("ACK %d received\n",ack.seqno);
      if(ack.seqno >= base) {
        base = ack.seqno + 1;
           }
       sleep(1);

   }
    else if(ack.type == -1){ // on nack goback to seqno of the corrupted frame for resending everything from it
     seq = ack.seqno;
     printf("Go Back and resend from %d\n", ack.seqno);
    }
 
     }


}
void gobackarqclient(){
  client = socket(AF_INET,SOCK_STREAM,0);
  
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(1235);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  connect(client,(struct sockaddr*)&addr,sizeof(addr));
  
  Frame frame,ack;
  
  pthread_t sender,receiver; // Client simultaneously send data and receive ack or nack
  pthread_create(&sender,NULL,gobacksenddata,NULL);
  sleep(1);
  pthread_create(&receiver,NULL,gobackreceivedata,NULL);
  sleep(1);

  while(1);
  

  close(client);

}
