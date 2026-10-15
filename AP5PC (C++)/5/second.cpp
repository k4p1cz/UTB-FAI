#include <iostream>
#include <string>

using namespace std;

class Employee{
private:
	string* firstName;
	string lastName;
	int birthYear;
	double salary;

public:
	Employee(): firstName(new string()), lastName(), birthYear(0), salary(0){}

	Employee(const string& newFirstName, const string& newLastName, int newBirthYear, double newSalary)
		    : firstName(new string(newFirstName)), lastName(newLastName), birthYear(newBirthYear), salary(newSalary){}

	Employee(const Employee& other)
		    : firstName(new string(*other.firstName)), lastName(other.lastName), birthYear(other.birthYear), salary(other.salary){}

	~Employee(){
		delete firstName;
	}

	Employee& operator= (const Employee& other){
		if(this != &other){
			*firstName = *other.firstName;
			lastName = other.lastName;
			birthYear = other.birthYear;
			salary = other.salary;
		}
		return *this;
	}

	const string& getFirstName() const{
		return *firstName;
	}

	const string& getLastName() const{
		return lastName;
	}

	int getBirthYear() const{
		return birthYear;
	}

	double getSalary() const{
		return salary;
	}

	void print() const{
		cout << *firstName << ' ' << lastName << ", rok narozeni: " << birthYear << ", plat: " << salary << '\n';
	}
};

int main(){
	Employee* employees = nullptr;
	int employeeCount = 0;
	int choice = -1;

	do{
		cout << "\n--- Menu ---\n"
			 << "1. Vlozit noveho zamestnance\n"
			 << "2. Vypocitat prumernou mzdu\n"
			 << "3. Vypsat nejstarsiho a nejmladsiho zamestnance\n"
			 << "4. Vypsat vsechny zamestnance\n"
			 << "0. Konec\n"
			 << "Volba: ";

		cin >> choice;

		if(choice == 1){
			Employee* newEmployee;
			int copyEmployee = 0;

			if(employeeCount > 0){
				cout << "Kopirovat existujiciho zamestnance? (1 ano, 0 ne): ";
				if(!(cin >> copyEmployee) || (copyEmployee != 0 && copyEmployee != 1)){
					cout << "Neplatna volba.\n";
					cin.clear();
					continue;
				}
			}

			if(copyEmployee == 1){
				int employeeNumber;
				cout << "Cislo zamestnance ke kopii (1-" << employeeCount << "): ";
				if(!(cin >> employeeNumber) || employeeNumber < 1 || employeeNumber > employeeCount){
					cout << "Neplatne cislo zamestnance.\n";
					cin.clear();
					continue;
				}
				newEmployee = new Employee(employees[employeeNumber - 1]);
			}else{
				string firstName;
				string lastName;
				int birthYear;
				double salary;

				cout << "Jmeno: ";
			    getline(cin, firstName);
				cout << "Prijmeni: ";
				getline(cin, lastName);
				cout << "Rok narozeni: ";
				if(!(cin >> birthYear)){
					cout << "Neplatny rok narozeni.\n";
					cin.clear();
					continue;
				}
				cout << "Plat: ";
				if(!(cin >> salary)){
					cout << "Neplatny plat.\n";
					cin.clear();
					continue;
				}
				newEmployee = new Employee(firstName, lastName, birthYear, salary);
			}

			Employee* newArray = new Employee[employeeCount + 1];
			for(int i = 0; i < employeeCount; ++i){
				newArray[i] = employees[i];
			}
			newArray[employeeCount] = *newEmployee;
			delete newEmployee;
			delete[] employees;
			employees = newArray;
			employeeCount++;
			cout << "Zamestnanec byl vlozen.\n";
		}else if(choice == 2){
			if(employeeCount == 0) {
				cout << "Nejsou vlozeni zadni zamestnanci.\n";
			}else{
				double totalSalary = 0;
				for(int i = 0; i < employeeCount; ++i){
					totalSalary += employees[i].getSalary();
				}
				cout << "Prumerna mzda: " << totalSalary / employeeCount << '\n';
			}
		}else if(choice == 3){
			if(employeeCount == 0){
				cout << "Nejsou vlozeni zadni zamestnanci.\n";
			}else{
				int oldestIndex = 0;
				int youngestIndex = 0;
				for(int i = 1; i < employeeCount; ++i){
					if(employees[i].getBirthYear() < employees[oldestIndex].getBirthYear()){
						oldestIndex = i;
					}
					if(employees[i].getBirthYear() > employees[youngestIndex].getBirthYear()){
						youngestIndex = i;
					}
				}
				cout << "Nejstarsi: " << employees[oldestIndex].getFirstName() << ' '
					 << employees[oldestIndex].getLastName() << '\n';
				cout << "Nejmladsi: " << employees[youngestIndex].getFirstName() << ' '
					 << employees[youngestIndex].getLastName() << '\n';
			}
		}else if(choice == 4){
			if(employeeCount == 0){
				cout << "Nejsou vlozeni zadni zamestnanci.\n";
			}else{
				for(int i = 0; i < employeeCount; ++i){
					cout << i + 1 << ". ";
					employees[i].print();
				}
			}
		}
	}while(choice != 0);

	delete[] employees;
	return 0;
}