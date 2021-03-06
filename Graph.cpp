#include <iostream>
#include <fstream>

#include "structures/Pair.h"
#include "structures/Vector.h"
#include "structures/Stack.h"
#include "structures/Queue.h"
#include "structures/BinarySearchTree.h"
#include "helpers/MyStrings.h"
#include "Graph.h"
#include "Node.h"

// ------------------------ BIG FOUR HELPERS ----------------------

void Graph::clear() {}

void Graph::copy(const Graph& other) {
	strcpy(id, other.id);
	directed = other.directed;
	nodes = other.nodes;
}

// --------------------------- BIG FOUR ---------------------------

Graph::Graph(const char* graphId) {
	strcpy(id, graphId);
}
Graph::Graph(const Graph& other) {
	copy(other);
}
Graph& Graph::operator=(const Graph& other) {
	if(this != &other) {
		copy(other);
	}
	return *this;
}
Graph::~Graph() {
	clear();
}

// ------------------------- FILE OPERATIONS ----------------------

void Graph::readFromFile(const char* path) {
	if(path == NULL) {
		return;
	}

	clear();

	char buff[1024];
	char word[51];
	std::ifstream inputGraphFile(path);

	inputGraphFile>> directed;
	inputGraphFile.getline(buff, 1023);
	inputGraphFile.getline(buff, 1023);

	Vector<Node*> indexedNodes;
	while(inputGraphFile.peek() != '\n' && inputGraphFile.getline(buff, 1023)) {
		strcpy(word, buff, ' ');
		Node newNode;
		nodes.add(word, newNode);
		indexedNodes.add(nodes.getElement(word));
	}

	inputGraphFile.getline(buff, 1023);

	int newIndex = 0, newWeight = 0;
	int totalNodes = indexedNodes.getSize();

	for(int index = 0; index < totalNodes; ++index) {
		while(inputGraphFile.peek() != '\n') {
            inputGraphFile.getline(word, 50, ' ');
            newIndex = getNuberFromWord(word);
            inputGraphFile.getline(word, 50, ',');
            newWeight = getNuberFromWord(word);
			indexedNodes[index]->addNeighbour(indexedNodes[newIndex], newWeight);
			if(inputGraphFile.peek() == ' '){
				inputGraphFile.ignore();
			}
		}
        inputGraphFile.getline(buff, 1023);
	}

	inputGraphFile.close();
}

void Graph::writeToFile(const char* path) {
	if(path == NULL) {
		return;
	}

	char buff[51];

	std::ofstream outputGraphFile(path);

	outputGraphFile<< directed<< std::endl<< std::endl;

	int index = 0;
	BinarySearchTree<EnumeratedNode> indexedNodes;
	for(TrenarySearchTree<Node>::Iterator iter = nodes.begin(); !iter.isFinished(); ++iter) {
		iter.getWord(buff);
		outputGraphFile<< buff<< std::endl;
		indexedNodes.add(EnumeratedNode(&(*iter), index++));
	}

	outputGraphFile<< std::endl;

	for(TrenarySearchTree<Node>::Iterator iter = nodes.begin(); !iter.isFinished(); ++iter) {
		(*iter).writeToFile(outputGraphFile, indexedNodes);
		outputGraphFile<< std::endl;
	}

	outputGraphFile.close();
}

// ------------------------ OTHER METHODS -------------------------

bool Graph::hasNode(const char* nodeId) {
	return nodes.getElement(nodeId) != NULL;
}

bool Graph::hasArc(const char* nodeId1, const char* nodeId2) {
	Node* node1 = nodes.getElement(nodeId1);
	Node* node2 = nodes.getElement(nodeId2);

	if(node1 == NULL || node2 == NULL) {
		return false;
	}

	return node1->hasNeighbour(node2);
}

// --------------------------- GETTERS -----------------------------

const char* Graph::getId() {
	return id;
}

// ------------------------- NODE METHODS --------------------------

void Graph::addNode(const char* nodeId) {
	nodes.add(nodeId, Node());
}

void Graph::removeNode(const char* nodeId) {
	Node* oldNode = nodes.getElement(nodeId);
	nodes.remove(nodeId);
	for(TrenarySearchTree<Node>::Iterator iter = nodes.begin(); !iter.isFinished(); ++iter) {
		(*iter).removeNeighbour(oldNode);
	}
}

// -------------------------- ARC METHODS --------------------------

void Graph::addArc(const char* nodeId1, const char* nodeId2, int weight) {
	Node* node1 = nodes.getElement(nodeId1);
	Node* node2 = nodes.getElement(nodeId2);

	if(node1 != NULL && node2 != NULL) {
		node1->addNeighbour(node2, weight);
		if(!directed) {
			node2->addNeighbour(node1, weight);
		}
	}
}

void Graph::removeArc(const char* nodeId1, const char* nodeId2) {
	Node* node1 = nodes.getElement(nodeId1);
	Node* node2 = nodes.getElement(nodeId2);

	if(node1 != NULL && node2 != NULL) {
		node1->removeNeighbour(node2);
	}
}

// ------------------------ SEARCH METHODS ------------------------

void Graph::searchAlgorithm(const char* nodeId1, const char* nodeId2, SearchAlgorithm searchAlgorithm) {

	Node* node1 = nodes.getElement(nodeId1);
	Node* node2 = nodes.getElement(nodeId2);

	if(node1 == NULL || node2 == NULL) {
		return;
	}

    BinarySearchTree<AlgorithmNode> optimalityTable;
    for(TrenarySearchTree<Node>::Iterator iter = nodes.begin(); !iter.isFinished(); ++iter) {
		optimalityTable.add(AlgorithmNode(&(*iter)));
	}
	optimalityTable.getElement(AlgorithmNode(node1))->changeOptimalReach(0, NULL);

    int dijkstraCost = 0;
    switch(searchAlgorithm) {
        case BFS:
            bfs(node1, node2, optimalityTable);
            break;
        case DFS_Shortest:
            dfsShortest(node1, node2, optimalityTable);
            break;
        case DFS_Longest:
            dfsLongest(node1, node2, optimalityTable);
            break;
        case Dijkstra:
            dijkstraCost = dijkstra(node1, node2, optimalityTable);
            break;
    }

    if(optimalityTable.getElement(AlgorithmNode(node2))->getParentAddress() == NULL) {
        std::cout<< "no path found"<< std::endl;
        return;
    }
    std::cout<< "path found: "<< std::endl;
    if(searchAlgorithm == Dijkstra) {
        std::cout<< "cost: "<< dijkstraCost<< std::endl;
    }

    Stack<Node*> pathStack;
    AlgorithmNode pathElement = *(optimalityTable.getElement(AlgorithmNode(node2)));
    while(pathElement.getAddress() != node1) {
        pathStack.push(pathElement.getAddress());
        pathElement = *(optimalityTable.getElement(AlgorithmNode(pathElement.getParentAddress())));
    }
    pathStack.push(pathElement.getAddress());

    char nodeName[51];
    while(!pathStack.isEmpty()) {
        for(TrenarySearchTree<Node>::Iterator iter = nodes.begin(); !iter.isFinished(); ++iter) {
            if(&(*iter) == pathStack.getTop()) {
                iter.getWord(nodeName);
                std::cout<< nodeName<< " ";
                pathStack.pop();
                break;
            }
        }
    }
    std::cout<< std::endl;
}

void Graph::bfs(Node* node1, Node* node2, BinarySearchTree<AlgorithmNode>& optimalityTable) {
    Queue< Pair<Node*, int> > bfsQueue;
    bfsQueue.enqueue(Pair<Node*, int>(node1, 0));
    while(!bfsQueue.isEmpty()) {
        Node* topNode = bfsQueue.getFront().first;
        if(topNode != node2) {
            topNode->bfsVisit(bfsQueue, optimalityTable);
            bfsQueue.dequeue();
        } else {
            break;
        }
    }

}
void Graph::dfsShortest(Node* node1, Node* node2, BinarySearchTree<AlgorithmNode>& optimalityTable) {
    Stack< Pair<Node*, int> > dfsStack;
    dfsStack.push(Pair<Node*, int>(node1, 0));
    while(!dfsStack.isEmpty()) {
        Node* topNode = dfsStack.getTop().first;
        topNode->dfsShortVisit(dfsStack, optimalityTable);
    }
}
void Graph::dfsLongest(Node* node1, Node* node2, BinarySearchTree<AlgorithmNode>& optimalityTable) {
    Stack< Pair<Node*, int> > dfsStack;
    dfsStack.push(Pair<Node*, int>(node1, 0));
    while(!dfsStack.isEmpty()) {
        Node* topNode = dfsStack.getTop().first;
        topNode->dfsLongVisit(dfsStack, optimalityTable);
    }
}

int Graph::dijkstra(Node* node1, Node* node2, BinarySearchTree<AlgorithmNode>& optimalityTable) {
    Queue< Pair<Node*, int> > bfsQueue;
    bfsQueue.enqueue(Pair<Node*, int>(node1, 0));
    while(!bfsQueue.isEmpty()) {
        Node* topNode = bfsQueue.getFront().first;
        topNode->dijkstraVisit(bfsQueue, optimalityTable);
        bfsQueue.dequeue();
    }

    return optimalityTable.getElement(AlgorithmNode(node2))->getCost();
}

