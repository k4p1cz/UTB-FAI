#include <iostream>
#include <cmath>

using namespace std;

class Equation{
private:
	double* A;
	double* B;
	double* C;

public:
	Equation(){
		A = new double(0);
		B = new double(0);
		C = new double(0);
	}

	~Equation(){
		delete A;
		delete B;
		delete C;
        A = 0;
        B = 0;
        C = 0;
	}

	void setCoefficients(double coefficientA, double coefficientB, double coefficientC){
		*A = coefficientA;
		*B = coefficientB;
	    *C = coefficientC;
	}

	void solve() const{
		const double discriminant = (*B * *B) - (4 * *A * *C);

		if(discriminant < 0){
			cout << "Rovnice nema reseni v oboru realnych cisel.\n";
		}else if(discriminant == 0){
			const double root = -*B / (2 * *A);
			cout << "Rovnice ma jeden koren: x = " << root << '\n';
		}else{
 			const double root1 = (-*B + sqrt(discriminant)) / (2 * *A);
			const double root2 = (-*B - sqrt(discriminant)) / (2 * *A);
			cout << "Rovnice ma dva koreny: x1 = " << root1 << ", x2 = " << root2 << '\n';
		}
	}
};

int main(){
	Equation* equation = new Equation();
	int choice = -1;

	do{
		cout << "\n--- Kvadraticka rovnice ---\n"
			 << "1. Nastavit koeficienty A, B, C\n"
	 	     << "2. Vypocitat rovnici\n"
		     << "0. Konec\n"
			 << "Volba: ";
		cin >> choice;

		if(choice == 1){
			double coefficientA, coefficientB, coefficientC;
			cout << "Zadejte A, B a C: ";
			if(cin >> coefficientA >> coefficientB >> coefficientC){
                if(coefficientA == 0){
                    cout << "Koeficient A nesmi byt 0.\n";
                    continue;
                }
				equation->setCoefficients(coefficientA, coefficientB, coefficientC);
			}else{
				cout << "Neplatny vstup.\n";
				cin.clear();
			}
		}else if(choice == 2) {
			equation->solve();
		}else if(choice != 0) {
			cout << "Neplatna volba.\n";
		}
	}while (choice != 0);

	delete equation;
	return 0;
}
