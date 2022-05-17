#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <unordered_map>

#include "csv_parser.hpp"
#include "row.hpp"

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> v)
{
	std::for_each(v.begin(), v.end(), [&os](T value)
	{
		os << value << std::endl;
	});

	return os;
}

namespace csv
{	
	template<typename T>
	std::ostream& operator<<(std::ostream& os, std::vector<T> v)
	{
		std::for_each(v.begin(), v.end(),
			[&os](T elem)
			{
				os << elem << std::endl;
			});

		return os;
	}

	std::ostream& operator<<(std::ostream& os, Parser parser)
	{
		os << parser._content;
		return os;
	}

	Parser::Parser(const std::string& path, char sep):_sep(sep)
	{
		//file opening
	    std::fstream fs;
	    fs.open(path, std::ios::in); //read mode
	    //make sure that the file exists
	    if (!fs.good())
	    {
	        std::perror("File did not open correctly.");
	        throw;
	    }
	    //storage of the file line per line inside a vector
	    for (std::string line; std::getline(fs, line, '\n'); ) 
    	{
        	_file.push_back(line);
    	}
    	//storage of the header inside the _header vector
    	std::stringstream ss(_file[0]);
    	std::string item;
      	while (std::getline(ss, item, _sep)) _header.push_back(item);
      	//storage of the row inside the content vector
      	for(size_t i = 1; i < _file.size(); i++)
      	{
      		_content.push_back(Row(_header, static_cast<std::stringstream>(_file[i]), _sep));
      	}
      	fs.close();
	}

	Parser::~Parser()
	{
		std::cout << "Parser end of use." << std::endl;
	}

	size_t Parser::get_nrow() const
	{
		return _content.size();
	}

	size_t Parser::get_ncolumn() const
	{
		return _header.size();
	}

	Row Parser::operator[](int pos)
	{
		return _content[pos];
	}

}