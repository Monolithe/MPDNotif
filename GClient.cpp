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
}

GClient::~GClient() {
}

void GClient::startConnection() {
	try {
		std::cout << "Connection to " << client->getIp() << ":" << client->getPort() << " ..." << std::endl;
		client->initConnection();
		std::cout << "Success !" << std::endl;
	}
	catch(const MpdErrorException &ex) {
		throw;
	}
}

std::string GClient::musicServerState() {
	struct mpd_status *status;
	struct mpd_song *song;
	try {
		status = this->client->getStatus();
		song = this->client->getActualSong();
	}
	catch(const MpdErrorException &ex) {
		throw;
	}
	std::string state("");
	if(mpd_status_get_state(status) == MPD_STATE_PAUSE) {
		state +="(Paused) ";
	}
	std::string volume("Volume : " + std::to_string(mpd_status_get_volume(status)) + "%");
	mpd_status_free(status);
	std::string songString("");
	songString += getTag(song, MPD_TAG_ARTIST);
	songString += " : ";
	songString += getTag(song, MPD_TAG_TITLE);
	mpd_song_free(song);
	std::string musicServerState(state + songString + "\n" + volume);
	return musicServerState;
}

std::string GClient::getTag(const struct mpd_song *song, enum mpd_tag_type type) {
	const char *value;
	std::string valueString("");
	value = mpd_song_get_tag(song, type, 0);
	valueString += value;
	return valueString;
}

MPDClient* GClient::getClient() {
	return client;
}

} /* namespace mpd */
