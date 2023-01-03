#define _WINSOCK_DEPRECATED_NO_WARNINGS
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
	// �������� ������ ���ظ� ���� �ʱ� ���� �ͺ������� �ٲ��ش�
	// ���� ����-> �ͺ��� ���� ���� �ٲ�����Ѵ�.
	// �ͺ��� ������ �׳� ��ȯ�Ҷ��� �ֱ� ������ ������ ó������� �Ѵ�.
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	u_long iMode = 1;
	ioctlsocket(sock, FIONBIO, &iMode);							// true �� ���� ������ �ͺ��� �������� �ٲ��ش�. �� �ݴ뵵 ����
	//iMode = 0;
	// �ͺ����̸� ������ �Ⱥ����� ������ ��ȯ�ǵ��� �Ѵ�.
	
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
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			// �ֱ� ������ ��ȯ�Ѵ�.
			//WSAEWOULDBLOCK ���ƴ϶�� ����
			return 1;
		}
		// WSAEWOULDBLOCK �̸� �׳� ��ȯ�Ѱ� �׷��� �ٽ� Ŀ������ �� �� �ִ�.
		// ������ ����
	}
	char szMsg[256] = { 0, };
	fgets(szMsg, 256, stdin);
	while (1)
	{
		int iSendBytes = send(sock, szMsg, strlen(szMsg), 0);							// ������ �޸𸮿� �ִ� ����Ʈ�� �󸶸�ŭ ������.
		if (iSendBytes == SOCKET_ERROR)		// -1�� ���� ���� ����
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				// �ֱ� ������ ��ȯ�Ѵ�.
				//WSAEWOULDBLOCK ���ƴ϶�� ����
				closesocket(sock);
				return 1;
			}
			continue;
		}
		break;
	}
	char szRecvMsg[256] = { 0, };
	while (1)
	{
		int iRecvBytes = recv(sock, szRecvMsg, 256, 0);															// ������
		if (iRecvBytes == SOCKET_ERROR)		// -1�� ���� ���� ����
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				// �ֱ� ������ ��ȯ�Ѵ�.
				//WSAEWOULDBLOCK ���ƴ϶�� ����
				closesocket(sock);
				return 1;
			}
			continue;
		}
		break;
	}
	printf("%s\n", szRecvMsg);
	closesocket(sock);				// ������ ����� ������ �ݾ���� �Ѵ�.
	WSACleanup();
}