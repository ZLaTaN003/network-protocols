# Implementation of Computer Network Protocols

A modular implementation of common Computer Network protocols and algorithms in C.

## Implemented Protocols

* TCP Client/Server
* UDP Client/Server
* FTP Client/Server
* Stop-and-Wait ARQ
* Go-Back-N ARQ
* Selective Repeat ARQ
* Leaky Bucket Algorithm
* Distance Vector Routing Protocol

## Build

```bash
make
```

## Usage

```bash
./program tcp server
./program tcp client

./program udp server
./program udp client

./program ftp server
./program ftp client <ip> <filename>

./program stopwait server
./program stopwait client

./program goback server
./program goback client

./program selective server
./program selective client

./program network leakybucket
./program network dvp
```

## Clean

```bash
make clean
```
