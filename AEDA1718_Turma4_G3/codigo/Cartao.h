#ifndef CARTAO_H_
#define CARTAO_H_

#include <string>
#include "Data.h"

/**
 * @brief Class Card
 */
class Cartao{
	unsigned int id; //**< Card ID */
	unsigned int saldo; //**< Card Balance */
	std::string nome; //**< Card Owner name */
	std::string profissao; //**< Card Owner job */
	Data data_nascimento; //**< Card Owner birth date */
	float nMedAno; //**< Card Owner average flights per year */
	static unsigned int ultimo_id; //**< Last Card ID, used to get next ID*/
public:

	/**
	 * @brief Card default constructor
	 */
	Cartao();

	/**
	 * @brief Card constructor
	 *
	 * @param saldo Card Balance
	 * @param nome Card Owner name
	 * @param profissao Card Owner job
	 * @param data_nascimento Card Owner birth date
	 * @param nMedAno Card Owner average flights per year
	 */
	Cartao(unsigned int saldo, std::string nome, std::string profissao, Data data_nascimento, float nMedAno);

	/**
	 * @brief Card constructor
	 *
	 * @param id Card ID
	 * @param saldo Card Balance
	 * @param nome Card Owner name
	 * @param profissao Card Owner job
	 * @param data_nascimento Card Owner birth date
	 * @param nMedAno Card Owner average flights per year
	 */
	Cartao(unsigned int id, unsigned int saldo, std::string nome, std::string profissao, Data data_nascimento, float nMedAno);

	/**
	 * @brief Gets Card ID
	 *
	 * @return Returns Card ID
	 */
	unsigned int get_id() const;

	/**
	 * @brief Gets Card Balance
	 *
	 * @return Returns Card Balance
	 */
	unsigned int get_saldo() const;

	/**
	 * @brief Gets Card Owner average flights per year
	 *
	 * @return Returns Card Owner average flights per year
	 */
	float get_nMedAno() const;

	/**
	 * @brief Gets Card Owner Name
	 *
	 * @return Returns Card Owner Name
	 */
	std::string get_name() const;

	/**
	 * @brief Gets Card Owner Job
	 *
	 * @return Returns Card Owner Job
	 */
	std::string get_profissao() const;

	/**
	 * @brief Gets Card Owner Birth Date
	 *
	 * @return Returns Card Owner Birth Date
	 */
	Data get_data() const;

	/**
	 * @brief Display Card Information
	 */
	void display() const;

	/**
	 * @brief Changes Card Information according to the user
	 */
	void change();

	/**
	 * @brief Subtracts from balance
	 *
	 * @param valor Value to be subtracted from balance
	 */
	void subtract_to_balance(unsigned int valor);

	/**
	 * @brief Adds to balance
	 *
	 * @param valor Value to be added to balance
	 */
	void add_to_balance(unsigned int valor);
};



#endif /* CARTAO_H_ */
