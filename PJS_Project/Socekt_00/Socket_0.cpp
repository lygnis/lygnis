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
	sa.sin_addr.s_addr = inet_addr("192.168.0.12");					// IP �ּ� ��Ʈ���� 4����Ʈ�� �ٲ���� �Ѵ�.
	sa.sin_port = htons(10000);									// ��Ʈ��ȣ
	
	// IP�� ��Ʈ��ȣ�� �����϶�
	int iRet = connect(sock, (sockaddr*)&sa, sizeof(sa));// ������, ��Ʈ);
	if (iRet == SOCKET_ERROR)		// -1�� ���� ���� ����
		return 1;

	char szMsg[256] = { 0, };
	fgets(szMsg, 256, stdin);
	int iSendBytes = send(sock, szMsg, strlen(szMsg), 0);							// ������ �޸𸮿� �ִ� ����Ʈ�� �󸶸�ŭ ������.

	char szRecvMsg[256] = { 0, };
	recv(sock, szRecvMsg, 256, 0);															// ������
	printf("%s\n", szRecvMsg);
	closesocket(sock);				// ������ ����� ������ �ݾ���� �Ѵ�.
	WSACleanup();
}