#include <iostream>
#include <vector>
using namespace std;
/*
Implementacja grafu macierz incydencji:
- petle oznaczane sa jako 2 
- liczenie stopnia wchodzacego polega na zliczeniu ilosci 1 w macierzy dla danego wierzcholka
- liczenia stopnia wychodzacecgo polega na zliczeniu ilosci -1 w macierzy dla danego wierzcholka
- petle w przypadku stopnia wierzcholka zwiekszaja jego stopien o 2
- petle w przypadku stopnia wchodzacego i wychodzacego zwiekszaja stopien o 1
*/
class Graph{
	private:
		int NumberOfNodes;
        int NumberOfEdges;
		bool isDirected;
		int **incidenceMatrix;
        int lastEdge;
	public:
		Graph(int nodes, bool help, int edges){
            lastEdge = 0;
			isDirected = help;
			NumberOfNodes = nodes;
            NumberOfEdges = edges;
			incidenceMatrix = new int*[NumberOfNodes];
			for(int i = 0; i < NumberOfNodes; i++){
				incidenceMatrix[i] = new int[NumberOfEdges];
			}
			for(int i = 0; i < NumberOfNodes; i++){
				for(int j = 0; j < NumberOfEdges; j++){
					incidenceMatrix[i][j] = 0;
				}
			}
			
		}
        void InsertEdges(int a, int b){
            if(a == b){
                incidenceMatrix[a-1][lastEdge] = 2;
            }else{
            	if(isDirected){
                    incidenceMatrix[a-1][lastEdge] = -1;
                    incidenceMatrix[b-1][lastEdge] = 1;	
            	}else{
            		incidenceMatrix[a-1][lastEdge] = 1;
            		incidenceMatrix[b-1][lastEdge] = 1;
            	}
            
            }
            lastEdge++;
        }
        int Degree(int node){
            int count = 0;
            for(int i = 0; i < NumberOfEdges; i++){
                count += incidenceMatrix[node-1][i];
            }
            return count;
        }
        int DegreeIn(int node){
            int count = 0;
            for(int i = 0; i < NumberOfEdges; i++){
                if(incidenceMatrix[node-1][i] == 1 || incidenceMatrix[node-1][i] == 2) {
                    count++;
                }
            }
            return count;
        }
        int DegreeOut(int node){
            int count = 0;
            for(int i = 0; i < NumberOfEdges; i++){
                if(incidenceMatrix[node-1][i] == -1 || incidenceMatrix[node-1][i] == 2) {
                    count++;
                }
            }
            return count;
        }
        vector<int> Neighbors(int node) {
            vector<int> neighbors;
            for (int j = 0; j < NumberOfEdges; j++) {
                bool connected = false;
                for (int i = 0; i < NumberOfNodes; i++) {
                    if (i != node - 1 && incidenceMatrix[i][j] != 0) {
                        if (incidenceMatrix[node - 1][j] == 2 || incidenceMatrix[node - 1][j] == 1) {
                            neighbors.push_back(i + 1);
                        }
                        connected = true;
                        break;
                    }
                }
                if (!connected && incidenceMatrix[node - 1][j] == 2) {
                    neighbors.push_back(node);
                }
            }
            return neighbors;
        }
        vector<int> NeighborTo(int node) {
            vector<int> neighbors;
            for (int j = 0; j < NumberOfEdges; j++) {
                if (incidenceMatrix[node - 1][j] != 0) {
                    for (int i = 0; i < NumberOfNodes; i++) {
                        if (i != node - 1 && incidenceMatrix[i][j] != 0) {
                            neighbors.push_back(i + 1);
                            break;
                        }
                    }
                }
                if (incidenceMatrix[node - 1][j] == 2) {
                neighbors.push_back(node);
            }
            }
            return neighbors;
        }
        void Display() {
            cout << "Incidence Matrix:" << endl;
            for (int i = 0; i < NumberOfNodes; i++) {
                for (int j = 0; j < NumberOfEdges; j++) {
                    cout << incidenceMatrix[i][j] << " ";
                }
                cout << endl;
            }
        }
};

int main(){
    Graph graf(5, false , 3);
    graf.InsertEdges(2,3);
    graf.InsertEdges(2,2);
    graf.InsertEdges(2,4);
    graf.Display();
    cout << graf.DegreeOut(2) << endl;
    vector<int> somsiad = graf.Neighbors(2);
    for(int som : somsiad){
        cout << som << " ";
    }
    cout << endl;
}
