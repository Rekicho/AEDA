#include "Cartao.h"
#include "Excecoes.h"
#include <iostream>

using namespace std;

unsigned int Cartao::ultimo_id = 0;

Cartao::Cartao() : id(++ultimo_id){}

Cartao::Cartao(unsigned int saldo, string nome, string profissao, Data data_nascimento, float nMedAno) : id(++ultimo_id), saldo(saldo), nome(nome), profissao(profissao), data_nascimento(data_nascimento), nMedAno(nMedAno){}

Cartao::Cartao(unsigned int id, unsigned int saldo, string nome, string profissao, Data data_nascimento, float nMedAno) :id(id), nome(nome), profissao(profissao), data_nascimento(data_nascimento), nMedAno(nMedAno), saldo(saldo)
{
	if (id > ultimo_id)
	{
		ultimo_id = id;
	}
}
unsigned int Cartao::get_id() const
{
	return id;
}

unsigned int Cartao::get_saldo() const
{
	return saldo;
}

string Cartao::get_profissao() const
{
	return profissao;
}

string Cartao::get_name() const
{
	return nome;
}

float Cartao::get_nMedAno() const
{
	return nMedAno;
}

Data Cartao::get_data() const
{
	return data_nascimento;
}

void Cartao::display() const
{
	cout << "ID: " << id << endl << "Balance: " << saldo << endl << "Name: " << nome << endl << "Job: " << profissao << endl << "Birth date: ";

	data_nascimento.displayDia();

	cout << endl << "Average number of flights per year: " << nMedAno << endl;
}

void Cartao::change()
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

	cout << endl << "Do you want to change passenger's job (Y/N)?" << endl;
	operacao = cin.get();
	cin.clear();
	cin.ignore(1000, '\n');

	if (operacao == 'Y' || operacao == 'y')
	{
		cout << endl << "New passenger job?" << endl;
		getline(cin,profissao);
	}

	cout << endl << "Do you want to change passenger's birth date (Y/N)?" << endl;
	operacao = cin.get();
	cin.clear();
	cin.ignore(1000, '\n');

	if (operacao == 'Y' || operacao == 'y')
	{
		unsigned int ano_temp, mes_temp, dia_temp;

		cout << endl << "Passenger birth year?" << endl;
		cin >> ano_temp;
		if(cin.fail())
			throw FailedInput("Failed to input passenger birth year.");
		cin.ignore(1000, '\n');

		cout << endl << "Passenger birth month?" << endl;
		cin >> mes_temp;
		if(cin.fail())
			throw FailedInput("Failed to input passenger birth month.");
		cin.ignore(1000, '\n');

		cout << endl << "Passenger birth day?" << endl;
		cin >> dia_temp;
		if(cin.fail())
			throw FailedInput("Failed to input passenger birth day.");
		cin.ignore(1000, '\n');

		Data data_temp(ano_temp,mes_temp,dia_temp);

		data_nascimento = data_temp;
	}

	cout << endl << "Do you want to change passenger's average number of flights per year (Y/N)?" << endl;
	operacao = cin.get();
	cin.clear();
	cin.ignore(1000, '\n');

	if (operacao == 'Y' || operacao == 'y')
	{
		float nMedAno_temp;
		cout << endl << "New passenger average number of flights per year?" << endl;
		cin >> nMedAno_temp;
		if(cin.fail())
			throw FailedInput("Failed to input passenger average number of flights per year.");
		cin.ignore(1000, '\n');

		nMedAno = nMedAno_temp;
	}

}

void Cartao::subtract_to_balance(unsigned int valor)
{
	if (saldo < valor)
		throw IncorrectValue("Client does no have enough money for that reservation.");
	saldo -= valor;
}

void Cartao::add_to_balance(unsigned int valor)
{
	saldo += valor;
}
