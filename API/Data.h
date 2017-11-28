
#ifndef DATA_H
#define DATA_H

#include <string>

class Reaction {
public: 
	std::string userID;
	std::string type;
};

class Post {
public :
	std::string id;
	std::string message;
	std::vector<Reaction> reactions;
	std::vector<std::string> comments;
	Post(std::string set_id, std::string set_message){
		id = set_id;
		message = set_message;
	}

	Post(){
		id = "";
		message = "";
	}
};


class User {
public:
	std::string id;
	std::vector<Reaction> reactions;
	std::string name; 
	std::vector<Post> posts;
	int shareCount;
	int commentCount;

	User(std::string set_id, std::string set_name){
		id = set_id;
		name = set_name;
		shareCount = 0;
		commentCount = 0;
	}

	User(){
		id = "";
		name = "";
		shareCount = 0;
		commentCount = 0;
	}
	//std::unique_ptr<Post> posts(new PostVector);
};

bool ContainsID(std::vector<User> users,std::string id);
int getUserIndex(std::vector<User> users,std::string id);
void UpdateUserInfos();

#endif