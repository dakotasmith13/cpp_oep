#include "login.h";
#include "Portfolio.h"
#include <iostream>
using namespace std;

bool test_Stock();
bool test_Portfolio();
bool test_Login();


int main() {
	
	if (test_Stock())
	{
		cout << "Passed all Stock test cases." << endl;
	}
	if (test_Portfolio())
	{
		cout << "Passed all Portfolio test cases." << endl;
	}
	if (test_Login())
	{
		cout << "Passed all Login test cases." << endl;
	}

	return 0;
}

bool test_Stock()
{
	bool passed = true;
	// create Stock object
	Stock s;
	Stock s2("TEST", 5.5, 10, false);
	Stock bought_stock;
	
	// alt constructor test
	if (s2.get_ticker() != "TEST" || s2.get_price() != 5.5 || s2.get_quantity() != 10 || s2.get_has_dividend() == "Yes")
	{
		passed = false;
		cout << "Failed alternate constructor test case." << endl;
	}

	// testing buy stock method
	cout << "TO BUY: TSLA, QUANT: 10, PRICE: 10, DIVIDEND: NO" << endl;
	bought_stock = s.buy_stock();

	if (bought_stock.get_ticker() != "TSLA" || bought_stock.get_quantity() != 10 || bought_stock.get_price() != 10 || bought_stock.get_has_dividend() == "Yes")
	{
		passed = false;
		cout << "Failed buy stock test case." << endl;
	}

	// testing setters
	s.set_ticker("AAPL");
	if (s.get_ticker() != "AAPL")
	{
		passed = false;
		cout << "Failed set ticker test case." << endl;
	}

	s.set_quantity(3);
	if (s.get_quantity() != 3)
	{
		passed = false;
		cout << "Failed set quantity test case." << endl;
	}

	s.set_price(10.5);
	if (s.get_price() != 10.5)
	{
		passed = false;
		cout << "Failed set price test case." << endl;
	}

	s.set_has_dividend(true);
	if (s.get_has_dividend() != "Yes")
	{
		passed = false;
		cout << "Failed set has dividend test case." << endl;
	}

	return passed;
}

bool test_Portfolio()
{
	bool passed = true;
	Portfolio p;
	Stock s("TSLA", 3.00, 3.00, true);
	Stock s2("AAPL", 4.00, 3.00, true);
	vector<Stock> collection{ s };
	vector<Stock> portfolio_collection;
	// use existing username
	string username = "dakota";
	
	// get stock collection test
	portfolio_collection = p.get_stock_collection(username);
	for (int i = 0; i < portfolio_collection.size(); i++)
	{
		if (portfolio_collection[i].get_ticker() != collection[i].get_ticker())
		{
			passed = false;
			cout << "Failed get stock collection test case." << endl;
		}
	}

	// update portfolio test
	// first update collection to be tested against
	collection.push_back(s2);
	p.update_portfolio(username, s2);
	for (int i = 0; i < portfolio_collection.size(); i++)
	{
		if (portfolio_collection[i].get_ticker() != collection[i].get_ticker())
		{
			passed = false;
			cout << "Failed update portfolio test case." << endl;
		}
	}

	// sell stock test
	cout << "TO SELL: AAPL, Q: 3, PRICE: 4" << endl;
	collection.erase(collection.begin() + 1);
	portfolio_collection = p.sell_stock(username, "AAPL");
	for (int i = 0; i < portfolio_collection.size(); i++)
	{
		if (portfolio_collection[i].get_ticker() != collection[i].get_ticker())
		{
			passed = false;
			cout << "Failed sell stock test" << endl;
		}
	}

	return passed;
} 

bool test_Login()
{
	bool passed = true;
	Login l;
	vector<vector<string>> users{ {"daksmith", "Password123!"}, {"dakota", "Password123!"} };

	// test load users from file
	if (l.load_users_from_file() != users)
	{
		passed = false;
		cout << "Failed load users from file test case." << endl;
	}

	cout << "USERNAME TO CREATE: admin PASS: Password123!" << endl;
	// create account & password strength embedded w/in 
	l.create_account();

	// has account test/ create account test
	if (!l.has_account("admin"))
	{
		passed = false;
		cout << "Failed has account test case." << endl;
	}

	// verify password test/ create account test
	if (!l.verify_password("admin", "Password123!"))
	{
		passed = false;
		cout << "Failed verify password test case." << endl;
	}

	// logout test
	l.set_username("dakota");
	l.set_password("Password123!");
	l.logout();
	if (!l.get_username().empty() && !l.get_password().empty())
	{
		passed = false;
		cout << "Failed logout test case." << endl;
	}
	
	return passed;
}