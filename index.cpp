#include <iostream>
#include <omp.h>
#include <signal.h>
#include<sys/wait.h>
#include <unistd.h>

using namespace std;

#define NT 3

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


int main() {
    int mypid = getpid();
    cout << "O meu codigo e " << mypid << endl;
    
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
                sleep(4);
                }  
            
        case 2: 
            cout << omp_get_num_threads() << "Cabron!" << endl;
            while (true) {
                cout << "jo soe el respetor de conexiones " << endl;
                sleep(3);
                }  
            
        default:
            cout << "Jo no deveria existir " << endl;
            break;
        }
     
    }
    
// */
}