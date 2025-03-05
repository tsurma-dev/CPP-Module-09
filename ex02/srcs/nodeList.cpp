#include "../includes/nodeList.hpp"

nodeList::nodeList() {}
nodeList::~nodeList() {}

nodeList::nodeList(int value) : _value(value) {}

nodeList::nodeList(nodeList& other) : _value(other._value), _chains(other._chains) {}

nodeList& nodeList::operator=(nodeList& other) {
  this->_value = other._value;
  this->_chains = other._chains;
  return (*this);
}
