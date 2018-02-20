#ifndef DATA_H_
#define DATA_H_

class Data
{
	unsigned int ano;  		///< year of the Date
	unsigned int mes; 		///< month of the Date
	unsigned int dia;		///< day of the Date
	unsigned int hora;		///< hour of the Date
	unsigned int minuto;	///< minutes of the Date
public:

	/**
	 * @brief Default constructor of Data
	 */
	Data();

	/**
	 * @brief Default constructor of Data
	 *
	 * @param ano year of the Date
	 * @param mes month of the Date
	 * @param dia day of the Date
	 */
	Data(unsigned int ano, unsigned int mes, unsigned int dia);

	/**
	 * @brief Default constructor of Data
	 *
	 * @param ano year of the Date
	 * @param mes month of the Date
	 * @param dia day of the Date
	 * @param hora hour of the Date
	 * @para minuto minute of the Date
	 */
	Data(unsigned int ano, unsigned int mes, unsigned int dia, unsigned int hora, unsigned int minuto);

	/**
	 * @brief Gets the year of Date
	 *
	 * @return ano
	 */
	unsigned int get_ano() const;

	/**
	 * @brief Gets the month of Date
	 *
	 * @return mes
	 */
	unsigned int get_mes() const;

	/**
	 * @brief Gets the day of Date
	 *
	 * @return dia
	 */
	unsigned int get_dia() const;

	/**
	 * @brief Gets the hour of Date
	 *
	 * @return hora
	 */
	unsigned int get_hora() const;

	/**
	 * @brief Gets the minute of Date
	 *
	 * @return minuto
	 */
	unsigned int get_minuto() const;

	/**
	 * @brief Displays the Date
	 */
	void display() const;

	/**
	 * @brief Display the Day of Date
	 */
	void displayDia() const;

	/**
	 * @brief Compares two Dates
	 *
	 * @param d1 Date 1
	 * @param d2 Date 2
	 *
	 * @return return true if d1 < d2 and false otherwise
	 */
	friend bool operator<(const Data& d1, const Data& d2);

	/**
	 * @brief Compares two Dates
	 *
	 * @param d1 Date 1
	 * @param d2 Date 2
	 *
	 * @return return true if d1 year,month,day are equal to d2 year,month,day and false otherwise
	 */
	friend bool operator==(Data d1, Data d2);

	/**
	 * @brief Changes the current Date with the information given by the user
	 */
	void setCurrentDate();

	/**
	 * @brief Adds value days to date
	 *
	 * @param value number of days to be added
	 */
	void addDay(unsigned int value);
};



#endif /* DATA_H_ */
