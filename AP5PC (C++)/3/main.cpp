#include <iostream>

using namespace std;

class Number
{
private:
	double value;

public:
	void setValue(double newValue)
	{
		value = newValue;
	}

	void displayValue()
	{
		cout << value << endl;
	}
};

class Fraction
{
private:
	int numerator;
	int denominator;

public:
	void setNumerator(int newNumerator)
	{
		numerator = newNumerator;
	}

	void setDenominator(int newDenominator)
	{
		denominator = newDenominator;
	}

	void displayNumerator()
	{
		cout << numerator << endl;
	}

	void displayDenominator()
	{
		cout << denominator << endl;
	}

	double calculateValue()
	{
		return static_cast<double>(numerator) / denominator;
	}
};

int main()
{
	Number number;
	double numberValue;

	cout << "Enter the number value: ";
	cin >> numberValue;
	number.setValue(numberValue);

	cout << "Number value: ";
	number.displayValue();

	Fraction fraction;
	int numerator;
	int denominator;

	cout << "Enter the numerator: ";
	cin >> numerator;
	fraction.setNumerator(numerator);

	do
	{
		cout << "Enter the denominator (must not be zero): ";
		cin >> denominator;
	} while (denominator == 0);

	fraction.setDenominator(denominator);

	cout << "Fraction value: " << fraction.calculateValue() << endl;

	return 0;
}
