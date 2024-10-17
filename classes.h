#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <chrono>

#define TAM 10

class Conta {
    private:
        int saldo;
        pthread_mutex_t mutex;
    public:
        Conta(){
            saldo = 0;
            pthread_mutex_init(&mutex, NULL);
        }
        
        ~Conta(){
            pthread_mutex_destroy(&mutex);
        }

        void depositar(int valor){
            pthread_mutex_lock(&mutex);
            saldo += valor;
            pthread_mutex_unlock(&mutex);
        }

        void sacar(int valor){
            pthread_mutex_lock(&mutex);
            saldo -= valor;
            pthread_mutex_unlock(&mutex);
        }

        int getSaldo(){
            pthread_mutex_lock(&mutex);
            int saldoAtual = saldo;
            pthread_mutex_unlock(&mutex);
            return saldoAtual;
        }
};

void* produtor(void* arg){
    Conta* conta = (Conta*)arg;
    for (int i = 0; i < 1000; i++){
        conta->depositar(rand() % 100);
        std::cout << "Deposito realizado. Saldo atual: " << conta->getSaldo() << std::endl;
        usleep(100000); // 0.1 segundo para simular tempo de operação
    }
    return NULL;
}

void* consumidor(void* arg){
    Conta* conta = (Conta*)arg;
    for (int i = 0; i < 1000; i++) {
        conta->sacar(rand() % 50);
        std::cout << "Saque realizado. Saldo atual: " << conta->getSaldo() << std::endl;
        usleep(150000); // 0.15s
    }
    return NULL;
}

// int main(){
//     pthread_t p1, p2;
//     pthread_create(&p1, NULL, &produtor, NULL);
//     pthread_create(&p2, NULL, &consumidor, NULL);
//     pthread_join(p1, NULL);
//     pthread_join(p2, NULL);
// }
