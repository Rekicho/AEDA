#include "Passageiro.h"
#include "Excecoes.h"
#include <iostream>

using namespace std;

unsigned int Passageiro::ultimo_id = 0;

Passageiro::Passageiro() : id(++ultimo_id){}

Passageiro::~Passageiro(){}

unsigned int Passageiro::getID() const
{
	return id;
}

void Passageiro::display() const
{
	cout << "ID: " << id << endl;
}

void Passageiro::change(){}

float Passageiro::getPriceWithCard(unsigned int preco)
{
	return preco;
}

void Passageiro::subtract_to_balance(unsigned int valor){}

void Passageiro::add_to_balance(unsigned int valor){}

PassageiroNormal::PassageiroNormal() : Passageiro(){}

PassageiroNormal::PassageiroNormal(unsigned int saldo, string nome) : Passageiro(), saldo(saldo), nome(nome){}

void PassageiroNormal::display() const
{
	Passageiro::display();

	cout << "Type: Passenger without card" << endl << "Name: " << nome << endl << "Balance: " << saldo << endl;
}

void PassageiroNormal::change()
{
	char operacao;

	cout << endl << "Do you want to change passenger's balance (Y/N)?" << endl;
	operacao = cin.get();
	cin.clear();
	cin.ignore(1000, '\n');

	if (operacao == 'Y' || operacao == 'y')
	{
		unsigned int saldo_temp;

		cout << endl << "New passenger balance?" << endl;
		cin >> saldo_temp;

		if(cin.fail())
			throw FailedInput("Failed to input passenger balance.");
		cin.ignore(1000, '\n');

		saldo = saldo_temp;
	}

	cout << endl << "Do you want to change passenger's name (Y/N)?" << endl;
	operacao = cin.get();
	cin.clear();
	cin.ignore(1000, '\n');

	if (operacao == 'Y' || operacao == 'y')
	{
		cout << endl << "New passenger name?" << endl;
		getline(cin,nome);
	}

}

float PassageiroNormal::getPriceWithCard(unsigned int preco)
{
	return preco;
}

void PassageiroNormal::subtract_to_balance(unsigned int valor)
{
	if (saldo < valor)
		throw IncorrectValue("Client does no have enough money for that reservation.");

	saldo -= valor;
}

void PassageiroNormal::add_to_balance(unsigned int valor)
{
	saldo += valor;
}

PassageiroCartao::PassageiroCartao() : Passageiro(){}

PassageiroCartao::PassageiroCartao(Cartao cartao) : Passageiro(), cartao(cartao){};

void PassageiroCartao::display() const
{
	cout << "Type: Passenger with card" << endl << "Card: " << endl;
	cartao.display();
}

void PassageiroCartao::change()
{
	cartao.change();
}

float PassageiroCartao::getPriceWithCard(unsigned int preco)
{
	return (preco * ((100-cartao.get_nMedAno())/100));
}

void PassageiroCartao::subtract_to_balance(unsigned int valor)
{
	cartao.subtract_to_balance(valor);
}

void PassageiroCartao::add_to_balance(unsigned int valor)
{
	cartao.add_to_balance(valor);
}
