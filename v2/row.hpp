#include <iostream>
#include <cmath> // for std::sqrt

#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <unordered_map>
//#include "Character.hpp"

#ifndef ROW_HPP
#define ROW_HPP

namespace csv
{
	class Row
	{
		friend std::ostream& operator<<(std::ostream& os, Row row);
		friend std::vector<int> get_answer(Row row); 
		friend class Character;

		public:
			Row(std::vector<std::string> header, std::stringstream ssline, char sep);
			~Row();

			std::string operator[](int pos);
			std::string operator[](std::string header_name);

			int length();

		private:
			std::vector<std::string> _content;
			std::vector<std::string> _header;
	};
}

#endif