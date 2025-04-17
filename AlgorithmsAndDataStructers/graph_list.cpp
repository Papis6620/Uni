#include <iostream>

using namespace std;
/*
Implementacja garafu lista sasiedztwa:
- krawedzie wielokrotne oznaczane sa przez kilkukrotne dodanie wierzchloka do listy sasiedztwa danego wierzcholka
- uwzglednienie petli podczas liczenia stopnia wierzcholka - jezeli napotkamy petle(wierzcholek jest w swojej liscie sasiedztwa) to zwiekszamy o 2 stopien wierzcholka
- uwzglednienie petli podczas liczenia stopnia wchodzacego i wychodzacego wierzcholka - zwiekszamy o 1 stopien wchodzacy jak i wychodzacy w przypadku napotkania petli
*/
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

class Graph{
	private:
		int numberOfNodes;
		bool isDirected;
		List *listOfNodes;
	public:
        Graph(int nodes, bool help){
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
    // int numOfNodes, numOfEdges;
    // bool isDirected;
    // cout << "Podaj liczbę wierzchołków: ";
    // cin >> numOfNodes;
    // cout << "Podaj liczbę krawędzi: ";
    // cin >> numOfEdges;
    // cout << "Podaj czy graf jest skierowany czy nie? (1 - skierowany, 0 - nie skierowany): ";
    // cin >> isDirected;

    // Graph graf(numOfNodes, isDirected);

    // for (int i = 0; i < numOfEdges; ++i) {
	// 	cout << "Podaj pierwszy wierzchołek: " << endl;
    //     int a, b;
    //     cin >> a; 
	// 	cout << "Podaj drugi wierzchołek: " << endl;
	// 	cin >> b;
    //     graf.InsertEdges(a, b);
    // }
	Graph graf(5, false);
	graf.InsertEdges(1,2);
	graf.InsertEdges(1,2);
	graf.InsertEdges(2,3);
	graf.InsertEdges(3,2);
	graf.InsertEdges(3,3);
	graf.Display();
	List neighbours = graf.Neighbors(3);
    neighbours.Display();
    cout << graf.DegreeOut(3);
}