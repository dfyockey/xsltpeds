/*
 * Proca.hpp
 *
 *  Created on: Oct 28, 2020
 *      Author: David Yockey
 */

#ifndef PROCA_HPP_
#define PROCA_HPP_

#include <boost/filesystem.hpp>
#include <string>
#include "CollectionProcessor.hpp"

namespace bfs = boost::filesystem;

class Proca : public CollectionProcessor {
public:
	void init(){}
	void proc(string datestamp, string xmlfilepath, string newdir);
	void fint();
private:
	string newdir;
};

#endif /* PROCA_HPP_ */
