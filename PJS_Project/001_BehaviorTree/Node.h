#pragma once
namespace BT
{
	class Node
	{
	public:
		virtual bool Invoke() = 0;
	};

	class CompositeNode : public Node
	{
	public:

	public:
		CompositeNode();
		virtual ~CompositeNode();
	};

	class DecoratorNode : public Node
	{
	public:
		DecoratorNode();
		virtual ~DecoratorNode();

	private:

	};
}

