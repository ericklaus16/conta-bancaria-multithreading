#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <chrono>

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
            if(saldo < 500000){
                saldo += valor;
            }
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
    for (int i = 0; i < 1000; i++){ // 10.000 operações
        conta->depositar(rand() % 100);
        // std::cout << "Deposito realizado. Saldo atual: " << conta->getSaldo() << std::endl;
        // usleep(5000); // 0.1 segundo para simular tempo de operação
    }
    return NULL;
}

void* consumidor(void* arg){
    Conta* conta = (Conta*)arg;
    for (int i = 0; i < 1000; i++) {
        conta->sacar(rand() % 50);
        // std::cout << "Saque realizado. Saldo atual: " << conta->getSaldo() << std::endl;
        // usleep(7500); // 0.15s
    }
    return NULL;
}