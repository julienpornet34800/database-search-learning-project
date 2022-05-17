#include <iostream>
#include <cmath> // for std::sqrt

#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include "row.hpp"

namespace csv
{
	/*Friend operator*/
	template<typename T>
	std::ostream& operator<<(std::ostream& os, std::vector<T> v)
	{
		std::for_each(v.begin(), v.end(),
			[&os](T elem)
			{
				os << "{" << elem << "}" << "\t";
			});

		return os;
	}
		
	std::ostream& operator<<(std::ostream& os, csv::Row row)
	{
		os << row._content;
		return os;
	}

	/*Friend function*/
	std::vector<int> get_answer(Row row)
	{
		std::vector<int> vec;
		
		std::transform(row._content.begin() + 1, row._content.end(), std::back_inserter(vec),
        [&](std::string s) {
            return stoi(s);
        });

		return vec;
	}

	/*Constructor and destructor*/
	Row::Row(std::vector<std::string> header, std::stringstream ssline, char sep) : _header(header)
	{
    	std::string item;
    	size_t count = 0;

    	//convert string line in vector
      	while (std::getline(ssline, item, sep))
      	{	 
      		_content.push_back(item);
      		count++;
      		if (count > _header.size()) throw;
      	}
	}

	Row::~Row()
	{}

	std::string Row::operator[](int pos)
	{
		return _content[pos];
	}

	std::string Row::operator[](std::string header_name)
	{
		size_t pos = 0;
		bool key = false;
		
		for(size_t i = 0; i < _header.size(); i++)
		{	
				if (_header[pos] != header_name && key == false)
					pos++;
				else
					key = true;
		};
		
		if (pos > _header.size())
			throw;
		
		return _content[static_cast<int>(pos)];
	}

}


