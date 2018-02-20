#ifndef EXCECOES_H_
#define EXCECOES_H_

#include <string>

/**
 * @brief Class FailedInput - Exception thrown when the user inputs something unexpected
 */
class FailedInput
{
public:
	std::string info; /**< Error message */

	/**
	 * @brief FailedInput constructor
	 * @param informacao Error message
	 */
	FailedInput(std::string informacao){info = informacao;}
};

/**
 * @brief Class WrongOption - Exception thrown when the user selects an unexisting option
 */
class WrongOption
{
public:
	int option; /**< Operation chosen by the user */
	/**
	 * @brief WrongOption constructor
	 * @param opcao Operation chosen by the user
	 */
	WrongOption(char opcao){option = opcao;}
};

/**
 * @brief Class IncorrectValue - Exception thrown when the user inputs a unexpected value
 */
class IncorrectValue
{
public:
	std::string msg; /**< Error message */
	/**
	 * @brief IncorrectValue constructor
	 * @param mensagem Error message
	 */
	IncorrectValue(std::string mensagem){this->msg = mensagem;}
};

#endif /* EXCECOES_H_ */
