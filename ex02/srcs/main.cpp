#include "../includes/PmergeMe.hpp"
#include <stdlib.h>
#include <iomanip>
#include <sys/time.h>

static void printIntVector(std::vector<int>& input) {
	for (size_t i = 0; i < input.size(); ++i) {
		std::cout << input[i] << " ";
	}
	std::cout << std::endl;
}

static void RfillInput(std::vector<int>& input, size_t amount) {
	input.empty();
	input.reserve(amount);
	for (size_t i = 0; i < amount; ++i)
		input.push_back(rand());

}

int main(void) {
	std::vector<int> input;
	timeval VecBegin, VecEnd, ListBegin, ListEnd;
	double VecDuration = 0, ListDuration = 0;


	RfillInput(input, 1000);
	PmergeMe a(input);
	gettimeofday(&VecBegin, 0);
	a.FordJohnsonSortVec();
	gettimeofday(&VecEnd, 0);

	gettimeofday(&ListBegin, 0);
	a.FordJohnsonSortList();
	gettimeofday(&ListEnd, 0);

	VecDuration = (VecEnd.tv_sec - VecBegin.tv_sec) * 1000 + (VecEnd.tv_usec - VecBegin.tv_usec) * 1e-3;
	ListDuration = (ListEnd.tv_sec - ListBegin.tv_sec) * 1000 + (ListEnd.tv_usec - ListBegin.tv_usec) * 1e-3;
	std::cout << std::fixed << std::setprecision(4);
	std::cout << "before: ";
	printIntVector(input);

	std::cout << "After: ";
	a.printNodeVector();
	std::cout << "Time to process a range of " << a.ChainVec.size() << " with std::vector : " << VecDuration << " ms\n";
	std::cout << "Time to process a range of " << a.ChainList.size() << " with std::list : " << ListDuration << " ms\n";

	// for (std::vector<node*>::iterator it = a.ChainVec.begin(); it + 1 != a.ChainVec.end(); ++it) {
	// 	if ((*it)->_value > (*(it + 1))->_value)
	// 		std::cout << "WROOOONG" << std::endl;
	// }

	// std::list<nodeList*>::iterator listit = a.ChainList.begin();
	// std::list<nodeList*>::iterator listittwo(listit);
	// listittwo++;
	// while (listittwo != a.ChainList.end()) {
	// 	if ((*listit)->_value > (*listittwo)->_value)
	// 		std::cout << "WROOONG" << "\n";
	// 		// std::cout << "\n" << (*listit)->_value << " " << (*listittwo)->_value << "\n";
	// 	listit++;
	// 	listittwo++;
	// }

	return (0);
}
