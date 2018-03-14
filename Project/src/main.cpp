#include "Companhia.h"
#include "Excecoes.h"
#include <iostream>

using namespace std;

void airplane_menu(Companhia &companhia)
{
	int operacao = -1;

	cout << endl << "What do you want to do?" << endl << "1. View Airplanes" << endl << "2. Add Airplane" << endl << "3. Change Airplane" << endl << "4. Remove Airplane" << endl << "Any other option will bring you back to the main menu." << endl;
	cin >> operacao;
	cin.clear();
	cin.ignore(1000, '\n');
	switch (operacao)
	{
	case 1: companhia.displayAvioes();
	break;
	case 2: companhia.addAviao();
	break;
	case 3: companhia.changeAviao();
	break;
	case 4: companhia.removeAviao();
	break;
	default: break;
	}
}

void flight_menu(Companhia &companhia)
{
	int operacao = -1;

	cout << endl << "What do you want to do?" << endl << "1. View Flights" << endl << "2. Add Flight" << endl << "3. Change Flight" << endl << "4. Remove Flight" << endl << "Any other option will bring you back to the main menu." << endl;
	cin >> operacao;
	cin.clear();
	cin.ignore(1000, '\n');
	switch (operacao)
	{
	case 1: companhia.displayVoos();
	break;
	case 2: companhia.addVoo();
	break;
	case 3: companhia.changeVoo();
	break;
	case 4: companhia.removeVoo();
	break;
	default: break;
	}
}

void passenger_menu(Companhia &companhia)
{
	int operacao = -1;

	cout << endl << "What do you want to do?" << endl << "1. View Passengers" << endl << "2. Add Passenger" << endl << "3. Change Passenger" << endl << "4. Remove Passenger" << endl << "Any other option will bring you back to the main menu." << endl;
	cin >> operacao;
	cin.clear();
	cin.ignore(1000, '\n');
	switch (operacao)
	{
	case 1: companhia.displayPassageiros();
	break;
	case 2: companhia.addPassageiro();
	break;
	case 3: companhia.changePassageiro();
	break;
	case 4: companhia.removePassageiro();
	break;
	default: break;
	}
}

void reservation_menu(Companhia &companhia)
{
	int operacao = -1;

	cout << endl << "What do you want to do?" << endl << "1. View Reservations" << endl << "2. Make Reservation" << endl << "3. Remove Reservation" << endl << "Any other option will bring you back to the main menu." << endl;
	cin >> operacao;
	cin.clear();
	cin.ignore(1000, '\n');
	switch (operacao)
	{
	case 1: companhia.displayReservations();
	break;
	case 2: companhia.makeReservation();
	break;
	case 3: companhia.removeReservation();
	break;
	default: break;
	}
}

void maintenance_menu(Companhia &companhia)
{
	int operacao = -1;

	cout << endl << "What do you want to do?" << endl << "1. View Maintenances" << endl << "2. Make Maintenance" << endl << "3. Reschedule Maintenance" << endl << "4. View Maintenances by Day" << endl << "Any other option will bring you back to the main menu." << endl;
	cin >> operacao;
	cin.clear();
	cin.ignore(1000, '\n');
	switch (operacao)
	{
	case 1: companhia.displayMaintenances();
	break;
	case 2: companhia.makeMaintenance();
	break;
	case 3: companhia.rescheduleMaintenance();
	break;
	case 4: companhia.displayMaintenancesbyDay();
	break;
	default: break;
	}
}

void tecnician_menu(Companhia &companhia)
{
	int operacao = -1;

	cout << endl << "What do you want to do?" << endl << "1. View Tecnicians" << endl << "2. Add Tecnician" << endl << "3. Change Tecnician" << endl << "4. Remove Tecnician" << endl << "Any other option will bring you back to the main menu." << endl;
	cin >> operacao;
	cin.clear();
	cin.ignore(1000, '\n');
	switch (operacao)
	{
	case 1: companhia.displayTecnicians();
	break;
	case 2: companhia.addTecnician();
	break;
	case 3: companhia.changeTecnician();
	break;
	case 4: companhia.removeTecnician();
	break;
	default: break;
	}
}

int main_menu(Companhia &companhia)
{
	int operacao = -1;

	cout << endl << "What do you want to do?" << endl << "0. Quit" << endl << "1. View / Change Airplanes" << endl << "2. View / Change Flights" << endl << "3. View / Change Passengers" << endl << "4. View / Change Reservation" << endl << "5. Make Promotion" << endl << "6. Sort" << endl << "7. View / Change / Make Maintenance" << endl << "8. View / Change Tecnicians" << endl << "9. View Inactive Passengers" << endl;
	cin >> operacao;
	if(cin.fail())
		throw FailedInput("Failed to input option.");
	cin.ignore(1000, '\n');

	switch (operacao)
	{
	case 0: break;
	case 1:	airplane_menu(companhia);
	break;
	case 2: flight_menu(companhia);
	break;
	case 3: passenger_menu(companhia);
	break;
	case 4: reservation_menu(companhia);
	break;
	case 5: companhia.makePromotion();
	break;
	case 6: companhia.sort();
	break;
	case 7: maintenance_menu(companhia);
	break;
	case 8: tecnician_menu(companhia);
	break;
	case 9: companhia.displayInactive();
	break;
	default: throw WrongOption(operacao);
	}

	return operacao;
}

int main()
{
	string ficheiro_avioes = "avioes.txt";
	string ficheiro_voo = "voo.txt";
	string ficheiro_clientes = "clientes.txt";
	string ficheiro_tecnicos = "tecnicos.txt";

	Companhia companhia("AEDA",ficheiro_avioes,ficheiro_voo,ficheiro_clientes, ficheiro_tecnicos);

	int operacao = -1;

	do
	{
		try
		{
			operacao = main_menu(companhia);
		}
		catch(FailedInput &e)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl << e.info << " Returning to Main Menu." << endl;
		}
		catch(IncorrectValue &e)
		{
			cout << endl << e.msg << " Returning to Main Menu." << endl;
		}
		catch(WrongOption &e)
		{
			cout << endl << e.option << "is not a valid option. Try again!" << endl;
		}
		catch(Companhia::Airplanes_Empty &e)
		{
			cout << endl << "There are no airplanes. Returning to Main Menu." << endl;
		}
		catch(Companhia::AirplaneNotFound &e)
		{
			cout << endl << "There is no airplane with ID =" << e.id << ". Returning to Main Menu." << endl;
		}
		catch(Companhia::Clientes_Empty &e)
		{
			cout << endl << "There are no passengers. Returning to Main Menu." << endl;
		}
		catch(Companhia::ClientNotFound &e)
		{
			cout << endl << "There is no client with ID = " << e.id << ". Returning to Main Menu." << endl;
		}
		catch(Aviao::FlightsEmpty &e)
		{
			cout << endl << "There are no flights in the desired airplane. Returning to Main Menu." << endl;
		}
		catch(Aviao::FlightFull &e)
		{
			cout << endl << "The desired flight is full. Returning to Main Menu." << endl;
		}
		catch(Aviao::FlightNotFound &e)
		{
			cout << endl << "There is no flight with ID = " << e.id << " in the desired airplane. Returning to Main Menu." << endl;
		}
		catch(Voo::PassengersEmpty &e)
		{
			cout << endl << "There are no reservations in the desired flight. Returning to Main Menu." << endl;
		}
		catch(Voo::PassageiroNotFound &e)
		{
			cout << endl << "There is no passenger with ID = " << e.id << " in the desired flight. Returning to Main Menu." << endl;
		}
		catch(Voo::CantDoPromotion &e)
		{
			cout << endl << "Can't do promotion. Returning to Main Menu." << endl;
		}
		catch(Companhia::NotToday &e)
		{
			cout << endl << "Can't do maintenance on airplane with ID = " << e.id << " beacuse that airplane maintenance is not scheduled for today.";
		}
		catch(Companhia::Tecnicians_Empty &e)
		{
			cout << endl << "There are no tecnicians. Returning to Main Menu." << endl;
		}
		catch(Companhia::TecnicianNotFound &e)
		{
			cout << endl << "There is no tecnician with ID = " << e.id << ". Returning to Main Menu." << endl;
		}
	} while (operacao != 0);

	companhia.escreve_Ficheiros(ficheiro_avioes, ficheiro_voo, ficheiro_clientes, ficheiro_tecnicos);

	return 0;
}
