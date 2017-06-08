/*
 * NotificationException.hpp
 *
 *  Created on: 8 juin 2017
 *      Author: maxime
 */

#ifndef NOTIFICATIONEXCEPTION_HPP_
#define NOTIFICATIONEXCEPTION_HPP_

namespace notify {

class NotificationException : public std::exception {
public:
	NotificationException(std::string const& phrase="") throw()
    	:m_phrase(phrase) {}

	virtual const char* what() const throw() {
         return m_phrase.c_str();
    }

    virtual ~NotificationException() throw() {}

private:
    std::string m_phrase;            //Description de l'erreur
};

} /* namespace notify */


#endif /* NOTIFICATIONEXCEPTION_HPP_ */
