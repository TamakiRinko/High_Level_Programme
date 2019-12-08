#include<iostream>
#include<string>
#include<map>
using namespace std;

struct Date {
	int year;
	int month;
	int day;
	Date(int year, int month, int day) : year(year), month(month), day(day) {}
	Date(const Date& d) : year(d.year), month(d.month), day(d.day) {}
	bool operator==(const Date& d) {						//重载==，用于比较
		return (year == d.year && month == d.month && day == d.day);
	}
	friend ostream& operator<<(ostream& out, const Date& d) {
		out << "(" << d.year << ", " << d.month << ", " << d.day << ")";
		return out;
	}
};

struct cmp {
	bool operator()(const Date& d1, const Date& d2) {		//重载函数运算操作符，被自动调用
		if (d1.year > d2.year || (d1.year == d2.year && d1.month > d2.month) ||
			(d1.year == d2.year && d1.month == d2.month && d1.day > d2.day)) {
			return true;
		}
		return false;
	}
};

class MeaningfulDate {
private:
	map<Date, string, cmp> events;				//根据cmp给出的排序方式进行排序
public:
	MeaningfulDate() {}
	~MeaningfulDate() {
		events.clear();
	}
	bool addDate(Date d, string event);
	size_t deleteDate(Date d);
	bool modifyDate(Date d, string event);
	string findEvent(Date d);
	Date* findDate(string event);
	void showInOrder();
};

bool MeaningfulDate::addDate(Date d, string event) {
	return events.insert(pair<Date, string>(d, event)).second;
}

size_t MeaningfulDate::deleteDate(Date d) {
	return events.erase(d);								//删除键的个数
}

bool MeaningfulDate::modifyDate(Date d, string event) {
	auto it = events.find(d);
	if (it == events.end()) {
		return false;
	}
	events.erase(it);
	return events.insert(pair<Date, string>(d, event)).second;
}

string MeaningfulDate::findEvent(Date d) {
	auto it = events.find(d);
	if (it != events.end()) {
		return it->second;
	}
	return "";
}

Date* MeaningfulDate::findDate(string event) {
	for (auto it = events.begin(); it != events.end(); ++it) {
		if (it->second == event) {							//比较事件
			Date* d = new Date(it->first);
			return d;
		}
	}
	return nullptr;											//查找失败则返回nullptr
}

void MeaningfulDate::showInOrder() {
	cout << "有纪念意义的日期: " << endl;
	for (auto it = events.begin(); it != events.end(); ++it) {
		cout << it->first << ", " << it->second << endl;
	}
	cout << endl;
}

int main(int argc, char const *argv[]) {
	MeaningfulDate m;
	Date a(2001, 1, 1);
	Date b(2000, 2, 1);
	Date c(2000, 1, 1);
	Date d(1999, 1, 1);
	Date e(2001, 2, 9);
	m.addDate(a, "事件: 1");
	m.addDate(b, "事件: 2");
	m.addDate(c, "事件: 3");
	m.addDate(d, "事件: 4");
	m.addDate(e, "事件: 5");
	m.addDate(a, "事件: 6");						 //插入键相同的键值对，失败
	m.showInOrder();								//按有意义日期的顺序由大至小打印

	Date* date = m.findDate("事件: 5");
	if(date == nullptr){
		cout << "该事件无对应的日期!" << endl;
	}else{											//找到对应事件的日期
		cout << "对应日期是: "<< *date << endl;
	}

	string event = m.findEvent(Date(2001, 2, 2));
	if(event == ""){								//找不到对应日期的事件
		cout << "该日期无对应事件!" << endl;
	}else{
		cout << "对应事件是: " << event << endl;
	}

	cout << endl;

	if(!m.modifyDate(d, "事件: 7")){				//修改成功
		cout << "修改" << d << "失败!该日期没有事件!" << endl;
	}
	m.showInOrder();

	if(m.deleteDate(e) <= 0){						//删除成功
		cout << "删除" << d << "失败!" << endl;
	}
	m.showInOrder();
	return 0;
}