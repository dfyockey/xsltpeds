/*
 * Procf.hpp
 *
 *  Created on: Oct 28, 2020
 *      Author: David Yockey
 */

#ifndef PROCF_HPP_
#define PROCF_HPP_

#include "CollectionProcessor.hpp"

class Procf : public CollectionProcessor {
public:
	Procf (string xslfile, string datestamp) : CollectionProcessor (xslfile, datestamp) {};
	void init(){};
	void proc(bfs::path xmlfilepath);
	void fnit(){};
};


#endif /* PROCF_HPP_ */
