#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "Portfolio.h"
#include "Stock.h"


using namespace std;


Stock::Stock(string ticker, float buy_price, float quantity, bool has_dividend)
{
	this->ticker_symbol = ticker;
	this->buy_price = buy_price;
	this->quantity = quantity;
	this->has_dividend = has_dividend;
}

// getters
string Stock::get_ticker() const
{
	return this->ticker_symbol;
}
float Stock::get_price() const
{
	return this->buy_price;
}
float Stock::get_quantity() const
{
	return this->quantity;

}
string Stock::get_has_dividend() const
{
	if (has_dividend)
	{
		return "Yes";
	}
	else
	{
		return "No";
	}

}

// setters
void Stock::set_ticker(string stock_ticker)
{
	this->ticker_symbol = stock_ticker;
}

void Stock::set_price(float new_price)
{
	this->buy_price = new_price;
}

void Stock::set_quantity(float new_quantity)
{
	this->quantity = new_quantity;
}

void Stock::set_has_dividend(bool has_dividend)
{
	this->has_dividend = has_dividend;
}

char Stock::get_confirmation_from_user() const {
	string user_string;

	// get user input
	getline(cin, user_string);

	// if input has more than 1 char or is empty
	while (user_string.length() > 1 || user_string.empty() || user_string != "y" && user_string != "n")
	{
		if (user_string.empty())
		{
			cout << "No input. Enter 'y' or 'n': ";
			getline(cin, user_string);
		}
		else
		{
			cout << "Invalid input. Enter 'y' or 'n': ";
			getline(cin, user_string);
		}
	}
	// convert string to char
	char user_char = user_string.at(0);
	return user_char;
}

string Stock::get_stock_from_user(string decision) const {
	string user_string;

	// get user input
	getline(cin, user_string);
	// string stream to split up user input
	stringstream s(user_string);

	// get count of number of words in string
	int count = 0;
	while (s >> user_string)
	{
		count++;
	}

	// if input has more than word or is empty
	while (user_string.empty() || count > 1 || decision == "stock" && user_string.size() > 5)
	{
		if (user_string.empty())
		{
			// re-prompt, then check for # of words again
			if (decision == "stock")
			{
				cout << "No input. Enter the ticker of the stock: ";
			}
			else
			{
				cout << "No input. Enter your first name: ";
			}
			count = 0;
			getline(cin, user_string);
			stringstream empty(user_string);
			while (empty >> user_string)
			{
				count++;
			}
		}
		else
		{
			// re-prompt, then check for # of words again
			if (decision == "stock")
			{
				cout << "Invalid input. Enter a valid stock ticker: ";
			}
			else
			{
				cout << "Invalid input. Enter your first name: ";

			}
			count = 0;
			getline(cin, user_string);
			stringstream invalid(user_string);
			while (invalid >> user_string)
			{
				count++;
			}
		}
	}
	// return validated single word
	return user_string;
}

float Stock::get_float_from_user() const {
	// to enter while loop and check that only a number is entered
	bool valid_num = false, invalid_char = false;
	string user_input;
	stringstream ss, ss2;
	int count = 0;
	float user_dbl;

	// while input is not valid double
	while (!valid_num)
	{
		// get user input
		getline(cin, user_input);
		string temp;
		// load into stringstream
		ss.str(user_input);
		ss2.str(user_input);
		// count how many spaces in input
		while (ss2 >> temp)
		{
			count++;
		}
		ss2.clear();

		// if any chars that are letters in the input, flag invalid_char
		if (user_input.length() > 0)
		{
			for (char c : user_input)
			{
				if (isalpha(c))
				{
					invalid_char = true;
				}
			}

		}
		// if not an int, more than one word, or an invalid character is entered
		if (!(ss >> user_dbl) || count > 1 || invalid_char || user_dbl < 0)
		{
			if (user_input.empty())
			{
				cout << "No input. Enter a number: ";
				// reset
				ss.clear();
				user_input.clear();
				temp.clear();
				count = 0;
				invalid_char = false;
			}
			else
			{
				cout << "Invalid input. Enter a number: ";
				// reset
				ss.clear();
				user_input.clear();
				temp.clear();
				count = 0;
				invalid_char = false;
			}
		}
		else
		{
			// leave while loop
			valid_num = true;

		}
	}
	return user_dbl;
}

Stock Stock::buy_stock() const
{
	// if bought successfully
	bool has_dividend = false;
	Portfolio user_portfolio;
	vector<Stock> stock_collection;

	// get symbol
	cout << "Please enter the symbol of the stock you would like to purchase: ";
	const string ticker = get_stock_from_user("stock");

	// get price
	cout << "Please enter the current price of " << ticker << ": ";
	const float price_of_buy = get_float_from_user();

	// get quantity
	cout << "Please enter the quantity of stock (max 20): ";
	float quantity_to_buy = get_float_from_user();

	while (quantity_to_buy > 20)
	{
		cout << "Please enter a positive integer less than 20: ";
		quantity_to_buy = get_float_from_user();
	}

	// get if stock has dividend
	cout << "Does this stock have a dividend? (y/n): ";
	const char dividend_c = get_confirmation_from_user();

	if (dividend_c == 'y')
	{
		has_dividend = true;
	}

	// create new stock
	Stock new_stock(ticker, price_of_buy, quantity_to_buy, has_dividend);
	return new_stock;
}

vector<Stock> Stock::sell_stock(vector<Stock> stocks) const
{
	bool find_stock = false;
	Stock sell_stock;
	float price_bought, quantity_owned = 0;
	int count = 0;

	// get symbol of stock to be sold
	cout << "Please enter the symbol of the stock you would like to sell: ";
	const string stock_to_sell = get_stock_from_user("stock");

	for (Stock s: stocks)
	{
		count++;
		if (s.get_ticker() == stock_to_sell)
		{
			find_stock = true;
			string ticker = s.get_ticker();
			price_bought = s.get_price();
			quantity_owned = s.get_quantity();
		}
	}

	// if stock is owned
	if (find_stock)
	{
		// quantity to be sold
		cout << "Please enter how many you would like to sell: ";
		float quantity_sell = get_float_from_user();
		while (quantity_owned < quantity_sell)
		{
			cout << "You only own " << quantity_owned << " shares. Please enter a valid number: ";
			quantity_sell = get_float_from_user();
		}

		// price to be sold at
		cout << "Please enter the current price of the stock: ";
		const float current_price = get_float_from_user();

		// confirmation of selling
		cout << "Are you sure you would like to sell " << quantity_sell << " shares of " << stock_to_sell << " at " << current_price << " each? (y/n): ";
		const char confirm_c = get_confirmation_from_user();


		if (confirm_c == 'y')
		{
			if (quantity_owned > quantity_sell)
			{
				stocks.at(count - 1).set_quantity(quantity_owned - quantity_sell);
				count = 0;
			}
			else
			{
				stocks.erase(stocks.begin() + count - 1);
				count = 0;
			}
			// display profit gain/ loss
			float profit =  (quantity_sell * current_price) - (quantity_sell * price_bought);
			if (profit >=0 )
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

ostream& operator << (ostream& outs, const Stock& sObj)
{
	// overload for printing vector of stocks
	outs << fixed
		<< setprecision(2)
		<< setw(5) << sObj.get_ticker()
		<< setw(8) << sObj.get_quantity()
		<< setw(14) << sObj.get_price()
		<< setw(8) << sObj.get_has_dividend();

	return outs;
}
