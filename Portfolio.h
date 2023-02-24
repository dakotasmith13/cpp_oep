#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include <string>
#include <vector>
#include "Stock.h"

using std::vector;

/*
 * This program contains:
 * Portfolio class with getters and setters
 * display_portfolio takes in the name of the user and displays their stocks
 * update_portfolio takes in a vector of stocks to update their portfolio to
 */

class Portfolio
{
public:
	// default constructor
	Portfolio() = default;

	// alt constructor: name and vector of stocks
	Portfolio(std::string, vector<Stock>);

	// getters
	std::string get_user_name() const;
	vector<Stock> get_stock_collection() const;

	// setters
	void set_user_name(std::string);

	// display portfolio
	void display_portfolio(std::string) const;

	// update portfolio w/ new stocks
	void update_portfolio(vector<Stock>&);
	std::vector<Stock> sell_stock(std::string stock_to_sell) const;


private:
	// Fields
	std::string user_name;
	vector<Stock> stock_collection;
};


#endif
