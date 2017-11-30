/* Copyright 2017 Lola Holiday
Copyright 2017 Paul Salvador Inventado

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "fbpastpost.h"
#include <iostream>

//Declare a new ViewController zfor the LoginController to control the login window
LoginController::LoginController(std::string windowName):ViewController(windowName){
}

//Important -- Glade window and button handlers go here under init
void LoginController::init(){
	window->set_title("FaceBook BetaFeed - Login");
	window->set_default_size(400, 300);	
	window->set_position(Gtk::WIN_POS_CENTER_ALWAYS);

	Gtk::Button* lButton = nullptr;
  	builder->get_widget("btn_fblogin", lButton);
	lButton->signal_clicked().connect( sigc::mem_fun(*this, &LoginController::login) );
	//The API person will take care of the auth. token, which will execute before the next window is shown
}

//API auth will be made before new posts window is shown
void LoginController::login(){
	//API auth call - return to this function afterwards
	gapManager->showView("posts_window");
}

//The action to perform once the exit button is clicked on Login
bool LoginController::clickClose(GdkEventAny* evt){
	gapManager->exit();
	return false;
}

//Controller for the posts on the FB page
PostController::PostController(std::string windowName):ViewController(windowName){

}

//*** Question - after login, will next window be showing multiple posts or one post?
//if multiple posts how to select a post to react to?
//new idea - each time "select new post" button is clicked, get a new post from FB page and cycle through all of them per click

//Init for PostController
void PostController::init(){
	window->set_title("BetaFeed - All Game Posts");
	window->set_default_size(600, 800);	
	window->set_position(Gtk::WIN_POS_CENTER_ALWAYS);

	//Added button to Posts window to "Cycle through" posts as they are listed on the FB page
	Gtk::Button* cButton = nullptr;
  	builder->get_widget("cyclePost_btn", cButton);
	cButton->signal_clicked().connect( sigc::mem_fun(*this, &PostController::cyclePost) );

	//Adding a button to Posts window to be able to select an individual post when it is displayed
	Gtk::Button* pButton = nullptr;
  	builder->get_widget("selectPost_btn", pButton);
	pButton->signal_clicked().connect( sigc::mem_fun(*this, &PostController::selectPost) );
}

//Function that shows the next post on the page when button is pressed
//If most recent post is reached, restart at first post on page
void PostController::cyclePost(){
	//API CALL - show the next post in this window
	//no back and forth functionality yet
}

//Function that selects the shown post in the window to react to, opens reaction window
void PostController::selectPost(){
	gapManager->showView("reaction_window");
}

//when post_window is closed, return to login window
bool PostController::clickClose(GdkEventAny* evt){
	gapManager->showView("start_window");
	return false;
}

//Controller for the Reactions user can make on that post
ReactionController::ReactionController(std::string windowName):ViewController(windowName){

}

//Init for ReactionController
void ReactionController::init(){
	window->set_title("BetaFeed - Rate This Game");
	window->set_default_size(400, 400);	
	window->set_position(Gtk::WIN_POS_CENTER_ALWAYS);

	//Adding reaction buttons to this window only - reactions 1-7 (like, love, wow, haha, sad, angry, thank) 
	//no comment handling for now

	//Like reaction
	Gtk::Button* r1Button = nullptr;
  	builder->get_widget("like_btn", r1Button);
	r1Button->signal_clicked().connect( sigc::mem_fun(*this, &ReactionController::Like) );
}

//Function that selects the shown post on the page to react to - do not show new window
void ReactionController::Like(){
	//store 1 like (+1) in databse ranking system associated with this post ID & user ID
	std::cout << "You rated this game positively.\n";
}

//when reaction_window is closed, return to post window
bool ReactionController::clickClose(GdkEventAny* evt){
	gapManager->showView("posts_window");
	return false;
}