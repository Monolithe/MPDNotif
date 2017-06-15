/*
 * Notification.cpp
 *
 *  Created on: 8 juin 2017
 *      Author: maxime
 */

#include "Notification.h"

namespace notify {

Notification::Notification(const char *name, const char *songInfos) {
	notify_init("MPDNotif");
	this->notification = notify_notification_new(name, songInfos, NULL);
	notify_notification_set_timeout(notification, 2000);
}

Notification::~Notification() {
	g_object_unref(G_OBJECT(this->notification));
	if(notify_is_initted()) {
		notify_uninit();
	}
}

void Notification::run() {
	if(!notify_notification_show(notification, NULL)) {
		throw notify::NotificationException("Error : null notification");
	}
}

} /* namespace notify */
