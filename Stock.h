#ifndef STOCK_H
#define STOCK_H

#include <string>

/*
 * This program contains:
 * Stock class with getters and setters
 * get_confirmation_from_user that validates user input for a char
 * get_stock_from_user validates user input for stock name
 * get_float_from_user validates user input for a float
 * buy_stock that allows user to purchase a stock and add to their portfolio
 *
 */ 


class Stock
{

public:
	// default constructor
	Stock() {}

	// alt constructor: name of stock, price bought, quantity bought, has dividend
	Stock(std::string, float, float, bool);

	// getters
	std::string get_ticker() const;
	float get_price() const;
	float get_quantity() const;
	std::string get_has_dividend() const;

	// setters
	void set_ticker(std::string);
	void set_price(float);
	void set_quantity(float);
	void set_has_dividend(bool);

	// validation
	static char get_confirmation_from_user();
	static std::string get_stock_from_user(std::string);
	static float get_float_from_user();

	// methods
	Stock buy_stock() const;

	// overloaded operator
	// allows formatted printing of vector of stocks
	friend std::ostream& operator << (std::ostream& outs, const Stock& sObj);

private:
	// Fields
	std::string ticker_symbol;
	float buy_price;
	float quantity;
	bool has_dividend;
};


#endif