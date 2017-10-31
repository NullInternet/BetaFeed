/*

BetaFeed
Name: FB_Post.cpp

Code to create a Glade window for a user to respond to a Facebook Post.
The IDs will be entered into the database after the user submits a Like or comment.

*/

#include <gtkmm.h>
#include <iostream>

double postID = 0;
double userID = 0;
double commentID = 0;
int numberOfUserComments = 0;
int numberOfUserLikes = 0;

//FB Like stub - uses specific datatype in API
//pass in variables on a user-by-user/post-by-post basis
void FacebookLike(double postID, double userID, int numberOfUserLikes)
{
	//API detection if this userID has made a like
	//record the post ID, the user ID, and an integer for the user's Like
	numberOfUserLikes++; //increment likes according to each user

	//send all above data to the database table
	std::cout << "Your rating has been recorded" << std::flush; 
	std::cout << "User " << userID << " has made " << numberOfUserLikes << "like(s) in total" << std::flush; 
}

//FB Comment stub - uses specific datatype in API
//pass in variables on a user-by-user/post-by-post basis
void FacebookComment(double postID, double userID, double commentID, int numberOfUserComments)
{
	//API detection if this userID has made a comment
	//record Comment ID or just numberOfComments?
	//record the post ID, the user ID, the comment ID
	numberOfUserComments++; //increment comments according to those on post by this user

	//send all above data to the database table
	std::cout << "Your comment has been recorded" << std::flush; 
	std::cout << "User " << userID << " has made " << numberOfUserComments << " comment(s) in total" << std::flush; 
}

//MAIN FUNCTION FOR GLADE POST WINDOW
void on_response_clicked()
{
	//this is a stub with random numbers, replace with API call in proper datatypes
	//need post ID, user ID, comment ID (if applicable), number of user likes/comments in total
	//need detection of user like and comment then the below functions are run       
	FacebookLike(0, 0, numberOfUserLikes); //stub - grab Like data from user with API call
	FacebookComment(0, 0, 0, numberOfUserComments); //stub - grab Comment data from user with API call
}

int main(int argc, char *argv[])
{
	auto post =  Gtk::Application::create(argc, argv);
	//Glade code for showing new window for Post
	Glib::RefPtr<Gtk::Builder> PostBuilder = Gtk::Builder::create_from_file("FB_Post.glade");
  	Gtk::Window* postWindow = nullptr;
  	PostBuilder->get_widget("post_window", postWindow);

	//Implement API call here to retrieve FB Post frame and Like/comment functionality frame

  	Gtk::Button* postButton = nullptr;
  	PostBuilder->get_widget("response_button", postButton);
	
  	postButton->signal_clicked().connect( sigc::ptr_fun(on_response_clicked) );	
	return post->run(*postWindow);
}