#include "Portfolio.h"

#include <iostream>

using namespace std;

// default constructor
Portfolio::Portfolio(string name, vector<Stock> stocks)
{
	this->user_name = name;
	this->stock_collection = stocks;
}

// getters
string Portfolio::get_user_name() const
{
	return user_name;
}
vector<Stock> Portfolio::get_stock_collection() const
{
	return stock_collection;
}

// setters
void Portfolio::set_user_name(string name)
{
	this->user_name = name;
}

// display portfolio
void Portfolio::display_portfolio(string name) const
{
	cout << "Portfolio of " << name << ": " << endl;
	cout << "STOCK\t" << "QUANTITY   " << "BUY PRICE   " << "DIVIDEND" << endl;
	for (Stock s : stock_collection)
	{
		cout << s << endl;
	}

}

// update portfolio w/ new stocks
void Portfolio::update_portfolio(vector<Stock>& stocks)
{
	this->stock_collection = stocks;
}