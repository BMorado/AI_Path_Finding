#pragma once
#include <vector>
#include "unordered_map"
#include "Node.h"

class Graph
{
private:
	std::unordered_map<int, Node*> node;

	std::vector<std::vector<float>> cost; // cost[1][3]
public:
	Graph();
	~Graph();
	bool OnCreate(std::vector<Node*> nodes_);
	int numNodes();
	Node* getNodes(int label) { return node[label]; }
	void AddweightedConnection(Node* fromNode, Node* toNode,float weight);
	std::vector<Node*> Neighbours(Node* fromNode);
	std::vector<Node*> DijkstraFindPath(Node* statNode, Node* goalNode);
	std::vector<Node*> AStarFindPath(Node* startNode, Node* goalNode);
};

