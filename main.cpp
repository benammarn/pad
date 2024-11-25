#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>

#include <ctime>
#include "TestResult.h"
extern "C" {
#include "Zeitmessung.h"
}

using namespace std;


TestResult LoesungA(const string &s);
TestResult LoesungB(const string &s);


class TestCase
{
    public:
	TestResult result;
	string s;

	TestCase(const string &s)
	{
	    istringstream(s) >> result.position >> result.length >> TestCase::s;
	}

	size_t size()
	{
	    return s.length();
	}

	friend ostream & operator << (ostream &os, const TestCase &t) {
	    os << "Result = {" << t.result.position << ", " << t.result.length << "}, s = "  << t.s << endl;
	    return os;
	}
	    
};

int main()
{
    TestResult result;
    t_stopwatch MyWatch;
    t_timevalue durationA=0, durationB;


    ofstream runtimelog("runtime.txt", ofstream::out);

    ifstream infile("examples.txt");

    string line;
    while (getline(infile, line))
    {
	TestCase t(line);
	
	// print test case
	// cout << t;

	cout << "Test (size=" << t.size() << ") A: ";
	startStopwatch(&MyWatch);
	result = LoesungA(t.s);
	durationA=stopStopwatch(&MyWatch);

	if (result == t.result) cout << "OK"; else cout << "FAILED!";

	cout << " B: ";
	startStopwatch(&MyWatch);
	result = LoesungB(t.s);
	durationB=stopStopwatch(&MyWatch);

	if (result == t.result) cout << "OK"; else cout << "FAILED!";

	cout << endl << "   runtime A: " << durationA << " B: " << durationB << endl;
	runtimelog << t.size() << " " << durationA << " " << durationB << endl;
    }

    return 0;
}
