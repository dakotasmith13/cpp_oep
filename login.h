#ifndef LOGIN_H
#define LOGIN_H

#include <string>

class Login
{
public:
	// default constructor
	Login() {};
	// alt constructor
	Login(std::string username, std::string password);

	// getters
	std::string get_username() const;
	std::string get_password() const;

	// setters 
	void set_username(std::string username);
	void set_password(std::string password);

	// verify if user has account
	bool has_account(std::string username);
	bool create_account();
	bool has_portfolio(std::string username);
	// verify if password meets strength requirement
	bool password_strength(std::string password);

private:
	std::string username;
	std::string password;
};

#endif