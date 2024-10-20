#include "pMergeMe.hpp"
#include <iostream>
#include <algorithm>

std::vector<int> generate_jacobsthal_sequence(int max_value) {
	std::vector<int> jacobsthal = {0, 1};
	int j2 = 0, j1 = 1;
	while (true) {
		int next_value = j1 + 2 * j2;
		if (next_value > max_value) {
			break;
		}
		jacobsthal.push_back(next_value);
		j2 = j1;
		j1 = next_value;
	}
	jacobsthal.erase(jacobsthal.begin());
	jacobsthal.erase(jacobsthal.begin());
	return jacobsthal;
}

void printNodeVector(const std::vector<node*>& chains) {
	for (int i = 0; i < chains.size(); ++i) {
		std::cout << chains[i]->_value << " ";
	}
	std::cout << std::endl;
}

void printIntVector(const std::vector<int>& vec) {
	for (int i = 0; i < vec.size(); ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

void printNodeChain(const node& obj) {
	std::cout << "Value: " << obj._value << "\n";
	for (int i = 0; i > obj._chains.size(); ++i) {
		std::cout << obj._chains[i]->_value << " ";
	}
	std::cout << std::endl;
}

void insertInSortedOrder(std::vector<node*>& vec, node* obj, std::vector<node*>::iterator start, std::vector<node*>::iterator end) {

	// Find the correct position to insert the pointer to the object within the given range
	std::vector<node*>::iterator it = std::lower_bound(start, end, obj, [](const node* a, const node* b) {
		return a->_value < b->_value; // Compare based on _value
	});

	// Insert the pointer to the given object
	vec.insert(it, obj);
}

void buildTree(std::vector<node*>& chains, node*& reserve) {
	for (std::vector<node*>::iterator it = chains.begin(); it != chains.end();) {
		if (it + 1 == chains.end()) {
			reserve = *it;
			it = chains.erase(it);
			return;
		}
		if ((*it)->_value > (*(it + 1))->_value) {
			(*it)->_chains.push_back((*(it + 1)));
			chains.erase(it + 1);
			++it;
		} else {
			(*(it + 1))->_chains.push_back((*it));
			it = chains.erase(it);
		}
	}
}

void mergeInsert(std::vector<node*>& chains, std::vector<int>& jacobsthal, node*& reserve) {
	//copy the main chain to be able to find the correct pointers during sorting and inserting
	std::vector<node*> toSortChain(chains);


	//preemptively insert the most recent pairing of the first element at the start.
	chains.insert(chains.begin(), toSortChain[0]->_chains.back());

	int jacobsStore = 1;
	std::vector<node*>::iterator terminus;
	node *obj;

	// go through the jacobsthal sequence until it's bigger than the initial chain
	// i = index into the Jacobsthal sequence
	// j = jacobsthal number counting down to the previous one, indexing into the toSortChain
	// terminus = the position of the object that j references in the main chain
	// obj = the last added element of terminus
	for (size_t i = 1; i < jacobsthal.size() && jacobsthal[i] <= toSortChain.size(); ++i) {
		jacobsStore = jacobsthal[i];
		for (size_t j = jacobsthal[i] - 1; j > jacobsthal[i - 1] - 1; --j) {
			terminus = std::find(chains.begin(), chains.end(), toSortChain[j]);
			obj = toSortChain[j]->_chains.back();
			insertInSortedOrder(chains, obj, chains.begin(), terminus);
		}
	}

	// if there was a node in reserve, insert it
	if (reserve != nullptr)
		insertInSortedOrder(chains, reserve, chains.begin(), chains.end());

	// sort what was larger than the last jacobsthal position from back to front
	for (size_t i = toSortChain.size() - 1; i > jacobsStore - 1 && i >= 0; --i) {
		terminus = std::find(chains.begin(), chains.end(), toSortChain[i]);
		obj = toSortChain[i]->_chains.back();
		insertInSortedOrder(chains, obj, chains.begin(), terminus);
	} 

	//pop every node that was inserted
	for (std::vector<node*>::iterator it = toSortChain.begin(); it != toSortChain.end(); ++it) {
		(*it)->_chains.pop_back();
	}
}

void FordJohnsonSort(std::vector<node*>& chains, std::vector<int>& jacobsthal) {

	std::cout << "Before chaining: ";
	printNodeVector(chains);
	std::cout << std::endl;

	node* reserve = nullptr;

	if (chains.size() <= 2) {
		if ((*chains.begin())->_value > (*chains.begin() + 1)->_value)
			std::swap(chains[0], chains[1]);
		return ;
	}

	buildTree(chains, reserve);

	std::cout << "Before recursion: ";
	printNodeVector(chains);
	std::cout << std::endl;

	FordJohnsonSort(chains, jacobsthal);

	std::cout << "After recursion: ";
	printNodeVector(chains);
	std::cout << std::endl;

	mergeInsert(chains, jacobsthal, reserve);

	std::cout << "After merge: ";
	printNodeVector(chains);
	std::cout << std::endl;

}

int main() {
	std::vector<node*> chains = {
		new node(10), new node(9), new node(8), new node(7),
		new node(6), new node(5), new node(4), new node(3), new node(2)
	};

	std::vector<node*> store(chains);

	std::vector<int> jacobsthal = generate_jacobsthal_sequence(chains.size());

	FordJohnsonSort(chains, jacobsthal);
	printNodeVector(chains);

	for (std::vector<node*>::iterator it = store.begin(); it != store.end(); it++) {
		delete (*it);
	}
}