#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <time.h>
#include <thread>
#include <ctime>
#include <regex>

using namespace std;

void firstThread(vector<string> names, int numOfLines) {
	for (int i = 0; i < numOfLines; i++) {
		cout << i << " " << names.at(i) << endl;
	}
}

string modifyString(string modifyString) {
	string rebuildString;

	std::regex find_the_ea("ea");
	rebuildString = regex_replace(modifyString, find_the_ea, "9999999999999999");

	return rebuildString;
}

void secondThread(vector<string> names, int min, int cap) {
	try {
		for (int i = min; i < cap; i++) {
			string nameAtI = modifyString(names.at(i));
			cout << i << " " << nameAtI << endl;
		}
		cout << "\n" << endl;
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
}

int main() {

	ifstream textFileRead("LastNames.txt");
	istream_iterator<string> iterator(textFileRead), end;
	vector<string> namesList(iterator, end);
	cout << "Read " << namesList.size() << " numbers" << endl;

	time_t starttime1 = time(0);

	secondThread(namesList, 0, namesList.size());

	time_t endtime1 = time(0);

	time_t starttime2 = time(0);

	thread core1(secondThread, namesList, 0, 15000);
	thread core2(secondThread, namesList, 15000, 30000);
	thread core3(secondThread, namesList, 30000, 45000);
	thread core4(secondThread, namesList, 45000, 60000);
	thread core5(secondThread, namesList, 60000, 75000);
	thread core6(secondThread, namesList, 75000, (namesList.size() - 1));

	//running the program using multiple threads
	core1.join();
	core2.join();
	core3.join();
	core4.join();
	core5.join();
	core6.join();

	cout << "Total Lines for both: " << namesList.size() << endl;


	cout << "STARTING TIME Single Thread: " << starttime1 << endl;
	cout << "ENDING TIME Single Thread: " << endtime1 << endl;
	int elapsed1 = endtime1 - starttime1;
	cout << "SECONDS: " << elapsed1 << endl;

	time_t endtime2 = time(0);
	cout << "STARTING TIME 6 Threads: " << starttime2 << endl;
	cout << "ENDING TIME 6 Threads: " << endtime2 << endl;
	int elapsed2 = endtime2 - starttime2;
	cout << "SECONDS: " << elapsed2 << endl;

	textFileRead.close();
	return 0;
}