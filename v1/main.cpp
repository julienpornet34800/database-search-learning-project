#include <iostream>
#include "csv_parser.hpp"
#include "row.hpp"
#include <map>
#include <array>

/*	to compile
*	g++ -std=c++17 -pedantic -Wall -Wextra *.cpp
*/

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, std::pair<T,U> p)
{
	os << "{"<< p.first << ", " << p.second << "}";
	return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> v)
{
	std::for_each(v.begin(), v.end(), [&os](T elem)
	{
		os << elem << "\t";
	});
	return os;
}

int main()
{	
	std::cout << "Program is starting." << std::endl;
	csv::Parser questions = csv::Parser("questions.csv");
	csv::Parser characters = csv::Parser("personnages.csv");

	int current_ans;
	std::vector<int> user_ans;
	for(size_t i = 0; i<questions.get_nrow(); i++)
	{
		std::cout << questions[static_cast <int>(i)] << "\t(réponse entre 0 et 5)" << std::endl;
		std::cin >> current_ans;
		user_ans.push_back(current_ans);
	}

	std::vector<int> character_ans;
	std::vector<std::pair<size_t,int>> best_candidate;
	for(size_t i = 0; i<characters.get_nrow(); i++)
	{
		std::vector<int> diff_ans;
		character_ans = get_answer(characters[i]);

		std::transform(character_ans.begin(), character_ans.end(), user_ans.begin(), std::back_inserter(diff_ans),
			[](int elem1, int elem2)
			{
				std::cout << "elem1: " << elem1 << "\t";
				std::cout << "elem2: " << elem2 << std::endl;
				return abs(elem1-elem2);
			});

		best_candidate.push_back({static_cast <int>(i), std::accumulate(diff_ans.begin(), diff_ans.end(), 0)});
		std::cout << "diff_ans\n" << diff_ans << std::endl;
	}

	std::cout << "best_candidate\n" << best_candidate << std::endl;
	/*void sort( RandomIt first, RandomIt last, Compare comp );*/
	std::sort(best_candidate.begin() , best_candidate.end(), [](std::pair<int, int> elem1, std::pair<int, int> elem2)
		{
			if (elem1.second >= elem2.second) return false;
			else return true;
		});
	std::cout << "best_candidate\n" << best_candidate << std::endl;
	std::cout << "The best candidate is :" << std::endl;
	std::cout << characters[best_candidate[0].first][0] << std::endl;


	return 0;
}
