#include <winsock2.h>
#include<stdio.h>
#include"custom.h"

int hello_client(int argc, char* argv[]) {
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	char messages[30];
	int strLen;

	if (argc != 3) {
		printf("Usage: %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		error_handling("WSAStartup() error!");
	}

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET) {
		error_handling("socket() error");
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2]));

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR){
		error_handling("connect error");
	}
	strLen = recv(hSocket, messages, sizeof(messages) - 1, 0);

	if (strLen == -1){
		error_handling("read error");
	}
	printf("Message from server %s", messages);

	closesocket(hSocket);
	WSACleanup();
	return 0;

}

