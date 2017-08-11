build/MPDNotif: build/main.o build/GClient.o  build/MPDClient.o build/Notification.o 
	g++ -o build/MPDNotif build/main.o build/GClient.o build/MPDClient.o build/Notification.o `pkg-config --cflags --libs glib-2.0` `pkg-config --cflags --libs gtk+-2.0` `pkg-config --cflags --libs libmpdclient` `pkg-config --cflags --libs libmpd` `pkg-config --cflags --libs libnotify`
	
build/main.o: main.cpp include/MPDClient.h include/GClient.h include/MpdErrorException.hpp include/Notification.h include/NotificationException.hpp
	g++ -o build/main.o -c main.cpp `pkg-config --cflags --libs glib-2.0` `pkg-config --cflags --libs gtk+-2.0` `pkg-config --cflags --libs libmpdclient` `pkg-config --cflags --libs libmpd` -W -Wall

build/GClient.o: src/GClient.cpp ./include/GClient.h
	g++ -o build/GClient.o -c src/GClient.cpp `pkg-config --cflags --libs glib-2.0` `pkg-config --cflags --libs gtk+-2.0` -W -Wall

build/MPDClient.o: src/MPDClient.cpp include/MPDClient.h
	g++ -o build/MPDClient.o -c src/MPDClient.cpp `pkg-config --cflags --libs glib-2.0` `pkg-config --cflags --libs gtk+-2.0` `pkg-config --cflags --libs libmpdclient` `pkg-config --cflags --libs libmpd` -W -Wall

build/Notification.o: src/Notification.cpp include/Notification.h
	g++ -o build/Notification.o -c src/Notification.cpp `pkg-config --cflags --libs glib-2.0` `pkg-config --cflags --libs gtk+-2.0` -W -Wall
