#ifndef PMERGEME_HPP_
#define PMERGEME_HPP_

#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include "node.hpp"
#include "nodeList.hpp"


class pMergeMe
{
private:
	void generateJacobsthalSequenceVec();
	void generateJacobsthalSequenceList();
	void buildTreeVec(node*& reserve);
	void buildTreeList(nodeList*& reserve);
	void mergeInsertVec(node*& reserve);
	void mergeInsertList(nodeList*& reserve);
	void insertionVec(node*& obj, std::vector<node*>::iterator end);
	void insertionList(nodeList*& obj, std::list<nodeList*>::iterator end);
public:
	void printNodeVector();
	void printNodeList();
	pMergeMe(std::vector<int> input);
	std::vector<node*> ChainVec;
	std::vector<node*> backupVec;
	std::vector<int> jacobsthalVec;

	std::list<nodeList*> ChainList;
	std::list<nodeList*> backupList;
	std::list<int> jacobsthalList;
	void FordJohnsonSortVec();
	void FordJohnsonSortList();
	~pMergeMe();
};


#endif
