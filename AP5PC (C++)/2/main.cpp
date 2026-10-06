#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Employee {
    string name;
    string surname;
    int dateOfBirth;
    double salary;
};

void listAllEmployees(const vector<Employee> &employees);
double averageSalary(const vector<Employee> &zamestnanci);
void oldestAndYoungest(const vector<Employee> &employees);
void saveToFile(const vector<Employee> &employees);
void enterKeyToContinue(); 

int main(void) {
    vector<Employee> employees;
    int count;

    cout << "Zadejte pocet zamestnancu: ";
    cin >> count;

    if (count <= 0) {
        cout << "Pocet musi byt kladny.\n";
        return 0;
    }

    employees.resize(count);

    for (int i = 0; i < count; i++) {
        cout << "\nZamestnanec cislo " << i + 1 << ":\n";
        cout << "Jmeno: ";
        cin >> employees[i].name;

        cout << "Prijmeni: ";
        cin >> employees[i].surname;

        cout << "Rok narozeni: ";
        cin >> employees[i].dateOfBirth;

        cout << "Vyska platu: ";
        cin >> employees[i].salary;
    }

    int choice;

    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Zmenit mzdu vybraneho zamestnance\n";
        cout << "2. Vypocitat prumernou mzdu\n";
        cout << "3. Nejstarsi a nejmladsi zamestnanec\n";
        cout << "4. Vypsat vsechny zamestnance a ulozit do souboru\n";
        cout << "5. Konec\n";
        cout << "Vyberte moznost: ";
        cin >> choice;

        switch (choice) {
            case 1:
                int index;
                cout << "Zadejte cislo zamestnance (1-" << employees.size() << "): ";
                cin >> index;

                if (index < 1 || index > employees.size()) {
                    cout << "Neplatne cislo.\n";
                    break;
                }

                cout << "Aktualni mzda: " << employees[index - 1].salary << " CZK\n";
                cout << "Nova mzda: ";
                cin >> employees[index - 1].salary;
                cout << "Mzda upravena.\n";

                enterKeyToContinue();
                break;

            case 2:
                cout << "Prumerna mzda: " << averageSalary(employees) << " CZK\n";
                enterKeyToContinue();
                break;

            case 3:
                oldestAndYoungest(employees);
                enterKeyToContinue();
                break;

            case 4:
                listAllEmployees(employees);
                saveToFile(employees);
                enterKeyToContinue();
                break;

            case 5:
                cout << "Program ukoncen.\n";
                break;

            default:
                cout << "Neplatna volba.\n";
                break;
        }

    } while (choice != 5);

    return 0;
}

void listAllEmployees(const vector<Employee> &employees) {
    cout << "\n--- Seznam zamestnancu ---\n";

    for (int i = 0; i < employees.size(); i++) {
        cout << i + 1 << ". "
             << employees[i].name << " "
             << employees[i].surname << " | "
             << employees[i].dateOfBirth << " | "
             << employees[i].salary << " CZK\n";
    }

}

double averageSalary(const vector<Employee> &employees) {
    double totalSalary = 0;

    for (int i = 0; i < employees.size(); i++) {
        totalSalary += employees[i].salary;
    }

    if (employees.empty()) {
        return 0;
    }

    return totalSalary / employees.size();
}

void oldestAndYoungest(const vector<Employee> &employees) {
    if (employees.empty()) {
        cout << "Nejsou zadni zamestnanci.\n";
        return;
    }

    int indexOldest = 0;
    int indexYoungest = 0;

    for (int i = 1; i < employees.size(); i++) {
        if (employees[i].dateOfBirth < employees[indexOldest].dateOfBirth) {
            indexOldest = i;
        }

        if (employees[i].dateOfBirth > employees[indexYoungest].dateOfBirth) {
            indexYoungest = i;
        }
    }

    cout << "Nejstarsi zamestnanec: "
         << employees[indexOldest].name << " "
         << employees[indexOldest].surname << "\n";

    cout << "Nejmladsi zamestnanec: "
         << employees[indexYoungest].name << " "
         << employees[indexYoungest].surname << "\n";

}

void saveToFile(const vector<Employee> &employees) {
    ofstream file("zamestnanci.txt");

    if (!file) {
        cout << "Soubor se nepodarilo otevrit.\n";
        return;
    }

    for (int i = 0; i < employees.size(); i++) {
        file << employees[i].name << " "
             << employees[i].surname << " "
             << employees[i].dateOfBirth << " "
             << employees[i].salary << "\n";
    }

    cout << "Data byla ulozena do souboru zamestnanci.txt\n";
}

void enterKeyToContinue(){
    cout << "\n\nPress Enter to continue..." << endl;
    cin.ignore();
    cin.get(); 
}