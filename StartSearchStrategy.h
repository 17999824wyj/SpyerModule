#pragma once
#include "Strategy.h"
#include <string>

class StartSearchStrategy : public Strategy
{
private:
	std::string toSearch;
public:
	StartSearchStrategy(std::string toSearch);
	~StartSearchStrategy();
	void execute() override;
};