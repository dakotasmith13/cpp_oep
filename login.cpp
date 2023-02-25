#include "login.h"
#include "Stock.h"

#include <iostream>
#include <fstream>

using namespace std;

// alt constructor
Login::Login(string username, string password)
{
	this->username = username;
	this->password = password;
}

// getters
string Login::get_username() const
{
	return this->username;
}
string Login::get_password() const
{
	return this->password;
}

// setters 
void Login::set_username(string username)
{
	this->username = username;
}
void Login::set_password(string password)
{
	this->password = password;
}

vector<vector<string>> Login::load_users_from_file()
{
	ifstream user_file("../../../users.txt");
	vector<string> indiv_user;
	vector<vector<string>> all_user;
	string header, user;

	getline(user_file, header);

	while (getline(user_file, user))
	{
		// get first position of tab to index username
		size_t pos = user.find("\t");
		string user_name = user.substr(0, pos);
		// get second position of tab to index password
		size_t pos_2 = user.substr(pos + 1).find("\t");
		string pass = user.substr(pos + 1, pos_2);
		// get third position of tab to index if has portfolio
		size_t pos_3 = user.substr(pos_2 + 1).find("\t");
		string has_portfolio = user.substr(pos_3 + pos_2 + 2);
		indiv_user.push_back(user_name);
		indiv_user.push_back(pass);
		indiv_user.push_back(has_portfolio);
		all_user.push_back(indiv_user);
	}
	
	user_file.close();
	return all_user;
}

// verify if user has account
bool Login::has_account(string username)
{
	// get vector of users
	vector<vector<string>> users = load_users_from_file();

	// determine if user already exists
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i][0] == username)
		{
			return true;
		}
	}

	return false;
}

bool Login::verify_password(string username, string password)
{
	// get vector of users
	vector<vector<string>> users = load_users_from_file();

	// determine if password correct
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i][0] == username)
		{
			if (users[i][1] == password)
			{
				return true;
			}
		}
	}

	return false;
}


void Login::create_account()
{
	// get username
	cout << "Please enter a username: ";
	string user = Stock::get_stock_from_user("name");
	// verify username not already taken
	while (has_account(user))
	{
		cout << "Username already taken, please try a different one: ";
		user = Stock::get_stock_from_user("name");
	}
	// get password
	cout << "Please choose a password (Must be between 8-25 chars, contain one upper, lower, special char, and one number): ";
	string pass;
	cin >> pass;
	// verify password meets strength requirements
	while (!password_strength(pass))
	{
		cin.clear();
		cin >> pass;
	}

	// add user to file of users
	ofstream user_file("../../../users.txt");
	user_file << user + "\t" << pass + "\t" << "n" << endl;

}

bool Login::has_portfolio(string username)
{
	vector<vector<string>> users = load_users_from_file();

	// verify if user has portfolio
	for (int i = 0; i < users.size(); i++)
	{
		// find username
		if (users[i][0] == username)
		{
			if (users[i][2] == "y")
			{
				return true;
			}
		}
	}
	return false;
}

// verify if password meets strength requirement
bool Login::password_strength(string password)
{
	bool special_char_check = false, has_upper = false, has_lower = false, has_digit = false;

	if (password.length() < MIN_PASS_LENGTH)
	{
		cout << "Password must contain at least 8 characters." << endl;
		return false;
	}
	if (password.length() > MAX_PASS_LENGTH)
	{
		cout << "Password must contain 25 characters or less." << endl;
		return false;
	}
	
	for (char c : password)
	{
		if (SPECIAL_CHAR.find(c))
		{
			special_char_check = true;
		}
		if (isupper(c))
		{
			has_upper = true;
		}
		if (islower(c))
		{
			has_lower = true;
		}
		if (isdigit(c))
		{
			has_digit = true;
		}
	}

	if (!special_char_check || !has_upper || !has_lower || !has_digit)
	{
		if (!special_char_check)
		{
			cout << "Password must contain at least one special character." << endl;
			return false;
		}
		if (!has_upper)
		{
			cout << "Password must contain at least one uppercase letter." << endl;
			return false;
		}
		if (!has_lower)
		{
			cout << "Password must contain at least one lowercase letter." << endl;
			return false;
		}
		if (!has_digit)
		{
			cout << "Password must contain at least one number." << endl;
			return false;
		}
		else 
		{
			return true;
		}
	}
}

void Login::logout()
{
	this->username = "";
	this->password = "";
}