#ifndef NODE_HPP_
#define NODE_HPP_

#include <vector>

class node {
public:
	int					_value;
	std::vector<node*>	_chains;
	node(int value) : _value(value) {};
	~node();
private:
	node();
};

#endif
