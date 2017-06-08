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

using namespace mpd;
using namespace notify;

int main(int argc, char *argv[]) {
	int opt;
	std::string ip("");
	int port;

	while((opt = getopt(argc, argv, "c:p:h")) != -1) {
		switch(opt) {
			case 'c':
				ip += optarg;
				break;
			case 'p':
				port = std::strtol(optarg, NULL, 10);
				break;
			case 'h': // TODO : help
				break;
		}
	}

	if(ip.empty()) {
		ip += DEFAULT_IP;
	}

	if(port == 0) {
		port = DEFAULT_PORT;
	}

	int ret = 0;
	MPDClient client(ip, port, 3000);
	GClient gclient(&client);
	try {
		gclient.startConnection();
		Notification notif(gclient.musicServerState().c_str());
		notif.run();
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
