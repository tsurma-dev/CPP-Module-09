#ifndef PMERGEME_HPP_
#define PMERGEME_HPP_

#include <vector>

class node {
public:
	int					_value;
	std::vector<node*>	_chains;
	node(int value) : _value(value) {};
	node();
	~node();
};


node::node() {}
node::~node() {}


#endif