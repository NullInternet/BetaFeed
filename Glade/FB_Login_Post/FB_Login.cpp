/*

BetaFeed
Name: FB_Login.cpp

Code to create a Glade window facilitating Facebook Login for a user.
Hides to show the Facebook Post window after successful login.

*/

#include <gtkmm.h>
#include <iostream>

//FB Login stub - will be populated with login token
//returns true for successful login and false if not (allow for retry?)
//Needs API to verify correct login and if user can retry
void FacebookLogin(int LOGINTOKEN)
{
	if(LOGINTOKEN == 1)
	{
		//after verification of login token
		std::cout << "Successful login" << std::flush; 
	}
	else if(LOGINTOKEN != 1)
	{
		//if login token not verified correctly
		std::cout << "Unsuccessful login" << std::flush; 
	}
}

//MAIN FUNCTION FOR GLADE LOGIN WINDOW
void on_login_clicked()
{
	std::cout << "Starting the login process..." << std::flush; 
	//start the FacebookLogin main function to get logintoken
	//this is a stub, replace 1 with API call in proper datatype
        FacebookLogin(1);
}


int main(int argc, char *argv[])
{
  //MAIN GLADE WINDOW CODE

  auto login =  Gtk::Application::create(argc, argv);

  Glib::RefPtr<Gtk::Builder> LoginBuilder = Gtk::Builder::create_from_file("FB_Login.glade");
  Gtk::Window* loginWindow = nullptr;
  LoginBuilder->get_widget("login_window", loginWindow);

  Gtk::Button* loginButton = nullptr;
  LoginBuilder->get_widget("login_button", loginButton);

  loginButton->signal_clicked().connect( sigc::ptr_fun(on_login_clicked) );
  return login->run(*loginWindow);
}
