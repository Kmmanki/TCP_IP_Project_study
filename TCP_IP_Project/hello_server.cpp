#include <winsock2.h>
#include<stdio.h>
#include"custom.h"

void error_handling(const char* message);


int hello_server(int argc, char *argv[]) {
	WSADATA wsaData;
	SOCKET hServerSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;

	int szclntAddr;
	char messages[] = "hello wold\n";

	if (argc != 2) {
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		error_handling("WSAStartup() error!");
	}

	hServerSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServerSock == -1) {
		error_handling("socket() error");
	}

	memset(&servAddr, 0, sizeof(servAddr));

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));

	if (bind(hServerSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		error_handling("bind error");
	}

	if (listen(hServerSock, 5) == SOCKET_ERROR)
		error_handling("listen error");

	szclntAddr = sizeof(clntAddr);

	hClntSock = accept(hServerSock, (SOCKADDR*)&clntAddr, &szclntAddr);
	if (hClntSock == INVALID_SOCKET)
		error_handling("accept error");

	send(hClntSock, messages, sizeof(messages), 0);

	closesocket(hClntSock);
	closesocket(hServerSock);
	WSACleanup();
	return 0;
}

void error_handling(const char* message)
{
	fputs(message, stderr); //문자열 출력
	fputc('\n', stderr); //문자 출력
	exit(1);
}