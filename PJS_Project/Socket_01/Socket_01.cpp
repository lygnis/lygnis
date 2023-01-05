#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>

// ������ �����Լ� ������ ������
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

		int iSendBytes = send(sock_1, szMsg, strlen(szMsg), 0);							// ������ �޸𸮿� �ִ� ����Ʈ�� �󸶸�ŭ ������.
		if (iSendBytes == SOCKET_ERROR)		// -1�� ���� ���� ����
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				// �ֱ� ������ ��ȯ�Ѵ�.
				//WSAEWOULDBLOCK ���ƴ϶�� ����
				closesocket(sock_1);
				return 1;
			}
		}
	}
	closesocket(sock_1);

}
//// ���� ����
//// �������� ������ ���ظ� ���� �ʱ� ���� �ͺ������� �ٲ��ش�
//// ���� ����-> �ͺ��� ���� ���� �ٲ�����Ѵ�.
//// �ͺ��� ������ �׳� ��ȯ�Ҷ��� �ֱ� ������ ������ ó������� �Ѵ�.
//SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
//u_long iMode = 1;
//ioctlsocket(sock, FIONBIO, &iMode);							// true �� ���� ������ �ͺ��� �������� �ٲ��ش�. �� �ݴ뵵 ����

int main()
{
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	// Ŭ���̾�Ʈ
	// sockaddr ����Ʈ ������ ��������� �Ѵ�. ������
	SOCKADDR_IN sa;												// ����Ʈ ������ �ϴ°ͺ��� ���ϴ�.
	sa.sin_family = AF_INET;									// ����
	sa.sin_addr.s_addr = inet_addr("192.168.0.12");					// IP �ּ� ��Ʈ���� 4����Ʈ�� �ٲ���� �Ѵ�.
	sa.sin_port = htons(10000);									// ��Ʈ��ȣ
		// IP�� ��Ʈ��ȣ�� �����϶�
		// ������ �Ǽ� ��ȯ�� �Ǵ°����� ������ ��ȯ�Ǵ°��� ������ �ȵǵ� ��ȯ�� �Ǵ°��� Ȯ���ؾ��Ѵ�.
	int iRet = connect(sock, (sockaddr*)&sa, sizeof(sa));// ������, ��Ʈ);
	if (iRet == SOCKET_ERROR)		// -1�� ���� ���� ����
	{
		int iError = WSAGetLastError();
		printf("%d", iError);
		return 1;
	}
	// win api�� ����� ������ ����
	DWORD dwThreadID;				// ������ ID
	HANDLE hClient = CreateThread(0, 0, SendThread, (LPVOID)sock, 0, &dwThreadID);
	u_long iMode = TRUE;
	ioctlsocket(sock, FIONBIO, &iMode);

	// recv
	while (1)
	{
		char szRecvMsg[256] = { 0, };
		int iRecvBytes = recv(sock, szRecvMsg, 256, 0);															// ������
		if (iRecvBytes == 0)
		{
			printf("���� ��������\n");
			break;
		}
		if (iRecvBytes == SOCKET_ERROR)		// -1�� ���� ���� ����
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				// �ֱ� ������ ��ȯ�Ѵ�.
				//WSAEWOULDBLOCK ���ƴ϶�� ����
				closesocket(sock);
				printf("���� ������ ����\n");
				return 1;
			}
			continue;
		}
		printf("Recv--->%s\n", szRecvMsg);
	}
	CloseHandle(hClient);
	closesocket(sock);				// ������ ����� ������ �ݾ���� �Ѵ�.
	WSACleanup();
}