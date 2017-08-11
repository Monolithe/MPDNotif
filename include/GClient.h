/*
 * GClient.h
 *
 *  Created on: 7 juin 2017
 *      Author: Monolithe
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
	void runMainLoop();
	MPDClient* getClient();

private:
	MPDClient *client;
	bool connectionStarted;
};

} /* namespace mpd */

#endif /* GCLIENT_H_ */
