#include "classes.h"

void executarTesteSequencial(){
    Conta conta;
    auto comeco = std::chrono::high_resolution_clock::now(); // Iniciar contagem

    for (int i = 0; i < 500; i++){
        conta.depositar(rand() % 100);
        // std::cout << "Deposito sequencial. Saldo atual: " << conta.getSaldo() << std::endl;
    }


    for (int i = 0; i < 500; i++){
        conta.sacar(rand() % 50);
        // std::cout << "Saque sequencial. Saldo atual: " << conta.getSaldo() << std::endl;
    }

    auto fim = std::chrono::high_resolution_clock::now(); // Finalizar tempo
    std::chrono::duration<double> duracao = fim - comeco; 
    std::cout.precision(3);
    std::cout << "Tempo sequencial: " << duracao.count() << std::endl;
}

int main(){
    std::cout << "Executando teste sequencial..." << std::endl;
    executarTesteSequencial();
    return 0;
}