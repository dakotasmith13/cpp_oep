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

vector<Stock> Portfolio::sell_stock(string stock_to_sell) const
{
	bool find_stock = false;
	Stock sell_stock;
	float price_bought, quantity_owned = 0;
	int index = 0;
	vector<Stock> stocks = get_stock_collection();

	for (int i = 0; i < stocks.size(); i++)
	{
		if (stocks[i].get_ticker() == stock_to_sell)
		{
			find_stock = true;
			string ticker = stocks[i].get_ticker();
			price_bought = stocks[i].get_price();
			quantity_owned = stocks[i].get_quantity();
			index = i;
		}
	}

	// if stock is owned
	if (find_stock)
	{
		// quantity to be sold
		cout << "Please enter how many you would like to sell: ";
		float quantity_sell = Stock::get_float_from_user();
		while (quantity_owned < quantity_sell)
		{
			cout << "You only own " << quantity_owned << " shares. Please enter a valid number: ";
			quantity_sell = Stock::get_float_from_user();
		}

		// price to be sold at
		cout << "Please enter the current price of the stock: ";
		const float current_price = Stock::get_float_from_user();

		// confirmation of selling
		cout << "Are you sure you would like to sell " << quantity_sell << " shares of " << stock_to_sell << " at " << current_price << " each? (y/n): ";
		const char confirm_c = Stock::get_confirmation_from_user();


		if (confirm_c == 'y')
		{
			if (quantity_owned > quantity_sell)
			{
				stocks.at(index).set_quantity(quantity_owned - quantity_sell);
				index = 0;
			}
			else
			{
				stocks.erase(stocks.begin() + index);
				index = 0;
			}
			// display profit gain/ loss
			float profit = (quantity_sell * current_price) - (quantity_sell * price_bought);
			if (profit >= 0)
			{
				cout << "You made " << profit << "$ from this stock" << endl;
			}
			else
			{
				cout << "You lost " << profit << "$ from this stock" << endl;
			}

		}
	}
	else
	{
		cout << "You do not own this stock." << endl;
	}

	return stocks;
}