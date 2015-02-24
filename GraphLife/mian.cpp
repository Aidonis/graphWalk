#include <iostream>
#include "Graph.h"

void BuildNodes(float a_Width, float a_Height, float a_Matrix);

Graph graph(5);

int main(){

	std::cout << "Graph has: " << graph.nodes.size() << " nodes" << std::endl;
	std::cout << "Node 12 has: " << graph.nodes[11]->edges.size() << " edges" << std::endl;

	bool areNeighbors = Neighbors(graph.nodes[1], graph.nodes[2]);
	std::cout << "Node 1 and Node 5 are neighbors: " << areNeighbors << std::endl;

	std::cout << graph.SearchBFS(graph.nodes[3], graph.nodes[12]) << std::endl;

	std::cout << "What has been visted" << std::endl;
	for (int i = 0; i < graph.nodes.size(); i++){
		if (graph.nodes[i]->visited == true){
			std::cout << "(" << graph.nodes[i]->x << "," << graph.nodes[i]->y << ")" << std::endl;
		}
	}
	graph.ResetVisted();
	

	system("pause");
	return 0;
}
