/*
 * main.cpp
 *
 *  Created on: 6 juin 2017
 *      Author: maxime
 */

#include <iostream>
#include <memory>
#include <mpd/connection.h>

#include "MPDClient.h"
#include "GClient.h"
#include "MpdErrorException.hpp"

using namespace mpd;

int main(int argc, char *argv[]) {
	int ret = 0;
	const char *ip = "127.0.0.1";
	int port = 6600;
	MPDClient client(ip, port, 0);
	GClient gclient(&client);
	try {
		gclient.startConnection();
		std::cout << gclient.musicServerState() << std::endl;
	}
	catch(const MpdErrorException &ex) {
		std::cerr << ex.what() << std::endl;
		ret = EXIT_FAILURE;
	}
	return ret;
}
