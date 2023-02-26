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

char Stock::get_confirmation_from_user() {
	string user_string;

	// get user input
	getline(cin >> ws, user_string);

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
	cin.clear();
	
	// convert string to char
	char user_char = user_string.at(0);
	return user_char;
}

string Stock::get_stock_from_user(string decision) {
	string user_string;

	// get user input
	getline(cin >> ws, user_string);
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
				cout << "No input. Enter your username: ";
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
				cout << "Invalid input. Enter your username: ";

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

float Stock::get_float_from_user() {
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

ostream& operator << (ostream& outs, const Stock& sObj)
{
	// overload for printing vector of stocks
	outs << fixed
		<< setprecision(2)
		<< sObj.get_ticker() + "\t"
		<< sObj.get_quantity() 
		<< "\t" 
		<< sObj.get_price() 
		<< "\t"
		<< sObj.get_has_dividend();

	return outs;
}
