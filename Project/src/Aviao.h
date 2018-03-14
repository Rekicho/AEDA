#ifndef AVIAO_H_
#define AVIAO_H_

#include "Voo.h"

/**
 * @brief Class Airplane
 */
class Aviao
{
	unsigned int id; //**< Airplane ID */
	std::string nome; //**< Airplane Name */
	unsigned int lotacao; //**< Airplane Capacity */
	std::vector<Voo *> voos; //**< Vector of flights pointers from this airplane*/
	unsigned int periocidade_manutencao; //**< Airplane maintenance frequency */
	Data proxima_manutencao; //**< Airplane next maintenance date */

	static unsigned int ultimo_id; //**< Airplane last ID, used to get next ID */
public:

	/**
	 * @brief Airplane default constructor
	 */
	Aviao();

	/**
	 * @brief Airplane constructor
	 *
	 * @param id Airplane ID
	 */
	Aviao(unsigned int id);

	/**
	 * @brief Airplane destructor
	 *
	 * Frees space created with new for flights pointers
	 */
	~Aviao();

	/**
	 * @brief Airplane constructor
	 *
	 * @param nome Airplane name
	 * @param lotacao Airplane capacity
	 */
	Aviao(std::string nome, unsigned int lotacao);

	/**
	 * @brief Airplane constructor
	 *
	 * @param text_line Line of text taken from file to create an airplane
	 * @param voos All flights, needed because we store their id on airplanes file.
	 */
	Aviao(std::string text_line,std::vector<Voo*> & voos);

	/**
	 * @brief Airplane constructor
	 *
	 * @param nome Airplane name
	 * @param lotacao Airplane capacity
	 * @param periocidade_manutencao Airplane maintenance frequency
	 * @param proxima_manutencao Airplane next maintenance date
	 */
	Aviao(std::string nome, unsigned int lotacao, unsigned int periocidade_manutencao, Data proxima_manutencao);

	/**
	 * @brief Gets Airplane ID
	 *
	 * @return Returns Airplane ID
	 */
	unsigned int getID() const;

	/**
	 * @brief Gets Airplane Name
	 *
	 * @return Returns Airplane Name
	 */
	std::string getNome() const;

	/**
	 * @brief Gets Airplane Capacity
	 *
	 * @return Returns Airplane Capacity
	 */
	unsigned int getLotacao() const;

	/**
	 * @brief Gets Airplane Flights
	 *
	 * @return Returns Airplane Flights
	 */
	std::vector<Voo*> getVoos() const;

	unsigned int getPeriodicidade_Manutencao() const;

	Data getProxima_Manutencao() const;

	void setProxima_Manutencao(const Data proxima_mantuencao);
	/**
	 * @brief Displays Airplane Information
	 */
	void display() const;

	/**
	 * @brief Changes Airplane Information
	 *
	 * Changes Airplane Information, by asking the user what he wants to be changed.
	 */
	Aviao change();

	/**
	 * @brief Displays the information of all the flights from this airplane
	 */
	void displayVoos() const;

	/**
	 * @brief Adds a flight to the flights vector
	 *
	 * Adds a flight to the flights vector by asking flight information to the user
	 */
	Aviao addVoo();

	/**
	 * @brief Changes a flight Information
	 *
	 * Changes Flight Information, by asking the user what he wants to be changed.
	 */
	void changeVoo();

	/**
	 * @brief Removes a flight from the flights vector
	 *
	 * Removes a flight the user wants to remove form the flights vector.
	 */
	Aviao removeVoo();

	/**
	 * @brief Removes a Passanger from all flights from this airplane
	 *
	 * @param id_passageiro Passenger to be removed ID
	 */
	void removePassageiro(unsigned int id_passageiro);

	/**
	 * @brief Displays all the reservations of a flight
	 *
	 * Displays all the reservations of a flight provided by the user.
	 */
	void displayReservations() const;

	/**
	 * @brief Makes a reservaiton on a flight from the passanger
	 *
	 * @param cliente Passanger pointer to the client to make reservation.
	 */
	void makeReservation(Passageiro * cliente);

	/**
	 * @brief Removes a reservaiton on a flight from the passanger
	 *
	 * @param id_cliente Passanger id from the client to make reservation.
	 */
	void removeReservation(unsigned int id_cliente);

	/**
	 * @brief Makes Flight Promotion
	 */
	void makePromotion();

	/**
	 * @brief Compares two Airplanes
	 *
	 * @param a1 Airplane to compare with
	 *
	 * @return return true if next maintenance is before a1 next maintenance and false otherwise
	 */
	bool operator<(const Aviao &a1) const;

	/**
	 * @brief Compares two Airplanes
	 *
	 * @param a1 Airplane to compare with
	 *
	 * @return return true if ID is equal to a1 ID and false otherwise
	 */
	bool operator==(const Aviao &a1) const;

	/**
	 * @brief Class FlightsEmpty - thrown when the user tries to access flights information and there are no flights
	 */
	class FlightsEmpty{};

	/**
	 * @brief Class FlightsFull - thrown when the user tries to add passenger to the flight but it is already full
	 */
	class FlightFull{};

	/**
	 * @brief Class FlightNotFound - thrown when the user tries to access a non existing flight
	 */
	class FlightNotFound
	{
	public:
		unsigned int id; //**< ID not found */

		/**
		 * @brief FailedNotFound constructor
		 * @param id ID not found
		 */
		FlightNotFound(unsigned int id){this->id = id;}
	};
};

#endif /* AVIAO_H_ */
