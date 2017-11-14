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

#ifndef OAUTH2_H
#define OAUTH2_H

#include <webkit2/webkit2.h>
#include <gtkmm.h>
#include <string>
#include "Data.h"

class OAuth2 {
  private:
		std::string loginEndpoint;
		std::string successParam;
		WebKitWebView* page;
		void (*callback)(std::string, std::string);
		static void pageLoaded(WebKitWebView*, WebKitLoadEvent, gpointer);
		Glib::RefPtr<Gtk::Application> app;
		
	public:
		static std::vector<User> users;
		static std::string accessToken;
		static std::string currentID;
		static Post *tmpPost;
		static Reaction *tmpReaction;
		OAuth2(std::string, std::string);
		void init();
		void setCallback(void (*func)(std::string, std::string));
		void filterReply(std::string);
		void DisplayData();
		static void temp(std::string x, std::string y){}
};



#endif
