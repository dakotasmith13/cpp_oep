#include <iostream>
#include <sstream>
#include <string>
#include "login.h"
#include "Stock.h"
#include "Portfolio.h"
#include <iomanip>
using namespace std;

// used for view stock prices option
// will not be changed by user
struct Preset_Stock
{
    string stock_name;
    string stock_ticker;
    double current_price;
    string dividend;
};

string login();
void display_menu();
// input validation
int get_int_from_user();


int main()
{
    string username;
	char carry_on = 'y';
    Stock s, new_stock;
	vector<Stock> stocks_collection;
    Portfolio p;
    bool success_login = false;

    username = login();

    // depending on choice, call function
    while (carry_on == 'y')
    {
        Login l(username);
        display_menu();
        const int choice = get_int_from_user();
        cout << "\n";
        // buy stock
        if (choice == 1)
        {
            new_stock = s.buy_stock();
            // update portfolio with new stock
            p.update_portfolio(username, new_stock);
            cout << "Successfully purchased " << new_stock.get_ticker() << "!" << endl;
            cout << "\n";
        }
        // sell stock
        else if (choice == 2)
        {
            // check if portfolio empty
            if (p.get_stock_collection(username).empty())
            {
                cout << "You do not currently own any stock." << endl;
                cout << "\n" << endl;
            }
            else
            {
                // get symbol of stock to be sold
                cout << "Please enter the symbol of the stock you would like to sell: ";
                const string stock_to_sell = Stock::get_stock_from_user("stock");
                // get new vector of stocks with updated stock values
                stocks_collection = p.sell_stock(username, stock_to_sell);
                // update portfolio with updated vector
				cout << "\n";
            }
        }
        else if (choice == 3)
        {
            // check if empty
            if (p.get_stock_collection(username).empty())
            {
                cout << username << ", your portfolio is currently empty" << endl;
                cout << "\n" << endl;
            }
            else
            {
                // display portfolio
                p.display_portfolio(username);
                cout << "\n";
                cout << "Would you like to return to the menu? (y/n): ";
                carry_on = s.get_confirmation_from_user();
            }   
        }
        else if (choice == 4)
        {
            // create stocks to be displayed
            Preset_Stock tesla = { "Tesla", "TSLA", 189.98,"N" };
            Preset_Stock apple = { "Apple", "AAPL", 154.50,"Y" };
            Preset_Stock amazon = {"Amazon", "AMZN", 103.39,"N" };
            Preset_Stock microsoft = { "Microsoft", "MSFT", 258.35, "Y" };
            Preset_Stock netflix = { "Netflix", "NFLX", 365.90, "N" };
            Preset_Stock gamestop = { "Gamestop", "GME", 22.25, "N" };
            vector<Preset_Stock> preset_stocks = { tesla, apple, amazon, microsoft, netflix, gamestop };

            // header
            cout << "    Name   Ticker  Current Price Has Dividend" << endl;
            // display stocks
            for (Preset_Stock s : preset_stocks)
            {
                cout << setw(9) << s.stock_name << "    " << s.stock_ticker + "    " << setw(5) << s.current_price << setw(1) << "\t  " + s.dividend + "\n";
            }
            cout << "\n";
            cout << "Would you like to return to the menu? (y/n): ";
            carry_on = s.get_confirmation_from_user();
        }
        else if (choice == 5)
        {
            Login l;
            l.logout();
            carry_on = 'n';
        }
    }

    cout << "Thank you for using the VST!" << endl;
    

	return 0;
}

string login() 
{
    cout << "Welcome to the Virtual Stock Trader" << endl;
    cout << "Do you already have a login? (y/n): ";
    char has_login = Stock::get_confirmation_from_user();
    // create Login object to call methods on
    Login l;
    if (has_login == 'n')
    {
        l.create_account();
        cout << "Account created successfully.\n" << endl;
    }
    cout << "Welcome, please enter your username: ";
    string user = Stock::get_stock_from_user("name");
    while (!l.has_account(user))
    {
        cout << "User does not exist, please try again: ";
        user = Stock::get_stock_from_user("name");
    }
    cout << "Please enter your password: ";
    string pass;
    cin >> pass;
    while (!l.verify_password(user, pass))
    {
        cout << "Incorrect password, please try again: ";
        cin.clear();
        cin >> pass;
    }
    return user;

}

void display_menu()
{
    // display options to user
    cout << "\n";
    cout << "Welcome to the Virtual Stock Trader!" << endl;
    cout << "1. Buy stock" << endl;
    cout << "2. Sell stock" << endl;
    cout << "3. View portfolio" << endl;
    cout << "4. View stock prices" << endl;
    cout << "5. Logout" << endl;

}

int get_int_from_user() 
{
    // to enter while loop and check that only a number is entered
    bool valid_num = false, invalid_char = false;
    string user_input;
    stringstream ss, ss2;
    int count = 0, user_int;

    cout << "Please choose an option (1-5): ";

    // while input is not valid integer
    while (!valid_num)
    {
        // get user input
        getline(cin >> ws, user_input);
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
        if (!(ss >> user_int) || count > 1 || invalid_char || user_int < 1 || user_int > 5)
        {
            if (user_input.empty())
            {
                cout << "No input. Please enter a number 1-5: ";
                // reset
                ss.clear();
                user_input.clear();
                temp.clear();
                count = 0;
                invalid_char = false;
            }
            else
            {
                cout << "Invalid input. Please enter a number 1-5: ";
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
    return user_int;
}