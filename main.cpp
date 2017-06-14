/*
 * main.cpp
 *
 *  Created on: 6 juin 2017
 *      Author: maxime
 */

#include <iostream>
#include <memory>
#include <mpd/connection.h>
#include <string.h>

#include "MPDClient.h"
#include "GClient.h"
#include "MpdErrorException.hpp"
#include "Notification.h"
#include "NotificationException.hpp"

#define DEFAULT_PORT 6600
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_TIMEOUT 3000

using namespace mpd;
using namespace notify;

void showHelp() {
	std::cout << "MPDNotif is a notification client for mpd\nUsage MPDnotif [-c IP] [-p PORT] [-t TIMEOUT]\nOptions :\n-c <IP> : set mpd server host\n-p <PORT> : set mpd server port\n-t <TIMEOUT> : set connection timeout\n-h : show this help\n";
}

int main(int argc, char *argv[]) {
	int opt;
	std::string ip("");
	unsigned int port = 0;
	unsigned int timeout = 0;
	bool daemonMode = false;

	while((opt = getopt(argc, argv, "d:c:p:t:h")) != -1) {
		switch(opt) {
			case 'd':
				daemonMode = true;
				break;
			case 'c':
				ip += optarg;
				break;
			case 'p':
				port = std::strtol(optarg, NULL, 10);
				break;
			case 't':
				timeout = std::strtol(optarg, NULL, 10);
				break;
			case 'h':
				showHelp();
				return 0;
				break;
		}
	}

	if(ip.empty()) {
		ip += DEFAULT_IP;
	}

	if(port == 0) {
		port = DEFAULT_PORT;
	}

	if(timeout == 0) {
		timeout = DEFAULT_TIMEOUT;
	}

	int ret = 0;
	MPDClient client(ip, port, timeout);
	GClient gclient(&client);
	try {
		gclient.startConnection();
		gclient.runMainLoop();
	}
	catch(const MpdErrorException &ex) {
		std::cerr << ex.what() << std::endl;
		ret = EXIT_FAILURE;
	}
	catch(const NotificationException &ex) {
		std::cerr << ex.what() << std::endl;
		ret = EXIT_FAILURE;
	}
	return ret;
}
