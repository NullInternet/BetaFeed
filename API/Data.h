
#ifndef DATA_H
#define DATA_H

#include <string>

class Post {
public :
	std::string id;
	std::string message;
	int reactions[7] = { 0,0,0,0,0,0,0 };
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
	int reactions[7] = { 0,0,0,0,0,0,0 };
	std::string name; 
	std::vector<Post> posts;

	User(std::string set_id, std::string set_name){
		id = set_id;
		name = set_name;
	}

	User(){
		id = "";
		name = "";
	}
	//std::unique_ptr<Post> posts(new PostVector);
};

#endif