#include "Voo.h"
#include "Excecoes.h"
#include <iostream>
#include <ctime>

using namespace std;

unsigned int Voo::ultimo_id = 0;

Voo::Voo() : id(++ultimo_id){}

Voo::~Voo(){}

Voo::Voo(string partida, string destino, Data data_partida, Data data_chegada, unsigned int preco) : id(++ultimo_id), partida(partida), destino(destino), data_partida(data_partida), data_chegada(data_chegada), preco(preco){}

unsigned int Voo::getID() const
{
	return id;
}

void Voo::display() const
{
	cout << "ID: " << id << endl << "From: " << partida << " ";

	data_partida.display();

	cout << endl << "To: " << destino << " ";

	data_chegada.display();

	cout << endl;
}

void Voo::change()
{
	char operacao;

	cout << endl << "Do you want to change flight's departing point (Y/N)?" << endl;
	operacao = cin.get();
	cin.clear();
	cin.ignore(1000, '\n');

	if (operacao == 'Y' || operacao == 'y')
	{
		cout << endl << "New flight departing point?" << endl;
		getline(cin,partida);
	}

	cout << endl << "Do you want to change flight's landing point (Y/N)?" << endl;
	operacao = cin.get();
	cin.clear();
	cin.ignore(1000, '\n');

	if (operacao == 'Y' || operacao == 'y')
	{
		cout << endl << "New flight landing point?" << endl;
		getline(cin,destino);
	}

	cout << endl << "Do you want to change flight's departing date (Y/N)?" << endl;
	operacao = cin.get();
	cin.clear();
	cin.ignore(1000, '\n');

	Data data_partida_temp = data_partida;
	Data data_chegada_temp = data_chegada;

	if (operacao == 'Y' || operacao == 'y')
	{
		unsigned int ano_temp, mes_temp, dia_temp, hora_temp, minuto_temp;

		cout << endl << "New Flight departing year?" << endl;
		cin >> ano_temp;
		if(cin.fail())
			throw FailedInput("Failed to input flight departing year.");
		cin.ignore(1000, '\n');

		cout << endl << "New Flight departing month?" << endl;
		cin >> mes_temp;
		if(cin.fail())
			throw FailedInput("Failed to input flight departing month.");
		cin.ignore(1000, '\n');

		cout << endl << "New Flight departing day?" << endl;
		cin >> dia_temp;
		if(cin.fail())
			throw FailedInput("Failed to input flight departing day.");
		cin.ignore(1000, '\n');

		cout << endl << "New Flight departing hour?" << endl;
		cin >> hora_temp;
		if(cin.fail())
			throw FailedInput("Failed to input flight departing hour.");
		cin.ignore(1000, '\n');

		cout << endl << "New Flight departing minute?" << endl;
		cin >> minuto_temp;
		if(cin.fail())
			throw FailedInput("Failed to input flight departing minute.");
		cin.ignore(1000, '\n');

		Data data_temp(ano_temp, mes_temp, dia_temp, hora_temp, minuto_temp);

		data_partida_temp = data_temp;
	}

	cout << endl << "Do you want to change flight's landing date (Y/N)?" << endl;
	operacao = cin.get();
	cin.clear();
	cin.ignore(1000, '\n');

	if (operacao == 'Y' || operacao == 'y')
	{
		unsigned int ano_temp, mes_temp, dia_temp, hora_temp, minuto_temp;

		cout << endl << "New Flight landing year?" << endl;
		cin >> ano_temp;
		if(cin.fail())
			throw FailedInput("Failed to input flight landing year.");
		cin.ignore(1000, '\n');

		cout << endl << "New Flight landing month?" << endl;
		cin >> mes_temp;
		if(cin.fail())
			throw FailedInput("Failed to input flight landing month.");
		cin.ignore(1000, '\n');

		cout << endl << "New Flight landing day?" << endl;
		cin >> dia_temp;
		if(cin.fail())
			throw FailedInput("Failed to input flight landing day.");
		cin.ignore(1000, '\n');

		cout << endl << "New Flight landing hour?" << endl;
		cin >> hora_temp;
		if(cin.fail())
			throw FailedInput("Failed to input flight landing hour.");
		cin.ignore(1000, '\n');

		cout << endl << "New Flight landing minute?" << endl;
		cin >> minuto_temp;
		if(cin.fail())
			throw FailedInput("Failed to input flight landing minute.");
		cin.ignore(1000, '\n');

		Data data_temp(ano_temp, mes_temp, dia_temp, hora_temp, minuto_temp);

		data_chegada_temp = data_temp;
	}

	if (!(data_partida_temp < data_chegada_temp))
		throw IncorrectValue("The flight can't arrive before it leaves!");

	data_partida = data_partida_temp;
	data_chegada = data_chegada_temp;

	cout << endl << "Do you want to change flight price (Y/N)?" << endl;
	operacao = cin.get();
	cin.clear();
	cin.ignore(1000, '\n');

	if (operacao == 'Y' || operacao == 'y')
	{
		unsigned int preco_temp;

		cout << endl << "New Flight price?" << endl;
		cin >> preco_temp;

		if(cin.fail())
			throw FailedInput("Failed to input flight landing year.");
		cin.ignore(1000, '\n');

		preco = preco_temp;
	}
}

void Voo::removePassageiro(unsigned int id_passageiro){}

void Voo::displayReservations() const{}

void Voo::makeReservation(Passageiro * cliente){}

void Voo::removeReservation(unsigned int cliente){}

void Voo::makePromotion(unsigned int lotacao){}

VooComercial::VooComercial(): Voo(){}

VooComercial::VooComercial(string partida, string destino, Data data_partida, Data data_chegada, unsigned int preco) : Voo(partida, destino, data_partida, data_chegada, preco){}

void VooComercial::display() const
{
	Voo::display();
	cout << "Type: Comercial fligth" << endl << "Price: " << preco << " per ticket" << endl;
}

void VooComercial::removePassageiro(unsigned int id_passageiro)
{
	for(vector<Passageiro *>::iterator it = passageiros.begin(); it != passageiros.end(); it++)
	{
		if ((*it)->getID() == id_passageiro)
		{
			passageiros.erase(it);
			return;
		}
	}
}

void VooComercial::displayReservations() const
{
	if(passageiros.empty())
		throw PassengersEmpty();

	for(vector<Passageiro *>::const_iterator it = passageiros.begin(); it != passageiros.end(); it++)
	{
		cout << endl;
		(*it)->display();
	}

	cout << endl << endl;
}

void VooComercial::makeReservation(Passageiro * cliente)
{
	float price = cliente->getPriceWithCard(preco);

	cliente->subtract_to_balance((unsigned int) price);

	passageiros.push_back(cliente);
}

void VooComercial::removeReservation(unsigned int id_cliente)
{
	if(passageiros.empty())
		throw PassengersEmpty();

	for(vector<Passageiro *>::iterator it = passageiros.begin(); it != passageiros.end(); it++)
	{
		if ((*it)->getID() == id_cliente)
		{
			float price = (*it)->getPriceWithCard(preco);

			(*it)->add_to_balance((unsigned int) price);

			passageiros.erase(it);

			return;
		}
	}

	throw PassageiroNotFound(id_cliente);
}

void VooComercial::makePromotion(unsigned int lotacao)
{
	Data agora;

	agora.setCurrentDate();

	struct tm a = {0,agora.get_minuto(),agora.get_hora(),agora.get_dia(),agora.get_mes() - 1,agora.get_ano()-1900};
	struct tm b = {0,data_partida.get_minuto(),data_partida.get_hora(),data_partida.get_dia(),data_partida.get_mes() - 1,data_partida.get_ano()-1900};
	time_t x = mktime(&a);
	time_t y = mktime(&b);

	double difference = difftime(y, x) / (60 * 60);

	if (difference >= 48)
		throw CantDoPromotion();

	if ((float)(passageiros.size() / lotacao) < 0.5)
	{
		preco *= 0.9;
		return;
	}

	throw CantDoPromotion();

}

bool VooComercial::checkFull(unsigned int lotacao)
{
	if (lotacao > passageiros.size())
		return false;

	return true;
}

VooAlugado::VooAlugado(): Voo()
{
	passageiro = nullptr;
}

VooAlugado::VooAlugado(string partida, string destino, Data data_partida, Data data_chegada, unsigned int preco) : Voo(partida, destino, data_partida, data_chegada, preco)
{
	passageiro = nullptr;
}

void VooAlugado::display() const
{
	Voo::display();
	cout << "Type: Rented flight" << endl << "Price: " << preco << " for the rent" << endl;
}

void VooAlugado::removePassageiro(unsigned int id_passageiro)
{
	if (passageiro->getID() == id_passageiro)
		passageiro = nullptr;
}

void VooAlugado::displayReservations() const
{
	if (passageiro == nullptr)
		throw PassengersEmpty();

	else
	{
		cout << endl;
		passageiro->display();
		cout << endl << endl;
	}
}

void VooAlugado::makeReservation(Passageiro * cliente)
{
	float price = cliente->getPriceWithCard(preco);

	cliente->subtract_to_balance((unsigned int) price);

	passageiro = cliente;
}

void VooAlugado::removeReservation(unsigned int id_cliente)
{
	if (passageiro == nullptr)
		throw PassengersEmpty();

	float price = passageiro->getPriceWithCard(preco);

	passageiro->add_to_balance((unsigned int) price);

	passageiro = nullptr;
}

void VooAlugado::makePromotion(unsigned int lotacao)
{
	Data agora;

	agora.setCurrentDate();

	struct tm a = {0,agora.get_minuto(),agora.get_hora(),agora.get_dia(),agora.get_mes() - 1,agora.get_ano()-1900};
	struct tm b = {0,data_partida.get_minuto(),data_partida.get_hora(),data_partida.get_dia(),data_partida.get_mes() - 1,data_partida.get_ano()-1900};
	time_t x = mktime(&a);
	time_t y = mktime(&b);

	double difference = difftime(y, x) / (60 * 60);

	if (difference >= 48)
		throw CantDoPromotion();

	if (passageiro == nullptr)
	{
		preco *= 0.9;
		return;
	}

	throw CantDoPromotion();
}

bool VooAlugado::checkFull(unsigned int lotacao)
{
	if (passageiro == nullptr)
		return true;

	return false;
}
