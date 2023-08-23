#include "CppCal.hpp"

CppCal::CppCal() { return; };

CppCal::CppCal(int year) : _year(year)
{
	setup();
	save("");
	return;
};

CppCal::CppCal(int year, int season, int month) : _year(year), _season(season), _month(month)
{
	setup();
	return;
};

CppCal::~CppCal() { return; }

void  CppCal::setup()
{
	setMonthList();
	setDayCount();
	setWeekDays();
	if (isLeap())
		_day_count["February"] = 29;
	_html = "<!doctype html>\n\
<html lang=\"en\">\n\
<head>\n\
<meta charset=\"utf-8\">\n\
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\
<title>Gregorian Calendar</title>\n\
<meta name=\"description\" content=\"Generated with CppCal::MiladAhmadi\">\n\
<link rel=\"icon\" href=\"/favicon.ico\">\n\
</head>\n\
<body>\n";
}

void CppCal::setMonthList()
{
	_month_list.push_back("January");
	_month_list.push_back("February");
	_month_list.push_back("March");
	_month_list.push_back("April");
	_month_list.push_back("May");
	_month_list.push_back("Jun");
	_month_list.push_back("July");
	_month_list.push_back("August");
	_month_list.push_back("September");
	_month_list.push_back("October");
	_month_list.push_back("November");
	_month_list.push_back("December");
	return;
}

void CppCal::setDayCount()
{
	_day_count.insert(std::pair<std::string, int>("January", 31));
	_day_count.insert(std::pair<std::string, int>("February", 28));
	_day_count.insert(std::pair<std::string, int>("March", 31));
	_day_count.insert(std::pair<std::string, int>("April", 30));
	_day_count.insert(std::pair<std::string, int>("May", 31));
	_day_count.insert(std::pair<std::string, int>("Jun", 30));
	_day_count.insert(std::pair<std::string, int>("July", 31));
	_day_count.insert(std::pair<std::string, int>("August", 31));
	_day_count.insert(std::pair<std::string, int>("September", 30));
	_day_count.insert(std::pair<std::string, int>("October", 31));
	_day_count.insert(std::pair<std::string, int>("November", 30));
	_day_count.insert(std::pair<std::string, int>("December", 31));
	return;
}

void CppCal::setWeekDays()
{
	_week_list.push_back("Mo");
	_week_list.push_back("Tu");
	_week_list.push_back("We");
	_week_list.push_back("Th");
	_week_list.push_back("Fr");
	_week_list.push_back("Sa");
	_week_list.push_back("Su");
	return;
}

bool CppCal::isLeap()
{
	if ((_year % 400 == 0) || (_year % 100 != 0 && _year %4 == 0))
		return (true);
	return (false);
}

int CppCal::save(std::string path)
{
	std::ofstream file;
	if (!path.empty() && path.substr(path.length() - 5) == ".html" && path.length() > 5)
		_path = path;
	else
	{
		_path = "./calendar_" + std::to_string(_year);
		_path +=  ".html";
	}
    file.open (_path.c_str());
    file << _html;
	file << "<h1>Hello World</h1>\n";
    file << "</body>\n</html>";
    file.close();
	std::cout << "Calendar generated in " << _path << std::endl;
	return (0);
}

int CppCal::create()
{
	return (0);
}