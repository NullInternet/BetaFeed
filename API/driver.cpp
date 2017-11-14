#include <cpprest/http_client.h>
#include <cpprest/uri.h>  
#include "oauth2.h"
#include <iostream>

using namespace web; 
using namespace web::http;
using namespace web::http::client; 

std::vector<User> OAuth2::users;
std::string OAuth2::accessToken;
std::string OAuth2::currentID;
Post *OAuth2::tmpPost;
Reaction *OAuth2::tmpReaction;

bool ContainsID(std::vector<User> users,std::string id){
	if(users.size() == 0)
	{
		return false;
	}

	for(int i = 0; i < users.size(); i++)
	{
		if(users[i].id == id)
		{
			return true;
		}
		for(int j = 0; j < users[i].posts.size(); j++)
		{
			if(users[i].posts[j].id == id)
			{
				return true;
			}
		}
	}
	return false;
}

int getUserIndex(std::vector<User> users,std::string id){
	for(int i = 0; i < users.size(); i++)
	{
		if(users[i].id == id)
		{
			return i;
		}
	}
	return 0;
}

void callme(std::string param, std::string value){
  //std::cout << "success parameter: " << param << std::endl << "access_token: " << value << std::endl << std::flush;

  http_client clientPost(U("https://graph.facebook.com/v2.10"));
  uri_builder builder(U("/128300407873012/feed"));
	builder.append_query(U("access_token"), value);
	OAuth2::accessToken = value;
	std::cout << builder.to_string() << std::endl;

	pplx::task<void> requestTaskPost = clientPost.request(methods::GET, builder.to_string()).then([] (http_response responsePost){
		json::array dataPost = responsePost.extract_json().get().at(U("data")).as_array();
		for(int i=0; i<dataPost.size(); i++){	

			std::string id = dataPost[i].at(U("id")).as_string();
			std::string message;
			if(dataPost[i].has_field(U("message")))
				message = dataPost[i].at(U("message")).as_string();
			else
				message = dataPost[i].at(U("story")).as_string();
			std::cout << "\nPost ID: " << id << std::endl << "Post message: " << message << std::endl;
			OAuth2::tmpPost = new Post(id,message);
			uri_builder builderUser(U("/"));
			builderUser.append(U(OAuth2::tmpPost->id));
			builderUser.append(U("?fields=from"));
			builderUser.append_query(U("access_token"), OAuth2::accessToken);
			//std::cout << builderUser.to_string() << std::endl;

			http_client clientUser(U("https://graph.facebook.com/v2.10"));
			pplx::task<void> requestTaskUser = clientUser.request(methods::GET, builderUser.to_string()).then([] (http_response responseUser){
				json::value dataUser = responseUser.extract_json().get().at(U("from"));
				// for(int ii=0; ii<dataUser.size(); ii++)
				// {
					std::string id = dataUser.at(U("id")).as_string();
					std::string name = dataUser.at(U("name")).as_string();
					std::cout << "FROM User ID: " << id << std::endl << "username: " << name << std::endl;
					User *user  = new User(id,name);
					if(!ContainsID(OAuth2::users,id))
					{
						OAuth2::users.push_back(*user);
					}
					OAuth2::currentID = id;
				//}
			});
			requestTaskUser.wait();
			
			uri_builder builderReactions(U("/"));
			builderReactions.append(U(OAuth2::tmpPost->id));
			builderReactions.append(U("/reactions"));
			builderReactions.append_query(U("access_token"), OAuth2::accessToken);

			http_client clientReactions(U("https://graph.facebook.com/v2.10"));
			pplx::task<void> requestTaskReactions = clientReactions.request(methods::GET, builderReactions.to_string()).then([] (http_response responseReactions){
				json::array dataReactions = responseReactions.extract_json().get().at(U("data")).as_array();
				for(int ii=0; ii<dataReactions.size(); ii++)
				{
					OAuth2::tmpReaction = new Reaction();

					std::string id = dataReactions[ii].at(U("id")).as_string();
					std::string type = dataReactions[ii].at(U("type")).as_string();
					std::cout << "POST REACTIONS : " << id << std::endl << "type: " << type << std::endl;

					int reactionIndex = 0;
					
					if (type == "LIKE")
							reactionIndex = 0;
					else if (type == "LOVE")
							reactionIndex = 1;
					else if (type == "WOW")
							reactionIndex = 2;
					else if (type == "HAHA")
							reactionIndex = 3;
					else if (type == "SAD")
							reactionIndex = 4;
					else if (type == "ANGRY")
							reactionIndex = 5;
					else if (type == "THANKFUL")
							reactionIndex = 6;
					OAuth2::tmpReaction->userID = id;
					OAuth2::tmpReaction->type = type;
					OAuth2::tmpPost->reactions.push_back(*OAuth2::tmpReaction);
					OAuth2::users[getUserIndex(OAuth2::users,id)].reactions.push_back(*OAuth2::tmpReaction);
				}
			});
			
			requestTaskReactions.wait();

			//post->reactions = OAuth2::users[getUserIndex(OAuth2::users,OAuth2::currentID)].reactions;
			OAuth2::users[getUserIndex(OAuth2::users,OAuth2::currentID)].posts.push_back(*OAuth2::tmpPost);

		}
	});

  requestTaskPost.wait();
}

int main(){
	uri_builder login("https://www.facebook.com/v2.10/dialog/oauth");
	login.append_query("client_id", 128037214567410);
	login.append_query("response_type", "token");
	login.append_query("scope", "user_posts");
	login.append_query("redirect_uri", "https://www.facebook.com/connect/login_success.html");

	OAuth2 auth(login.to_string(), "access_token");
	auth.setCallback(callme);
	auth.init();
	
	auth.DisplayData();
	return 0;
}
