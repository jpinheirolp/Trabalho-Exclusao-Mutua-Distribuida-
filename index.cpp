#include <iostream>
#include <omp.h>

#define NT 3

int main() {
    
    // Coordenador de threads
    #pragma omp parallel for num_threads(NT)
    for (int i = 0; i < 10; i++) {
        int thread_num = omp_get_thread_num();
        if (thread_num == 0) {
            std::cout << "Jo soe el respondedor del terminal" << thread_num << std::endl;
        }
        else if (thread_num == 1) {
            std::cout << "Jo soe el executor de la distribuicion multipla destribuida " << thread_num << std::endl;
        }
        else if (thread_num == 2) {
            std::cout << "jo soe el respetor de conexiones " << thread_num << std::endl;
        }
    }
// */
}