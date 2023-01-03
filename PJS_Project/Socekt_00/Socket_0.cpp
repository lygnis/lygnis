#include <WinSock2.h>
#include <iostream>
#define SERVER_CODE
#ifndef SERVER_CODE

#endif // !SERVER_CODE

int main()
{
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	// 소켓 설정
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	// 클라이언트
	// sockaddr 바이트 단위를 지정해줘야 한다. 불편함
	SOCKADDR_IN sa;												// 바이트 단위로 하는것보다 편하다.
	sa.sin_family = AF_INET;									// 고정
	sa.sin_addr.s_addr = inet_addr("192.168.0.12");					// IP 주소 스트링을 4바이트로 바꿔줘야 한다.
	sa.sin_port = htons(10000);									// 포트번호
	
	// IP에 포트번호로 접속하라
	int iRet = connect(sock, (sockaddr*)&sa, sizeof(sa));// 목적지, 포트);
	if (iRet == SOCKET_ERROR)		// -1은 접속 실패 오류
		return 1;

	char szMsg[256] = { 0, };
	fgets(szMsg, 256, stdin);
	int iSendBytes = send(sock, szMsg, strlen(szMsg), 0);							// 보낼때 메모리에 있는 바이트를 얼마만큼 보낸다.

	char szRecvMsg[256] = { 0, };
	recv(sock, szRecvMsg, 256, 0);															// 받을때
	printf("%s\n", szRecvMsg);
	closesocket(sock);				// 소켓을 만들면 무조건 닫아줘야 한다.
	WSACleanup();
}