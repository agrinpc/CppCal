#include "CppCal.hpp"

CppCal::CppCal() { return; };

CppCal::CppCal(t_data data) : _year(data.year), _title(data.title), _name(data.name), _text(data.text), _fs(data.fs)
{
	_month = 0;
	init();
	addBtns();
	for (size_t i = 0; i < _year.size(); i++)
	{
		std::cout << "Generating \033[32m" << _year[i] << "\033[0m calendar..." << std::endl;
		setup(_year[i]);
		create(_year[i]);
	}
	save();
	return;
}

CppCal::~CppCal() { return; }

void	CppCal::init()
{
	setMonthList();
	setDayCount();
	setWeekDays();
	setStyle();
	_html = "<!doctype html>\n\
<html lang=\"en\">\n\
<head>\n\
<meta charset=\"utf-8\">\n\
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\
<title>Gregorian Calendar</title>\n\
<meta name=\"description\" content=\"Generated with CppCal::MiladAhmadi\">\n\
<link rel=\"icon\" href=\"favicon.ico\">\n";
	_html += _style;
	_html += "</head>\n<body>\n<main>\n<div class=\"big-row\">\n";
	return;
}

void	CppCal::setup(int year)
{
	int	m;
	int	c;
	int y;
	if (isLeap(year))
		_day_count["February"] = 29;
	else
		_day_count["February"] = 28;
	
	if (_month == 0 || _month == 1)
		year--;
	c = year / 100;
	y = year % 100;
	m = ((_month + 10) % 12) + 1;
	_week_day = (((1 + (int)std::floor(2.6 * m - 0.2) - 2 * c + y + (int)std::floor(y / 4) + (int)std::floor(c / 4)) % 7) + 6) % 7;
	return;
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

void CppCal::setStyle()
{
	int size = _year.size() * 100;
	_style = "<style>\
@import url('https://fonts.googleapis.com/css2?family=Anton&family=Audiowide&family=Didact+Gothic&family=Poppins:wght@100;200;300;400;500;600;700;800;900&family=VT323&display=swap');\
* {\
margin: 0;\
padding: 0;\
font-family: 'Didact Gothic', sans-serif;\
}\
body {\
overflow-x: hidden;\
background-color: #efefef;\
}\
main {\
width: 100%;\
overflow-x:auto;\
}\
.big-row {\
width: "+ std::to_string(size) + "vw;\
display:flex;\
flex-direction: row\
}\
.container {\
width: 100vw;\
display: flex;\
margin-bottom: 100px;\
justify-content: center;\
align-items: center;\
min-height: 100vh;\
background-color: #efefef;\
}\
.wrapper {\
width: 100%;\
max-width: 1050px;\
background-color: #efefef;\
padding: 50px;\
display: flex;\
justify-content: space-around;\
flex-wrap: wrap;\
}\
.header {\
width:100%;\
display:flex;\
justify-content:space-between;\
align-items:center;\
}\
.download{\
padding:8px 14px;\
background-color:rgba(255,255,255,0.6);\
color:#000;\
border:none;\
border-radius:9px;\
cursor:pointer;\
transition: all ease 0.2s;\
}\
.download:hover{\
background-color: rgba(0,0,0,0.6);\
color: #fff;\
}\
table {\
width: 30%;\
margin: 10px;\
background-color: #fff;\
padding: 10px;\
border-radius: 15px;\
box-shadow: rgba(50, 50, 93, 0.25) 0px 13px 27px -5px, rgba(0, 0, 0, 0.3) 0px 8px 16px -8px;\
}\
.wrapper.clone {\
width: 2100px;\
max-width: 2200px;\
background-color: #efefef;\
padding: 100px;\
display: flex;\
justify-content: space-around;\
flex-wrap: wrap;\
}\
.clone table {\
box-shadow: none;\
border: 1px solid #aaa;\
border-radius: 30px;\
margin: 20px;\
padding: 20px;\
font-size:32px;\
}\
.clone td {\
padding: 4px;\
}\
td {\
text-align: center;\
padding: 2px;\
}\
.d_day {\
position:relative;\
display:inline-block;\
text-align:center;\
width: 22px;\
height: 22px;\
line-height:22px;\
background-color: #e63946;\
border-radius: 50%;\
color: #fff;\
}\
.d_day::after {\
content: \"My first day in ETAS\";\
display:block;\
position:absolute;\
width:max-content;\
padding: 8px 14px;\
background-color:#3d405b;\
color:#fff;\
opacity:0;\
bottom: 28px;\
border-radius: 12px;\
transition: all ease 0.3s;\
}\
.d_day:hover::after {\
opacity:1;\
}\
.clone .d_day {\
display:inline-block;\
text-align:center;\
width: 44px;\
height: 44px;\
line-height:44px;\
background-color: transparent;\
border-radius: 50%;\
color: #000;\
}\
th {\
padding-bottom: 15px;\
padding-top: 5px;\
color: #F4A261;\
}\
.clone th {\
padding-bottom: 30px;\
padding-top: 10px;\
}\
.weekend {\
color: #e63946;\
}\
.week {\
color: #2A9D8F;\
}\
h1 {\
font-size: "+std::to_string(_fs)+"px;\
color: #457b9d;\
margin: 30px 0;\
}\
.clone h1 {\
font-size: "+std::to_string(_fs * 2)+"px;\
margin: 60px 0;\
}\
p {\
width: 95%;\
max-width: 900px;\
text-align: justify;\
margin-bottom: 36px;\
}\
.clone p {\
max-width: 1800px;\
font-size: 40px;\
margin-bottom: 80px;\
}\
.btn {\
width:50px;\
height:50px;\
background-color:rgba(255,255,255,0.6);\
text-align:center;\
border-radius:50%;\
color:#000;\
font-size:32px;\
font-weight:bold;\
position:fixed;\
top:45%;\
cursor:pointer;\
transition: all ease 0.2s;\
}\
.btn:hover{\
background-color: rgba(0,0,0,0.6);\
color: #fff;\
}\
.btn-next{\
right:15px;\
}\
.btn-pre{\
left:15px;\
}\
@media only screen and (max-width: 600px){\
.header{\
padding:10px;\
flex-direction: column;\
}\
h1{\
font-size: "+std::to_string(_fs / 2) +"px;\
}\
p{\
font-size:14px;\
padding: 10px;\
}\
table {\
width:95%;\
}\
}\
</style>";
}

bool CppCal::isLeap(int year)
{
	if ((year % 400 == 0) || (year % 100 != 0 && year %4 == 0))
		return (true);
	return (false);
}

int CppCal::save()
{
	std::ofstream	file;
	std::string		output;

	std::ifstream 	ico_src("assets/favicon.ico", std::ios::binary);
    std::ofstream	ico_dst("output/favicon.ico",   std::ios::binary);
	std::ifstream 	cjs_src("assets/canvas.js", std::ios::binary);
    std::ofstream	cjs_dst("output/canvas.js",   std::ios::binary);
    ico_dst << ico_src.rdbuf();
    cjs_dst << cjs_src.rdbuf();
	output = "output/" + _name + ".html";
    file.open (output.c_str());
    file << _html;
    file << "</div>\n</main>\n\
<script src=\"canvas.js\"></script>\
<script>\
let size = document.querySelector('.container').offsetWidth;\
let move = true;\
window.onresize = () => {\
size = document.querySelector('.container').offsetWidth;\
};\
const div = document.querySelector('main');\
function next() {\
if (move) {\
move = false;\
div.scrollBy({left:size,behavior:'smooth'});\
setTimeout(()=> {move = true;}, 1000);\
}\
}\
function pre(){\
if (move) {\
move = false;\
div.scrollBy({left:-size,behavior:'smooth'});\
setTimeout(()=> {move = true;}, 800);\
}\
}\
function download(year){\
const tg = document.querySelector('#w-'+year);\
let clone = tg.cloneNode(true);\
clone.classList.add('clone');\
let btn = clone.querySelector('button');\
btn.parentNode.removeChild(btn);\
let tmp = document.createElement('div');\
tmp.style.width = '2300px';\
document.body.appendChild(tmp);\
tmp.appendChild(clone);\
html2canvas(tmp,{\
windowWidth: 2300,\
windowHeight: tmp.scrollHeight\
}).then(canvas => {\
document.body.appendChild(canvas);\
let image = canvas.toDataURL(\"image/png\").replace(\"image/png\", \"image/octet-stream\");\
let link = document.createElement('a');\
document.body.appendChild(link);\
link.setAttribute('download', 'cal_'+year+'.png');\
link.setAttribute('href', image);\
link.click();\
document.body.removeChild(link);\
document.body.removeChild(canvas);\
document.body.removeChild(tmp);\
})\
}\
</script>\
</body>\n</html>";
    file.close();
	std::cout << "Calendar saved in \033[33m" << output << "\033[0m" << std::endl;
	return (0);
}

void	CppCal::addBtns()
{
	if (_year.size() > 1)
		_html += "<div class=\"btn btn-next\" onClick=\"next()\">></div><div class=\"btn btn-pre\" onClick=\"pre()\"><</div>";
}

int CppCal::create(int year)
{
	int wc = _week_day;
	int d;
	int	st = 0;

	if (year == 1582)
		st = 9;
	_html += "<div class=\"container\">\n\
<div class=\"wrapper\" id=\"w-"+std::to_string(year)+"\">\n<div class=\"header\">\n\
<h1>"+ _title + " - " + std::to_string(year) + "</h1>\n\
<button class=\"download\" onclick=\"download("+std::to_string(year)+")\">Download</button></div>\n\
<p>\n" + _text + "\n</p>\n";
for (int i = st; i < 12; i++)
{
	d = 1;
	_html += "<table><thead>\n\
<tr>\n<th colspan=\"8\">\n";
	_html += _month_list[i];
	_html += "\n</th>\n</tr>\n\
</thead>\n<tbody>\n";
	_html += "<tr>\n<td class=\"week\">\nWk\n</td>\n";
	for (int j = 0; j < 7; j++)
	{
		if (j == 6)
			_html += "<td class=\"weekend\">\n";
		else
			_html += "<td>\n";
		_html += _week_list[j];
		_html += "\n</td>\n";
	}
	_html += "</tr>\n";
	for (int j = 0; j < 6; j++)
	{
		if (d <= _day_count[_month_list[i]])
		{
			_html += "<tr>\n";
			_html += "<td class=\"week\">\n";
			_html += std::to_string(wc / 7 + 1);
			_html += "\n</td>";
			for (int k = 0; k < 7; k++)
			{
				if (j == 0 && k == 0)
				{
					for (int l = 0; l < _week_day; l++)
					{
						_html += "<td></td>\n";
						k++;
					}
				}
				if (d <= _day_count[_month_list[i]])
				{
					wc++;
					if (k == 6)
						_html += "<td class=\"weekend\">\n" + std::to_string(d) + "\n";
					else
					{
						if (year == 2023 && i == 9 && d == 2)
							_html += "<td><span class=\"d_day\">\n" + std::to_string(d) + "\n</span>";
						else
							_html += "<td>\n" + std::to_string(d) + "\n";
					}
					_html += "</td>";
				}
				else
					_html += "<td></td>\n";
				d++;
			}
			_html += "</tr>\n";
		}
	}
	_html += "</tbody>\n</table>\n";
	_week_day += _day_count[_month_list[i]];
	_week_day = _week_day % 7;
}
_html += "</div>\n\
</div>";
	return (0);
}