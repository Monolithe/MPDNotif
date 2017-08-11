/*
 * MpdErrorException.hpp
 *
 *  Created on: 6 juin 2017
 *      Author: maxime
 */

#ifndef MPDERROREXCEPTION_HPP_
#define MPDERROREXCEPTION_HPP_

#include <exception>
#include <string>

namespace mpd {

class MpdErrorException : public std::exception {
public:
	MpdErrorException(std::string const& phrase="") throw()
    	:m_phrase(phrase) {}

	virtual const char* what() const throw() {
         return m_phrase.c_str();
    }

    virtual ~MpdErrorException() throw() {}

private:
    std::string m_phrase;            //Description de l'erreur
};

} /* namespace mpd */

#endif /* MPDERROREXCEPTION_HPP_ */
