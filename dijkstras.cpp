#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char ** argv){
	//check for correct number of command line arguments
	if (argc != 2){
		cout << "format: ./dijkstras input.txt" << endl;
		return -1;
	}
	
	//setting input from input file
	ifstream input(argv[1]);
	string line;

	//get number of nodes
	int numNodes;
	getline(input, line);
	numNodes = stoi(line);

	//get names of nodes
	getline(input, line);
	istringstream ss(line);
	vector<string> nodes(numNodes, "");
	for (int i = 0; i < numNodes; i++){
		ss >> nodes[i];
	}

	//set up adjacency matrix
	int adjMat[numNodes][numNodes];
	for (int i = 0; i < numNodes; i++){
		getline(input, line);
		ss.clear();
		ss.str(line);
		for (int j = 0; j < numNodes; j++){
			ss >> adjMat[i][j];			
		}
	}

	//print adjacency matrix
	cout << "Adjacency Matrix :" << endl << endl;
	cout << "\t";
	for (string n : nodes)
		cout << n << "\t";
	cout << endl;
	for (int i = 0; i < numNodes; i++){
		cout << nodes[i] << "\t";
		for (int j = 0; j < numNodes; j++){
			cout << adjMat[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;

	//get name of starting node from cin
	cout << "Enter starting node :" << endl;
	string start;
	cin >> start;
	cout << endl;

	//find starting node index
	int u = 0;
	for (int i = 0; i < numNodes; i++){
		if (nodes[i] == start) u = i;
	}

	//keep track of which nodes have been visited
	vector<bool> visited(numNodes, false);
	vector<string> nPrime;

	//keep track of distance from u for each node
	vector<int> dist(numNodes, 9999); //9999 = infinity
	dist[u] = 0;
	
	//keep track of previous node in path from u for each node
	vector<string> prev(numNodes, "");

	//print result table header
	cout << "N'\t\t";
	for (int i = 0; i < numNodes; i++){
		cout << "D(" << nodes[i] << "),p(" << nodes[i] << ")\t";
	}
	cout << endl;
	
	//shortest path
	for (int i = 0; i < numNodes - 1; i++){
		//find unvisited node with min distance from u
		int v = 0;
		int min = 9999;
		for (int j = 0; j < numNodes; j++){
			if (dist[j] < min && !visited[j]){
				v = j;
				min = dist[j];
			}
		}
		
		//mark this min node as visited & add to n prime
		visited[v] = true;
		nPrime.push_back(nodes[v]);

		//update dist[j] for each unvisited neighbor j of v
		for (int j = 0; j < numNodes; j++){
			if (dist[v] + adjMat[v][j] < dist[j] && !visited[j] && dist[v] != 9999 && adjMat[v][j] > 0){
				dist[j] = dist[v] + adjMat[v][j];
				prev[j] = nodes[v];
			}
		}

		//print row of result table
		for (int j = 0; j < nPrime.size(); j++){
			cout << nPrime[j];
		}
		cout << "\t\t";
		for (int j = 0; j < numNodes; j++){
			if (visited[j]) cout << "   \t\t";
			else if (dist[j] == 9999) cout << "9999\t\t";
			else cout << dist[j] << "," << prev[j] << "\t\t";
		}
		cout << endl;
	}
	
	//print final row of result table
	for (int i = 0; i < nPrime.size(); i++){
		cout << nPrime[i];
	}
	for (int i = 0; i < numNodes; i++){
		if (!visited[i]) cout << nodes[i] << endl;
	}
	
	return 0;
}

