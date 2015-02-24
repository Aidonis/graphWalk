#include "Graph.h"

//Graph Nodes
GraphNode::GraphNode(int a_x, int a_y){
	x = a_x;
	y = a_y;
	visited = false;
	weight = 0;
	previousNode = NULL;
}

void GraphNode::AddEdge(GraphNode * a_node){
	Edge newEdge;
	newEdge.Start = this;
	newEdge.End = a_node;
	edges.push_back(newEdge);
}

void GraphNode::RemoveEdge(GraphNode * a_node){
	EdgeList::iterator edgeToDelete = edges.end();
	for (EdgeList::iterator e = edges.begin(); e != edges.end(); e++){
		if ((*e).End == a_node){
			edgeToDelete = e;
		}
	}
	if (edgeToDelete != edges.end()){
		edges.erase(edgeToDelete);
	}
}

//Graph
Graph::Graph(unsigned int a_size){
	for (unsigned int r = 0; r < a_size; r++) {
		for (unsigned int c = 0; c < a_size; c++) {
			nodes.push_back(new GraphNode(r, c));
		}
	}
	// < v > ^
	for (unsigned int r = 0; r < a_size; r++) {
		for (unsigned int c = 0; c < a_size; c++) {
			if (c > 0) {
				nodes[(r * a_size) + c]->AddEdge(nodes[(r * a_size) + c - 1]);
			}
			if (r < a_size - 1) {
				nodes[(r * a_size) + c]->AddEdge(nodes[((r + 1) * a_size) + c]);
			}
			if (c < a_size - 1) {
				nodes[(r * a_size) + c]->AddEdge(nodes[(r * a_size) + c + 1]);
			}
			if (r > 0) {
				nodes[(r * a_size) + c]->AddEdge(nodes[((r - 1) * a_size) + c]);
			}
		}
	}
}

void Graph::AddNode(GraphNode* a_node){
	nodes.push_back(a_node);
}

void Graph::ResetVisted(){
	for (NodeList::iterator i = nodes.begin(); i != nodes.end(); i++){
		(*i)->visited = false;
	}
}

bool Graph::SearchDFS(GraphNode* a_Start, GraphNode* a_End){
	std::stack<GraphNode*> NodeStack;
	NodeStack.push(a_Start);

	while (!NodeStack.empty()){
		GraphNode* current = NodeStack.top();
		NodeStack.pop();
		if (current->visited == true){
			continue;
		}

		current->visited = true;

		if (current == a_End){
			return true;
		}
		for (int i = 0; i < current->edges.size(); i++){
			NodeStack.push(current->edges[i].End);
		}
	}

	return false;

}

bool Graph::SearchBFS(GraphNode* a_Start, GraphNode* a_End){
	std::queue<GraphNode*> NodeQueue;
	NodeQueue.push(a_Start);

	while (!NodeQueue.empty()){
		GraphNode* current = NodeQueue.front();
		NodeQueue.pop();
		if (current->visited == true){
			continue;
		}
		current->visited = true;
		if (current == a_End){
			return true;
		}
		for (int i = 0; i < current->edges.size(); i++){
			NodeQueue.push(current->edges[i].End);
		}
	}
	return false;
}

bool Graph::SearchDJK(GraphNode* a_Start, GraphNode* a_End){
	std::list<GraphNode*>nodeList;
	for (int i = 0; i < nodes.size(); i++){
		nodes[i]->weight = INFINITY;
	}
	a_Start->weight = 0;
	nodeList.push_back(a_Start);
	while (!nodeList.empty()){
		GraphNode* current = nodeList.back();
		nodeList.pop_back();
		if (current->visited == true){
			continue;
		}
		current->visited = true;
		if (current == a_End){
			return true;
		}
		for (int i = 0; i < current->edges.size(); i++){
			nodeList.push_back(current->edges[i].End);
		}
		
	}
	return false;
}

bool Neighbors(GraphNode* a_nodeA, GraphNode* a_nodeB){
	for (int i = 0; i < 4; i++){
		if (a_nodeA->edges[i].End == a_nodeB){
			return true;
		}
	}
	return false;
}