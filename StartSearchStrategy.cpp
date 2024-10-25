#include "StartSearchStrategy.h"
#include <iostream>
#include <cstdlib>

StartSearchStrategy::StartSearchStrategy(std::string toSearch)
{
	this->toSearch = toSearch;
}

StartSearchStrategy::~StartSearchStrategy()
{
	if (!this->toSearch.empty()) {
		this->toSearch.clear();
	}
}

void StartSearchStrategy::execute()
{
	std::string command = "start https://www.baidu.com/s?wd=" + this->toSearch;
	system(command.c_str());
}