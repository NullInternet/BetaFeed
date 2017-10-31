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

class OAuth2 {
  private:
		char* loginEndpoint;
		char* successParam;
		WebKitWebView* page;
		void (*callback)(char*, char*);
		static void pageLoaded(WebKitWebView*, WebKitLoadEvent, gpointer);
		Glib::RefPtr<Gtk::Application> app;
	
	public:
		OAuth2(char*, char*);
		void init();
		void setCallback(void (*func)(char*, char*));
		void filterReply(char*);
		static void temp(char* x, char* y){}
};

#endif
