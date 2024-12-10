#include "Graph.h"

#include <iostream>
#include <map>
#include <queue>
#include <Vector.h>


Graph::Graph()
{
}

Graph::~Graph()
{
}

bool Graph::OnCreate(std::vector<Node*> nodes_)
{
	// given a list of nodes, initialized a matrix of cost with 0.0
	int numNodes = nodes_.size();
	cost.resize(numNodes);
	for (int i = 0; i < numNodes; ++i)
	{
		// populate internal map
		if(i != nodes_[i]->getLable())
		{
			//makes sure no nodes is skipped ALL NODES SHOULD BE NAMED IN A SEQUENTIAL ORDER 
			std::cerr << "Node with lable i not in the i position for "<< i <<'\n';
			return false;
		}
		node[i] = nodes_[i];

		// Set up connections
		cost[i].resize(numNodes);
		for (int j = 0; j < numNodes; ++j)
		{
			cost[i][j] = 0.0f;
		}
	}
	return true;
}

int Graph::numNodes()
{
	return node.size();
}

void Graph::AddweightedConnection(Node* fromNode, Node* toNode, float weight)
{
	cost[fromNode->getLable()][toNode->getLable()] = weight;
}

std::vector<Node*> Graph::Neighbours(Node* fromNode)
{
	 std::vector<Node*> result = {};
	 int from = fromNode->getLable();
	 for (int j = 0; j < numNodes(); ++j)
	 {
		 if (cost[from][j] > 0.0f)
		 {
			 result.push_back(getNodes(j));
		 }
	 }
	 return result;
}

struct NodeAndPriority
{
	Node* node;
	float priority;

	bool operator()(NodeAndPriority const& lhs, NodeAndPriority const& rhs)
	{
		return lhs.priority > rhs.priority;
	}
};

std::vector<Node*> Graph::DijkstraFindPath(Node* startNode, Node* goalNode)
{
    std::vector<Node*> result;
    result.clear();
    Node* currentNode = startNode;
    // Frontier priority queue to explore nodes with minimum cost first
    std::priority_queue<NodeAndPriority, std::deque<NodeAndPriority>, NodeAndPriority> frontier;
    frontier.push(NodeAndPriority{ currentNode, 0.0f });
    // Track the path using came_from (initialize with -1 for no predecessor)
    std::vector<int> came_from(numNodes(), -1);
    // Cost so far to reach each node
    std::map<int, float> cost_so_far;
    int start = startNode->getLable();
    int goal = goalNode->getLable();
    cost_so_far[start] = 0.0f;
    while (!frontier.empty())
    {
        currentNode = frontier.top().node;
        frontier.pop();

        if (currentNode->getLable() == goal)
        {
            break;
        }
        for (Node* next : Neighbours(currentNode))
        {
    
            float new_cost = cost_so_far[currentNode->getLable()] + cost[currentNode->getLable()][next->getLable()];

        
            if (cost_so_far.find(next->getLable()) == cost_so_far.end() || new_cost < cost_so_far[next->getLable()])
            {
                cost_so_far[next->getLable()] = new_cost;
                frontier.push(NodeAndPriority{ next, new_cost });
                came_from[next->getLable()] = currentNode->getLable();
            }
        }
    }
    int current = goal;
    while (current != start)
    {
        if (current == -1)  
        {
            std::cerr << "Error: No path found from start to goal.\n" ;
            result.clear();
            return result;
        }

        result.push_back(node.at(current));
        current = came_from[current];
    }
    result.push_back(node.at(start));  

    std::reverse(result.begin(), result.end());  
    // Print path (for debugging)
    for (auto value : result)
    {
        std::cout << value->getLable() << '\n';
    }
    return result;
}

MATH::Vec2 NodeToGrid(int label_)
{
    int x = label_ / 25;
    int y = label_ % 25;
    return MATH::Vec2(x, y);
}

float heuristic(Node* node, Node* goalNode) {
    int j = node->getLable() / 25;
    int i = node->getLable() % 25;
    // Example using Manhattan distance as heuristic
    float dx = std::abs(NodeToGrid(node->getLable()).x - NodeToGrid(goalNode->getLable()).x);
    float dy = std::abs(NodeToGrid(node->getLable()).y - NodeToGrid(goalNode->getLable()).y);
    return dx + dy;
}

std::vector<Node*> Graph::AStarFindPath(Node* startNode, Node* goalNode)
{
    std::vector<Node*> result;
    result.clear();
    Node* currentNode = startNode;
    std::priority_queue<NodeAndPriority, std::deque<NodeAndPriority>, NodeAndPriority> frontier;
    frontier.push(NodeAndPriority{ currentNode, 0.0f });
    std::vector<int> came_from(numNodes(), -1);
    // Cost to reach each node from start
    std::map<int, float> cost_so_far;
    int start = startNode->getLable();
    int goal = goalNode->getLable();
    cost_so_far[start] = 0.0f;
    while (!frontier.empty()) {
        currentNode = frontier.top().node;
        frontier.pop();

        // Check if we reached the goal
        if (currentNode->getLable() == goal) {
            break;
        }
        for (Node* next : Neighbours(currentNode)) {
  
            float new_cost = cost_so_far[currentNode->getLable()] + cost[currentNode->getLable()][next->getLable()];

            if (cost_so_far.find(next->getLable()) == cost_so_far.end() || new_cost < cost_so_far[next->getLable()]) {
                cost_so_far[next->getLable()] = new_cost;
                float priority = new_cost+heuristic(goalNode, next);  // A* uses cost + heuristic
                frontier.push(NodeAndPriority{ next, priority });
                came_from[next->getLable()] = currentNode->getLable();
            }
        }
    }
    int current = goal;
    while (current != start) {
        if (current == -1) {  // If path not found
            std::cerr << "Error: No path found from start to goal." << std::endl;
            result.clear();
            return result;
        }

        result.push_back(node.at(current));
        current = came_from[current];
    }
    result.push_back(node.at(start));  
    std::reverse(result.begin(), result.end());  
    for (auto value : result) {
        std::cout << value->getLable() << '\n';
    }
    return result;
}


//std::vector<Node*> Graph::FindPath(Node* startNode, Node* goalNode)
//{
//
//	std::vector<Node*> result;
//	result.clear();
//	float new_cost;
//	float priority;
//	Node* currentNode = startNode;
//
//	// Frontier
//	std::priority_queue<NodeAndPriority, std::deque<NodeAndPriority>, NodeAndPriority> frontier;
//	frontier.push(NodeAndPriority{ currentNode,0.0f });
//
//	//track solution path
//	std::vector<int>came_from;
//	// initialize to a value that can not be the label of a node
//	came_from.resize(numNodes(), -1);
//
//	// cost so far
//	//use map not vector to allow detecting if a node has an entry
//	int start = startNode->getLable();
//	int goal = goalNode->getLable();
//	// using int because we are using the label of the node
//	std::map<int, float>cost_so_far;
//	cost_so_far[start] = 0.0f;
//
//	// TO DO
//
//	// Loop through the frontier, while it is not empty
//	while (!frontier.empty())
//	{
//		// get top node,  save it in  current node
//		currentNode = frontier.top().node;
//		// pop the top node
//		frontier.pop();
//		// if its the goal then break out the loop
//		if (currentNode->getLable() == goal)
//		{
//			break;
//		}
//		// for the neighbours of current node
//		for (Node* next : Neighbours(currentNode))
//		{
//			//calculate new cost
//			int new_cost = cost_so_far[currentNode->getLable()] + cost[currentNode->getLable()][next->getLable()];
//			//if the neighbour is not a index in cost so far or new cost is lower than teh cost so far
//			if (cost_so_far.find(next->getLable()) == cost_so_far.end() || new_cost < cost_so_far[next->getLable()])
//			{
//				// found a better path update data structures 
//				cost_so_far[next->getLable()] = new_cost;
//				priority = new_cost;
//				frontier.push(NodeAndPriority{ next,priority });
//				came_from[next->getLable()] = currentNode->getLable();
//			}
//		}
//
//	}
//	// TO DO
//	// follow the bread crumbs in came_from to rebuild the path, store in result 
//	int current = goal;  // Start from the goal node's label
//	while (current != start)
//	{
//		result.push_back(node.at(current));  // Add current node to path
//		current = came_from[current];        // Move to previous node
//
//		// Check if a path was not found
//		if (current == -1) {
//			std::cerr << "Error: No path found from start to goal." << std::endl;
//			result.clear();
//			return result;
//		}
//	}
//	result.push_back(node.at(start));  // Add start node to path
//	std::reverse(result.begin(), result.end());  // Reverse to get correct order
//	for (auto value : result)
//	{
//		std::cout << value->getLable() << '\n';
//	}
//
//	return result;
//}