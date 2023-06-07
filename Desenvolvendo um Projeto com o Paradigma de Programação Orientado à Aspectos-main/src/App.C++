#include <iostream>

class ContaBancaria {
public:
    virtual void depositar(double valor) = 0;
    virtual void sacar(double valor) = 0;
    virtual void consultarSaldo() = 0;
};

class MinhaConta : public ContaBancaria {
public:
    void depositar(double valor) override {
        saldo += valor;
    }

    void sacar(double valor) override {
        if (valor <= saldo) {
            saldo -= valor;
        } else {
            std::cout << "Saldo insuficiente." << std::endl;
        }
    }

    void consultarSaldo() override {
        std::cout << "Saldo: " << saldo << std::endl;
    }

private:
    double saldo = 0;
};

int main() {
    MinhaConta minhaConta;
    minhaConta.depositar(1000);
    minhaConta.consultarSaldo();
    minhaConta.sacar(500);
    minhaConta.consultarSaldo();

    return 0;
}
