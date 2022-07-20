#include <iostream>
#include <string>

using namespace std;

const int queue_size = 15;

class Queue { // an interface for a queue

private:
    int n; // number of items in queue
    int f; // front
    int r; // rear
    int Q[queue_size]; // array of items
    int max_size; // maximum size of queue

public:
Queue() {
    n = 0; // number of items in queue
    f = 0; // front
    r = 0;
    Q[queue_size]; // array of items
    max_size = sizeof(Q);
}

int size() { // number of items in queue
    return n;
} 
bool empty() { // is queue empty?
    return n == 0;
}
int front() { // return front item
    if (this->empty()) {
        length_error("Queue is empty");
        }
    return Q[f];
}
void enqueue (int x) { // add item to queue
    if (n == max_size) {
        length_error("Queue maxsize surpassed");
        return;
    }
    
    Q[r] = x;
    r = (r + 1) % max_size;
    n++;
}
// enqueue element at rear
void dequeue()  // dequeue element at front
{
    if (this->empty()) {
        length_error("Queue is empty");
        return;
    }
    f = (f + 1) % max_size;
    n--;
}

string full_queue() {
    int i = f;
    string s = "";
    while (i != r) {
        s += to_string(Q[i]) + ",";
        i = (i + 1) % max_size;
    }
    return s;
};

};





int main() {
    cout << "teste" << endl;
     int rnd_nums[10];
     rnd_nums[2] = 2;//new int[10];
    Queue q = Queue();

    //q.dequeue();
    cout << q.size() << endl;
    q.enqueue(13);
    q.enqueue(25);
    q.enqueue(26);
    q.enqueue(27);
    cout << q.full_queue() << endl;
    
    
    q.enqueue(28);
    q.enqueue(29);
    q.dequeue();
    cout << q.front() << endl;
    q.enqueue(44);
    q.enqueue(45);
    q.dequeue();
    cout << q.front() << endl;
    q.enqueue(50);
    q.enqueue(51);
    q.enqueue(52);
    q.enqueue(53);
    q.enqueue(54);
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    cout << q.front() << endl;

}
// */