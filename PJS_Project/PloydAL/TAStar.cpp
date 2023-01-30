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
		// ���� ���������� ���Ѵ�� �� �� �ִٴ� �÷��׸� �־���� �Ѵ�.
		m_Walls.push_back(index);
	}

	// 2���� �迭
	void TMapGenerator::Init()
	{
		// ��� ����� ����
		DWORD dwNumNodes = m_WorldSize.x* m_WorldSize.y;
		// ���̺��� �����ؾ� �Ѵ�.
		DWORD _dwNumPathList = dwNumNodes * dwNumNodes;
		// 2���� �迭�� 1�������� ��ģ��.
		_AllPathList.resize(_dwNumPathList);
		// �����忡�� ������� �� ��
		// ��ü ���
		for (int x = 0; x < m_WorldSize.x; x++)
		{
			for (int y = 0; y < m_WorldSize.y; y++)
			{
				// �ε��� �ȿ��ִ� ���� ����Ʈ�� ������
				TIndex index(x, y);
				auto iter = std::find(m_Walls.begin(), m_Walls.end(), index);
				// ��� ��带 ������� �ϵ� �� ����� 1�� �Ѵ�. 
				// ���� �� �� ���°��� -1�� �Ѵ�.
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
		// x, y�� ����� �Ѵ�.
		// ������ ���°� �ƴ϶� ������ ����.
		// ���� ��忡�� 8������鸸 ���� �����ִ�
		for (int node = 0; node < dwNumNodes; node++)
		{
			std::vector<int> cost;
			cost.resize(dwNumNodes);
			for (int y = 0; y < dwNumNodes; y++)
			{
				for (int x = 0; x < dwNumNodes; x++)
				{
					// ���� ��忡�� ��ü�������� ������.
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
					// �ڱ� �ڽ��϶�
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