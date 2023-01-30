#include "MPloyd.h"
namespace MPloyd
{
	TMapGenerator::TMapGenerator()
	{
		m_Direction8.push_back({ 0,-1 });
		m_Direction8.push_back({ 0,+1 });
		m_Direction8.push_back({ -1,0 });
		m_Direction8.push_back({ +1,0 });

		m_Direction8.push_back({-1,-1});		
		m_Direction8.push_back({ +1,-1 });
		m_Direction8.push_back({ -1,+1 });		
		m_Direction8.push_back({ +1,+1 });		
	}
	void TMapGenerator::SetWorldSize(TIndex ws)
	{
		m_WorldSize = ws;
	}
	void TMapGenerator::AddColision(TIndex index)
	{
		// 길이 막혀있을때 무한대로 갈 수 있다는 플래그를 넣어줘야 한다.
		m_Walls.push_back(index);
	}

	// 2차원 배열
	void TMapGenerator::Init()
	{
		// 모든 노드의 개수
		DWORD dwNumNodes = m_WorldSize.x* m_WorldSize.y;
		// 테이블을 생성해야 한다.
		DWORD _dwNumPathList = dwNumNodes * dwNumNodes;
		// 2차원 배열을 1차원으로 펼친것.
		_AllPathList.resize(_dwNumPathList);
		// 현재노드에서 현재노드로 갈 때
		// 전체 노드
		for (int x = 0; x < m_WorldSize.x; x++)
		{
			for (int y = 0; y < m_WorldSize.y; y++)
			{
				// 인덱스 안에있는 값이 리스트가 있으면
				TIndex index(x, y);
				auto iter = std::find(m_Walls.begin(), m_Walls.end(), index);
				// 모든 노드를 대상으로 하되 그 비용을 1로 한다. 
				// 그중 갈 수 없는곳은 -1로 한다.
				if (iter != m_Walls.end())
				{
					_AllNodeList[x* m_WorldSize .x+y] = -1;
				}
				else
				{
					_AllNodeList[x* m_WorldSize.x+y] = 1;
				}

			}
		}
		// x, y로 계산을 한다.
		// 밑으로 가는게 아니라 옆으로 간다.
		// 현재 노드에서 8방향노드들만 직접 갈수있다
		for (int node = 0; node < dwNumNodes; node++)
		{
			std::vector<int> cost;
			cost.resize(dwNumNodes);
			for (int y = 0; y < dwNumNodes; y++)
			{
				for (int x = 0; x < dwNumNodes; x++)
				{
					// 현재 노드에서 전체방향으로 못간다.
					//cost[]
				}
				_AllPathCostList.push_back(cost);
			}
		}
	}

	void TMapGenerator::AllPathGenerator()
	{

		for (int y = 0; y < dwNumNodes; y++)
		{
			pathlist path;
			for (int x = 0; x < dwNumNodes; x++)
			{
				TIndex index(y, x);
				if (y == x)
				{
					// 자기 자신일때
					path.push_back(index);
				}
				else
				{

				}
				path.push_back(index);
			}
			_AllPathList.push_back(path);
		}
	}

	pathlist TMapGenerator::findpath(	TIndex start,
										TIndex target)
	{
		pathlist path;
		return path;		
	}

	bool TMapGenerator::DetectCollision(TIndex coord)
	{
		if (coord.x < 0 || coord.x >= m_WorldSize.x ||
			coord.y < 0 || coord.y >= m_WorldSize.y)
		{
			return true;
		}

		if (std::find(m_Walls.begin(),
					  m_Walls.end(), coord) 
					!= m_Walls.end())
		{
			return true;
		}		
		return false;
	}
	Node* TMapGenerator::findNodeList(  NodeSet& list, 
										TIndex newIndex)
	{
		for (auto node : list)
		{
			if (node->index == newIndex)
			{
				return node;
			}
		}
		return nullptr;
	}
	uint TMapGenerator::Distance(TIndex s,TIndex t)
	{
		TIndex ret = { abs(s.x - t.x), abs(s.y - t.y)};
		//return 10 * (ret.x + ret.y);
		return sqrt(pow(ret.x, 2) + pow(ret.y, 2)) * 10;
	}
	void TMapGenerator::DeleteNodes(NodeSet& nodes)
	{
		for (auto it = nodes.begin();
			it != nodes.end();
			)
		{
			delete* it;
			it = nodes.erase(it);
		}
	}
};