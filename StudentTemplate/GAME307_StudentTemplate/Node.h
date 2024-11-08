#pragma once
class Node
{
private:
	int lable;
public:
	Node(int lable_) :lable{ lable_}{}
	~Node();

	int getLable() { return lable; };
};

