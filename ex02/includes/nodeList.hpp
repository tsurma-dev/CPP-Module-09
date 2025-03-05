#ifndef NODELIST_HPP_
#define NODELIST_HPP_

#include <list>

class nodeList {
public:
	int					_value;
	std::list<nodeList*>	_chains;

	nodeList(int value);
  nodeList(nodeList& other);
  nodeList& operator=(nodeList& other);
	~nodeList();
private:
	nodeList();
};

#endif
