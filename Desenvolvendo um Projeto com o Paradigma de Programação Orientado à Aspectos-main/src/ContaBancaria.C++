#include <iostream>
#include <stdexcept>

class SaldoInsuficienteException : public std::exception {
public:
    const char* what() const throw() {
        return "Saldo insuficiente!";
    }
};

class ContaBancaria {
protected:
    double saldo;

public:
    void depositar(double valor) {
        saldo += valor;
    }

    virtual void sacar(double valor) = 0;

    void consultarSaldo() {
        std::cout << "Saldo: " << saldo << std::endl;
    }
};

class VerificarSaldo {
public:
    static void before(ContaBancaria* conta, double valor) {
        if (conta->saldo - valor < 0) {
            throw SaldoInsuficienteException();
        }
    }
};

class MinhaContaBancaria : public ContaBancaria {
public:
    void sacar(double valor) override {
        VerificarSaldo::before(this, valor);
        saldo -= valor;
    }
};

int main() {
    ContaBancaria* conta = new MinhaContaBancaria();
    conta->depositar(1000);
    conta->consultarSaldo();

    try {
        conta->sacar(500);
        std::cout << "Saque realizado com sucesso!" << std::endl;
    } catch (const std::exception& ex) {
        std::cout << "Erro: " << ex.what() << std::endl;
    }

    conta->consultarSaldo();

    delete conta;
    return 0;
}
