#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>

// 쓰레드 시작함수 보내는 쓰레드
DWORD WINAPI SendThread(LPVOID IpThreadParameter)
{
	SOCKET sock_1 = (SOCKET)IpThreadParameter;
	while (1)
	{
		char szMsg[256] = { 0, };
		printf("%s", "send--->");
		fgets(szMsg, 256, stdin);
		szMsg[strlen(szMsg) - 1] = 0;
		if (strcmp(szMsg, "exit") == 0)
		{
			break;
		}

		int iSendBytes = send(sock_1, szMsg, strlen(szMsg), 0);							// 보낼때 메모리에 있는 바이트를 얼마만큼 보낸다.
		if (iSendBytes == SOCKET_ERROR)		// -1은 접속 실패 오류
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				// 최근 에러를 반환한다.
				//WSAEWOULDBLOCK 가아니라면 오류
				closesocket(sock_1);
				return 1;
			}
		}
	}
	closesocket(sock_1);

}
//// 소켓 설정
//// 블럭형으로 했을때 피해를 받지 않기 위해 넌블럭형으로 바꿔준다
//// 블럭형 소켓-> 넌블럭형 소켓 으로 바꿔줘야한다.
//// 넌블럭형 소켓은 그냥 반환할때도 있기 때문에 조건을 처리해줘야 한다.
//SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
//u_long iMode = 1;
//ioctlsocket(sock, FIONBIO, &iMode);							// true 면 블럭형 소켓을 넌블럭형 소켓으로 바꿔준다. 그 반대도 가능

int main()
{
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	// 클라이언트
	// sockaddr 바이트 단위를 지정해줘야 한다. 불편함
	SOCKADDR_IN sa;												// 바이트 단위로 하는것보다 편하다.
	sa.sin_family = AF_INET;									// 고정
	sa.sin_addr.s_addr = inet_addr("192.168.0.12");					// IP 주소 스트링을 4바이트로 바꿔줘야 한다.
	sa.sin_port = htons(10000);									// 포트번호
		// IP에 포트번호로 접속하라
		// 접속이 되서 반환이 되는것이지 오류로 반환되는건지 접속이 안되도 반환이 되는건지 확인해야한다.
	int iRet = connect(sock, (sockaddr*)&sa, sizeof(sa));// 목적지, 포트);
	if (iRet == SOCKET_ERROR)		// -1은 접속 실패 오류
	{
		int iError = WSAGetLastError();
		printf("%d", iError);
		return 1;
	}
	// win api를 사용해 쓰레드 생성
	DWORD dwThreadID;				// 스레드 ID
	HANDLE hClient = CreateThread(0, 0, SendThread, (LPVOID)sock, 0, &dwThreadID);
	u_long iMode = TRUE;
	ioctlsocket(sock, FIONBIO, &iMode);

	// recv
	while (1)
	{
		char szRecvMsg[256] = { 0, };
		int iRecvBytes = recv(sock, szRecvMsg, 256, 0);															// 받을때
		if (iRecvBytes == 0)
		{
			printf("서버 정상종료\n");
			break;
		}
		if (iRecvBytes == SOCKET_ERROR)		// -1은 접속 실패 오류
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				// 최근 에러를 반환한다.
				//WSAEWOULDBLOCK 가아니라면 오류
				closesocket(sock);
				printf("서버 비정상 종료\n");
				return 1;
			}
			continue;
		}
		printf("Recv--->%s\n", szRecvMsg);
	}
	CloseHandle(hClient);
	closesocket(sock);				// 소켓을 만들면 무조건 닫아줘야 한다.
	WSACleanup();
}