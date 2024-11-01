#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <chrono>

class Conta {
    private:
        int saldo;
        pthread_mutex_t mutex;
        int sinc = 1; // Se sinc é igual a 0, então ativa a sincronização
    public:
        Conta(int sincro = 1){
            saldo = 0;
            pthread_mutex_init(&mutex, NULL);
            sinc = sincro;
        }
        
        ~Conta(){
            pthread_mutex_destroy(&mutex);
        }

        void depositar(int valor){
            if (sinc == 0) pthread_mutex_lock(&mutex);

            if(saldo < 500000) saldo += valor;

            if (sinc == 0) pthread_mutex_unlock(&mutex);
        }

        void sacar(int valor){
            if (sinc == 0) pthread_mutex_lock(&mutex);

            saldo -= valor;

            if (sinc == 0) pthread_mutex_unlock(&mutex);
        }

        int getSaldo(){
            if(sinc == 0) pthread_mutex_lock(&mutex);

            int saldoAtual = saldo;

            if(sinc == 0) pthread_mutex_unlock(&mutex);
            
            return saldoAtual;
        }

        void setSinc(int s){
            sinc = s;
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