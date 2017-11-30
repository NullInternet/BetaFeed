main: API/oauth2.h API/Data.h GUI/fbbetafeed.h GUI/gui.h userTable.h sharesTable.h postTable.h reactionTable.h commentTable.h  
	g++ API/oauth2.cpp API/driver.cpp GUI/gui.h GUI/BetaFeed_MainGUI.cpp TableFiles/commentTable.cpp TableFiles/postTable.cpp TableFiles/sharesTable.cpp TableFiles/reactionTable.cpp -o driver -std=c++11 -lboost_system -lcrypto -lssl -lcpprest `pkg-config gtkmm-3.0 webkit2gtk-4.0 --cflags --libs`
clean:
	rm driver
