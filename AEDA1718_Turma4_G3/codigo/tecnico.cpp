#include "Tecnico.h"
#include "Excecoes.h"
#include <iostream>

using namespace std;

unsigned int Tecnico::ultimo_id = 0;

Tecnico::Tecnico() : id(++ultimo_id){}

Tecnico::Tecnico(unsigned int id) : id(id){}

Tecnico::Tecnico(string nome, vector<string> especialidade) : id(++ultimo_id), nome(nome), especialidade(especialidade){}

unsigned int Tecnico::getID() const
{
	return id;
}

string Tecnico::getnome() const
{
	return nome;
}

vector<string>Tecnico::getespecialidades() const
{
	return especialidade;
}

vector<Aviao> Tecnico::getmanutencoes() const
{
	return manutencoes;
}

void Tecnico::display() const
{
	cout << endl << endl << "Id: " << id << endl << "Name: " << nome << endl << "Specialities: ";

	for(unsigned int i = 0; i < especialidade.size(); i++)
		cout << especialidade[i] << "; ";

	cout << endl << "Maintenances: ";

	for(unsigned int i = 0; i < especialidade.size(); i++)
		cout << manutencoes[i].getID() << "; ";

	cout << endl;
}

void Tecnico::change()
{
	char operacao;

	cout << endl << "Do you want to change tecnician's name (Y/N)?" << endl;
	operacao = cin.get();
	cin.clear();
	cin.ignore(1000, '\n');

	if (operacao == 'Y' || operacao == 'y')
	{
		cout << endl << "New tecnician name?" << endl;
		getline(cin,nome);
	}

	cout << endl << "Do you want to change tecnician's specialities (Y/N)?" << endl;
	operacao = cin.get();
	cin.clear();
	cin.ignore(1000, '\n');

	if (operacao == 'Y' || operacao == 'y')
	{
		unsigned int n;
		vector<string> str_vect;
		string temp_str;
		cout << endl << "How many specialities does the tecnician have?";
		cin >> n;
		if(cin.fail())
			throw FailedInput("Failed to input number of specialities.");
		cin.ignore(1000, '\n');

		for(unsigned int i = 0; i < n; i++)
		{
			cout << endl << "Speciality name?";
			cin >> temp_str;

			str_vect.push_back(temp_str);
		}

		especialidade = str_vect;
	}
}
bool Tecnico::operator<(const Tecnico &t1) const
{
	if (manutencoes.empty())
		return true;

	vector<Aviao> temp = t1.getmanutencoes();

	if (temp.empty())
		return false;

	if(temp.back().getProxima_Manutencao() < manutencoes.back().getProxima_Manutencao())
		return false;

	return true;
}
