#include <cpprest/http_client.h>
#include <cpprest/uri.h>  
#include "oauth2.h"
#include <iostream>

using namespace web; 
using namespace web::http;
using namespace web::http::client; 

void callme(char* param, char* value){
  std::cout << "success parameter: " << param << std::endl << "access_token: " << value << std::endl << std::flush;

  http_client client(U("https://graph.facebook.com/v2.10"));
  uri_builder builder(U("/128300407873012/feed"));
	builder.append_query(U("access_token"), value);
	std::cout << builder.to_string() << std::endl;
  pplx::task<void> requestTask = client.request(methods::GET, builder.to_string()).then([] (http_response response){
    //std::cout << response.extract_json().get().as_array()[0];
		std::cout << response.extract_json().get().to_string();
    });
  requestTask.wait();
}

int main(){
	char* loginEndpoint = "https://www.facebook.com/v2.10/dialog/oauth?client_id=128037214567410&response_type=token&scope=user_posts&redirect_uri=https://www.facebook.com/connect/login_success.html";
	char* successParam = "access_token";
	OAuth2 auth(loginEndpoint, successParam);
	auth.setCallback(callme);
	auth.init();
	return 0;
}
