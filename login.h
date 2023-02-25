#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <vector>

class Login
{
public:
	// default constructor
	Login() {}
	// alt constructor
	Login(std::string username, std::string password);

	// getters
	std::string get_username() const;
	std::string get_password() const;

	// setters 
	void set_username(std::string username);
	void set_password(std::string password);

	// load users from file
	std::vector<std::vector<std::string>> load_users_from_file();
	// verify if user has account
	bool has_account(std::string username, std::string password);
	void create_account();
	bool has_portfolio(std::string username);
	// verify if password meets strength requirement
	bool password_strength(std::string password);

private:
	const int MIN_PASS_LENGTH = 8;
	const int MAX_PASS_LENGTH = 25;
	const std::string SPECIAL_CHAR = "!@#$%^&*?";
	std::string username;
	std::string password;
};

#endif