#include <iostream>
#include <fstream>
#include <map>
#include <limits>
#include <sstream>
#include <iomanip>
#include <algorithm>


std::string reformatDate(int date) {
	std::ostringstream formattedDate;
	int year = date / 10000;
	int month = (date / 100) % 100;
	int day = date % 100;

	formattedDate << year << "-" << std::setw(2) << std::setfill('0') << month << "-" << std::setw(2) << std::setfill('0') << day;
	return formattedDate.str();

}

void printMap(const std::map<int, float>& database) {
	std::map<int, float>::const_iterator it;
	for (it = database.begin(); it != database.end(); ++it) {
		std::cout << it->first << ": " << it->second << std::endl;
	}
}

bool leapYearCheck(int year) {
  return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

bool valiDate(int date) {
	int year = date / 10000;
	int month = (date / 100) % 100;
	int day = date % 100;
	int daysOfMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (month < 1 || month > 12)
		return (false);
	if (leapYearCheck(year) == true)
		daysOfMonth[1] = 29;
	if (day < 1 || day > daysOfMonth[month - 1])
		return (false);
	return (true);
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Please specify an input file." << std::endl;
    return (0);
  }
	std::ifstream in(argv[1]);
  if (in.is_open() == false) {
    std::cerr << "Cannot open input file. Please check if it exists." << std::endl;
    return (1);
  }
	std::ifstream data("data.csv");
  if (data.is_open() == false) {
    std::cerr << "Cannot open database. Please check if it exists." << std::endl;
    return (1);
  }
	std::map<int, float> database;
	std::string line;
	float floatstore;
	int		intstore;
	std::map<int, float>::iterator it;
	while (getline(data, line)) {


    if (line.find(',') != line.npos)
    floatstore = atof(line.c_str() + line.find(',') + 1);
    else {
      std::cerr << "Error: bad data => " << line << "\n";
      continue;
    }
    line.erase(std::remove(line.begin(), line.end(), '-'), line.begin() + line.find(','));
    database[atoi(line.c_str())] = floatstore;

  }
	while (getline(in, line)) {
		line.erase(std::remove(line.begin(), line.begin() + line.find('|'), '-'), line.begin() + line.find('|'));
		if (line.find('|') != line.npos)
			floatstore = atof(line.c_str() + line.find('|') + 1);
		intstore = atoi(line.c_str());
		if (intstore == 0)
			continue;
		if (valiDate(intstore) == false) {
			std::cerr << "Error: bad input => " << reformatDate(intstore) << "\n";
			continue;
		}
		else if (intstore < database.begin()->first)
			it = database.begin();
		else
			it = --database.lower_bound(intstore);
		if (floatstore > 1000)
			std::cerr << "Error: too large a number" << "\n";
		else if (floatstore < 0 || it->second < 0)
			std::cerr << "Error: negative number" << "\n";
		else {
      std::cout << std::fixed << std::setprecision(3);
			std::cout << reformatDate(intstore) << " => " << floatstore << " => " << floatstore * it->second << "\n";
    }
  }
}
