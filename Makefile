main: API/driver.cpp API/oauth2.cpp  
	g++ API/oauth2.cpp API/driver.cpp GUI/gui.h GUI/BetaFeed_MainGUI.cpp TableFiles/db.h TableFiles/db.cpp TableFiles/driver.cpp -o driver -std=c++11 -lboost_system -lcrypto -lssl -lcpprest `pkg-config gtkmm-3.0 webkit2gtk-4.0 --cflags --libs`
clean:
	rm driver
