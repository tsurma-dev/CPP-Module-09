#ifndef NODELIST_HPP_
#define NODELIST_HPP_

#include <list>

class nodeList {
public:
	int					_value;
	std::list<nodeList*>	_chains;
	nodeList(int value) : _value(value) {};
	nodeList();
	~nodeList();
};

#endif
