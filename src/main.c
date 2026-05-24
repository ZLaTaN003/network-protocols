#include <stdio.h>
#include <string.h>

#include "datalink.h"
#include "tcp.h"
#include "udp.h"
#include "network.h"
#include "application.h"

int main(int argc, char *argv[]) {

      if(argc < 3) {
         printf("Usage:\n");
         printf("%s tcp server\n", argv[0]);
         printf("%s tcp client\n", argv[0]);
         printf("%s udp server\n", argv[0]);
         printf("%s udp client\n", argv[0]);
         printf("%s ftp server\n", argv[0]);
         printf("%s ftp client\n", argv[0]);
         printf("%s stopwait server\n", argv[0]);
         printf("%s stopwait client\n", argv[0]);
         printf("%s goback server\n", argv[0]);
         printf("%s goback client\n", argv[0]);
         printf("%s selective server\n", argv[0]);
         printf("%s selective client\n", argv[0]);
         printf("%s network leakybucket\n", argv[0]);
         printf("%s network dvp\n", argv[0]);
        return 1;
    }
      
    
    
    if(strcmp(argv[1], "tcp") == 0) {
        if(strcmp(argv[2], "server") == 0) {
            tcpserver();
        }
        else if(strcmp(argv[2], "client") == 0) {
            tcpclient();
        }
        else {
            printf("Invalid TCP option\n");
        }
    }
    else if(strcmp(argv[1], "udp") == 0) {
        if(strcmp(argv[2], "server") == 0) {
            udpserver();
        }
        else if(strcmp(argv[2], "client") == 0) {
            udpclient();
        }
        else {
            printf("Invalid UDP option\n");
        }
    }
    else if(strcmp(argv[1], "ftp") == 0) {
        if(strcmp(argv[2], "server") == 0) {
            ftpserver();
        }
        else if(strcmp(argv[2], "client") == 0) {
            ftpclient(argv[3],argv[4]);
        }
        else {
            printf("Invalid FTP option\n");
        }
    }
    else if(strcmp(argv[1], "stopwait") == 0) {
        if(strcmp(argv[2], "server") == 0) {
            stopwaitserver();
        }
        else if(strcmp(argv[2], "client") == 0) {
            stopwaitclient();
        }
        else {
            printf("Invalid Stop-and-Wait option\n");
        }
    }
    else if(strcmp(argv[1], "goback") == 0) {
        if(strcmp(argv[2], "server") == 0) {
            gobackarqserver();
        }
        else if(strcmp(argv[2], "client") == 0) {
            gobackarqclient();
        }
        else {
            printf("Invalid Go-Back-N option\n");
        }
    }
    else if(strcmp(argv[1], "selective") == 0) {
        if(strcmp(argv[2], "server") == 0) {
            selectiverepeatarqserver();
        }
        else if(strcmp(argv[2], "client") == 0) {
            selectiverepeatarqclient();
        }
        else {
            printf("Invalid Selective Repeat option\n");
        }
    }
    else if(strcmp(argv[1], "network") == 0) {
        if(strcmp(argv[2], "leakybucket") == 0) {
            leakybucket();
        }
        else if(strcmp(argv[2], "dvp") == 0) {
            dvp();
        }
        else {
            printf("Invalid Network option\n");
        }
    }
    else {
        printf("Invalid protocol\n");
    }

    return 0;
}
