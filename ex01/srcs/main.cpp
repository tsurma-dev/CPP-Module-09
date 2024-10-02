#include <iostream>
#include <stack>
#include <algorithm>

int main(int argc, char* argv[]) {

	if (argc != 2) {
		std::cout << "Please start this program with one argument" << std::endl;
		return (0);
	}
	std::stack<int> stack;
	std::string input = argv[1];
	int hold;
	for (std::string::iterator it = input.begin(); it != input.end(); ++it) {
		if (isdigit(*it)) {
			stack.push(*it - '0');
			continue;
		}
		if ((*it == '+' || *it == '-' || *it == '*' || *it == '/') && stack.size() < 2) {
			std::cout << "Error" << std::endl;
			return (0);
		}
		switch (*it)
		{
		case '+':
			hold = stack.top();
			stack.pop();
			stack.top() += hold;
			break;
		case '-':
			hold = stack.top();
			stack.pop();
			stack.top() -= hold;
			break;
		case '/':
			hold = stack.top();
			stack.pop();
			stack.top() /= hold;
			break;
		case '*':
			hold = stack.top();
			stack.pop();
			stack.top() *= hold;
			break;
		default:
			break;
		}
	}
	if (stack.size() != 1) {
		std::cout << "Error" << std::endl;
		return (0);
	}
	std::cout << stack.top() << std::endl;
	return (0);
}
