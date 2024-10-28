#include "../includes/PmergeMe.hpp"
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <cctype>
#include <exception>


static void printIntVector(std::vector<int>& input) {
	for (size_t i = 0; i < input.size(); ++i) {
		std::cout << input[i] << " ";
	}
	std::cout << std::endl;
}

// static void RfillInput(std::vector<int>& input, size_t amount) {
// 	input.empty();
// 	input.reserve(amount);
// 	for (size_t i = 0; i < amount; ++i)
// 		input.push_back(rand());
// }

static void printError(std::string message) {
	std::cerr << "Error: " << message << std::endl;
}

static void argToInput(std::vector<int>& input, char** argv) {

	size_t i = -1;
	while (argv[1][++i] != '\0') {
		 if (!std::isdigit(argv[1][i]) && !std::isspace(argv[1][i])) {
			throw std::invalid_argument("Input has to only containe digits and whitespaces.");
		 }
	}

	char* token = std::strtok(argv[1], " ");
	while (token != NULL) {
		input.push_back(std::atoi(token));
		token = std::strtok(NULL, " ");
	}

	if (input.size() <= 2) {
		throw std::length_error("Too few elements to sort.");
	}
	for (std::vector<int>::iterator it = input.begin(); it != input.end(); ++it) {
		if (*it < 0)
			throw std::range_error("Numbers are not allowed to be negative.");
		}
}

int main(int argc, char**argv) {
	std::vector<int> input;
	std::clock_t VecStart, VecEnd, ListStart, ListEnd;
	double ListDuration, VecDuration;

	if (argc != 2) {
		printError("Please give a valid sequence in a single Argument");
		return (1);
	}
	try
	{
		argToInput(input, argv);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}

	// RfillInput(input, 100000);
	PmergeMe a(input);
	VecStart = std::clock();
	a.FordJohnsonSortVec();
	VecEnd = std::clock();

	ListStart = std::clock();
	a.FordJohnsonSortList();
	ListEnd = std::clock();

	VecDuration = 1000.0 * (VecEnd - VecStart) / CLOCKS_PER_SEC;
	ListDuration = 1000.0 * (ListEnd - ListStart) / CLOCKS_PER_SEC;
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
