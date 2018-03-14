#include "Excecoes.h"
#include "Data.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

Data::Data(){};

Data::Data(unsigned int ano, unsigned int mes, unsigned int dia) : ano(ano), mes(mes), dia(dia)
{
	hora = 0;
	minuto = 0;

	if(ano > 9999)
		throw IncorrectValue("Invalid year!");

	if(mes > 12)
		throw IncorrectValue("Invalid month!");

	if(dia > 31)
		throw IncorrectValue("Invalid day!");

	if(dia == 31 && (mes == 2 || mes == 4 || mes == 6 || mes == 9 || mes == 11))
		throw IncorrectValue("Invalid day!");

	if(dia == 30 && mes == 2)
		throw IncorrectValue("Invalid day!");

	//Verifica se o ano nao é bissexto
	if((dia == 29) && (mes == 2) && !((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)))
		throw IncorrectValue("Invalid day!");

}

Data::Data(unsigned int ano, unsigned int mes, unsigned int dia, unsigned int hora, unsigned int minuto) : ano(ano), mes(mes), dia(dia), hora(hora), minuto(minuto)
{
	if(ano > 9999)
		throw IncorrectValue("Invalid year!");

	if(mes > 12)
		throw IncorrectValue("Invalid month!");

	if(mes > 12)
		throw IncorrectValue("Invalid month!");

	if(dia > 31)
		throw IncorrectValue("Invalid day!");

	if(dia == 31 && (mes == 2 || mes == 4 || mes == 6 || mes == 9 || mes == 11))
		throw IncorrectValue("Invalid day!");

	if(dia == 30 && mes == 2)
		throw IncorrectValue("Invalid day!");

	//Verifica se o ano nao é bissexto
	if((dia == 29) && (mes == 2) && !((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)))
		throw IncorrectValue("Invalid day!");

	if(hora > 23)
		throw IncorrectValue("Invalid hour!");

	if(minuto > 59)
		throw IncorrectValue("Invalid minute!");
}


unsigned int Data::get_ano() const
{
	return ano;
}
unsigned int Data::get_mes() const
{
	return mes;
}
unsigned int Data::get_dia() const
{
	return dia;
}
unsigned int Data::get_hora() const
{
	return hora;
}
unsigned int Data::get_minuto() const
{
	return minuto;
}

void Data::display() const
{
	if (dia < 10)
		cout << "0" << dia << "/";

	else
		cout << dia << "/";

	if (mes < 10)
		cout << "0" << mes << "/";

	else
		cout << mes << "/";

	if (ano < 10)
		cout << "000" << ano << " ";

	else if (ano < 100)
		cout << "00" << ano << " ";

	else if (ano < 1000)
		cout << "0" << ano << " ";

	else
		cout << ano << " ";

	if (hora < 10)
		cout << "0"<< hora << ":";

	else
		cout << hora << ":";

	if (minuto < 10)
		cout << "0" << minuto;

	else
		cout << minuto;
}

void Data::displayDia() const
{
	if (dia < 10)
		cout << "0" << dia << "/";

	else
		cout << dia << "/";

	if (mes < 10)
		cout << "0" << mes << "/";

	else
		cout << mes << "/";

	if (ano < 10)
		cout << "000" << ano;

	else if (ano < 100)
		cout << "00" << ano;

	else if (ano < 1000)
		cout << "0" << ano;

	else
		cout << ano << " ";
}

bool operator<(const Data& d1, const Data& d2)
{
	if(d1.ano < d2.ano)
		return true;

	if(d1.ano > d2.ano)
		return false;

	if(d1.mes < d2.mes)
		return true;

	if(d1.mes > d2.mes)
		return false;

	if(d1.dia < d2.dia)
		return true;

	if(d1.dia > d2.dia)
		return false;

	if(d1.hora < d2.hora)
		return true;

	if(d1.hora > d2.hora)
		return false;

	if(d1.minuto < d2.minuto)
		return true;

	return false;
}

bool operator==(Data d1, Data d2)
{
	if(d1.ano == d2.ano && d1.mes == d2.mes && d1.dia == d2.dia)
		return true;

	return false;
}

void Data::setCurrentDate()
{
	time_t t = time(0);
	struct tm * now = localtime(&t);

	ano = (now->tm_year + 1900);
	mes = (now->tm_mon + 1);
	dia = now->tm_mday;
	hora = now->tm_hour;
	minuto = now->tm_min;
}

void Data::addDay(unsigned int value)
{
	time_t t = time(0);
	struct tm * now = localtime(&t);

	now->tm_year = ano - 1900;
	now->tm_mon = mes - 1;
	now->tm_mday = dia;
	now->tm_hour = hora;
	now->tm_min = minuto;

	now->tm_mday += value;

	t = mktime(now);
	now = localtime(&t);

	ano = (now->tm_year + 1900);
	mes = (now->tm_mon + 1);
	dia = now->tm_mday;
	hora = now->tm_hour;
	minuto = now->tm_min;
}
