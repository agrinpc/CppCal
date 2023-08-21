#ifndef CPP_CAL_H
#define CPP_CAL_H

#include <iostream>
#include <fstream>
#include <vector>

class CppCal {
	private:
		std::vector<int>			_day_count;
		std::vector<std::string>	_month_list;
		int							_season;
		int							_month;
		int							_year;
		int							_html;
		std::string					_path;
		CppCal();
	
	public:
		CppCal(int year);
		CppCal(int year, int season);
		CppCal(int year, int month);
		~CppCal();

		int		create();
		int		save(std::string path);
		void	show();

		void increaseMonth(unsigned int amount);
		void decreaseMonth(unsigned int amount);
		void increaseYear(unsigned int amount);
		void decreaseYear(unsigned int amount);
};

#endif