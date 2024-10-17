#include "classes.h"

void executarTesteMultithreadComSincronizacao(){
    Conta conta;
    pthread_t tProdutor, tConsumidor;

    auto comeco = std::chrono::high_resolution_clock::now(); // Iniciar contagem

    pthread_create(&tProdutor, NULL, produtor, (void*)&conta);
    pthread_create(&tConsumidor, NULL, consumidor, (void*)&conta);

    pthread_join(tProdutor, NULL);
    pthread_join(tConsumidor, NULL);

    auto fim = std::chrono::high_resolution_clock::now(); // Finalizar tempo
    std::chrono::duration<double> duracao = fim - comeco; 
    std::cout.precision(2);
    std::cout << "Tempo multithread com sincronizacao: " << duracao.count() << std::endl;
}

int main(){
    std::cout << "Executando teste multithread com sincronizacao..." << std::endl;
    executarTesteMultithreadComSincronizacao();
    usleep(1000000);
}