Makefile text for FB_Login:
FB_Login: FB_Login.cpp
	g++ FB_Login.cpp -o main -std=c++11 `pkg-config gtkmm-3.0 --cflags --libs`


Makefile text for FB_Post:
FB_Post: FB_Post.cpp
	g++ FB_Post.cpp -o main -std=c++11 `pkg-config gtkmm-3.0 --cflags --libs`
