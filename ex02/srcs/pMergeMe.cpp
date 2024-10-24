#include "../includes/pMergeMe.hpp"

void pMergeMe::generateJacobsthalSequenceVec() {
	this->jacobsthalVec.push_back(0);
	this->jacobsthalVec.push_back(1);
	int j2 = 0, j1 = 1;

	while (true) {
		size_t next_value = j1 + 2 * j2;
		if (next_value > this->ChainVec.size()) {
			break;
		}
		this->jacobsthalVec.push_back(next_value);
		j2 = j1;
		j1 = next_value;
	}
	this->jacobsthalVec.erase(this->jacobsthalVec.begin());
	this->jacobsthalVec.erase(this->jacobsthalVec.begin());
}

void pMergeMe::generateJacobsthalSequenceList() {
	this->jacobsthalList.push_back(0);
	this->jacobsthalList.push_back(1);
	int j2 = 0, j1 = 1;

	while (true) {
		size_t next_value = j1 + 2 * j2;
		if (next_value > this->ChainList.size()) {
			break;
		}
		this->jacobsthalList.push_back(next_value);
		j2 = j1;
		j1 = next_value;
	}
	this->jacobsthalList.pop_front();
	this->jacobsthalList.pop_front();
}

void pMergeMe::printNodeVector() {
	for (size_t i = 0; i < this->ChainVec.size(); ++i) {
		std::cout << this->ChainVec[i]->_value << " ";
	}
	std::cout << std::endl;
}

void pMergeMe::printNodeList() {
	for (std::list<nodeList*>::iterator it = this->ChainList.begin(); it != this->ChainList.end(); ++it) {
		std::cout << (*it)->_value << " ";
	}
	std::cout << std::endl;
}

	static bool compareNode(const node* a, const node* b) {
        return a->_value < b->_value;
    }

	static bool compareNodeList(const nodeList* a, const nodeList* b) {
        return a->_value < b->_value;
    }

void pMergeMe::insertionVec(node*& obj, std::vector<node*>::iterator end) {
    // Use the functor to perform the comparison within std::lower_bound
    std::vector<node*>::iterator it = std::lower_bound(
        this->ChainVec.begin(),
        end,
        obj,
        compareNode  // Use functor instead of lambda
    );

    // Insert the pointer to the given object at the correct position
    this->ChainVec.insert(it, obj);
}


void pMergeMe::insertionList(nodeList*& obj, std::list<nodeList*>::iterator end) {
    // Use the functor to perform the comparison within std::lower_bound
    std::list<nodeList*>::iterator it = std::lower_bound(
        this->ChainList.begin(),
        end,
        obj,
        compareNodeList
    );
	// Insert the pointer to the given object
	this->ChainList.insert(it, obj);
}

pMergeMe::pMergeMe(std::vector<int> input) {
	for (std::vector<int>::iterator it = input.begin(); it != input.end(); ++it) {
		this->ChainVec.push_back(new node(*it));
	}
	for (std::vector<int>::iterator it = input.begin(); it != input.end(); ++it) {
		this->ChainList.push_back(new nodeList(*it));
	}
	generateJacobsthalSequenceVec();
	generateJacobsthalSequenceList();

	this->backupVec = this->ChainVec;
	this->backupList = this->ChainList;
}

void pMergeMe::buildTreeVec(node*& reserve) {
	for (std::vector<node*>::iterator it = this->ChainVec.begin(); it != this->ChainVec.end();) {
		if (it + 1 == this->ChainVec.end()) {
			reserve = *it;
			it = this->ChainVec.erase(it);
			return;
		}
		if ((*it)->_value > (*(it + 1))->_value) {
			(*it)->_chains.push_back((*(it + 1)));
			this->ChainVec.erase(it + 1);
			++it;
		} else {
			(*(it + 1))->_chains.push_back((*it));
			it = this->ChainVec.erase(it);
			++it;
		}
	}
}

void pMergeMe::buildTreeList(nodeList*& reserve) {
	std::list<nodeList*>::iterator itj;
	for (std::list<nodeList*>::iterator it = this->ChainList.begin(); it != this->ChainList.end();) {
		itj = it;
		++itj;
		if (itj == this->ChainList.end()) {
			reserve = *it;
			it = this->ChainList.erase(it);
			return;
		}
		if ((*it)->_value > (*(itj))->_value) {
			(*it)->_chains.push_back((*(itj)));
			this->ChainList.erase(itj);
			++it;
		} else {
			(*(itj))->_chains.push_back((*it));
			it = this->ChainList.erase(it);
			++it;
		}
	}
}

void pMergeMe::mergeInsertVec(node*& reserve) {
	//copy the main chain to be able to find the correct pointers during sorting and inserting
	std::vector<node*> toSortChain(this->ChainVec);

	//preemptively insert the most recent pairing of the first element at the start.
	this->ChainVec.insert(this->ChainVec.begin(), toSortChain[0]->_chains.back());

	size_t jacobsStore = 1;
	std::vector<node*>::iterator terminus;
	node *obj;

	// go through the jacobsthal sequence until it's bigger than the initial chain
	// i = index into the Jacobsthal sequence
	// j = jacobsthal number counting down to the previous one, indexing into the toSortChain
	// terminus = the position of the object that j references in the main chain
	// obj = the last added element of terminus
	for (size_t i = 1; i < this->jacobsthalVec.size() && this->jacobsthalVec[i] <= static_cast<int>(toSortChain.size()); ++i) {
		jacobsStore = this->jacobsthalVec[i];
		for (size_t j = this->jacobsthalVec[i] - 1; j > static_cast<size_t>(this->jacobsthalVec[i - 1] - 1); --j) {
			terminus = std::find(this->ChainVec.begin(), this->ChainVec.end(), toSortChain[j]);
			obj = toSortChain[j]->_chains.back();
			insertionVec(obj, terminus);
		}
	}

	// if there was a node in reserve, insert it
	if (reserve != NULL)
		insertionVec(reserve, this->ChainVec.end());

	// sort what was larger than the last jacobsthal position from back to front
	for (size_t i = toSortChain.size() - 1; i > jacobsStore - 1; --i) {
		terminus = std::find(this->ChainVec.begin(), this->ChainVec.end(), toSortChain[i]);
		obj = toSortChain[i]->_chains.back();
		insertionVec(obj, terminus);
	}

	//pop every node that was inserted
	for (std::vector<node*>::iterator it = toSortChain.begin(); it != toSortChain.end(); ++it) {
		(*it)->_chains.pop_back();
	}
}

void pMergeMe::mergeInsertList(nodeList*& reserve) {
	//copy the main chain to be able to find the correct pointers during sorting and inserting
	std::list<nodeList*> toSortChain(this->ChainList);

	//preemptively insert the most recent pairing of the first element at the start.
	this->ChainList.insert(this->ChainList.begin(), (*toSortChain.begin())->_chains.back());

	size_t jacobsStore = 1;
	std::list<nodeList*>::iterator terminus;
	std::list<int>::iterator temp;
	std::list<nodeList*>::iterator tempListIt;

	nodeList *obj;
	// go through the jacobsthal sequence until it's bigger than the initial chain
	// i = index into the Jacobsthal sequence
	// j = jacobsthal number counting down to the previous one, indexing into the toSortChain
	// terminus = the position of the object that j references in the main chain
	// obj = the last added element of terminus
	


	for (size_t i = 1; i < this->jacobsthalList.size(); ++i) {
		temp = this->jacobsthalList.begin();
		std::advance(temp, i);
		if (*temp > static_cast<int>(toSortChain.size()))
			break;
		for (size_t j = *temp - 1; j > jacobsStore ; --j) {
			tempListIt = toSortChain.begin();
			std::advance(tempListIt, j);
			terminus = std::find(this->ChainList.begin(), this->ChainList.end(), *tempListIt);
			obj = (*tempListIt)->_chains.back();
			insertionList(obj, terminus);
		}
			jacobsStore = *temp;
	}

	// if there was a node in reserve, insert it
	if (reserve != NULL)
		insertionList(reserve, this->ChainList.end());

	// sort what was larger than the last jacobsthal position from back to front
	
	tempListIt = toSortChain.end();
	--tempListIt;
	for (size_t i = toSortChain.size() - jacobsStore; i > 0; --i) {
		terminus = std::find(this->ChainList.begin(), this->ChainList.end(), *tempListIt);
		obj = (*tempListIt)->_chains.back();
		insertionList(obj, terminus);
		--tempListIt;
	}
	//pop every node that was inserted
	for (std::list<nodeList*>::iterator it = toSortChain.begin(); it != toSortChain.end(); ++it) {
		(*it)->_chains.pop_back();
	}
}

void pMergeMe::FordJohnsonSortVec() {
	node* reserve = NULL;

	if (this->ChainVec.size() == 1)
		return;
	buildTreeVec(reserve);
	FordJohnsonSortVec();
	mergeInsertVec(reserve);

}

void pMergeMe::FordJohnsonSortList() {
	nodeList* reserve = NULL;

	if (this->ChainList.size() == 1)
		return;
	buildTreeList(reserve);
	FordJohnsonSortList();
	mergeInsertList(reserve);
}

pMergeMe::~pMergeMe() {
  for (std::vector<node *>::iterator it = this->backupVec.begin();
       it != backupVec.end(); ++it) {
    if (*it != NULL) delete (*it);
  }
  for (std::list<nodeList *>::iterator it = this->backupList.begin();
       it != backupList.end(); ++it) {
    if (*it != NULL) delete (*it);
  }
}
