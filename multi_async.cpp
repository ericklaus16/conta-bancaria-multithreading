#include "classes.h"
#include <vector>

void executarTesteMultithreadSemSincronizacao(int numProdutores, int numConsumidores){
    Conta conta;

    std::vector<pthread_t> produtores(numProdutores);
    std::vector<pthread_t> consumidores(numConsumidores);

    auto comeco = std::chrono::high_resolution_clock::now(); // Iniciar contagem

    for(int i = 0; i < numProdutores; i++){
        pthread_create(&produtores[i], NULL, produtor, (void*)&conta);
    }

    for(int i = 0; i < numConsumidores; i++){
        pthread_create(&consumidores[i], NULL, consumidor, (void*)&conta);
    }

    for(int i = 0; i < numProdutores; i++){
        pthread_join(produtores[i], NULL);
    }

    for(int i = 0; i < numProdutores; i++){
        pthread_join(consumidores[i], NULL);
    }

    auto fim = std::chrono::high_resolution_clock::now(); // Finalizar tempo
    std::chrono::duration<double> duracao = fim - comeco; 
    std::cout.precision(3);
    std::cout << "Teste multithread sem sincronizacao: " << std::endl;
    std::cout << "Produtores: " << numProdutores << std::endl;
    std::cout << "Consumidores: " << numConsumidores << std::endl;
    std::cout << "Saldo: " << conta.getSaldo() << std::endl;
    std::cout << "Tempo total: " << duracao.count() << std::endl;
}

int main(){
    std::cout << "Executando teste multithread sem sincronizacao..." << std::endl;
    executarTesteMultithreadSemSincronizacao(1, 1); // 1 produtor, 1 consumidor
    executarTesteMultithreadSemSincronizacao(8, 8); // 8 produtores, 8 consumidores
    executarTesteMultithreadSemSincronizacao(7, 8); // 7 produtores, 8 consumidores
    executarTesteMultithreadSemSincronizacao(3, 1); // 3 produtores, 1 consumidor
    usleep(1000000);
}