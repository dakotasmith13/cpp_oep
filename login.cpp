#include "login.h"

using namespace std;

// default constructor
Login::Login() {};
// alt constructor
Login::Login(string username, string password)
{

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

// verify if user has account
bool Login::has_account(string username)
{
	return false;
}

bool Login::create_account()
{
	return false;
}

bool Login::has_portfolio(string username)
{
	return false;
}

// verify if password meets strength requirement
bool Login::password_strength(string password)
{
	return false;
}