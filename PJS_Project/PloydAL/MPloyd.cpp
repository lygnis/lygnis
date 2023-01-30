#include "MPloyd.h"

namespace AStar
{
	TMapGenerator::TMapGenerator()
	{
		m_Direction8.push_back({ 0,-1 });
		m_Direction8.push_back({ 0,+1 });
		m_Direction8.push_back({ -1,0 });
		m_Direction8.push_back({ +1,0 });

		m_Direction8.push_back({ -1,-1 });
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
		m_Walls.push_back(index);
	}

	pathlist TMapGenerator::findpath(TIndex start,
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
	Node* TMapGenerator::findNodeList(NodeSet& list,
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
	uint TMapGenerator::Distance(TIndex s, TIndex t)
	{
		TIndex ret = { abs(s.x - t.x), abs(s.y - t.y) };
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