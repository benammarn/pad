
class TestResult
{
    public:
	int position;
	int length;

	TestResult()
	    :position{0}, length{0}
	{}

	TestResult(int position, int length)
	    : position{position}, length{length}
	{}

	bool operator == (const TestResult &t)
	{
	    return position == t.position && length == t.length;
	}
};

