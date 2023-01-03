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
	sa.sin_addr.s_addr = htonl(INADDR_ANY);				// 모든 IP를 수용한다.
	sa.sin_port = htons(10000);									// 포트번호

	// IP에 포트번호로 접속하라
	int iRet = bind(sock, (sockaddr*)&sa, sizeof(sa));// 목적지, 포트);
	if (iRet == SOCKET_ERROR)		// -1은 접속 실패 오류
		return 1;
	iRet = listen(sock, SOMAXCONN);						// 듣는다
	if (iRet == SOCKET_ERROR)
		return 1;

	// 접속되면 반환된다. 소켓에 접속되면 반환된다.
	SOCKADDR_IN clientSD;		// 클라이언트 정보
	int length = sizeof(clientSD);
	SOCKET clientSock = accept(sock, (sockaddr*)&clientSD, &length);				// 누군가 들어오면 accept 함수는 소켓을 반환한다.
	printf("클라이언트 접속 : IP:%s, PORT:%d\n",
		inet_ntoa(clientSD.sin_addr), ntohs(clientSD.sin_port));																		// 누군지 출력한다.
	char szRecvMsg[256] = { 0, };
	int iRecvBytes = recv(clientSock, szRecvMsg, 256, 0);															// 받을때
	printf("%s\n", szRecvMsg);

	int iSendBytes = send(clientSock, szRecvMsg, strlen(szRecvMsg), 0);				// echo 시스템 받은걸 그대로 반환해준다.
	closesocket(clientSock);				// 소켓을 만들면 무조건 닫아줘야 한다.
	WSACleanup();
}