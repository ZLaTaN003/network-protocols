CC = gcc

OBJ = main.o tcpserver.o tcpclient.o udpserver.o udpclient.o \
stopnwaitarqserver.o stopnwaitarqclient.o gobackarqserver.o \
gobackarqclient.o selectiverepeatarqserver.o \
selectiverepeatarqclient.o leakybucket.o distancevector.o \
ftpserver.o ftpclient.o

program: $(OBJ)
	$(CC) $(OBJ) -o program

%.o: %.c
	$(CC) -c $<

clean:
	rm -f *.o program
