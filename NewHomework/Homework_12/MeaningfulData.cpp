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
	// bool operator<(const Date& d){
	//     return true;
	// }
	// bool operator()(const Date& d) {
	// 	if (year > d.year || (year == d.year && month > d.month) ||
	// 		(year == d.year && month == d.month && day > d.day)) {
	// 		return true;
	// 	}
	// 	return false;
	// }
	bool operator==(const Date& d) {
		return (year == d.year && month == d.month && day == d.day);
	}
	friend ostream& operator<<(ostream& out, const Date& d) {
		out << d.year << ", " << d.month << ", " << d.day;
		return out;
	}
};

struct cmp {
	bool operator()(const Date& d1, const Date& d2) {
		if (d1.year > d2.year || (d1.year == d2.year && d1.month > d2.month) ||
			(d1.year == d2.year && d1.month == d2.month && d1.day > d2.day)) {
			return true;
		}
		return false;
	}
};

class MeaningfulDate {
private:
	map<Date, string, cmp> events;
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
	int getNum();
};

bool MeaningfulDate::addDate(Date d, string event) {
	return events.insert(pair<Date, string>(d, event)).second;
}

size_t MeaningfulDate::deleteDate(Date d) {
	return events.erase(d);
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
		if (it->second == event) {
			Date* d = new Date(it->first);
			return d;
		}
	}
	return nullptr;
}

void MeaningfulDate::showInOrder() {
	for (auto it = events.begin(); it != events.end(); ++it) {
		cout << it->first << ", " << it->second << endl;
	}
}

int MeaningfulDate::getNum() {
	return events.size();
}

int main(int argc, char const *argv[]) {
	MeaningfulDate m;
	Date a(2001, 1, 1);
	Date b(2000, 2, 1);
	Date c(2000, 1, 1);
	Date d(1999, 1, 1);
	Date e(2001, 2, 9);
	m.addDate(a, "你是谁1");
	m.addDate(b, "你是谁2");
	m.addDate(c, "你是谁3");
	m.addDate(d, "你是谁4");
	m.addDate(e, "你是谁5");
	m.addDate(a, "你是谁6");
	m.showInOrder();

	cout << (m.findDate("你是谁8")) << endl;

	cout << m.findEvent(Date(2001, 2, 2)) << endl;
	cout << m.findEvent(Date(2001, 1, 1)) << endl;

	// m.modifyDate(d, "你是谁7");
	// m.showInOrder();

	// m.deleteDate(e);
	// m.showInOrder();
	return 0;
}