#include <iostream>
#include <vector>
#include <string>

#include "row.hpp"
#include "Character.hpp"

/*Friend function*/
std::ostream& operator<<(std::ostream& os, Character ch)
{
	os << ch._name;
	return os;
}
/*Constructor & destructor*/
Character::Character(csv::Row row) : _next_in_line(true), grade(0), _name(row["Name"])
{
	for(int i = 1; i < row.length(); i++)
	{	 
		_ans.push_back(stoi(row[i]));
	}
}

Character::~Character()
{}

/*Method*/
int Character::update_grade(std::vector<int> user_ans)
{
	std::vector<int> diff_ans;

	std::transform(_ans.begin(), _ans.end(), user_ans.begin(), std::back_inserter(diff_ans),
	[](int elem1, int elem2)
	{
		return abs(elem1-elem2);
	});
	
	return std::accumulate(diff_ans.begin(), diff_ans.end(), 0);
}
