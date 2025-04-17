#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class Queue{
    private:
        vector<pair<int, T>> data;
        void buildHeap(){
            int i = data.size() - 1;
            while (i > 0 && data[i].first > data[(i - 1) / 2].first) {
                swap(data[i], data[(i - 1) / 2]);
                i = (i - 1) / 2;
            }
        }
        void pushDown(){
            int i = 0;
            while (true) {
                int left_child = 2 * i + 1;
                int right_child = 2 * i + 2;
                int largest = i;
                
                if (left_child < data.size() && data[left_child].first > data[largest].first) {
                    largest = left_child;
                }

                if (right_child < data.size() && data[right_child].first > data[largest].first) {
                    largest = right_child;
                }

                if (largest != i) {
                    swap(data[i], data[largest]);
                    i = largest;
                } else {
                    break;
                }
            }
        }
    public:
        // void buildHeap(){
        //     int i = data.size() - 1;
        //     while (i > 0){
        //         if (data[i].first > data[(i - 1) / 2].first){
        //             int j = i;
        //             while (data[j].first > data[(j - 1) / 2].first){
        //                 swap(data[j], data[(j - 1) / 2]);
        //                 j = (j - 1) / 2;
        //             }
        //         }
        //         i--;
        //     }
        // }
        void Insert(int priority, T value){
            data.push_back(make_pair(priority, value));
            buildHeap();
        }
        void Display(){
            for(const auto& pair : data){
                cout << pair.second << ":" << pair.first << endl;
            }
        }
        T Get(){
            T result = data[0].second;
            swap(data[0], data[data.size()-1]);
            data.pop_back();
            pushDown();       
            return result;
        }
        
};

int main(){
    Queue<int> queue; 

    queue.Insert(3, 12);
    queue.Insert(1, 22);
    queue.Insert(2, 32);
    queue.Insert(4, 42);
    queue.Insert(7, 52);
    queue.Insert(6, 62);
    queue.Insert(2, 72);
    queue.Insert(8, 82);
    queue.Insert(4, 92);

    cout << "Queue: " << endl;
    queue.Display();
    int wynik = queue.Get();
    cout << "Queue get: " << wynik << endl;
    cout << "Queue: " << endl;
    queue.Display();

}
