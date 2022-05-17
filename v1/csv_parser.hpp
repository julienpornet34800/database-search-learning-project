#include <iostream>
#include <fstream>

#include <vector>
#include <unordered_map>
//#include <pair>

#include "row.hpp"

#ifndef CSV_PARSER_HPP
#define CSV_PARSER_HPP

namespace csv
{
	class Parser
    {
    	friend std::ostream& operator<<(std::ostream& os, Parser parser);

	    public:
	        Parser(const std::string&, char sep = ',');
	        ~Parser();

	        size_t get_nrow() const;
	        size_t get_ncolumn() const;

	        Row operator[](int pos);

	    private:
	    	char _sep;
	    	std::vector<std::string> _file;
	    	int _ncolumn;
	    	std::vector<std::string> _header;
	    	std::vector<Row> _content;

    };
}

#endif