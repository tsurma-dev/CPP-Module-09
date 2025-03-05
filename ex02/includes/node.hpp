#ifndef NODE_HPP_
#define NODE_HPP_

#include <vector>

class node {
public:
	int					_value;
	std::vector<node*>	_chains;

	node(int value);
  node(node& other);
  node& operator=(node& other);
	~node();
private:
	node();
};

#endif
