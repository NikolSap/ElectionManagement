#include <stdexcept>

using namespace std;

class InvalidInputException : public exception {
public:
	InvalidInputException() :exception("Invalid input") {}
};

class LoadFailed : public exception {
public:
	LoadFailed() :exception("failed to load") {}
};

class DivByZeroError : public exception {
public:
	DivByZeroError() :exception("div by zero illegal") {}
};

class DataNotFound : public exception {
public:
	DataNotFound() :exception("the data wasn't found.") {}
};

class NotEnoughtRepInParty : public exception {
public:
	NotEnoughtRepInParty() :exception("ther is not enoght rep in this party.") {}
};

/*
	catch (std::exception& e)
	{
		cout << e.what() << endl;
	}
*/