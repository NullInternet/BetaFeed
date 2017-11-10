/*
TO-DO:
 * change window title for login
 * trigger post window to show and login window to hide when user clicks login button

*/
/*

BetaFeed
Name: FB_LoginPost.cpp

Combined version of FB_Login and FB_Post cpp files.
Uses FB_LoginPost.glade

*/
/*
struct login_window
{
   GtkEntry *user;
   GtkEntry *pass;
};
typedef struct login_window widgets;
*/

#include <gtkmm.h>
#include <iostream>

//Login Window
//FB API needed - verification of FB credentials
void FacebookLogin()
{
	std::cout << "Successful login" << std::flush; 
	//Show the Post window after user's credentials are validated
	//postWindow->show();
  	//loginWindow->hide();
}

//Login Window
//function for login button to execute
void on_login()
{
	//This function needs to also record the username and password in arrays

	std::cout << "Starting the login process..." << std::flush; 
	//start the FacebookLogin main function to get logintoken
	//this is a stub, replace with API call in proper datatype
        FacebookLogin();
}

//Post window functions
//Post window
//Like receiving function
void on_like()
{
	//API detection if this userID has made a comment

	//send comment data (user ID, post ID, etc) to the database table
	std::cout << "Your like has been recorded" << std::flush; 
}

//Post window
//Comment receiving function
void on_comment()
{
	//API detection if this userID has made a comment

	//send like data (user ID, post ID, etc) to the database table
	std::cout << "Your comment has been recorded" << std::flush; 
}

//Login window/Post window main code
int main(int argc, char *argv[])
{
  auto FBinterface =  Gtk::Application::create(argc, argv);

  //one glade call, window show/hide handled within Glade
  Glib::RefPtr<Gtk::Builder> LoginBuilder = Gtk::Builder::create_from_file("FB_Loginonly.glade");

  Gtk::Window* loginWindow = nullptr;
  LoginBuilder->get_widget("login_window", loginWindow);

  Gtk::Button* loginButton = nullptr;
  LoginBuilder->get_widget("login_button", loginButton);

  loginButton->signal_clicked().connect( sigc::ptr_fun(on_login) );

	//Ideally start the post window after user logs in
	Glib::RefPtr<Gtk::Builder> PostBuilder = Gtk::Builder::create_from_file("FB_Postonly.glade");
	Gtk::Window* postWindow = nullptr;
	
	PostBuilder->get_widget("post_window", postWindow);
	
	//Split like and comment into separate buttons
	Gtk::Button* likeButton = nullptr;
	Gtk::Button* commentButton = nullptr;
	PostBuilder->get_widget("like", likeButton);
	PostBuilder->get_widget("comment", commentButton);
	
	likeButton->signal_clicked().connect( sigc::ptr_fun(on_like) );
	commentButton->signal_clicked().connect( sigc::ptr_fun(on_comment) );

return FBinterface->run(*loginWindow);
return FBinterface->run(*postWindow);
}
