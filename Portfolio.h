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
	Portfolio(vector<Stock>);

	// getters
	vector<Stock> get_stock_collection(std::string username);

	// display portfolio
	void display_portfolio(std::string username);

	// update portfolio w/ new stocks
	void update_portfolio(std::string username, Stock s);
	std::vector<Stock> sell_stock(std::string username, std::string stock_to_sell);


private:
	// Fields
	vector<Stock> stock_collection;
};


#endif
