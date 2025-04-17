#include <iostream>

using namespace std;

template<typename T>
struct Node{
    T value;
    Node* next;
};

template<typename T>
class List {
private:
    Node<T>* head;
public:
    List() : head(nullptr) {}

    ~List() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void Insert(T value) {
        Node<T>* ptr = new Node<T>();
        ptr->value = value;
        if(head == nullptr || value < head->value){
            ptr->next = head;
            head = ptr;
        }else{
            Node<T>* temp = head;
            while(temp->next != nullptr && temp->next->value < value){
                temp = temp->next;
            }
            ptr->next = temp->next;
            temp->next = ptr;
        }  
    }

    Node<T>* Search(T value) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->value == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void Delete(T value) {
        if (head == nullptr) {
            return;
        }

        Node<T>* toDel = Search(value);
        if (head == toDel) {
            head = head->next;
            delete toDel;
        } else {
            Node<T>* current = head;
            while (current->next != toDel) {
                current = current->next;
            }
            current->next = toDel->next;
            delete toDel;
        }
    }

    void Display() {
        Node<T>* current = head;
        while (current != nullptr) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }
    Node<T>* GetHead() const {
    return head;
    }
    
};
template<typename T>
class Set {
    private:
        List<T> list;
        Node<T>* assemble(T x, Node<T>* L, Node<T>* M);
        Node<T>* setUnion(Node<T>* L, Node<T>* M);
        Node<T>* intersect(Node<T>* L, Node<T>* M);
        Node<T>* difference(Node<T>* L, Node<T>* M);
    public:
        bool Contains(T value) {
            return list.Search(value) != nullptr;
        }
        void Insert(T value){
            if(!Contains(value)){
                list.Insert(value);
            }else{
                cout << "Value " << value << " already in set" << endl;
            }
        }
        void Delete(T value){
            if(Contains(value)){
                list.Delete(value);
            }else{
                cout << "Value " << value << " not in set" << endl;
            }
        }
        void Display(){
            list.Display();
        }
        Set<T> Union(const Set<T>& set) {
                Set<T> result;
                Node<T>* unionHead = setUnion(list.GetHead(), set.list.GetHead());
                while (unionHead != nullptr) {
                    result.Insert(unionHead->value);
                    unionHead = unionHead->next;
                }
                return result;
        }
        Set<T> Intersection(Set<T>& set){
            Set<T> result;
            Node<T>* interHead = intersect(list.GetHead(), set.list.GetHead());
            while (interHead != nullptr) {
                result.Insert(interHead->value);
                interHead = interHead->next;
            }
            return result;
        }
        Set<T> Difference(Set<T>& set){
            Set<T> result;
            Node<T>* diffHead = difference(list.GetHead(), set.list.GetHead());
            while (diffHead != nullptr) {
                result.Insert(diffHead->value);
                diffHead = diffHead->next;
            }
            return result;
        }
        
        Node<T>* GetHead() const {
            return list.GetHead();
        }
        
};
template<typename T>
Node<T>* Set<T>::assemble(T x, Node<T>* L, Node<T>* M) {
    Node<T>* first = new Node<T>;
    first->value = x;
    first->next = setUnion(L, M);
    return first;
}

template<typename T>
Node<T>* Set<T>::setUnion(Node<T>* L, Node<T>* M) {
    if (L == nullptr && M == nullptr)
        return nullptr;
    else if (L == nullptr)
        return assemble(M->value, nullptr, M->next);
    else if (M == nullptr)
        return assemble(L->value, L->next, nullptr);
    else if (L->value == M->value)
        return assemble(L->value, L->next, M->next);
    else if (L->value < M->value)
        return assemble(L->value, L->next, M);
    else
        return assemble(M->value, L, M->next);
}
template<typename T>
Node<T>* Set<T>::intersect(Node<T>* L, Node<T>* M) {
    if (L == nullptr || M == nullptr)
        return nullptr;
    else if (L->value == M->value)
        return assemble(L->value, intersect(L->next, M->next), nullptr);
    else if (L->value < M->value)
        return intersect(L->next, M);
    else
        return intersect(L, M->next);
}
template<typename T>
Node<T>* Set<T>::difference(Node<T>* L, Node<T>* M) {
    if (L == nullptr)
        return nullptr;
    else if (M == nullptr)
        return assemble(L->value, difference(L->next, nullptr), nullptr);
    else if (L->value == M->value)
        return difference(L->next, M->next);
    else if (L->value < M->value)
        return assemble(L->value, difference(L->next, M), nullptr);
    else
        return difference(L, M->next);
}
int main(){
    Set<int> set;
    set.Insert(2);
    set.Insert(5);
    set.Insert(3);
    set.Insert(4);
    set.Display();

    cout << "Set contains 2: " << (set.Contains(2) ? "Yes" : "No") << endl;
    
    set.Delete(2);
    set.Display();

    Set<int> otherSet;
    otherSet.Insert(3);
    otherSet.Insert(4);
    
    Set<int> UnionSet = set.Union(otherSet);
    cout << "Union set: ";
    UnionSet.Display();

    Set<int> diffSet = set.Difference(otherSet);
    cout << "Difference set: ";
    diffSet.Display();

    Set<int> interSet = set.Intersection(otherSet);
    cout << "Intersection set: ";
    interSet.Display();
}
    