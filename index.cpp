#include <iostream>
#include <fstream>
#include <omp.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <map>

using namespace std;

#define NT 3

const int queue_size = 15;

bool gambiarra_no_jutsu;
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
    if (n = max_size) {
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
        gambiarra_no_jutsu = true;
    }
    if (sig == SIGPROF){
        gambiarra_no_jutsu = false;
    }
    if (sig == SIGTERM){
        cout << "Caboooooou\n";

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
    int request_access(int process_id) {

        if (acess_queue.empty())  {
            cout << "Granted to Process " << process_id << " has access\n";
            return process_id;
        }
            // grant acess to process_id
            
            acess_queue.enqueue(process_id);
            
    }
    int release_access(int process_id) {

        if (process_id != acess_queue.front()) {
            // process_id did not request access
            return null;
        }
    
            acess_queue.dequeue();
            
            
        
        if (!acess_queue.empty()) {
                

            int process_with_acess = acess_queue.front();;
            // grant acess to process_with_acess
            cout << "Granted to Process " << process_with_acess << " has access\n";
            return process_with_acess;
        }
    }

    int get_acess() {

        return acess_queue.front();
        
    }
    
    
    string show_queue() {

        string s = acess_queue.full_queue();
        
        return s;
    }
};

class Process_Counter {
    private:
        map <int, int> dic_process;

    public:
        Process_Counter() {
            dic_process = map <int, int>();
            
        }
        void inc_process_count(int process_id) {
            if (dic_process[process_id] == 0) {
                dic_process[process_id] = 1;
            }
            else {
                dic_process[process_id]++;
            }
        }
        int get_process_count(int process_id) {
            return dic_process[process_id];
        }

};
 
int main() {
    
    Process_Counter process_counter;

    omp_lock_t coordinator_lock;

    ofstream MyFile("log.txt");

    int mypid = getpid();
    cout << "O meu codigo e " << mypid << endl;

    omp_init_lock(&coordinator_lock);

    CADME coordenator = CADME();

    string log_message;
    string terminal_message;
    
    // Coordenador de threads
    #pragma omp parallel num_threads(NT)
    {
        int thread_num = omp_get_thread_num();
        int i = 0;
        int j = 0;
    
        switch (thread_num) {
        case 0:
            while (true)
            {
            sleep(2000);

            if (signal(SIGUSR1, signal_handler) == SIG_ERR) {
                cout << "SIGUSR1 não foi capturado \n";
            } 
            if (signal(SIGPROF, signal_handler) == SIG_ERR) {
                cout << "SIPROF não foi capturado \n";
            }
            if (signal(SIGTERM, signal_handler) == SIG_ERR) {
                cout << "SIGTERM não foi capturado \n";
            }

            if(gambiarra_no_jutsu) {
                omp_set_lock(&coordinator_lock);
                cout << "La fila " <<coordenator.show_queue()<< endl;
                omp_unset_lock(&coordinator_lock);  
            }
            else { // falta printar qunatas vezes cada processo foi atendido
               cout << "Gambiarra não ativada" <<endl; 
            }
            
            //wait(NULL);
            
                 
            
            } 
         
        case 1:
            sleep(3);
            while (true) {
                
                omp_set_lock(&coordinator_lock);
                    cout << "Jo soe el executor de la distribuicion multipla destribuida, release acess "<< coordenator.get_acess() << endl;
                    coordenator.release_access(coordenator.get_acess());
                omp_unset_lock(&coordinator_lock);    

                i++;
                sleep(4);
                }  
            
        case 2: 
            cout << omp_get_num_threads() << "Cabron!" << endl;
            while (true) {

                cout << "jo soe el respetor de conexiones, release " << 1234213 + j << endl;
                omp_set_lock(&coordinator_lock); 
                    coordenator.request_access(1234213 + j);

                omp_unset_lock(&coordinator_lock);
                
                log_message = coordenator.show_queue();

                j++;

                MyFile << log_message << endl;
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