#include "../includes/node.hpp"

node::node() {}
node::~node() {}

node::node(int value) : _value(value) {}

node::node(node& other) : _value(other._value), _chains(other._chains) {}

node& node::operator=(node& other) {
  this->_value = other._value;
  this->_chains = other._chains;
  return (*this);
}
