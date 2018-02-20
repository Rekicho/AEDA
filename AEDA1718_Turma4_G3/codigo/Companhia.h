#ifndef COMPANHIA_H_
#define COMPANHIA_H_

#include "Aviao.h"
#include "Passageiro.h"
#include "Tecnico.h"
#include "BST.h"
#include <tr1/unordered_set>

struct hPassageiroPtr {
	int operator()(const PassageiroPtr & p1) const
	{
		int hashVal = 0;
		std::string key = to_string(p1.passageiro->getID());

		for(unsigned int i = 0; i < key.length() ; i++ )
			hashVal = 101*hashVal + key[i];

		return hashVal;
	}
	bool operator()(const PassageiroPtr & p1, const PassageiroPtr & p2) const
	{
		return p1.passageiro->getID() == p2.passageiro->getID();
	}
};

typedef tr1::unordered_set<PassageiroPtr, hPassageiroPtr, hPassageiroPtr> tabHPassageiro;

/**
 * @brief Class Companhia - creats the base of the project, main class
 */
class Companhia
{
	std::string nome; ///< nome of the Company
	std::vector<Aviao> avioes; ///< vector avioes of type Aviao of the Company
	std::vector<Passageiro *> clientes; ///< vector clients of type Passageiro*
	BST<Aviao> avioes_bst; ///< Airplanes binary search tree
	priority_queue<Tecnico> tecnicos; ///< Tecnicians priority queue
	tabHPassageiro passageiros_inativos; ///< Inactive passengers hash table
public:
	/**
	 * @brief Constructor of Class Companhia
	 *
	 * @param nome Name of the Company
	 * @param ficheiro_avioes Name of the file of planes
	 * @param ficheiro_voo Name of the file of the flights
	 * @param ficheiro_clientes Name of the file of the clients
	 * @param ficheiro_tecnicos Name of the file of the tecnicians
	 */
	Companhia (std::string nome, std::string ficheiro_avioes, std::string ficheiro_voo, std::string ficheiro_clientes, std::string ficheiro_tecnicos);

	/**
	 * @brief Default constructor of Class Companhia
	 *
	 * @param nome Name of the Company
	 */
	Companhia (std::string nome): avioes_bst(Aviao(0))
	{this->nome = nome;}

	/**
	 * @brief Destructor of the Class Companhia
	 *
	 * Frees memory allocated by new to store passenger pointers
	 */
	~Companhia();

	/**
	 * @brief Reads clients data from file of clients
	 *
	 * Opens the file and reads data to be put in the vector of Passageiro* clientes
	 *
	 * @param my_clients ifstream associated with file
	 */
	void Trata_fich_clientes(std::ifstream &my_clientes);

	/**
	 * @brief Reads flights data from file of flights
	 *
	 * Opens the file and reads data to be put in the vector of Voo* vooss
	 *
	 * @param text_line Line of the file
	 * @param vooss Vector of Voo * where is added the Voo
	 */
	void Trata_fich_voos(std::string text_line, std::vector<Voo *> & vooss);

	/**
	 * @brief Write in the files given the name of them
	 *
	 * @param ficheiro_avioes File of planes to be filled with the information
	 * @param ficheiro_voo File of flights to be filled with the information
	 * @param ficheiro_clientes File of clients to be filled with the information
	 * @param fichiero_tecnicos File of tecnicians to be filled with the information
	 */
	void escreve_Ficheiros(std::string ficheiro_avioes, std::string ficheiro_voo, std::string ficheiro_clientes, std::string ficheiro_tecnicos);

	/**
	 * @brief Displays the information of all Airplanes
	 */
	void displayAvioes() const;

	/**
	 * @brief Adds an Airplane on the Company with information asked to the user
	 */
	void addAviao();

	/**
	 * @brief Changes the Airplane with the information asked to the user
	 */
	void changeAviao();

	/**
	 * @brief Removes a Airplane thats the user wants to remove from the Company
	 */
	void removeAviao();

	/**
	 * @brief Displays the information of all Flights
	 */
	void displayVoos() const;

	/**
	 * @brief Adds a Flight on the Company with information asked to the user
	 */
	void addVoo();

	/**
	 * @brief Changes the Flight with the information asked to the user
	 */
	void changeVoo();

	/**
	 * @brief Removes a Flight thats the user wants to remove from the Company
	 */
	void removeVoo();

	/**
	 * @brief Displays the information of all Active Passengers
	 */
	void displayPassageiros() const;

	/**
	 * @brief Adds a Inactive Passenger on the Company with information asked to the user
	 */
	void addPassageiro();

	/**
	 * @brief Changes the Passenger with information asked to the user
	 */
	void changePassageiro();

	/**
	 * @brief Removes a Passenger thats the user wants to remove from the Company
	 */
	void removePassageiro();

	/**
	 * @brief Displays all the reservations of the Flight chosen by the user
	 */
	void displayReservations() const;

	/**
	 * @brief Does a Reservation of a Flight with the information asked to the user
	 */
	void makeReservation();

	/**
	 * @brief Removes the Reservation of a Flight thats the user wants to remove
	 */
	void removeReservation();

	/**
	 * @brief Does a Flight promotion
	 */
	void makePromotion();

	/**
	 * @brief Sorts Passengers and Airplanes
	 */
	void sort();

	/**
	 * @brief Displays the maintenance information of all Airplanes
	 */
	void displayMaintenances() const;

	/**
	 * @brief Does Airplane maintenance
	 */
	void makeMaintenance();

	/**
	 * @brief Reschedules Airplane maintenance
	 */
	void rescheduleMaintenance();

	/**
	 * @brief Displays the maintenance information of all Airplanes whose maintenance date is equal to the specified by the user
	 */
	void displayMaintenancesbyDay() const;

	/**
	 * @brief Displays the information of all Tecnicians
	 */
	void displayTecnicians() const;

	/**
	 * @brief Adds a Tecnician on the Company with information asked to the user
	 */
	void addTecnician();

	/**
	 * @brief Changes a Tecnician with the information asked to the user
	 */
	void changeTecnician();

	/**
	 * @brief Removes a Tecnician thats the user wants to remove from the Company
	 */
	void removeTecnician();

	/**
	 * @brief Displays the information of all Inactive Passengers
	 */
	void displayInactive();

	/**
	 * @brief Class Airplanes_Empty exception thrown when the user tries to get Airplanes information when there are no Airplanes
	 */
	class Airplanes_Empty{};

	/**
	 * @brief Class AirplaneNotFound exception thrown when the Airplane that the user wants to lookup doesn't exist
	 */
	class AirplaneNotFound
	{
	public:
		unsigned int id; ///< id of the supposed Airplane
		AirplaneNotFound(unsigned int id){this->id = id;} ///< @brief constructor of the exception
	};

	/**
	 * @brief Class Clientes_Empty exception thrown when the user tries to get Clients information when there are no Clients
	 */
	class Clientes_Empty{};

	/**
	 * @brief Class ClientNotFound exception thrown when the Client that the user wants to lookup doesn't exist
	 */
	class ClientNotFound
	{
	public:
		unsigned int id; ///< id of the supposed Client
		ClientNotFound(unsigned int id){this->id = id;} ///< @brief constructor of the exception
	};

	/**
	 * @brief Class NotToday exception thrown when the user tries to do maintenace on the wrong day
	 */
	class NotToday
	{
	public:
		unsigned int id; ///< id of the Airplane
		NotToday(unsigned int id){this->id = id;} ///< @brief constructor of the exception
	};

	/**
	 * @brief Class Clientes_Empty exception thrown when the user tries to get Tecnician information when there are no Tecnicians
	 */
	class Tecnicians_Empty{};

	/**
	 * @brief Class TecnicianNotFound exception thrown when the Tecnician that the user wants to lookup doesn't exist
	 */
	class TecnicianNotFound
	{
	public:
		unsigned int id;  ///< id of the supposed Tecniacian
		TecnicianNotFound(unsigned int id){this->id = id;}  ///< @brief constructor of the exception
	};
};

#endif /* COMPANHIA_H_ */
