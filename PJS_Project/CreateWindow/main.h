#pragma once
#include "MyWindow.h"
class main : public MyWindow
{
public:
	bool Init();			// �ʱ�ȭ	
	bool Frame();			// �ǽð� ���
	bool Render();		// ������
	bool Realese();		// �Ҹ� �� ����
};

