#include "Aviao.h"
#include "Excecoes.h"
#include <iostream>

using namespace std;

unsigned int Aviao::ultimo_id = 0;

Aviao::Aviao() : id(++ultimo_id){}

Aviao::~Aviao()
{
	//For some reason not working when doing FILE I/O, we don't know why, but for the program to work when commented it
	/*typename vector<Voo *>::iterator it;
	for (it=voos.begin(); it!=voos.end(); it++)
		delete *it;*/
};

Aviao::Aviao(unsigned int id) : id(id)
{
	if(id > ultimo_id)
		ultimo_id = id;
}

Aviao::Aviao(string nome, unsigned int lotacao) : id(++ultimo_id), nome(nome), lotacao(lotacao){}

Aviao::Aviao(std::string nome, unsigned int lotacao, unsigned int periocidade_manutencao, Data proxima_manutencao) : id(++ultimo_id), nome(nome), lotacao(lotacao), periocidade_manutencao(periocidade_manutencao), proxima_manutencao(proxima_manutencao){}

unsigned int Aviao::getID() const
{
	return id;
}

string Aviao::getNome() const
{
	return nome;
}

unsigned int Aviao::getLotacao() const
{
	return lotacao;
}

vector<Voo*> Aviao::getVoos() const
{
	return voos;
}

unsigned int Aviao::getPeriodicidade_Manutencao() const
{
	return periocidade_manutencao;
}

Data Aviao::getProxima_Manutencao() const
{
	return proxima_manutencao;
}

void Aviao::setProxima_Manutencao(const Data proxima_manutencao)
{
	this->proxima_manutencao = proxima_manutencao;
}

void Aviao::display() const
{
	cout << endl << "ID: " << id << endl << "Nome: " << nome << endl << "Lotacao: " << lotacao << endl << "Periocidade Manutencao: " << periocidade_manutencao << endl << "Proxima Manutencao: ";
	proxima_manutencao.displayDia();
	cout << endl;
}

Aviao Aviao::change()
{
	char operacao;

	cout << endl << "Do you want to change airplane's model (Y/N)?" << endl;

	operacao = cin.get();
	cin.clear();
	cin.ignore(1000, '\n');

	if (operacao == 'Y' || operacao == 'y')
	{
		cout << endl << "New airplane model?" << endl;
		getline(cin,nome);
	}

	cout << endl << "Do you want to change capacity (Y/N)?" << endl;

	operacao = cin.get();
	cin.clear();
	cin.ignore(1000, '\n');

	if (operacao == 'Y' || operacao == 'y')
	{
		unsigned int lotacao_temp;

		cout << endl << "New airplane capacity?" << endl;
		cin >> lotacao_temp;

		if(cin.fail())
			throw FailedInput("Failed to input airplane capacity.");
		cin.ignore(1000, '\n');

		if(lotacao_temp < voos.size())
			throw IncorrectValue("There are more reservations than the capacity you inserted.");

		lotacao = lotacao_temp;
	}

	cout << endl << "Do you want to change maintenance frequency (Y/N)?" << endl;
	operacao = cin.get();
	cin.clear();
	cin.ignore(1000, '\n');

	if (operacao == 'Y' || operacao == 'y')
	{
		unsigned int periocidade_manutencao_temp;

		cout << endl << "New airplane capacity?" << endl;
		cin >> periocidade_manutencao_temp;

		if(cin.fail())
			throw FailedInput("Failed to input airplane maintenance frequency.");
		cin.ignore(1000, '\n');

		periocidade_manutencao = periocidade_manutencao_temp;
	}

	cout << endl << "Do you want to change airplane next maintenance date (Y/N)?" << endl;
	operacao = cin.get();
	cin.clear();
	cin.ignore(1000, '\n');

	if (operacao == 'Y' || operacao == 'y')
	{
		unsigned int ano_temp, mes_temp, dia_temp;

		cout << endl << "Airplane next maintenance year?" << endl;
		cin >> ano_temp;
		if(cin.fail())
			throw FailedInput("Failed to input airplane next maintenance year.");
		cin.ignore(1000, '\n');

		cout << endl << "Airplane next maintenance month?" << endl;
		cin >> mes_temp;
		if(cin.fail())
			throw FailedInput("Failed to input airplane next maintenance month.");
		cin.ignore(1000, '\n');

		cout << endl << "Airplane next maintenance day?" << endl;
		cin >> dia_temp;
		if(cin.fail())
			throw FailedInput("Failed to input airplane next maintenance day.");
		cin.ignore(1000, '\n');

		Data data_temp(ano_temp,mes_temp,dia_temp);

		proxima_manutencao = data_temp;
	}

	return *this;
}

void Aviao::displayVoos() const
{
	if(voos.empty())
		throw FlightsEmpty();

	for(vector<Voo *>::const_iterator it = voos.begin(); it!=voos.end(); it++)
	{
		cout << endl;
		(*it)->display();
	}

	cout << endl << endl;
}

Aviao Aviao::addVoo()
{
	string partida_temp;
	string destino_temp;
	unsigned int preco_temp;
	char rented_flight;

	cout << endl << "Is the flight rented (Y/N)?" << endl;
	rented_flight = cin.get();
	cin.clear();
	cin.ignore(1000, '\n');

	cout << endl << "Flight departing point?" << endl;
	getline(cin,partida_temp);

	cout << endl << "Flight landing point?" << endl;
	getline(cin, destino_temp);

	unsigned int ano_temp, mes_temp, dia_temp, hora_temp, minuto_temp;

	cout << endl << "Flight departing year?" << endl;
	cin >> ano_temp;
	if(cin.fail())
		throw FailedInput("Failed to input flight departing year.");
	cin.ignore(1000, '\n');

	cout << endl << "Flight departing month?" << endl;
	cin >> mes_temp;
	if(cin.fail())
		throw FailedInput("Failed to input flight departing month.");
	cin.ignore(1000, '\n');

	cout << endl << "Flight departing day?" << endl;
	cin >> dia_temp;
	if(cin.fail())
		throw FailedInput("Failed to input flight departing day.");
	cin.ignore(1000, '\n');

	cout << endl << "Flight departing hour?" << endl;
	cin >> hora_temp;
	if(cin.fail())
		throw FailedInput("Failed to input flight departing hour.");
	cin.ignore(1000, '\n');

	cout << endl << "Flight departing minute?" << endl;
	cin >> minuto_temp;
	if(cin.fail())
		throw FailedInput("Failed to input flight departing minute.");
	cin.ignore(1000, '\n');

	Data data_partida_temp(ano_temp, mes_temp, dia_temp, hora_temp, minuto_temp);

	cout << endl << "Flight landing year?" << endl;
	cin >> ano_temp;
	if(cin.fail())
		throw FailedInput("Failed to input flight landing year.");
	cin.ignore(1000, '\n');

	cout << endl << "Flight landing month?" << endl;
	cin >> mes_temp;
	if(cin.fail())
		throw FailedInput("Failed to input flight landing month.");
	cin.ignore(1000, '\n');

	cout << endl << "Flight landing day?" << endl;
	cin >> dia_temp;
	if(cin.fail())
		throw FailedInput("Failed to input flight landing day.");
	cin.ignore(1000, '\n');

	cout << endl << "Flight landing hour?" << endl;
	cin >> hora_temp;
	if(cin.fail())
		throw FailedInput("Failed to input flight landing hour.");
	cin.ignore(1000, '\n');

	cout << endl << "Flight landing minute?" << endl;
	cin >> minuto_temp;
	if(cin.fail())
		throw FailedInput("Failed to input flight landing balance.");
	cin.ignore(1000, '\n');

	Data data_chegada_temp(ano_temp, mes_temp, dia_temp, hora_temp, minuto_temp);

	if (!(data_partida_temp < data_chegada_temp))
		throw IncorrectValue("The flight can't arrive before it leaves!");

	cout << endl << "Flight price?" << endl;
	cin >> preco_temp;
	if(cin.fail())
		throw FailedInput("Failed to input flight price.");
	cin.ignore(1000, '\n');

	if (rented_flight == 'Y' || rented_flight == 'y')
	{
		Voo * flight = new VooAlugado(partida_temp, destino_temp, data_partida_temp, data_chegada_temp, preco_temp);
		voos.push_back(flight);
	}

	else
	{
		Voo * flight = new VooComercial(partida_temp, destino_temp, data_partida_temp, data_chegada_temp, preco_temp);
		voos.push_back(flight);
	}

	return *this;
}

void Aviao::changeVoo()
{
	if(voos.empty())
		throw FlightsEmpty();

	unsigned int id_voo;
	cout << endl << "Flight ID?" << endl;
	cin >> id_voo;
	if(cin.fail())
		throw FailedInput("Failed to input flight ID.");
	cin.ignore(1000, '\n');

	for(vector<Voo *>::iterator it = voos.begin(); it!=voos.end(); it++)
	{
		if ((*it)->getID() == id_voo)
		{
			(*it)->change();
			return;
		}
	}

	throw FlightNotFound(id_voo);
}

Aviao Aviao::removeVoo()
{
	if(voos.empty())
		throw FlightsEmpty();

	unsigned int id_voo;
	cout << endl << "Flight ID?" << endl;
	cin >> id_voo;
	if(cin.fail())
		throw FailedInput("Failed to input flight ID.");
	cin.ignore(1000, '\n');

	bool found = false;

	for(vector<Voo *>::iterator it = voos.begin(); it!=voos.end(); it++)
	{
		if ((*it)->getID() == id_voo)
		{
			delete(*it);
			voos.erase(it);
			found = true;
			break;
		}
	}

	if(!found)
		throw FlightNotFound(id_voo);

	return *this;
}

void Aviao::removePassageiro(unsigned int id_passageiro)
{
	for(vector<Voo *>::iterator it = voos.begin(); it!=voos.end(); it++)
	{
		(*it)->removePassageiro(id_passageiro);
	}
}

void Aviao::displayReservations() const
{
	if(voos.empty())
		throw FlightsEmpty();

	unsigned int id_voo;
	cout << endl << "Flight ID?" << endl;
	cin >> id_voo;
	if(cin.fail())
		throw FailedInput("Failed to input flight ID.");
	cin.ignore(1000, '\n');

	for(vector<Voo *>::const_iterator it = voos.begin(); it!=voos.end(); it++)
	{
		if ((*it)->getID() == id_voo)
		{
			(*it)->displayReservations();
			return;
		}
	}

	throw FlightNotFound(id_voo);
}

void Aviao::makeReservation(Passageiro * cliente)
{
	if(voos.empty())
		throw FlightsEmpty();

	unsigned int id_voo;
	cout << endl << "Flight ID?" << endl;
	cin >> id_voo;
	if(cin.fail())
		throw FailedInput("Failed to input flight ID.");
	cin.ignore(1000, '\n');

	for(vector<Voo *>::iterator it = voos.begin(); it!=voos.end(); it++)
	{
		if ((*it)->getID() == id_voo)
		{
			if ((*it)->checkFull(lotacao))
				throw FlightFull();

			(*it)->makeReservation(cliente);
			return;
		}
	}

	throw FlightNotFound(id_voo);
}

void Aviao::removeReservation(unsigned int id_cliente)
{
	if(voos.empty())
		throw FlightsEmpty();

	unsigned int id_voo;
	cout << endl << "Flight ID?" << endl;
	cin >> id_voo;
	if(cin.fail())
		throw FailedInput("Failed to input flight ID.");
	cin.ignore(1000, '\n');

	for(vector<Voo *>::iterator it = voos.begin(); it!=voos.end(); it++)
	{
		if ((*it)->getID() == id_voo)
		{
			(*it)->removeReservation(id_cliente);
			return;
		}
	}

	throw FlightNotFound(id_voo);
}

void Aviao::makePromotion()
{
	if(voos.empty())
		throw FlightsEmpty();

	unsigned int id_voo;
	cout << endl << "Flight ID?" << endl;
	cin >> id_voo;
	if(cin.fail())
		throw FailedInput("Failed to input flight ID.");
	cin.ignore(1000, '\n');

	for(vector<Voo *>::iterator it = voos.begin(); it!=voos.end(); it++)
	{
		if ((*it)->getID() == id_voo)
		{
			(*it)->makePromotion(lotacao);
			return;
		}
	}

	throw FlightNotFound(id_voo);
}

bool Aviao::operator<(const Aviao &a1) const
{
	return proxima_manutencao < a1.getProxima_Manutencao();
}

bool Aviao::operator==(const Aviao &a1) const
				{
	return id == a1.getID();
				}
