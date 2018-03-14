#include "Companhia.h"
#include "Excecoes.h"
#include <iostream>

using namespace std;

Companhia::~Companhia()
{
	for (vector<Passageiro *>::iterator it=clientes.begin(); it!=clientes.end(); it++)
		delete *it;

	for (tabHPassageiro::iterator it=passageiros_inativos.begin(); it != passageiros_inativos.end(); it++)
		delete it->passageiro;
}

void Companhia::displayAvioes() const
{
	if (avioes.empty())
		throw Airplanes_Empty();
	for (unsigned int i = 0; i < avioes.size(); i++)
		avioes[i].display();
}

void Companhia::addAviao()
{
	string nome_temp;
	unsigned int lotacao_temp, periocidade_manutencao_temp;

	cout << endl << "Airplane model?" << endl;
	getline(cin,nome_temp);

	cout << endl << "Airplane capacity?" << endl;
	cin >> lotacao_temp;
	if(cin.fail())
		throw FailedInput("Failed to input airplane capacity.");
	cin.ignore(1000, '\n');

	cout << endl << "Airplane maintenance frequency?" << endl;
	cin >> periocidade_manutencao_temp;
	if(cin.fail())
		throw FailedInput("Failed to input airplane maintenance frequency.");
	cin.ignore(1000, '\n');

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
		throw FailedInput("Failed to input Airplane next maintenance day.");
	cin.ignore(1000, '\n');

	Data data_temp(ano_temp,mes_temp,dia_temp);

	Aviao aviao(nome_temp,lotacao_temp,periocidade_manutencao_temp,data_temp);

	avioes.push_back(aviao);
	avioes_bst.insert(aviao);
}

void Companhia::changeAviao()
{
	if (avioes.empty())
		throw Airplanes_Empty();

	unsigned int id_a_alterar;
	cout << endl << "Airplane ID?" << endl;
	cin >> id_a_alterar;
	if(cin.fail())
		throw FailedInput("Failed to input airplane ID.");
	cin.ignore(1000, '\n');

	Aviao aviao_temp;
	bool found = false;

	for (unsigned int i = 0; i < avioes.size(); i++)
	{
		if (avioes[i].getID() == id_a_alterar)
		{
			aviao_temp = avioes[i].change();
			found = true;
			break;
		}
	}

	if(!found)
		throw AirplaneNotFound(id_a_alterar);

	avioes_bst.remove(aviao_temp);
	avioes_bst.insert(aviao_temp);

}
void Companhia::removeAviao()
{
	if (avioes.empty())
		throw Airplanes_Empty();
	unsigned int id_a_remover;
	cout << endl << "Airplane ID?" << endl;
	cin >> id_a_remover;
	if(cin.fail())
		throw FailedInput("Failed to input airplane ID.");
	cin.ignore(1000, '\n');

	Aviao aviao_temp(id_a_remover);
	bool found = false;

	for (unsigned int i = 0; i < avioes.size(); i++)
	{
		if (avioes[i].getID() == id_a_remover)
		{
			avioes.erase(avioes.begin() + i);
			found = true;
			break;
		}
	}

	if(!found)
		throw AirplaneNotFound(id_a_remover);

	avioes_bst.remove(aviao_temp);

}

void Companhia::displayVoos() const
{
	if (avioes.empty())
		throw Airplanes_Empty();

	for (unsigned int i = 0; i < avioes.size(); i++)
	{
		cout << endl << "Airplane ID: " << avioes[i].getID() << endl << "Flights:" << endl;
		try
		{
			avioes[i].displayVoos();
		}
		catch(Aviao::FlightsEmpty &e)
		{
			cout << endl << "This airplanes has no flights." << endl << endl;
		}
	}
}

void Companhia::addVoo()
{
	if (avioes.empty())
		throw Airplanes_Empty();

	unsigned int id_aviao;
	cout << endl << "Airplane ID?" << endl;
	cin >> id_aviao;
	if(cin.fail())
		throw FailedInput("Failed to input airplane ID.");
	cin.ignore(1000, '\n');

	Aviao aviao_temp;
	bool found = false;

	for (unsigned int i = 0; i < avioes.size(); i++)
	{
		if (avioes[i].getID() == id_aviao)
		{
			aviao_temp = avioes[i].addVoo();
			found = true;
			break;
		}
	}

	if(!found)
		throw AirplaneNotFound(id_aviao);

	avioes_bst.remove(aviao_temp);
	avioes_bst.insert(aviao_temp);
}

void Companhia::changeVoo()
{
	if (avioes.empty())
		throw Airplanes_Empty();

	unsigned int id_aviao;
	cout << endl << "Airplane ID?" << endl;
	cin >> id_aviao;
	if(cin.fail())
		throw FailedInput("Failed to input airplane ID.");
	cin.ignore(1000, '\n');

	for (unsigned int i = 0; i < avioes.size(); i++)
	{
		if (avioes[i].getID() == id_aviao)
		{
			avioes[i].changeVoo();
			return;
		}
	}

	throw AirplaneNotFound(id_aviao);
}

void Companhia::removeVoo()
{
	if (avioes.empty())
		throw Airplanes_Empty();

	unsigned int id_aviao;
	cout << endl << "Airplane ID?" << endl;
	cin >> id_aviao;
	if(cin.fail())
		throw FailedInput("Failed to input airplane ID.");
	cin.ignore(1000, '\n');

	Aviao aviao_temp;
	bool found = false;

	for (unsigned int i = 0; i < avioes.size(); i++)
	{
		if (avioes[i].getID() == id_aviao)
		{
			aviao_temp = avioes[i].removeVoo();
			found = true;
			break;
		}
	}

	if(!found)
		throw AirplaneNotFound(id_aviao);

	avioes_bst.remove(aviao_temp);
	avioes_bst.insert(aviao_temp);
}

void Companhia::displayPassageiros() const
{
	if (clientes.empty())
		throw Clientes_Empty();

	for(vector<Passageiro *>::const_iterator it = clientes.begin(); it!=clientes.end(); it++)
	{
		cout << endl;
		(*it)->display();
	}

	cout << endl << endl;
}

void Companhia::addPassageiro()
{
	char passageiro_com_cartao;

	cout << endl << "Has the Passenger a card (Y/N)?" << endl;
	passageiro_com_cartao = cin.get();
	cin.clear();
	cin.ignore(1000, '\n');

	if (passageiro_com_cartao == 'Y' || passageiro_com_cartao == 'y')
	{
		unsigned int saldo_temp;
		string nome_temp;
		string profissao_temp;
		float nMedAno_temp;

		cout << endl << "Passenger balance?" << endl;
		cin >> saldo_temp;
		if(cin.fail())
			throw FailedInput("Failed to input passenger balance.");
		cin.ignore(1000, '\n');

		cout << endl << "Passenger name?" << endl;
		getline(cin,nome_temp);

		cout << endl << "Passenger job?" << endl;
		getline(cin,profissao_temp);

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

		cout << endl << "Passenger average number of flights per year?" << endl;
		cin >> nMedAno_temp;
		if(cin.fail())
			throw FailedInput("Failed to input passenger average number of flights per year.");;
		cin.ignore(1000, '\n');

		Cartao cartao_temp(saldo_temp, nome_temp, profissao_temp, data_temp, nMedAno_temp);

		Passageiro * passenger = new PassageiroCartao(cartao_temp);
		PassageiroPtr temp;
		temp.passageiro = passenger;
		passageiros_inativos.insert(temp);
	}

	else
	{
		unsigned int saldo_temp;
		string nome_temp;

		cout << endl << "Passenger balance?" << endl;
		cin >> saldo_temp;
		if(cin.fail())
			throw FailedInput("Failed to input passenger balance.");
		cin.ignore(1000, '\n');

		cout << endl << "Passenger name?" << endl;
		getline(cin,nome_temp);

		Passageiro * passenger = new PassageiroNormal(saldo_temp,nome_temp);
		PassageiroPtr temp;
		temp.passageiro = passenger;
		passageiros_inativos.insert(temp);
	}
}

void Companhia::changePassageiro()
{
	if (clientes.empty() && passageiros_inativos.empty())
		throw Clientes_Empty();

	unsigned int id_passageiro;
	cout << endl << "Passenger ID?" << endl;
	cin >> id_passageiro;
	if(cin.fail())
		throw FailedInput("Failed to input passenger ID.");
	cin.ignore(1000, '\n');

	for(vector<Passageiro *>::iterator it = clientes.begin(); it != clientes.end(); it++)
	{
		if ((*it)->getID() == id_passageiro)
		{
			(*it)->change();
			return;
		}
	}

	for(tabHPassageiro::iterator it = passageiros_inativos.begin(); it != passageiros_inativos.end(); it++)
	{
		if (it->passageiro->getID() == id_passageiro)
		{
			it->passageiro->change();
			return;
		}
	}

	throw ClientNotFound(id_passageiro);
}

void Companhia::removePassageiro()
{
	if (clientes.empty() && passageiros_inativos.empty())
		throw Clientes_Empty();

	unsigned int id_passageiro;
	cout << endl << "Passenger ID?" << endl;
	cin >> id_passageiro;
	if(cin.fail())
		throw FailedInput("Failed to input passenger ID.");
	cin.ignore(1000, '\n');

	//Procura passageiro em todos voos de todos os avioes, remove-o desses voos e depois remove-o do vector clientes, apagando-o (com delete)
	for (unsigned int i = 0; i < avioes.size(); i++)
		avioes[i].removePassageiro(id_passageiro);

	for(vector<Passageiro *>::iterator it = clientes.begin(); it != clientes.end(); it++)
	{
		if ((*it)->getID() == id_passageiro)
		{
			delete *it;
			clientes.erase(it);
			return;
		}
	}

	for(tabHPassageiro::iterator it = passageiros_inativos.begin(); it != passageiros_inativos.end(); it++)
	{
		if (it->passageiro->getID() == id_passageiro)
		{
			delete it->passageiro;
			passageiros_inativos.erase(it);
			return;
		}
	}

	throw ClientNotFound(id_passageiro);
}

void Companhia::displayReservations() const
{
	if (avioes.empty())
		throw Airplanes_Empty();

	unsigned int id_aviao;
	cout << endl << "Airplane ID?" << endl;
	cin >> id_aviao;
	if(cin.fail())
		throw FailedInput("Failed to input airplane ID.");
	cin.ignore(1000, '\n');

	for (unsigned int i = 0; i < avioes.size(); i++)
	{
		if (avioes[i].getID() == id_aviao)
		{
			avioes[i].displayReservations();
			return;
		}
	}

	throw AirplaneNotFound(id_aviao);
}

void Companhia::makeReservation()
{
	if (avioes.empty())
		throw Airplanes_Empty();

	if (clientes.empty())
		throw Clientes_Empty();

	Passageiro * cliente = nullptr;

	unsigned int id_passageiro;
	cout << endl << "Passenger ID?" << endl;
	cin >> id_passageiro;
	if(cin.fail())
		throw FailedInput("Failed to input passenger ID.");
	cin.ignore(1000, '\n');

	bool found = false;

	for(vector<Passageiro *>::iterator it = clientes.begin(); it != clientes.end(); it++)
	{
		if ((*it)->getID() == id_passageiro)
		{
			cliente = *it;
			found = true;
			break;
		}
	}

	if(!found)
	{
		for(tabHPassageiro::iterator it = passageiros_inativos.begin(); it != passageiros_inativos.end(); it++)
		{
			if (it->passageiro->getID() == id_passageiro)
			{
				cliente = it->passageiro;
				found = true;
				clientes.push_back(cliente);
				passageiros_inativos.erase(it);
			}
		}
	}

	if (!found)
		throw ClientNotFound(id_passageiro);

	//Procura o passageiro nos clientes e reserva-o no voo

	unsigned int id_aviao;
	cout << endl << "Airplane ID?" << endl;
	cin >> id_aviao;
	if(cin.fail())
		throw FailedInput("Failed to input airplane ID.");
	cin.ignore(1000, '\n');

	for (unsigned int i = 0; i < avioes.size(); i++)
	{
		if (avioes[i].getID() == id_aviao)
		{
			avioes[i].makeReservation(cliente);
			return;
		}
	}

	throw AirplaneNotFound(id_aviao);
}

void Companhia::removeReservation()
{
	if (avioes.empty())
		throw Airplanes_Empty();

	unsigned int id_passageiro;
	cout << endl << "Passenger ID?" << endl;
	cin >> id_passageiro;
	if(cin.fail())
		throw FailedInput("Failed to input passenger ID.");
	cin.ignore(1000, '\n');

	unsigned int id_aviao;
	cout << endl << "Airplane ID?" << endl;
	cin >> id_aviao;
	if(cin.fail())
		throw FailedInput("Failed to input airplane ID.");
	cin.ignore(1000, '\n');

	for (unsigned int i = 0; i < avioes.size(); i++)
	{
		if (avioes[i].getID() == id_aviao)
		{
			avioes[i].removeReservation(id_passageiro);
			return;
		}
	}

	throw AirplaneNotFound(id_aviao);
}

void Companhia::makePromotion()
{
	if (avioes.empty())
		throw Airplanes_Empty();

	unsigned int id_aviao;
	cout << endl << "Airplane ID?" << endl;
	cin >> id_aviao;
	if(cin.fail())
		throw FailedInput("Failed to input airplane ID.");
	cin.ignore(1000, '\n');

	for (unsigned int i = 0; i < avioes.size(); i++)
	{
		if (avioes[i].getID() == id_aviao)
		{
			avioes[i].makePromotion();
			return;
		}
	}

	throw AirplaneNotFound(id_aviao);
}

void Companhia::sort()
{
	//Ordena avioes por lotacao nao cresecente

	for (unsigned int p = 1; p < avioes.size(); p++)
	{
		Aviao tmp = avioes[p];
		int j;
		for (j = p; j > 0 && !(tmp.getLotacao() < avioes[j-1].getLotacao()); j--)
			avioes[j] = avioes[j-1];
		avioes[j] = tmp;
	}

	//Ordena clientes por ordem alfabetica de nomes

	if (clientes.empty())
		return;
	for(unsigned int j=clientes.size()-1; j>0; j--)
	{
		bool troca = false;

		for(unsigned int i = 0; i<j; i++)
			if(clientes[i+1]->getNome() < clientes[i]->getNome()) {
				swap(clientes[i],clientes[i+1]);
				troca = true;
			}
		if (!troca) return;
	}

}

void Companhia::displayMaintenances() const
{
	if(avioes_bst.isEmpty())
		throw Airplanes_Empty();

	BSTItrIn<Aviao> it(avioes_bst);

	while(!it.isAtEnd())
	{
		it.retrieve().display();
		it.advance();
	}
}

void Companhia::makeMaintenance()
{
	if (avioes.empty())
		throw Airplanes_Empty();

	unsigned int id_aviao;
	cout << endl << "Airplane ID?" << endl;
	cin >> id_aviao;
	if(cin.fail())
		throw FailedInput("Failed to input airplane ID.");
	cin.ignore(1000, '\n');

	Aviao aviao_temp;
	bool found = false;

	for (unsigned int i = 0; i < avioes.size(); i++)
	{
		if (avioes[i].getID() == id_aviao)
		{
			Data hoje;
			hoje.setCurrentDate();

			Data temp = avioes[i].getProxima_Manutencao();

			if(temp.get_ano() != hoje.get_ano() || temp.get_mes() != hoje.get_mes() || temp.get_dia() != hoje.get_dia())
				throw NotToday(id_aviao);

			temp.addDay(avioes[i].getPeriodicidade_Manutencao());

			avioes[i].setProxima_Manutencao(temp);

			found = true;
			break;
		}
	}

	if(!found)
		throw AirplaneNotFound(id_aviao);

	avioes_bst.remove(aviao_temp);
	avioes_bst.insert(aviao_temp);
}

void Companhia::rescheduleMaintenance()
{
	if (avioes.empty())
		throw Airplanes_Empty();

	unsigned int id_aviao;
	cout << endl << "Airplane ID?" << endl;
	cin >> id_aviao;
	if(cin.fail())
		throw FailedInput("Failed to input airplane ID.");
	cin.ignore(1000, '\n');

	Aviao aviao_temp;
	bool found = false;

	for (unsigned int i = 0; i < avioes.size(); i++)
	{
		if (avioes[i].getID() == id_aviao)
		{
			unsigned int ano_temp, mes_temp, dia_temp;

			cout << endl << "New maintenance year?" << endl;
			cin >> ano_temp;
			if(cin.fail())
				throw FailedInput("Failed to input new maintenance year.");
			cin.ignore(1000, '\n');

			cout << endl << "New maintenance month?" << endl;
			cin >> mes_temp;
			if(cin.fail())
				throw FailedInput("Failed to input new maintenance month.");
			cin.ignore(1000, '\n');

			cout << endl << "New maintenance day?" << endl;
			cin >> dia_temp;
			if(cin.fail())
				throw FailedInput("Failed to input new maintenance day.");
			cin.ignore(1000, '\n');

			Data data_temp(ano_temp,mes_temp,dia_temp);

			avioes[i].setProxima_Manutencao(data_temp);

		}
	}

	if(!found)
		throw AirplaneNotFound(id_aviao);

	avioes_bst.remove(aviao_temp);
	avioes_bst.insert(aviao_temp);
}

void Companhia::displayMaintenancesbyDay() const
{
	if(avioes_bst.isEmpty())
		throw Airplanes_Empty();

	unsigned int ano_temp, mes_temp, dia_temp;

	cout << endl << "New maintenance year?" << endl;
	cin >> ano_temp;
	if(cin.fail())
		throw FailedInput("Failed to input maintenance year.");
	cin.ignore(1000, '\n');

	cout << endl << "New maintenance month?" << endl;
	cin >> mes_temp;
	if(cin.fail())
		throw FailedInput("Failed to input maintenance month.");
	cin.ignore(1000, '\n');

	cout << endl << "New maintenance day?" << endl;
	cin >> dia_temp;
	if(cin.fail())
		throw FailedInput("Failed to input maintenance day.");
	cin.ignore(1000, '\n');

	Data data_temp(ano_temp,mes_temp,dia_temp);

	BSTItrIn<Aviao> it(avioes_bst);

	while(!it.isAtEnd())
	{
		if (data_temp == it.retrieve().getProxima_Manutencao())
			it.retrieve().display();

		it.advance();
	}
}

void Companhia::displayTecnicians() const
{
	if(tecnicos.empty())
		throw Tecnicians_Empty();

	priority_queue<Tecnico> temp = tecnicos;

	while(!temp.empty())
	{
		temp.top().display();
		temp.pop();
	}
}

void Companhia::addTecnician()
{
	string nome_temp;
	unsigned int n;
	string temp_str;
	vector<string> temp_vect;

	cout << endl << "Tecnician name?" << endl;
	getline(cin,nome_temp);

	cout << endl << "How many specialities does the tecnician have?";
	cin >> n;
	if(cin.fail())
		throw FailedInput("Failed to input number of specialities.");
	cin.ignore(1000, '\n');

	for(unsigned int i = 0; i < n; i++)
	{
		cout << endl << "Speciality name?";
		cin >> temp_str;

		temp_vect.push_back(temp_str);
	}

	Tecnico temp(nome_temp,temp_vect);
	tecnicos.push(temp);
}

void Companhia::changeTecnician()
{
	if(tecnicos.empty())
		throw Tecnicians_Empty();

	unsigned int id_a_alterar;
	cout << endl << "Tecnician ID?" << endl;
	cin >> id_a_alterar;
	if(cin.fail())
		throw FailedInput("Failed to input tecnician ID.");
	cin.ignore(1000, '\n');

	Tecnico temp(0);
	vector<Tecnico> vect_temp;

	while(!tecnicos.empty())
	{
		if(tecnicos.top().getID() == id_a_alterar)
			temp = tecnicos.top();

		else vect_temp.push_back(tecnicos.top());

		tecnicos.pop();
	}

	for (unsigned int i = 0; i < vect_temp.size(); i++)
		tecnicos.push(vect_temp[i]);

	if(temp.getID() == 0)
		throw TecnicianNotFound(id_a_alterar);

	temp.change();
	tecnicos.push(temp);
}

void Companhia::removeTecnician()
{
	if(tecnicos.empty())
		throw Tecnicians_Empty();

	unsigned int id_a_remover;
	cout << endl << "Tecnician ID?" << endl;
	cin >> id_a_remover;
	if(cin.fail())
		throw FailedInput("Failed to input tecnician ID.");
	cin.ignore(1000, '\n');

	Tecnico temp(0);
	vector<Tecnico> vect_temp;

	while(!tecnicos.empty())
	{
		if(tecnicos.top().getID() == id_a_remover)
			temp = tecnicos.top();

		else vect_temp.push_back(tecnicos.top());

		tecnicos.pop();
	}

	for (unsigned int i = 0; i < vect_temp.size(); i++)
		tecnicos.push(vect_temp[i]);

	if(temp.getID() == 0)
		throw TecnicianNotFound(id_a_remover);
}

void Companhia::displayInactive()
{
	if (passageiros_inativos.empty())
		throw Clientes_Empty();

	for(tabHPassageiro::iterator it = passageiros_inativos.begin(); it != passageiros_inativos.end(); it++)
	{
			it->passageiro->display();
	}

}
