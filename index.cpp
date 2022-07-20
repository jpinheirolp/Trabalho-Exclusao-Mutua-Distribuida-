#include <iostream>
#include <fstream>
#include <omp.h>
#include <signal.h>
#include<sys/wait.h>
#include <unistd.h>
#include <string>

using namespace std;

#define NT 3

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

void signal_handler(int sig) {
    if (sig == SIGUSR1){
        cout << "Busque conhecimento\n";
    }
    if (sig == SIGPROF){
        cout << "Qual a pergunta?\n";
    }
    if (sig == SIGTERM){
        cout << "42\n";

        exit(0);

    }
}

class CADME {//Centralised Algorythm for Distributed Mutual Exclusion
private:
    Queue acess_queue;

public:
    CADME() {
        acess_queue = Queue();
    }
    void request_access(int process_id) {
        bool is_empty; 
        #pragma omp critical
            is_empty = acess_queue.empty();

        if (is_empty)  
            // grant acess to process_id
            return
        #pragma omp critical    
            acess_queue.enqueue(process_id);
    }
    void release_access(int process_id) {
        int process_to_release;
        #pragma omp critical
            process_to_release = acess_queue.front();

        if (process_id != process_to_release) {
            // process_id did not request access
            return;
        }

        #pragma omp critical
            acess_queue.dequeue();
        
        bool is_empty; 
        #pragma omp critical
            is_empty = acess_queue.empty();
        
        if (!is_empty) {
            queue_head;
            #pragma omp critical
                queue_head = acess_queue.front();
            int process_with_acess = queue_head;
            // grant acess to process_with_acess
        }
    }
    
    
    string show_queue() {
        #pragma omp critical
            s = acess_queue.full_queue();
        return s;
    }
};

 
int main() {

    ofstream MyFile("log.txt");

    int mypid = getpid();
    cout << "O meu codigo e " << mypid << endl;

    Queue fila = Queue();
    
    // Coordenador de threads
    #pragma omp parallel num_threads(NT)
    {
        int thread_num = omp_get_thread_num();
    
        switch (thread_num) {
        case 0:
            while (true)
            {
            if (signal(SIGUSR1, signal_handler) == SIG_ERR) {
                cout << "SIGUSR1 não foi capturado \n";
            } 
            if (signal(SIGPROF, signal_handler) == SIG_ERR) {
                cout << "SIPROF não foi capturado \n";
            }
            if (signal(SIGTERM, signal_handler) == SIG_ERR) {
                cout << "SIGTERM não foi capturado \n";
            }
            cout << "UNO " << endl;

            sleep(20);
            cout << "DUE " << endl;
            wait(NULL);
            cout << "isso nunca e impresso na tela";
            
            } 
            /*    
            for (int i = 0; i < 10; i++) {
                cout << "Jo soe el respondedor del terminal" << endl;
                            break;
                }    
            //*/
        case 1:
            while (true) {
                cout << "Jo soe el executor de la distribuicion multipla destribuida " << endl;
                fila.enqueue(omp_get_num_threads());
                sleep(4);
                }  
            
        case 2: 
            cout << omp_get_num_threads() << "Cabron!" << endl;
            while (true) {
                cout << "jo soe el respetor de conexiones " << fila.front() << endl;

                MyFile << "dias de luta " << endl;
                sleep(3);
                }  
            
        default:
            cout << "Jo no deveria existir " << endl;
            break;
        }
     
    }
    
    MyFile.close();

    return 0;
// */
}