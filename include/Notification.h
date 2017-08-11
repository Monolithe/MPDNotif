/*
 * Notification.h
 *
 *  Created on: 8 juin 2017
 *      Author: Monolithe
 */

#ifndef NOTIFICATION_H_
#define NOTIFICATION_H_

#include <libnotify/notify.h>
#include <libnotify/notification.h>
#include <glib.h>
#include <iostream>

#include "NotificationException.hpp"

namespace notify {

class Notification {
public:
	Notification(const char *name, const char *songInfos);
	virtual ~Notification();
	void run();

private:
	NotifyNotification *notification;
};

} /* namespace notify */

#endif /* NOTIFICATION_H_ */
