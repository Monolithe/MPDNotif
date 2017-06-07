/*
 * GClient.h
 *
 *  Created on: 7 juin 2017
 *      Author: maxime
 */

#ifndef GCLIENT_H_
#define GCLIENT_H_

#include <iostream>

#include "MPDClient.h"
#include "MpdErrorException.hpp"

namespace mpd {

class GClient {
public:
	GClient(MPDClient *client);
	virtual ~GClient();
	void startConnection();
	std::string musicServerState();
	static std::string getTag(const struct mpd_song *song, enum mpd_tag_type type);
	MPDClient* getClient();

private:
	MPDClient *client;
};

} /* namespace mpd */

#endif /* GCLIENT_H_ */
