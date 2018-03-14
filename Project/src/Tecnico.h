#ifndef TECNICO_H_
#define TECNICO_H_

#include "Aviao.h"

/**
 * @brief Class Tecnician
 */
class Tecnico
{
	unsigned int id; //**< Tecnician ID */
	std::string nome; //**< Tecnician name */
	std::vector<std::string> especialidade; //**< Tecnician specialities */
	std::vector<Aviao> manutencoes; //**< Tecnician maintenances */

	static unsigned int ultimo_id; //**< Tecnician last ID, used to get next ID */

public:
	/**
	 * @brief Tecnician default constructor
	 */
	Tecnico();

	/**
	 * @brief Tecnician constructor
	 *
	 * @param id Tecnician ID
	 */
	Tecnico(unsigned int id);

	/**
	 * @brief Tecnician constructor
	 *
	 * @param nome Tecnician name
	 * @param especialidade Tecnician specialities
	 */
	Tecnico(std::string nome, std::vector<std::string> especialidade);

	/**
	 * @brief Tecnician constructor
	 *
	 * @param text_line Line taken from Tecnician text file
	 * @param avioes Airplanes to be used to get tecnician maintenances
	 */
	Tecnico(std::string text_line, std::vector<Aviao >  & avioes);

	/**
	 * @brief Gets tecnician id
	 *
	 * @return Tecnician ID
	 */
	unsigned int getID() const;

	/**
	 * @brief Gets tecnician name
	 *
	 * @return Tecnician name
	 */
	std::string getnome() const;

	/**
	 * @brief Gets tecnician specialities
	 *
	 * @return Tecnician specialities
	 */
	std::vector<std::string> getespecialidades() const;

	/**
	 * @brief Gets tecnician maintenances
	 *
	 * @return Tecnician maintenances
	 */
	std::vector<Aviao> getmanutencoes() const;

	/**
	 * @brief Displays Tecnician information
	 */
	void display() const;

	/**
	 * @brief Changes Tecnician information
	 *
	 * Changes Tecnician information, with information provided by the user
	 */
	void change();

	/**
	 * @brief Compares two Tecnicians
	 *
	 * @param t1 Tecnician to compare with
	 *
	 * @return return true if last maintenance is before a1 last maintenance and false otherwise
	 */
	bool operator<(const Tecnico &t1) const;
};



#endif /* TECNICO_H_ */
