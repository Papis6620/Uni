/*
Implementacja grafu metodą macierzy sąsiedztwa:
- Krawędzie wielokrotne oznaczane są przez liczby całkowite (np. 2 - dwie krawędzie pomiędzy wierzchołkami).
- Uwzględnienie pętli podczas obliczania stopnia wierzchołka - jeżeli napotkano pętlę podczas liczenia stopnia wierzchołka, dodajemy x2 liczbę do stopnia wierzchołka.
- Uwzględnienie pętli podczas obliczania stopnia wychodzącego i wchodzącego wierzchołka - zwiększenie stopnia o 1 zarówno w stopniu wychodzącym jak i wchodzącym przy napotkaniu pętli.
Implementacja grafu macierzą incydencji:
- Pętle oznaczane są jako 2.
- Liczenie stopnia wchodzącego polega na zliczeniu ilości 1 w macierzy dla danego wierzchołka.
- Liczenie stopnia wychodzącego polega na zliczeniu ilości -1 w macierzy dla danego wierzchołka.
- Pętle w przypadku stopnia wierzchołka zwiększają jego stopień o 2.
- Pętle w przypadku stopnia wchodzącego i wychodzącego zwiększają stopień o 1.
Implementacja grafu listą sąsiedztwa:
- Krawędzie wielokrotne oznaczane są przez kilkukrotne dodanie wierzchołka do listy sąsiedztwa danego wierzchołka.
- Uwzględnienie pętli podczas liczenia stopnia wierzchołka - jeżeli napotkamy pętlę (wierzchołek jest w swojej liście sąsiedztwa), to zwiększamy o 2 stopień wierzchołka.
- Uwzględnienie pętli podczas liczenia stopnia wchodzącego i wychodzącego wierzchołka - zwiększamy o 1 stopień wchodzący jak i wychodzący w przypadku napotkania pętli.
*/
#include <iostream>
#include <vector>
using namespace std;

class GraphAdj{
	private:
		int NumberOfNodes;
		bool isDirected;
		int **matrix;
	public:
		GraphAdj(int nodes, bool help){
			isDirected = help;
			NumberOfNodes = nodes;
			matrix = new int*[NumberOfNodes];
			for(int i = 0; i < NumberOfNodes; i++){
				matrix[i] = new int[NumberOfNodes];
			}
			for(int i = 0; i < NumberOfNodes; i++){
				for(int j = 0; j < NumberOfNodes; j++){
					matrix[i][j] = 0;
				}
			}
			
		}
		void InsertEdges(int a, int b){
			if(isDirected){
				matrix[a-1][b-1]++;
			}else{
				if(a == b){
					matrix[a - 1][b - 1]++;
				}else{
					matrix[a - 1][b - 1]++;
					matrix[b - 1][a - 1]++;
				}
			}
		}
		void Display(){
			for(int i = 0; i < NumberOfNodes; i++){
				for(int j = 0; j < NumberOfNodes; j++){
					cout << matrix[i][j];
				}
				cout << endl;
			}
		}
		int DegreeOut(int node){
			int count = 0;
			for(int i = 0; i < NumberOfNodes; i++){
				if(matrix[node-1][i]){
					count += matrix[node-1][i];
				}
			}
			return count;
		}
		int DegreeIn(int node){
			int count = 0;
			for(int i = 0; i < NumberOfNodes; i++){
				if(matrix[i][node-1]){
					count += matrix[i][node-1];
				}
			}
			return count;
		}
		int Degree(int node){
			int count = 0;
			for(int i = 0; i < NumberOfNodes; i++){
				if(matrix[i][node-1]){
					if(i == node-1){
						count += matrix[i][node-1]*2;
					}else{
						count += matrix[i][node-1];
					}
				}
			}
			return count;
		}
		vector<int> Neighbors(int node){
			vector<int> neighbors;
			for(int i = 0; i < NumberOfNodes; i++){
				if(matrix[node-1][i] != 0){
					neighbors.push_back(i+1);
				}
			}
			return neighbors;
		}
		vector<int> NeighborTo(int node){
			vector<int> neighbors;
			for(int i = 0; i < NumberOfNodes; i++){
				if(matrix[i][node-1] != 0){
					neighbors.push_back(i+1);
				}
			}
			return neighbors;
		}
};
class GraphInc{
	private:
		int NumberOfNodes;
        int NumberOfEdges;
		bool isDirected;
		int **incidenceMatrix;
        int lastEdge;
	public:
		GraphInc(int nodes, bool help, int edges){
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
struct Node{
    int value;
    Node* next;
};

class List {
private:
    Node* head;
public:
    List() : head(nullptr){}

    ~List() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void Insert(int value) {
        Node* ptr = new Node();
        ptr->value = value;
        if(head == nullptr || value < head->value){
            ptr->next = head;
            head = ptr;
        }else{
            Node* temp = head;
            while(temp->next != nullptr && temp->next->value < value){
                temp = temp->next;
            }
            ptr->next = temp->next;
            temp->next = ptr;
        }
    }

    Node* Search(int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->value == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void Delete(int value) {
        if (head == nullptr) {
            return;
        }

        Node* toDel = Search(value);
        if (head == toDel) {
            head = head->next;
            delete toDel;
        } else {
            Node* current = head;
            while (current->next != toDel) {
                current = current->next;
            }
            current->next = toDel->next;
            delete toDel;
        }
    }

    void Display() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }
    Node* GetHead() const {
        return head;
    }
};

class GraphList{
	private:
		int numberOfNodes;
		bool isDirected;
		List *listOfNodes;
	public:
        GraphList(int nodes, bool help){
            isDirected = help;
			numberOfNodes = nodes;
			listOfNodes = new List[numberOfNodes];
        }
        void InsertEdges(int a, int b){
            if (isDirected) {
                listOfNodes[a - 1].Insert(b);
            } else {
                listOfNodes[a - 1].Insert(b);
                if (a != b)
                    listOfNodes[b - 1].Insert(a);
            }
        }
        int DegreeOut(int node){
            int count = 0;
            Node* current = listOfNodes[node-1].GetHead();
            while (current != nullptr) {
                count++;
                current = current->next;
            }
            return count;
        }
        int DegreeIn(int node){
            int count = 0;
            for (int i = 0; i < numberOfNodes; i++) {
                Node* current = listOfNodes[i].GetHead();
                while (current != nullptr) {
                    if (current->value == node) {
                        count++;
                    }
                    current = current->next;
                }
            }
            return count;
        }
        int Degree(int node){
            int count = 0;
            Node* current = listOfNodes[node-1].GetHead();
            while (current != nullptr) {
                if(current->value == node){
                    count += 2;
                }else{
                    count++;
                }
                current = current->next;
            }
            return count;
        }
        List Neighbors(int node){
        	List neighbors;
        	Node* current = listOfNodes[node-1].GetHead();
	        while (current != nullptr) {
	            if(neighbors.Search(current->value) == nullptr){
	            	neighbors.Insert(current->value);
	            }
	            current = current->next;
	        }
            return neighbors;
        }
        List NeighborTo(int node){
            List neighbors;
            for(int i = 0; i < numberOfNodes; i++){
                if(listOfNodes[i].Search(node) != nullptr){
                    neighbors.Insert(i+1);
                }
            }
            return neighbors;
        }
        void Display(){
            for(int i = 0; i < numberOfNodes; i++){
                if(listOfNodes[i].GetHead() != nullptr){
                    cout << i+1 << ": ";
                    listOfNodes[i].Display();
                }
            }
        }
};
int main(){
}