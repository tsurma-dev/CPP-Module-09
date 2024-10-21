#include "pMergeMe.hpp"


int main(void) {
	std::vector<int> input = {5,6,2,1,9,8,5,3};
	pMergeMe a(input);
	a.FordJohnsonSortList();
	a.printNodeList();
	return (0);
}
