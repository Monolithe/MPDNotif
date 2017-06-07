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
