/*
 * main.cpp
 *
 *  Created on: 6 juin 2017
 *      Author: Monolithe
 */

#include <iostream>
#include <memory>
#include <mpd/connection.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>


#include "MPDClient.h"
#include "GClient.h"
#include "MpdErrorException.hpp"
#include "Notification.h"
#include "NotificationException.hpp"

#define DEFAULT_PORT 6600
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_TIMEOUT 3000

using namespace mpd;

static void showHelp() {
	std::cout << "MPDNotif is a notification client for mpd\nUsage MPDnotif [-d] [-c IP] [-p PORT] [-t TIMEOUT]\nOptions :\n-d : set daemon mode\n-c <IP> : set mpd server host\n-p <PORT> : set mpd server port\n-t <TIMEOUT> : set connection timeout\n-h : show this help\n";
}

pid_t proc_find(const char* name, pid_t actPid) {
    DIR* dir;
    struct dirent* ent;
    char* endptr;
    char buf[512];

    if (!(dir = opendir("/proc"))) {
        std::cerr << "can't open /proc" << std::endl;
        return -1;
    }

    while((ent = readdir(dir)) != NULL) {
        /* if endptr is not a null character, the directory is not
         * entirely numeric, so ignore it */
        long lpid = strtol(ent->d_name, &endptr, 10);

        if (*endptr != '\0') {
            continue;
        }

        if(lpid == actPid) {
        	continue;
        }

        /* try to open the cmdline file */
        snprintf(buf, sizeof(buf), "/proc/%ld/cmdline", lpid);
        FILE* fp = fopen(buf, "r");

        if (fp) {
            if (fgets(buf, sizeof(buf), fp) != NULL) {
                /* check the first token in the file, the program name */
                char* first = strtok(buf, " ");
                if (!strcmp(first, name)) {
                    fclose(fp);
                    closedir(dir);
                    return (pid_t)lpid;
                }
            }
            fclose(fp);
        }

    }

    closedir(dir);
    return -1;
}


static void daemonize(char *progName) {
    pid_t pid = proc_find(progName, getpid());
    if(pid != -1) {
    	std::cerr << "Error : process already exist at " << pid << " pid" << std::endl;
    	exit(EXIT_FAILURE);
    }
    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);
    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--) {
        close (x);
    }
}


int main(int argc, char *argv[]) {
	int opt;
	std::string ip("");
	unsigned int port = 0;
	unsigned int timeout = 0;
	bool daemonMode = false;

	while((opt = getopt(argc, argv, "c:p:t:h:d")) != -1) {
		switch(opt) {
			case 'c':
				ip += optarg;
				break;
			case 'p':
				port = std::strtol(optarg, NULL, 10);
				break;
			case 't':
				timeout = std::strtol(optarg, NULL, 10);
				break;
			case 'h':
				showHelp();
				return 0;
				break;
			case 'd':
				daemonMode = true;
				break;
		}
	}

	if(ip.empty()) {
		ip += DEFAULT_IP;
	}

	if(port == 0) {
		port = DEFAULT_PORT;
	}

	if(timeout == 0) {
		timeout = DEFAULT_TIMEOUT;
	}

	if(daemonMode) {
		daemonize(argv[0]);
	}

	int ret = 0;
	MPDClient client(ip, port, timeout);
	GClient gclient(&client);
	try {
		gclient.startConnection();
		gclient.runMainLoop();
	}
	catch(const MpdErrorException &ex) {
		if(daemonMode) {
			notify::Notification notif("mpd", ex.what());
			notif.run();
		}
		else {
			std::cerr << ex.what() << std::endl;
		}
		ret = EXIT_FAILURE;
	}
	catch(const notify::NotificationException &ex) {
		if(daemonMode) {
			notify::Notification notif("notification", ex.what());
			notif.run();
		}
		else {
			std::cerr << ex.what() << std::endl;
		}
		ret = EXIT_FAILURE;
	}
	return ret;
}
