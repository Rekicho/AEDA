#ifndef VOO_H_
#define VOO_H_

#include <vector>
#include "Passageiro.h"

/**
 * @brief Class Flight
 */
class Voo
{
protected:
	unsigned int id; //**< Flight ID */
	std::string partida; //**< Flight departure */
	std::string destino; //**< Flight destination*/
	Data data_partida; //**< Flight departure date */
	Data data_chegada; //**< Flight landing date */
	unsigned int preco; //**< Flight price */
	static unsigned int ultimo_id; //**< Flight last ID, used to get next ID */
public:
	/**
	 * @brief Airplane default constructor
	 */
	Voo();

	virtual ~Voo();

	/**
	 * @brief Airplane constructor
	 *
	 * @param partida Flight departure
	 * @param destino Flight destination
	 * @param data_partida Flight departure date
	 * @param data_chegada Flight landing date
	 * @param preco Flight price
	 */
	Voo(std::string partida, std::string destino, Data data_partida, Data data_chegada, unsigned int preco);

	/**
	 * @brief Airplane constructor
	 *
	 * @param text_line Line from airplane file.
	 */
	Voo(std::string text_line);

	/**
	 * @brief Gets Flight ID
	 *
	 * @return Returns Flight ID
	 */
	unsigned int getID() const;

	/**
	 * @brief Displays Flight information
	 */
	virtual void display() const;

	/**
	 * @brief Changes Flight information
	 *
	 * Changes Flight information, with information provided by the user.
	 */
	void change();

	/**
	 * @brief Removes Passenger from flight
	 *
	 * @param id_passageiro Passenger to be removed ID
	 */
	virtual void removePassageiro(unsigned int id_passageiro);

	/**
	 * @brief Displays all flight reservations
	 */
	virtual void displayReservations() const;

	/**
	 * @brief Makes reservation
	 *
	 * @param client Passenger to be reserved
	 */
	virtual void makeReservation(Passageiro * cliente);

	/**
	 * @brief Removes reservation
	 *
	 * @param client Passenger to be removed reservation
	 */
	virtual void removeReservation(unsigned int id_cliente);

	/**
	 * @brief Makes promotion
	 *
	 * @lotacao Capacity to check if promotion is available
	 */
	virtual void makePromotion(unsigned int lotacao);

	/**
	 * @brief Checks if the flight is full
	 *
	 * @param lotacao Airplance capacity
	 */
	virtual bool checkFull(unsigned int lotacao){return false;}

	/**
	 * @brief Writes flight information to file
	 *
	 * @param myfile Ofstream associated with file to be written to.
	 */
	virtual void escreve_fich_voos(std::ofstream &myfile) {}

	/**
	 * @brief Class FlightsEmpty - thrown when the user tries to access passengers information and there are no passengers
	 */
	class PassengersEmpty{};

	/**
	 * @brief Class PassageiroNotFound - thrown when the user tries to access a non existing passenger
	 */
	class PassageiroNotFound
	{
	public:
		unsigned int id; //**< ID not found */

		/**
		 * @brief Passageiro constructor
		 * @param id ID not found
		 */
		PassageiroNotFound(unsigned int id){this->id = id;}
	};

	/**
	 * @brief Class CantDoPromotion - thrown when user tries to do a promotion and can't
	 */
	class CantDoPromotion{};
};

/**
 * @brief Class ComercialFlight
 */
class VooComercial: public Voo
{
	//Does not need to delete Passageiro pointers in it's destructor, beacuse they are created and deleted in Company
	std::vector<Passageiro *> passageiros; //**< Flight passengers */
public:
	/**
	 * @brief ComercialAirplane default constructor
	 */
	VooComercial();

	/**
	 * @brief ComericalAirplane constructor
	 *
	 * @param partida Flight departure
	 * @param destino Flight destination
	 * @param data_partida Flight departure date
	 * @param data_chegada Flight landing date
	 * @param preco Flight price
	 */
	VooComercial(std::string partida, std::string destino, Data data_partida, Data data_chegada, unsigned int preco);

	/**
	 * @brief ComercialFlight constructor
	 *
	 * @param text_line Line of text taken from file to create an text_line.
	 * @param clientess All passengers, needed because we store their id on flights file.
	 */
	VooComercial(std::string text_line, std::vector<Passageiro*>  & clientess);

	/**
	 * @brief Displays Flight information
	 */
	void display() const;

	/**
	 * @brief Removes Passenger from flight
	 *
	 * @param id_passageiro Passenger to be removed ID
	 */
	void removePassageiro(unsigned int id_passageiro);

	/**
	 * @brief Displays all flight reservations
	 */
	void displayReservations() const;

	/**
	 * @brief Makes reservation
	 *
	 * @param client Passenger to be reserved
	 */
	void makeReservation(Passageiro * cliente);

	/**
	 * @brief Removes reservation
	 *
	 * @param client Passenger to be removed reservation
	 */
	void removeReservation(unsigned int id_cliente);

	/**
	 * @brief Makes promotion
	 *
	 * @lotacao Capacity to check if promotion is available
	 */
	void makePromotion(unsigned int lotacao);

	/**
	 * @brief Checks if the flight is full
	 *
	 * @param lotacao Airplance capacity
	 */
	bool checkFull(unsigned int lotacao);

	/**
	 * @brief Writes flight information to file
	 *
	 * @param myfile Ofstream associated with file to be written to
	 */
	void escreve_fich_voos(std::ofstream &myfile)
	{
		unsigned int i;
		myfile << 'C' << ';' << id << ';' << partida << ';' << destino << ';' << data_partida.get_dia() << '/' << data_partida.get_mes() << '/' << data_partida.get_ano() << ' ' << data_partida.get_hora() << ':' << data_partida.get_minuto() << ';';
		myfile << data_chegada.get_dia() << '/' << data_chegada.get_mes() << '/' << data_chegada.get_ano() << ' ' << data_chegada.get_hora() << ':' << data_chegada.get_minuto() << ';' << preco << ';';
		for (i = 0; i < passageiros.size() - 1; i++)
		{
			myfile << passageiros.at(i)->getID() << "/";

		}

		myfile << passageiros.at(i)->getID();
	}
};

/**
 * @brief Class RentedFlight
 */
class VooAlugado: public Voo
{
	//Does not need to delete Passageiro pointer in it's destructor, beacuse it is created and deleted in Company
	//If NULL, there is no passanger atributed to the flight
	Passageiro * passageiro; //**< Flight passenger */
public:

	/**
	 * @brief RentedFlight default constructor
	 */
	VooAlugado();

	/**
	 * @brief RentedFlight constructor
	 *
	 * @param partida Flight departure
	 * @param destino Flight destination
	 * @param data_partida Flight departure date
	 * @param data_chegada Flight landing date
	 * @param preco Flight price
	 */
	VooAlugado(std::string partida, std::string destino, Data data_partida, Data data_chegada, unsigned int preco);

	/**
	 * @brief RentedFlight constructor
	 *
	 * @param text_line Line of text taken from file to create an text_line.
	 * @param clientess All passengers, needed because we store their id on flights file.
	 */
	VooAlugado(std::string text_line, std::vector<Passageiro*>  & clientess);

	/**
	 * @brief Displays Flight information
	 */
	void display() const;

	/**
	 * @brief Removes Passenger from flight
	 *
	 * @param id_passageiro Passenger to be removed ID
	 */
	void removePassageiro(unsigned int id_passageiro);

	/**
	 * @brief Displays all flight reservations
	 */
	void displayReservations() const;

	/**
	 * @brief Makes reservation
	 *
	 * @param client Passenger to be reserved
	 */
	void makeReservation(Passageiro * cliente);

	/**
	 * @brief Removes reservation
	 *
	 * @param client Passenger to be removed reservation
	 */
	void removeReservation(unsigned int id_cliente);

	/**
	 * @brief Makes promotion
	 *
	 * @lotacao Capacity to check if promotion is available
	 */
	void makePromotion(unsigned int lotacao);

	/**
	 * @brief Checks if the flight is full
	 *
	 * @param lotacao Airplance capacity
	 */
	bool checkFull(unsigned int lotacao);

	/**
	 * @brief Writes flight information to file
	 *
	 * @param myfile Ofstream associated with file to be written to
	 */
	void escreve_fich_voos(std::ofstream &myfile)
	{
		myfile << 'A' << ';' << id << ';' << partida << ';' << destino << ';' << data_partida.get_dia() << '/' << data_partida.get_mes() << '/' << data_partida.get_ano() << ' ' << data_partida.get_hora() << ':' << data_partida.get_minuto() << ';';
		myfile << data_chegada.get_dia() << '/' << data_chegada.get_mes() << '/' << data_chegada.get_ano() << ' ' << data_chegada.get_hora() << ':' << data_chegada.get_minuto() << ';' << preco << ';' << passageiro->getID();}
	};

#endif /* VOO_H_ */
