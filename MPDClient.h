/*
 * MPDClient.h
 *
 *  Created on: 6 juin 2017
 *      Author: Monolithe
 *      MPDClient : class : Connect to the server
 */

#ifndef MPDCLIENT_H_
#define MPDCLIENT_H_

#include <mpd/client.h>
#include <mpd/status.h>
#include <mpd/entity.h>
#include <mpd/search.h>
#include <mpd/tag.h>
#include <mpd/message.h>

#include <string>
#include <string.h>

#include "MpdErrorException.hpp"
#include "Notification.h"


namespace mpd {

class MPDClient {
public:
	MPDClient(std::string ip, unsigned int port, unsigned int timeout);
	virtual ~MPDClient();
	void initConnection();
	void sendError();
	struct mpd_status* getStatus();
	struct mpd_song* getActualSong();
	std::string musicServerState();
	static std::string getTag(const struct mpd_song *song, enum mpd_tag_type type);
	void runMainLoop();
	void notifyInfos();
	struct mpd_connection* getConnection();
	std::string getIp();
	unsigned int getPort();
	unsigned int getTimeOut();

private:
	std::string ip;
	struct mpd_connection *connection;
	unsigned int port;
	unsigned int timeout;

};

} /* namespace mpd */

#endif /* MPDCLIENT_H_ */
