#include "../includes/pMergeMe.hpp"
#include <stdlib.h>

int main(void) {
	std::vector<int> input;
	for (int i = 0; i < 3000; ++i)
		input.push_back(rand());

	pMergeMe a(input);
	a.FordJohnsonSortVec();
	a.FordJohnsonSortList();
	// a.printNodeVector();

	// for (std::vector<node*>::iterator it = a.ChainVec.begin(); it + 1 != a.ChainVec.end(); ++it) {
	// 	if ((*it)->_value > (*(it + 1))->_value)
	// 		std::cout << "WROOOONG" << std::endl;
	// }

	std::list<nodeList*>::iterator listit = a.ChainList.begin();
	std::list<nodeList*>::iterator listittwo(listit);
	listittwo++;
	while (listittwo != a.ChainList.end()) {
		if ((*listit)->_value > (*listittwo)->_value)
			std::cout << "WROOONG" << "\n";
			// std::cout << "\n" << (*listit)->_value << " " << (*listittwo)->_value << "\n";
		listit++;
		listittwo++;
	}

	return (0);
}
