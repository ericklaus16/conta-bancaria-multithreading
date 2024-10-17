#include "classes.h"

void executarTesteMultithreadSemSincronizacao(){
    Conta conta;
    pthread_t tProdutor, tConsumidor;

    auto comeco = std::chrono::high_resolution_clock::now(); // Iniciar contagem

    pthread_create(&tProdutor, NULL, produtor, (void*)&conta);
    pthread_create(&tConsumidor, NULL, consumidor, (void*)&conta);

    pthread_join(tProdutor, NULL);
    pthread_join(tConsumidor, NULL);

    for(int i = 0; i < 10; i++){
        std::cout << "Saldo sem sincronizacao: " << conta.getSaldo() << std::endl;
    }

    auto fim = std::chrono::high_resolution_clock::now(); // Finalizar tempo
    std::chrono::duration<double> duracao = fim - comeco; 
    std::cout.precision(2);
    std::cout << "Tempo multithread sem sincronizacao: " << duracao.count() << std::endl;
}

int main(){
    std::cout << "Executando teste multithread sem sincronizacao..." << std::endl;
    executarTesteMultithreadSemSincronizacao();
    usleep(1000000);
}