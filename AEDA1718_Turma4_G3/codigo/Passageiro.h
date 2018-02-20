#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_

#include "Cartao.h"
#include <fstream>

/**
 * @brief Class Passenger
 */
class Passageiro
{
protected:
	unsigned int id; //**< Passenger ID */
	static unsigned int ultimo_id; //**< Passenger last ID, used to get next ID */
public:

	/**
	 * @brief Passenger default constructor
	 */
	Passageiro();

	virtual ~Passageiro();

	/**
	 * @brief Gets Passenger ID
	 *
	 * @return Returns Passenger ID
	 */
	unsigned int getID() const;

	/**
	 * @brief Displays Passenger information
	 */
	virtual void display() const;

	/**
	 * @brief Changes Passenger information
	 *
	 * Changes Passenger information, with information provided by the user
	 */
	virtual void change();

	/**
	 * @brief Gets Flight price with card
	 *
	 * @param preco Flight price
	 *
	 * @return Returns price with card
	 */
	virtual float getPriceWithCard(unsigned int preco);

	/**
	 * @brief Gets Passenger name
	 *
	 * @param preco Flight price
	 *
	 * @return Returns Passenger name
	 */
	virtual std::string getNome() = 0;

	/**
	 * @brief Subtracts from balance
	 *
	 * @param valor Value to be subtracted from balance
	 */
	virtual void subtract_to_balance(unsigned int valor);

	/**
	 * @brief Adds to balance
	 *
	 * @param valor Value to be added to balance
	 */
	virtual void add_to_balance(unsigned int valor);

	/**
	 * @brief Writes passenger information to file
	 *
	 * @param myfile Ofstream associated with file to be written to
	 */
	void virtual escreve_fich_passageiro(std::ofstream &myfile) {}
};

/**
 * @brief NormalPassenger class - Passenger without card
 */
class PassageiroNormal: public Passageiro
{
	unsigned int saldo; //**< Passenger balance */
	std::string nome; //**< Passenger name */
public:
	/**
	 * @brief NormalPassenger default constructor
	 */
	PassageiroNormal();
	/**
	 * @brief NormalPassenger constructor
	 *
	 * @param saldo Passenger balance
	 * @param nome Passenger name
	 */
	PassageiroNormal(unsigned int saldo, std::string nome);

	/**
	 * @brief NormalPassenger constructor
	 *
	 * @param text_line Line from passenger file.
	 */
	PassageiroNormal(std::string text_line);

	/**
	 * @brief Displays Passenger information
	 */
	void display() const;

	/**
	 * @brief Changes Passenger information with information provided by the user
	 */
	void change();

	/**
	 * @brief Gets Flight price with card
	 *
	 * @param preco Flight price
	 *
	 * @return Returns price with card
	 */
	float getPriceWithCard(unsigned int preco);

	/**
	 * @brief Gets Passenger name
	 *
	 * @return Returns Passenger name
	 */
	std::string getNome(){return nome;}

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

	/**
	 * @brief Writes passenger information to file
	 *
	 * @param myfile Ofstream associated with file to be written to
	 */
	void escreve_fich_passageiro(std::ofstream &myfile)
	{
		myfile << 'N' <<';' << id << ';' << saldo << ';' << nome;
	}
};

/**
 * @brief CardPassenger class - Passenger with card
 */
class PassageiroCartao: public Passageiro
{
	Cartao cartao; //**< Passenger card */
public:
	/**
	 * @brief CardPassenger default constructor
	 */
	PassageiroCartao();

	/**
	 * @brief CardPassenger constructor
	 *
	 * @param cartao Passenger card
	 */
	PassageiroCartao(Cartao cartao);

	/**
	 * @brief CardPassenger constructor
	 *
	 * @param text_line Line from passenger file.
	 */
	PassageiroCartao(std::string text_line);

	/**
	 * @brief Displays Passenger information
	 */
	void display() const;

	/**
	 * @brief Changes Passenger information with information provided by the user
	 */
	void change();

	/**
	 * @brief Gets Flight price with card
	 *
	 * @param preco Flight price
	 *
	 * @return Returns price with card
	 */
	float getPriceWithCard(unsigned int preco);

	/**
	 * @brief Gets Passenger name
	 *
	 * @return Returns Passenger name
	 */
	std::string getNome(){return cartao.get_name();}

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

	/**
	 * @brief Writes passenger information to file
	 *
	 * @param myfile Ofstream associated with file to be written to
	 */
	void escreve_fich_passageiro(std::ofstream &myfile)
	{
		myfile << 'C' << ';' << id << ';' << cartao.get_id() << ';' << cartao.get_name() << ';' << cartao.get_profissao() << ';' << cartao.get_data().get_dia() << '/' << cartao.get_data().get_mes() << '/' << cartao.get_data().get_ano() << ';' << cartao.get_saldo() << ';' << cartao.get_nMedAno();
	}
};

/**
 * @brief Class Passenger
 *
 * Only hols a passenger pointer
 */
struct PassageiroPtr
{
	Passageiro * passageiro; ///< Passenger pointer
};


#endif /* PASSAGEIRO_H_ */
