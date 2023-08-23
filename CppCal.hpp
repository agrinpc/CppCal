#ifndef CPP_CAL_H
#define CPP_CAL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class CppCal {
	private:
		std::map<std::string, int>	_day_count;
		std::vector<std::string>	_month_list;
		std::vector<std::string>	_week_list;
		int							_year;
		int							_season;
		int							_month;
		std::string					_html;
		std::string					_path;
		CppCal();
		void setMonthList();
		void setDayCount();
		void setWeekDays();
		void setup();
		bool isLeap();
	
	public:
		CppCal(int year);
		CppCal(int year, int season, int month);
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