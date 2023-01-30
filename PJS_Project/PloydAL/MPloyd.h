#pragma once
#include "PloydStd.h"
namespace MPloyd
{
	using uint = unsigned int;
	using pathlist = std::vector<TIndex>;
	//using Rowpath = std::vector<pathlist>;
	struct Node
	{
		uint G, H;
		TIndex index;
		Node* parent;
		uint  GetScore()
		{
			return G + H;
		}
		Node(TIndex i, Node* parent = nullptr)
		{
			index = i;
			this->parent = parent;
			G = H = 0;
		}
	};
	using NodeSet = std::set<Node*>;

	class TMapGenerator
	{
	private:
		TIndex  m_WorldSize;
		uint    m_Direction;
		pathlist m_Direction8;
		pathlist m_Walls;
		std::vector<pathlist> _AllPathList;
		// ��� ����� ����Ʈ�� ����� �־ -1�̸� ���� ���� 1�̸� �� �� �ִ�
		// ��� ����� �̵����� ����
		std::vector<int> _AllNodeList;

		std::vector<std::vector<int>> _AllPathCostList;
	public:
		void SetWorldSize(TIndex ws);
		void AddColision(TIndex ws);
		// 1) 2���� �迭 ����
		// Init �� ���� ������ �浹ü �۾� �� �Ǿ� �Ѵ�.
		void Init();
		// 3�� for ��ȸ �ϸ鼭 ��� ��� ����Ʈ ����
		void AllPathGenerator();

		// ����Ʈ ������ ���� �������ش�.
		pathlist findpath(TIndex start, TIndex end);

		bool DetectCollision(TIndex coord);
		Node* findNodeList(NodeSet& list, TIndex newIndex);
		uint Distance(TIndex src, TIndex target);
		void DeleteNodes(NodeSet& nodes);
		TMapGenerator();
	};
}


