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

#include "oauth2.h"
#include <iostream>
#include <gtkmm.h>
#include <webkit2/webkit2.h>
#include <regex>
#include <string>

OAuth2::OAuth2(std::string loginEndpoint, std::string successParam){
	this->loginEndpoint = loginEndpoint;
	this->successParam = successParam;
}

void OAuth2::pageLoaded(WebKitWebView  *web_view, WebKitLoadEvent load_event, gpointer user_data){
	if(load_event == WEBKIT_LOAD_FINISHED){
		OAuth2* authobj = (OAuth2*)user_data;
		authobj->filterReply((char*)webkit_web_view_get_uri (web_view));
	}
}

void OAuth2::setCallback(void (*func)(std::string param, std::string value)){
	callback = func;
}

void OAuth2::filterReply(std::string reply){
	std::regex tokensearch(".*" + successParam + "=(.*)&.*");
	std::smatch match;	
	std::regex_search(reply, match, tokensearch);
	if(match.size() > 1){
		(*callback)(successParam, match[1]);
		app->quit();
	}
}

void OAuth2::init(){
  app = Gtk::Application::create();

  OAuth2::accessToken = "";

  Gtk::Window window;
  window.set_default_size(800, 600);
	window.set_title("Authentication");

  page = WEBKIT_WEB_VIEW(webkit_web_view_new());
  
  Gtk::Widget* pageContainer = Glib::wrap(GTK_WIDGET(page));

  window.add(*pageContainer);
  webkit_web_view_load_uri(page, loginEndpoint.c_str());
  
	g_signal_connect(page, "load-changed", G_CALLBACK(pageLoaded), this);

  window.show_all();

  app->run( window ); 
}

void OAuth2::DisplayData(){
	std::cout << "\nUSERS DATA:\n\n";
	for(int i = 0; i < OAuth2::users.size(); i++){
		std::cout<< "\nUSER: " << OAuth2::users[i].name << "\nID: " << OAuth2::users[i].id 
				<< "\nLIKES: " << OAuth2::users[i].reactions[0] 
				<< " LOVE: " << OAuth2::users[i].reactions[1] 
				<< " WOW: " << OAuth2::users[i].reactions[2] 
				<< " HAHA: " << OAuth2::users[i].reactions[3] 
				<< " SAD: " << OAuth2::users[i].reactions[4] 
				<< " ANGRY: " << OAuth2::users[i].reactions[5] 
				<< " THANKFUL: " << OAuth2::users[i].reactions[6] << std::endl;
		for(int ii = 0; ii < OAuth2::users[i].posts.size(); ii++)
		{
			std::cout<< "\nPost[" << ii << "] Message: " << users[i].posts[ii].message << " ID: " << users[i].posts[ii].id
				<< "\nLIKES: " << OAuth2::users[i].posts[ii].reactions[0] 
				<< " LOVE: " << OAuth2::users[i].posts[ii].reactions[1] 
				<< " WOW: " << OAuth2::users[i].posts[ii].reactions[2] 
				<< " HAHA: " << OAuth2::users[i].posts[ii].reactions[3] 
				<< " SAD: " << OAuth2::users[i].posts[ii].reactions[4] 
				<< " ANGRY: " << OAuth2::users[i].posts[ii].reactions[5] 
				<< " THANKFUL: " << OAuth2::users[i].posts[ii].reactions[6]  << std::endl;
		}
	}
}