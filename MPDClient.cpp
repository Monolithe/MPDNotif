/*
 * MPDClient.cpp
 *
 *  Created on: 6 juin 2017
 *      Author: maxime
 */

#include "MPDClient.h"

namespace mpd {

MPDClient::MPDClient(std::string ip, unsigned int port, unsigned int timeout) {
	this->ip = ip;
	this->port = port;
	this->timeout = timeout;
	connection = NULL;
}

MPDClient::~MPDClient() {
	mpd_connection_free(this->connection);
}

void MPDClient::initConnection() {
	connection = mpd_connection_new(ip.c_str(), port, timeout);
	if(mpd_connection_get_error(connection) != MPD_ERROR_SUCCESS || !mpd_response_finish(this->connection)) {
		std::string s(mpd_connection_get_error_message(this->connection));
		throw mpd::MpdErrorException(s);
	}
}

struct mpd_status* MPDClient::getStatus() {
	struct mpd_status *status;
	mpd_command_list_begin(this->connection, true);
	mpd_send_status(this->connection);
	mpd_command_list_end(this->connection);
	status = mpd_recv_status(this->connection);
	if(status == NULL || mpd_connection_get_error(this->connection) != MPD_ERROR_SUCCESS || !mpd_response_finish(this->connection)) {
		std::string s(mpd_connection_get_error_message(this->connection));
		throw mpd::MpdErrorException(s);
	}
	return status;
}

struct mpd_song* MPDClient::getActualSong() {
	struct mpd_song *song;
	mpd_command_list_begin(this->connection, true);
	mpd_send_current_song(this->connection);
	mpd_command_list_end(this->connection);
	song = mpd_recv_song(this->connection);
	if(mpd_connection_get_error(connection) != MPD_ERROR_SUCCESS || !mpd_response_finish(this->connection)) {
		std::string s(mpd_connection_get_error_message(this->connection));
		throw mpd::MpdErrorException(s);
	}
	return song;
}

std::string MPDClient::musicServerState() {
	struct mpd_status *status;
	struct mpd_song *song;
	try {
		status = this->getStatus();
		song = this->getActualSong();
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

std::string MPDClient::getTag(const struct mpd_song *song, enum mpd_tag_type type) {
	const char *value;
	std::string valueString("");
	value = mpd_song_get_tag(song, type, 0);
	valueString += value;
	return valueString;
}



void MPDClient::runMainLoop() {
	while(mpd_connection_get_error(this->connection) == MPD_ERROR_SUCCESS) {
		if(mpd_connection_get_error(this->connection) != MPD_ERROR_SUCCESS) {
			std::string s(mpd_connection_get_error_message(this->connection));
			throw MpdErrorException(s);
		}

		for(unsigned j = 0; ; j++) {
			enum mpd_idle idle = mpd_run_idle(this->connection);
			const char *name = mpd_idle_name(idle);

			if(idle == 0 && mpd_connection_get_error(this->connection) != MPD_ERROR_SUCCESS) {
				std::string s(mpd_connection_get_error_message(this->connection));
				throw MpdErrorException(s);
			}

			if(name == NULL) {
				break;
			}

			if(strcmp(name, "player") == 0) {

				struct mpd_status *status = this->getStatus();

				if(mpd_status_get_error(status) != NULL) {
					std::string s(mpd_connection_get_error_message(this->connection));
					throw MpdErrorException(s);
				}

				if(mpd_status_get_state(status) == MPD_STATE_PLAY || mpd_status_get_state(status) == MPD_STATE_PAUSE) {
					this->notifyInfos();
				}
			}
		}
	}
}

void MPDClient::notifyInfos() {
	std::string musicServerState = this->musicServerState();
	notify::Notification notif("mpd", musicServerState.c_str());
	notif.run();
}

struct mpd_connection* MPDClient::getConnection() {
	return this->connection;
}

std::string MPDClient::getIp() {
	return this->ip;
}

unsigned int MPDClient::getPort() {
	return this->port;
}

unsigned int MPDClient::getTimeOut() {
	return this->port;
}

} /* namespace mpd */
