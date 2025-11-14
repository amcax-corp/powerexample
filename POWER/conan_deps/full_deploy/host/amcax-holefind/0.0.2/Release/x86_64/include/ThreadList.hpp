#pragma once
#include <string>
#include <unordered_map>

struct Thread;

class ThreadList
{
public:
	ThreadList() = default;
	void Init();
	std::string FindThread(Thread& message);
	std::pair<double, std::string> FindIter(Thread& message);
	void AddThread(Thread key, std::string standard);
	void ChangeThread(Thread key, std::string stanard);
	
private:
	std::unordered_map<std::string,    //diameter
		               std::vector<std::pair<double ,std::string>>> data;
};

