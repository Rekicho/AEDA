#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Companhia.h"
#include <string>


using namespace std;



Companhia::Companhia(string nome, string nome_avioes, string nome_voo, string nome_clientes,string nome_tecnicos) : avioes_bst(Aviao(0))
{
	ifstream my_avioes(nome_avioes);
	ifstream my_voos(nome_voo);
	ifstream my_clientes(nome_clientes);
	ifstream my_tecnicos(nome_tecnicos);

	string aviao;
	string voo;
	string cliente;
	string tecnico;
	vector<Voo *> vooss;

	//CLIENTES//////
	if (my_clientes.fail())
	{
		cerr << "Ficheiro inexistente \n";
		exit(1);
	}

	while (!my_clientes.eof())
	{
		Trata_fich_clientes(my_clientes);
	}
	my_clientes.close();



	//VOOS//////
	if (my_voos.fail())
	{
		cerr << "Ficheiro inexistente \n";
		exit(1);
	}

	while (!my_voos.eof())
	{
		getline(my_voos, voo);
		Trata_fich_voos(voo,vooss);
	}
	my_voos.close();
	//VOOS//////


	//AVIOES//////
	if (my_avioes.fail())
	{
		cerr << "Ficheiro inexistente \n";
		exit(1);
	}

	while (!my_avioes.eof())
	{
		getline(my_avioes, aviao);
		Aviao plane (aviao, vooss);

		avioes.push_back(plane);
		avioes_bst.insert(plane);
	}
	my_avioes.close();


	//TECNICOS//////

	if (my_tecnicos.fail())
	{
		cerr << "Ficheiro inexistente \n";
		exit(1);
	}

	while (!my_tecnicos.eof())
	{
		getline(my_tecnicos,tecnico);
		Tecnico tec(tecnico,avioes);
		tecnicos.push(tec);

	}
	my_tecnicos.close();
}

void Companhia::escreve_Ficheiros(string nome_avioes, string nome_voo, string nome_clientes,string nome_tecnicos)
{
	//CLIENTES
	unsigned int i;
	ofstream myfile_clientes;
	myfile_clientes.open(nome_clientes);
	for (i = 0; i < clientes.size(); i++)
	{
		if (i == 0)
		{
			myfile_clientes << 'S' << ';';
			clientes.at(i)->escreve_fich_passageiro(myfile_clientes);
		}
		else
		{
			myfile_clientes << endl;
			myfile_clientes << 'S' << ';';
			clientes.at(i)->escreve_fich_passageiro(myfile_clientes);


		}
	}

	tabHPassageiro::iterator it = passageiros_inativos.begin();

	while (it != passageiros_inativos.end())
	{
		if (it != passageiros_inativos.end())
		{
			myfile_clientes << endl;
		}
		myfile_clientes << 'I' << ';';
		it->passageiro->escreve_fich_passageiro(myfile_clientes);
		it++;

	}


	myfile_clientes.close();
	//o ultimo elemento a escrever no ficheiro tem de ser diferente uma
	//vez que o ultimo parametro deste nao deve ter endl


	//VOOS
	unsigned int k, j;
	ofstream myfile_voos;
	vector<Aviao> avioes_escr;
	myfile_voos.open(nome_voo);

	for (k = 0; k < avioes.size(); k++)
	{
		if (avioes.at(k).getVoos().size() != 0)
		{
			avioes_escr.push_back(avioes.at(k));
		}
	}

	for (k = 0; k < avioes_escr.size() - 1; k++)
	{

		if (avioes_escr.at(k).getVoos().size() == 1) // se apenas tiver 1 voo
		{
			avioes_escr.at(k).getVoos().at(0)->escreve_fich_voos(myfile_voos);
			myfile_voos << endl;
		}
		else
		{
			for (j = 0; j < avioes_escr.at(k).getVoos().size() - 1; j++) //verificar esta parte, podera dar erro com mais que um voo
			{
				avioes_escr.at(k).getVoos().at(j)->escreve_fich_voos(myfile_voos);
				myfile_voos << endl;
			}
			avioes_escr.at(k).getVoos().at(j)->escreve_fich_voos(myfile_voos);
			myfile_voos << endl;

		}
	}
	//myfile_voos << endl;
	if (avioes_escr.at(k).getVoos().size() == 0)
	{

	}
	else if (avioes_escr.at(k).getVoos().size() == 1) // se apenas tiver 1 voo
	{
		avioes_escr.at(k).getVoos().at(0)->escreve_fich_voos(myfile_voos);
	}
	else
	{
		for (j = 0; j < avioes_escr.at(k).getVoos().size() - 1; j++)
		{
			avioes_escr.at(k).getVoos().at(j)->escreve_fich_voos(myfile_voos);
			myfile_voos << endl;
		}
		avioes_escr.at(k).getVoos().at(j)->escreve_fich_voos(myfile_voos);

	}

	myfile_voos.close();

	//AVIOES

	unsigned int l;
	ofstream myfile_avioes;
	myfile_avioes.open(nome_avioes);
	for (l = 0; l < avioes.size() - 1; l++)
	{
		myfile_avioes << avioes.at(l).getID() << ';';
		myfile_avioes << avioes.at(l).getPeriodicidade_Manutencao() << ";";
		myfile_avioes << avioes.at(l).getProxima_Manutencao().get_dia() << "/";
		myfile_avioes << avioes.at(l).getProxima_Manutencao().get_mes() << "/";
		myfile_avioes << avioes.at(l).getProxima_Manutencao().get_ano() << ";";
		myfile_avioes << avioes.at(l).getNome() << ';';
		myfile_avioes << avioes.at(l).getLotacao() << ';';

		if (avioes.at(l).getVoos().size() == 0)
		{
			myfile_avioes << endl;
		}
		else
		{
			for (j = 0; j < avioes.at(l).getVoos().size() - 1; j++)
			{
				myfile_avioes << avioes.at(l).getVoos().at(j)->getID() << '/';
			}
			myfile_avioes << avioes.at(l).getVoos().at(j)->getID();
			myfile_avioes << endl;
		}
	}

	myfile_avioes << avioes.at(l).getID() << ';';
	myfile_avioes << avioes.at(l).getPeriodicidade_Manutencao() << ";";
	myfile_avioes << avioes.at(l).getProxima_Manutencao().get_dia() << "/";
	myfile_avioes << avioes.at(l).getProxima_Manutencao().get_mes() << "/";
	myfile_avioes << avioes.at(l).getProxima_Manutencao().get_ano() << ";";
	myfile_avioes << avioes.at(l).getNome() << ';';
	myfile_avioes << avioes.at(l).getLotacao() << ';';

	if (avioes.at(l).getVoos().size() == 0)
	{

	}
	else
	{
		for (j = 0; j < avioes.at(l).getVoos().size() - 1; j++)
		{
			myfile_avioes << avioes.at(l).getVoos().at(j)->getID() << '/';
		}
		myfile_avioes << avioes.at(l).getVoos().at(j)->getID();
		myfile_avioes.close();
	}


	//TECNICOS

	unsigned int m;
	ofstream myfile_tecnicos;
	myfile_tecnicos.open(nome_tecnicos);

	while (tecnicos.size() != 1)
	{
		Tecnico t = tecnicos.top();
		myfile_tecnicos << t.getID() << ";";
		myfile_tecnicos << t.getnome() << ";";

		//especialidades
		for (m = 0; m < t.getespecialidades().size() - 1; m++)
		{
			myfile_tecnicos << t.getespecialidades().at(m) << "/";
		}
		myfile_tecnicos << t.getespecialidades().at(m) << ";";

		//manutencoes
		for (m = 0; m < t.getmanutencoes().size() - 1; m++)
		{
			myfile_tecnicos << t.getmanutencoes().at(m).getID() << "/";
		}
		myfile_tecnicos << t.getmanutencoes().at(m).getID() << endl;

		tecnicos.pop();

	}

	//ultimo elemento da priority queue
	Tecnico t = tecnicos.top();
	myfile_tecnicos << t.getID() << ";";
	myfile_tecnicos << t.getnome() << ";";

	//especialidades
	if (t.getespecialidades().size() == 0)
	{
		myfile_tecnicos << ";";
	}
	else
	{


		for (m = 0; m < t.getespecialidades().size() - 1; m++)
		{
			myfile_tecnicos << t.getespecialidades().at(m) << "/";
		}
		myfile_tecnicos << t.getespecialidades().at(m) << ";";
	}
	//manutencoes
	if (t.getmanutencoes().size() == 0)
	{

	}
	else
	{
		for (m = 0; m < t.getmanutencoes().size() - 1; m++)
		{
			myfile_tecnicos << t.getmanutencoes().at(m).getID() << "/";
		}
		myfile_tecnicos << t.getmanutencoes().at(m).getID();
	}

	tecnicos.pop();


}

Aviao::Aviao(string text_line, vector<Voo* >  & vooss)
{
	vector<string> ids_voo; //usei string em vez de int pra poder usar o metodo caracter a caracter
	string id_1_voo;
	string ano, dia, mes;
	istringstream linha_aviao (text_line);
	char p_virgula;
	unsigned int temp;


	linha_aviao >> temp >> p_virgula;


	id = temp;
	linha_aviao >> temp >> p_virgula;
	periocidade_manutencao = temp;

	char carater;
	carater = linha_aviao.get();
	//DATA_PARTIDA
	while (carater != '/')
	{
		dia = dia + carater;
		carater = linha_aviao.get();
	}

	carater = linha_aviao.get();
	while (carater != '/')
	{
		mes = mes + carater;
		carater = linha_aviao.get();
	}

	carater = linha_aviao.get();

	while (carater != ';')
	{
		ano = ano + carater;
		carater = linha_aviao.get();
	}
	proxima_manutencao = Data(stoul(ano), stoul(mes), stoul(dia));

	carater = linha_aviao.get();

	while (carater != ';')
	{
		nome = nome + carater;
		carater = linha_aviao.get();

	}


	linha_aviao >> temp >> p_virgula;


	lotacao = temp;
	carater = linha_aviao.get();
	while (carater != -1)
	{

		if (carater != '/')
		{
			id_1_voo = id_1_voo + carater;


		}
		else
		{
			ids_voo.push_back(id_1_voo);
			id_1_voo.clear();

		}
		if (linha_aviao.peek() == -1)
		{
			ids_voo.push_back(id_1_voo);
		}
		carater = linha_aviao.get();
	}
	unsigned int i, k;

	for (i = 0; i < ids_voo.size(); i++)
	{
		for (k = 0; k < vooss.size(); k++)
		{
			if (stoul(ids_voo.at(i)) == vooss.at(k)->getID())
			{
				voos.push_back(vooss.at(k));
			}
		}

	}





}  


VooComercial::VooComercial (string text_line,vector<Passageiro*>  &clientess)
{
	string ano, dia, mes, horas, minutos;
	string anof, diaf, mesf, horasf, minutosf;
	istringstream linha_voo(text_line);
	char p_virgula, carater;
	linha_voo.ignore();
	linha_voo.ignore();
	linha_voo >> id >> p_virgula;
	vector<unsigned int> ids_clientes;
	string cliente_id;


	//partida
	carater = linha_voo.get();
	while (carater != ';')
	{
		partida = partida + carater;
		carater = linha_voo.get();
	}
	//destino
	carater = linha_voo.get();
	while (carater != ';')
	{
		destino = destino + carater;
		carater = linha_voo.get();
	}
	carater = linha_voo.get();

	//DATA_PARTIDA
	while (carater != '/')
	{
		dia = dia + carater;
		carater = linha_voo.get();
	}

	carater = linha_voo.get();
	while (carater != '/')
	{
		mes = mes + carater;
		carater = linha_voo.get();
	}

	carater = linha_voo.get();

	while (carater != ' ')
	{
		ano = ano + carater;
		carater = linha_voo.get();
	}

	carater = linha_voo.get();

	while (carater != ':')
	{
		horas = horas + carater;
		carater = linha_voo.get();
	}

	carater = linha_voo.get();

	while (carater != ';')
	{
		minutos = minutos + carater;
		carater = linha_voo.get();
	}
	//DATA_CHEGADA
	carater = linha_voo.get();

	while (carater != '/')
	{
		diaf = diaf + carater;
		carater = linha_voo.get();
	}

	carater = linha_voo.get();
	while (carater != '/')
	{
		mesf = mesf + carater;
		carater = linha_voo.get();
	}

	carater = linha_voo.get();

	while (carater != ' ')
	{
		anof = anof + carater;
		carater = linha_voo.get();
	}

	carater = linha_voo.get();

	while (carater != ':')
	{
		horasf = horasf + carater;
		carater = linha_voo.get();
	}

	carater = linha_voo.get();

	while (carater != ';')
	{
		minutosf = minutosf + carater;
		carater = linha_voo.get();
	}

	linha_voo >> preco;
	linha_voo.ignore();
	carater = linha_voo.get();


	while (carater != -1)
	{

		if (carater != '/')
		{
			cliente_id = cliente_id + carater;


		}
		else
		{
			ids_clientes.push_back(stoul(cliente_id));
			cliente_id.clear();

		}
		if (linha_voo.peek() == -1)
		{
			ids_clientes.push_back(stoul(cliente_id));
		}
		carater = linha_voo.get();
	}

	unsigned int i, k;

	for (i = 0; i < ids_clientes.size(); i++)
	{
		for (k = 0; k < clientess.size(); k++)
		{
			if (clientess.at(k)->getID() == ids_clientes.at(i))
			{
				passageiros.push_back(clientess.at(k));
			}
		}

	}

	data_partida = Data(stoul(ano), stoul(mes),stoul(dia), stoul(horas),stoul(minutos));
	data_chegada = Data(stoul(anof), stoul(mesf), stoul(diaf), stoul(horasf), stoul(minutosf));

}

VooAlugado::VooAlugado(string text_line, vector<Passageiro*>  & clientess)
{
	string id_cliente;
	string ano, dia, mes, horas, minutos;
	string anof, diaf, mesf, horasf, minutosf;
	istringstream linha_voo(text_line);
	char p_virgula, carater;
	linha_voo.ignore();
	linha_voo.ignore();


	linha_voo >> id >> p_virgula;


	//partida
	carater = linha_voo.get();
	while (carater != ';')
	{
		partida = partida + carater;
		carater = linha_voo.get();
	}
	//destino
	carater = linha_voo.get();
	while (carater != ';')
	{
		destino = destino + carater;
		carater = linha_voo.get();
	}
	carater = linha_voo.get();

	//DATA_PARTIDA
	while (carater != '/')
	{
		dia = dia + carater;
		carater = linha_voo.get();
	}

	carater = linha_voo.get();
	while (carater != '/')
	{
		mes = mes + carater;
		carater = linha_voo.get();
	}

	carater = linha_voo.get();

	while (carater != ' ')
	{
		ano = ano + carater;
		carater = linha_voo.get();
	}

	carater = linha_voo.get();

	while (carater != ':')
	{
		horas = horas + carater;
		carater = linha_voo.get();
	}

	carater = linha_voo.get();

	while (carater != ';')
	{
		minutos = minutos + carater;
		carater = linha_voo.get();
	}
	//DATA_CHEGADA
	carater = linha_voo.get();

	while (carater != '/')
	{
		diaf = diaf + carater;
		carater = linha_voo.get();
	}

	carater = linha_voo.get();
	while (carater != '/')
	{
		mesf = mesf + carater;
		carater = linha_voo.get();
	}

	carater = linha_voo.get();

	while (carater != ' ')
	{
		anof = anof + carater;
		carater = linha_voo.get();
	}

	carater = linha_voo.get();

	while (carater != ':')
	{
		horasf = horasf + carater;
		carater = linha_voo.get();
	}

	carater = linha_voo.get();

	while (carater != ';')
	{
		minutosf = minutosf + carater;
		carater = linha_voo.get();
	}

	linha_voo >> preco >> p_virgula;

	carater = linha_voo.get();

	bool tem_passageiro = false;

	while(carater != -1)
	{
		tem_passageiro = true;
		id_cliente = id_cliente + carater;
		carater = linha_voo.get();
	}

	if(tem_passageiro)
	{
		unsigned int id_temp = stoul(id_cliente);
		unsigned int k;

		for (k = 0; k < clientess.size(); k++)
		{
			if (clientess.at(k)->getID() == id_temp)
			{
				Passageiro * pass_temp = clientess.at(k);
				passageiro = pass_temp;
			}
		}
	}

	else passageiro = nullptr;


	data_partida = Data(stoul(ano), stoul(mes), stoul(dia), stoul(horas), stoul(minutos));
	data_chegada = Data(stoul(anof), stoul(mesf), stoul(diaf), stoul(horasf), stoul(minutosf));




}

void Companhia::Trata_fich_voos(string text_line, vector<Voo *> & vooss)
{ 

	char carater;

	carater = text_line.at(0); // fazer ignore 2 vezes  no construtor para eliminar o tipo de voo e o ponto e virgula
	if (carater == 'A')
	{

		Voo * flight = new VooAlugado(text_line,clientes);
		vooss.push_back(flight);
	}
	else
	{
		//chama construtor de comercial
		Voo * flight = new VooComercial(text_line,clientes);
		vooss.push_back(flight);
	}



}


void Companhia::Trata_fich_clientes(ifstream &my_clientes)
{
	char carater, carater_1;
	string cliente;


	getline(my_clientes, cliente);
	carater_1 = cliente.at(0);
	carater = cliente.at(2); // fazer ignore 4 vezes  no construtor para eliminar o char de atividade,o tipo de cliente e 2 pontos e virgula
	if (carater == 'C')
	{

		Passageiro * pass = new PassageiroCartao(cliente);
		PassageiroPtr temp_pass;
		temp_pass.passageiro = pass;
		if (carater_1 == 'S')
		{
			clientes.push_back(pass);
		}
		else
		{
			passageiros_inativos.insert(temp_pass);
		}

	}
	else
	{

		Passageiro * pass = new PassageiroNormal(cliente);
		PassageiroPtr temp_pass;
		temp_pass.passageiro = pass;
		if (carater_1 == 'S')
		{
			clientes.push_back(pass);
		}
		else
		{
			passageiros_inativos.insert(temp_pass);
		}
	}


}


PassageiroCartao::PassageiroCartao(string text_line)
{



	string nome, profissao, saldo;
	unsigned int id_cartao;
	string ano, dia, mes, horas, minutos;
	string v_medios;
	istringstream linha_cliente(text_line);
	char p_virgula, carater;
	linha_cliente.ignore();
	linha_cliente.ignore();
	linha_cliente.ignore();
	linha_cliente.ignore();
	linha_cliente >> id >> p_virgula;
	if (id > ultimo_id)
	{
		ultimo_id = id;
	}
	linha_cliente >> id_cartao >> p_virgula;
	carater = linha_cliente.get();
	//nome
	while (carater != ';')
	{
		nome = nome + carater;
		carater = linha_cliente.get();
	}
	//profissao
	carater = linha_cliente.get();
	while (carater != ';')
	{
		profissao = profissao + carater;
		carater = linha_cliente.get();
	}
	carater = linha_cliente.get();

	//DATA_NASCIMENTO
	while (carater != '/')
	{
		dia = dia + carater;
		carater = linha_cliente.get();
	}

	carater = linha_cliente.get();
	while (carater != '/')
	{
		mes = mes + carater;
		carater = linha_cliente.get();
	}

	carater = linha_cliente.get();

	while (carater != ';')
	{
		ano = ano + carater;
		carater = linha_cliente.get();
	}
	carater = linha_cliente.get();
	// saldo 
	while (carater != ';')
	{
		saldo = saldo + carater;
		carater = linha_cliente.get();
	}
	carater = linha_cliente.get();
	//numero medio de voos
	while (carater != -1)
	{
		v_medios = v_medios + carater;
		carater = linha_cliente.get();
	}
	Data dn(stoul(ano), stoul(mes), stoul(dia));

	Cartao cartao_temp (id_cartao,stoul(saldo), nome, profissao, dn, stof(v_medios));
	cartao = cartao_temp;


}


PassageiroNormal::PassageiroNormal(string text_line)
{

	istringstream linha_cliente(text_line);
	char p_virgula, carater;
	linha_cliente.ignore();
	linha_cliente.ignore();
	linha_cliente.ignore();
	linha_cliente.ignore();

	//id
	linha_cliente >> id >> p_virgula;
	if (id > ultimo_id)
	{
		ultimo_id = id;
	}

	//saldo
	linha_cliente >> saldo >> p_virgula;
	//nome
	carater = linha_cliente.get();
	while (carater != -1)
	{
		nome = nome + carater;
		carater = linha_cliente.get();
	}

}

Tecnico::Tecnico(string text_line, vector<Aviao >  & avioes)
{
	istringstream linha_tec(text_line);
	vector<string> ids_avioes; //usei string em vez de int pra poder usar o metodo caracter a caracter
	string id_1_aviao;
	string especialidade_1;

	char p_virgula;
	unsigned int temp;


	linha_tec >> temp >> p_virgula;


	id = temp;

	char carater;
	carater = linha_tec.get();
	while (carater != ';')
	{
		nome = nome + carater;
		carater = linha_tec.get();

	}


	carater = linha_tec.get();

	while (carater != ';')
	{

		if (carater != '/')
		{
			especialidade_1 = especialidade_1 + carater;


		}
		else
		{
			especialidade.push_back(especialidade_1);
			especialidade_1.clear();

		}
		if (linha_tec.peek() == ';')
		{
			especialidade.push_back(especialidade_1);
		}
		carater = linha_tec.get();

	}

	carater = linha_tec.get();
	while (carater != -1)
	{

		if (carater != '/')
		{
			id_1_aviao = id_1_aviao + carater;


		}
		else
		{
			ids_avioes.push_back(id_1_aviao);
			id_1_aviao.clear();

		}
		if (linha_tec.peek() == -1)
		{
			ids_avioes.push_back(id_1_aviao);
		}
		carater = linha_tec.get();

	}

	unsigned int i, k;

	for (i = 0; i < ids_avioes.size(); i++)
	{
		for (k = 0; k < avioes.size(); k++)
		{
			if (stoul(ids_avioes.at(i)) == avioes.at(k).getID())
			{
				manutencoes.push_back(avioes.at(k));
			}
		}

	}
}
