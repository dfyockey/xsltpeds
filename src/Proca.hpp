/*
 * Proca.hpp
 *
 *  Created on: Oct 28, 2020
 *      Author: David Yockey
 */

#ifndef PROCA_HPP_
#define PROCA_HPP_

#include "CollectionProcessor.hpp"

class Proca : public CollectionProcessor {
public:
	Proca (string datestamp) : CollectionProcessor (datestamp) {};
	void proc(bfs::path xmlfilepath);
	void fnit();
};

#endif /* PROCA_HPP_ */
