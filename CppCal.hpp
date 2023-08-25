#ifndef CPP_CAL_H
#define CPP_CAL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

typedef struct s_data
{
	std::vector<int>	year;
	std::string			title;
	std::string			text;
	std::string			name;
	bool				sort;
	bool				expand;
	int					fs;
}						t_data;

class CppCal {
	private:
		std::map<std::string, int>	_day_count;
		std::vector<std::string>	_month_list;
		std::vector<std::string>	_week_list;
		std::vector<int>			_year;
		std::string					_title;
		std::string					_name;
		std::string					_text;
		std::string					_html;
		std::string					_style;
		int							_month;
		int							_week_day;
		int							_fs;

		CppCal();
		void	setMonthList();
		void	setDayCount();
		void	setWeekDays();
		void	setStyle();
		void	addBtns();
		void	init();
		void	setup(int year);
		bool	isLeap(int year);
		int		create(int year);
		int		save();
	
	public:
		CppCal(t_data data);
		~CppCal();

};

#endif