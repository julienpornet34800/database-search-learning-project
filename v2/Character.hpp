#include <iostream>
#include <vector>

#include "row.hpp"

#ifndef CHARACTER_H
#define CHARACTER_H

class Character 
{
	friend std::ostream& operator<<(std::ostream& os, Character ch);

	public:
		Character(csv::Row row);
		~Character();

		int update_grade(std::vector<int> user_ans);

	private:
		bool _next_in_line;
		int grade;
		std::string _name;
		std::vector<int> _ans;
};

#endif