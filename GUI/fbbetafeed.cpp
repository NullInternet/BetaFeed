/*Copyright 2017 Paul Salvador Inventado

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

#ifndef FBBETAFEED
#define FBBETAFEED

#include "fbbetafeed.h"
#include <iostream>

/** ViewController for the Login top level window **/
LoginController::LoginController(GladeAppManager* gapManager, std::string windowName, bool isTopLevel):ViewController(gapManager, windowName, isTopLevel){
	// Sets the size and position of the window
	window->set_title("Facebook BetaFeed");
	window->set_default_size(400, 300);	
	window->set_position(Gtk::WIN_POS_CENTER_ALWAYS);

	// Assigns login() as handler for clicking on the login button
	Gtk::Button* pButton = nullptr;
  builder->get_widget("btn_fblogin", pButton);
	pButton->signal_clicked().connect( sigc::mem_fun(*this, &LoginController::login) );
	FbManager* mgr = FB::getManager();
	mgr->addConnectionListener(this);
}

void LoginController::login(){
	// Switch to the posts_window
	FbManager* mgr = FB::getManager();
	mgr->login(gapManager->getGtkApplication()->get_id());
}

void LoginController::loginSuccess(){
	gapManager->showView("posts_window");
}

bool LoginController::clickClose(GdkEventAny* evt){
	// Exit the GUI
	gapManager->exit();
	return false;
}

/** ViewController for the Posts window **/
PostController::PostController(GladeAppManager* gapManager, std::string windowName, bool isTopLevel):ViewController(gapManager, windowName, isTopLevel){

	// Sets the size and position of the window
	window->set_title("Posts");
	window->set_default_size(800, 600);	
	window->set_position(Gtk::WIN_POS_CENTER_ALWAYS);

	// Associates the post_box Box in the Glade file to a pointer for later use
	posts_container = nullptr;
  builder->get_widget("post_box", posts_container);

	// Associates the post_box Box in the Glade file to a pointer for later use
	remembered_posts_container = nullptr;
  builder->get_widget("make_a_new_post_box", make_posts_container);

	// Assigns refresh() as handler for clicking on the refresh button 
	Gtk::Button* pRefresh = nullptr;
  builder->get_widget("btn_refresh", pRefresh);
	pRefresh->signal_clicked().connect( sigc::mem_fun(*this, &PostController::refresh) );

	// Assigns makePost() as handler for clicking on the make post button 
	Gtk::Button* pMakePost = nullptr;
  	builder->get_widget("btn_make_post", pMakePost);
	pMakePost->signal_clicked().connect( sigc::mem_fun(*this, &PostController::makePost) );
}

void PostController::refresh(){
	// Place holder to API call that will create Post objects for each Facebook post retrieved.
	// Each post is sent to addPost so it is shown on the GUI

	FbManager* mgr = FB::getManager();
	std::vector<Post*> results = mgr->getPosts();
	for(Post* p : results){
		addPost(p);	
	}
}

void PostController::makePost(){
	// Place holder to API call that will create a new Post object for the FB post made with these features.
	// Features of new post:
	//	Game Title (string)
	//	Game URL (string)
	//	Game Pic (image selected on local computer)
	// *Does not show list of posts (handled in Refresh instead)
	
	if(posts.count(post->getId())==0){ // add post if has not been added yet
		// Creates a PostWidget object associated with a Post. All values of the Post are used for the display
		PostWidget* p = Gtk::manage(new PostWidget(post));
		// Stores the PostWidget object for reference (ID)
		posts[post->getId()] = p;

		// Define title, URL, pic of post
		// Store input within textEntry fields below
		new_post_game_title = new Gtk::Entry();
		new_post_game_url = new Gtk::Entry();
		// store entered text as char? 
		const gchar *title_text;
  		entry_text = gtk_entry_get_text(GTK_ENTRY(new_post_game_title));
		const gchar *url_text;
  		url_text = gtk_entry_get_text(GTK_ENTRY(new_post_game_url));

		// Add image to post - in progress
		// changed to simple button from filechooserbutton
		Gtk::Button* pGamePicture = nullptr;
  		builder->get_widget("btn_find_picture", pGamePicture);
		pGamePicture = gtk_file_chooser_button_new (_("Select an image file"), GTK_FILE_CHOOSER_ACTION_OPEN);
		// file chooser will open /etc folder by default		
		gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER (pGamePicture), "/etc");
		
		// Adds the PostWidget object into the post_box designed in the Glade file
		posts_container->add(*p);
	}
}

// Update the posts on main window tab when Refresh is pressed
void PostController::addPost(Post* post){
	if(posts.count(post->getId())==0){ // add post if has not been added yet
		// Creates a PostWidget object associated with a Post. All values of the Post are used for the display
		PostWidget* p = Gtk::manage(new PostWidget(post));
		// Stores the PostWidget object for reference (ID)
		posts[post->getId()] = p;
		// Adds the PostWidget object into the post_box designed in the Glade file
		posts_container->add(*p);
	}
}

bool PostController::clickClose(GdkEventAny* evt){
	// Switch the view to the login window when the x button is clicked
	gapManager->showView("start_window");
	return false;
}

/** Widget to represent Facebook posts **/
//PostWidget::PostWidget(std::string id, std::string titleText, std::string imageLoc, std::string messageText){
PostWidget::PostWidget(Post* p){
	post = p;
	title_separator = new Gtk::Separator(Gtk::ORIENTATION_VERTICAL);
	title = new Gtk::Label(p->getTitle(), Gtk::ALIGN_START);
	
	// Creates other widgets
	timestamp = new Gtk::Label(p->getTimestamp(), Gtk::ALIGN_START);
	message = new Gtk::Label(p->getMessage(), Gtk::ALIGN_START);
	
	// Add all widgets into the main Box
	pack_start(*timestamp, true, true, 5);

	if(!p->getImage().empty()){
		image = new Gtk::Image(p->getImage());
		image->set_halign(Gtk::ALIGN_START);
		pack_start(*image, true, true, 5);
	}

	pack_start(*message, true, true, 5);
	post_separator = new Gtk::Separator(Gtk::ORIENTATION_HORIZONTAL);
	pack_start(*post_separator, true, true, 5);

	// Tell GTK to refresh the GUI so as to show all added components
	show_all();
}

// getters and setters
std::string PostWidget::getId(){
	return id;
}

std::string PostWidget::getTitle(){
	return title->get_text();
}

std::string PostWidget::getImage(){
	//retrieve image here
	return "";
}

std::string PostWidget::getMessage(){
	return message->get_text();
}

Post* PostWidget::getPost(){
	return post;
}

#endif
