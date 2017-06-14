/*
 * GClient.cpp
 *
 *  Created on: 7 juin 2017
 *      Author: maxime
 */

#include "GClient.h"

namespace mpd {

GClient::GClient(MPDClient *client) {
	this->client = client;
	this->connectionStarted = false;
}

GClient::~GClient() {
}

void GClient::startConnection() {
	try {
		std::cout << "Connection to " << client->getIp() << ":" << client->getPort() << " ..." << std::endl;
		client->initConnection();
		std::cout << "Success !" << std::endl;
		this->connectionStarted = true;
	}
	catch(const MpdErrorException &ex) {
		throw;
	}
}

void GClient::runMainLoop() {
	if(connectionStarted) {
		this->client->runMainLoop();
	}
	else {
		throw MpdErrorException("Error : uninitialized connection");
	}
}

MPDClient* GClient::getClient() {
	return client;
}

} /* namespace mpd */
