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
		// 모든 노드의 리스트를 비용을 넣어서 -1이면 갈수 없고 1이면 갈 수 있다
		// 모든 노드의 이동가능 여부
		std::vector<int> _AllNodeList;

		std::vector<std::vector<int>> _AllPathCostList;
	public:
		void SetWorldSize(TIndex ws);
		void AddColision(TIndex ws);
		// 1) 2차원 배열 생성
		// Init 는 월드 사이즈 충돌체 작업 후 되야 한다.
		void Init();
		// 3중 for 순회 하면서 모든 노드 리스트 구축
		void AllPathGenerator();

		// 리스트 구축후 길을 리턴해준다.
		pathlist findpath(TIndex start, TIndex end);

		bool DetectCollision(TIndex coord);
		Node* findNodeList(NodeSet& list, TIndex newIndex);
		uint Distance(TIndex src, TIndex target);
		void DeleteNodes(NodeSet& nodes);
		TMapGenerator();
	};
}


