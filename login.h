#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <vector>

/*
 * This program contains:
 * Login class with getters and setters
 * load_users_from_file creates vector with vector of strings filled with usernames and passwords of users
 * has_account verifies that a username exists or not, returns true if exists
 * verify_password verifies that the entered password matches the pw of that user, return true if correct
 * create_account creates a new user and adds their username and password to file of users
 * password_strength determines if entered password meets pw requirements (8-25 chars, one upper, one lower, one number)
 * logout sets the username and password to "", as if the user had logged out
 *
 */

class Login
{
public:
	// default constructor
	Login() {}
	// alt constructor
	Login(std::string username);

	// getters
	std::string get_username() const;
	std::string get_password() const;

	// setters 
	void set_username(std::string username);
	void set_password(std::string password);

	// load users from file
	std::vector<std::vector<std::string>> load_users_from_file();
	// verify if user has account
	bool has_account(std::string username);
	bool verify_password(std::string username, std::string password);
	void create_account();
	// verify if password meets strength requirement
	bool password_strength(std::string password);
	void logout();

private:
	const int MIN_PASS_LENGTH = 8;
	const int MAX_PASS_LENGTH = 25;
	const std::string SPECIAL_CHAR = "!@#$%^&*?";
	std::string username;
	std::string password;
};

#endif