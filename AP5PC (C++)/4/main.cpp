#include <cmath>
#include <iostream>

using namespace std;

class ComplexNumber{
    public:
        double realPart;
        double imaginaryPart;

        ComplexNumber(double real, double imaginary): realPart(real), imaginaryPart(imaginary) {}

        void print() const{
            cout << realPart << (imaginaryPart < 0 ? " - " : " + ")
                << imaginaryPart << "i\n";
        }
};

class Point{
    public:
        double x;
        double y;

        Point(double xCoordinate, double yCoordinate): x(xCoordinate), y(yCoordinate) {}

        void move(double deltaX, double deltaY){
            x += deltaX;
            y += deltaY;
        }

        void rotate(double degrees){
            const double pi = 3.1415926535;
            const double angle = degrees * pi / 180.0;
            const double newX = x * cos(angle) - y * sin(angle);
            const double newY = x * sin(angle) + y * cos(angle);
            x = newX;
            y = newY;
        }

        void shear(double xFactor, double yFactor){
            const double newX = x + xFactor * y;
            const double newY = y + yFactor * x;
            x = newX;
            y = newY;
        }

        void reflect(int axis){
            if(axis == 1){
                y = -y;
            }else if (axis == 2){
                x = -x;
            }else{
                x = -x;
                y = -y;
            }
        }

        void print() const{
            cout << "Bod: (" << x << ", " << y << ")\n";
        }
};

int main(){
	double firstReal, firstImaginary, secondReal, secondImaginary;

	cout << "Zadejte realnou a imaginarni slozku prvniho cisla: ";
	cin >> firstReal >> firstImaginary;
	cout << "Zadejte realnou a imaginarni slozku druheho cisla: ";
	cin >> secondReal >> secondImaginary;

	ComplexNumber firstNumber(firstReal, firstImaginary);
	ComplexNumber secondNumber(secondReal, secondImaginary);
	ComplexNumber sum(firstNumber.realPart + secondNumber.realPart, firstNumber.imaginaryPart + secondNumber.imaginaryPart);
	ComplexNumber difference(firstNumber.realPart - secondNumber.realPart, firstNumber.imaginaryPart - secondNumber.imaginaryPart);

	cout << "Soucet: ";
	sum.print();
	cout << "Rozdil: ";
	difference.print();

	double pointX, pointY;
	cout << "\nZadejte souradnice bodu x a y: ";
	cin >> pointX >> pointY;
	Point point(pointX, pointY);

	int choice;
	do{
		point.print();
		cout << "1 - posun\n2 - otoceni\n3 - zkoseni\n4 - zrcadleni\n0 - konec\nVolba: ";
		cin >> choice;

		if (choice == 1) {
			double deltaX, deltaY;
			cout << "Zadejte posun dx a dy: ";
			cin >> deltaX >> deltaY;
			point.move(deltaX, deltaY);
		}else if (choice == 2) {
			double degrees;
			cout << "Zadejte uhel ve stupnich: ";
			cin >> degrees;
			point.rotate(degrees);
		}else if (choice == 3) {
			double xFactor, yFactor;
			cout << "Zadejte koeficient zkoseni x a y: ";
			cin >> xFactor >> yFactor;
			point.shear(xFactor, yFactor);
		}else if (choice == 4) {
			int axis;
			cout << "Zrcadlit podle: 1 - osy x, 2 - osy y, 3 - pocatku: ";
			cin >> axis;
			point.reflect(axis);
		}
	}while(choice != 0);

	return 0;
}
