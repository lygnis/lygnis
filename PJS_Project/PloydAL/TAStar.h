#pragma once
#include <windows.h>
#include <vector>
#include <set>
#include <iostream>

namespace AStar
{
	using uint = unsigned int;
	using pathlist = std::vector<TIndex>;
	
	struct Node
	{
		uint G, H;
		TIndex index;
		Node* parent;
		uint  GetScore()
		{
			return G + H;
		}
		Node(TIndex i, Node* parent =nullptr)
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
	public:
		void SetWorldSize(TIndex ws);
		void AddColision(TIndex ws);
		pathlist findpath(TIndex start, TIndex end);
		bool DetectCollision(TIndex coord);
		Node* findNodeList(NodeSet& list,TIndex newIndex);
		uint Distance(TIndex src,TIndex target);
		void DeleteNodes(NodeSet& nodes);
		TMapGenerator();
	};
}

