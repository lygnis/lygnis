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
	// ���� ����
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	// Ŭ���̾�Ʈ
	// sockaddr ����Ʈ ������ ��������� �Ѵ�. ������
	SOCKADDR_IN sa;												// ����Ʈ ������ �ϴ°ͺ��� ���ϴ�.
	sa.sin_family = AF_INET;									// ����
	sa.sin_addr.s_addr = htonl(INADDR_ANY);				// ��� IP�� �����Ѵ�.
	sa.sin_port = htons(10000);									// ��Ʈ��ȣ

	// IP�� ��Ʈ��ȣ�� �����϶�
	int iRet = bind(sock, (sockaddr*)&sa, sizeof(sa));// ������, ��Ʈ);
	if (iRet == SOCKET_ERROR)		// -1�� ���� ���� ����
		return 1;
	iRet = listen(sock, SOMAXCONN);						// ��´�
	if (iRet == SOCKET_ERROR)
		return 1;

	// ���ӵǸ� ��ȯ�ȴ�. ���Ͽ� ���ӵǸ� ��ȯ�ȴ�.
	SOCKADDR_IN clientSD;		// Ŭ���̾�Ʈ ����
	int length = sizeof(clientSD);
	SOCKET clientSock = accept(sock, (sockaddr*)&clientSD, &length);				// ������ ������ accept �Լ��� ������ ��ȯ�Ѵ�.
	printf("Ŭ���̾�Ʈ ���� : IP:%s, PORT:%d\n",
		inet_ntoa(clientSD.sin_addr), ntohs(clientSD.sin_port));																		// ������ ����Ѵ�.
	char szRecvMsg[256] = { 0, };
	int iRecvBytes = recv(clientSock, szRecvMsg, 256, 0);															// ������
	printf("%s\n", szRecvMsg);

	int iSendBytes = send(clientSock, szRecvMsg, strlen(szRecvMsg), 0);				// echo �ý��� ������ �״�� ��ȯ���ش�.
	closesocket(clientSock);				// ������ ����� ������ �ݾ���� �Ѵ�.
	WSACleanup();
}