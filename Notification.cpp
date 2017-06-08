/*
 * Notification.cpp
 *
 *  Created on: 8 juin 2017
 *      Author: maxime
 */

#include "Notification.h"

namespace notify {

Notification::Notification(const char *songInfos) {
	notify_init("MPDNotif");
	this->notification = notify_notification_new("mpd", songInfos, NULL);
	notify_notification_set_timeout(notification, 2000);
	if(!notify_notification_show(notification, NULL)) {
		throw notify::NotificationException("Error : null n	otification");
	}

}

Notification::~Notification() {
	g_object_unref(G_OBJECT(this->notification));
	if(notify_is_initted()) {
		notify_uninit();
	}
}
} /* namespace notify */
