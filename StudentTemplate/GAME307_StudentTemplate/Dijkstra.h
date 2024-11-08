#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <vector>
#include <queue>
#include "Graph.h"
#include "Node.h"



class Connections
{
	float cost;
	Node from_node;
	Node to_node;
	float GetCost();
	Node GetFromNide();
	Node GetToNode();
};
class Dijkstra
{
	std::queue<Node> pathFindDijkstra(Graph* graph_, Node* start_, Node* end_);

};

#endif
