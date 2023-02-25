#include "Portfolio.h"
#include "login.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// default constructor
Portfolio::Portfolio(vector<Stock> stocks)
{
	this->stock_collection = stocks;
}

// getters
vector<Stock> Portfolio::get_stock_collection(string username)
{
	ifstream user_file("../../../Portfolios/" + username + "_portfolio.txt");
	Stock indiv_stock;
	vector<Stock> all_stock;
	string header, stock;
	stringstream ss, ss2;
	float quant, price;
	getline(user_file, header);

	while (getline(user_file, stock))
	{ 
		bool dividend = false;
		// get first position of tab to index username
		size_t pos = stock.find("\t");
		string stock_name = stock.substr(0, pos);
		if (stock_name != "")
		{
			// get second position of tab to index password
			size_t pos_2 = stock.substr(pos + 1).find("\t");
			string quantity = stock.substr(pos + 1, pos_2);
			// get third position of tab to index if has portfolio
			size_t pos_3 = stock.substr(pos_2 + 1).find("\t");
			string buy_price = stock.substr(pos_3 + pos_2 + 2);
			size_t pos_4 = stock.substr(pos_3 + pos_2 + 2).find("\t");
			string has_dividend = stock.substr(pos_4 + pos_2 + pos_3 + 3);

			// convert strings to floats
			ss.str(quantity);
			ss >> quant;
			ss2.str(buy_price);
			ss2 >> price;

			// convert string to bool
			if (has_dividend == "Yes")
			{
				dividend = true;
			}

			// set stock values to values from file
			indiv_stock.set_ticker(stock_name);
			indiv_stock.set_quantity(quant);
			indiv_stock.set_price(price);
			indiv_stock.set_has_dividend(dividend);
			// add stock to vector
			all_stock.push_back(indiv_stock);
			ss.clear();
			ss2.clear();
		}
	}

	user_file.close();
	stock_collection = all_stock;
	return stock_collection;
}


// display portfolio
void Portfolio::display_portfolio(string username)
{
	// get stocks of user
	vector<Stock> collection = get_stock_collection(username);

	cout << "Portfolio of " << username << ": " << endl;
	cout << "STOCK QUANTITY BUY PRICE DIVIDEND" << endl;
	for (Stock s : collection)
	{
		cout << s << endl;
	}
}

// update portfolio w/ new stocks
void Portfolio::update_portfolio(string username, Stock s)
{
	// get stock data
	string name = s.get_ticker();
	float quantity_f = s.get_quantity();
	string quantity = to_string(quantity_f);
	float price_f = s.get_price();
	string price = to_string(price_f);
	string dividend = s.get_has_dividend();

	// open portfolio file for user
	ofstream stock_data("../../../Portfolios/" + username + "_portfolio.txt", std::ios_base::app);
	// write stock information to file
	stock_data << name + "\t" << quantity + "\t" << price + "\t" << dividend << endl;

	stock_data.close();
}

vector<Stock> Portfolio::sell_stock(string username, string stock_to_sell)
{
	bool find_stock = false;
	Stock sell_stock;
	float price_bought, quantity_owned = 0;
	int index = 0;
	vector<Stock> stocks = get_stock_collection(username);

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
		ofstream update_stocks("../../../Portfolios/" + username + "_portfolio.txt");

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
		update_stocks << "STOCK\tQUANITY\tBUY PRICE\tDIVIDEND" << endl;
		for (Stock s : stocks) 
		{
			update_stocks << s << endl;
		}
		update_stocks.close();
	}
	else
	{
		cout << "You do not own this stock." << endl;
	}

	return stocks;
}