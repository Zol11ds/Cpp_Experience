// MIKS ĀRE 8. grupa, 1. variants
#include <iostream>
using namespace std;

class OverflowException { };

class Human {
protected:
    string vards;
    char dzimums;
    int dzimsanas_gads;
public:
    Human();
    Human(string var, char dz, int dzg);
    virtual ~Human() {
        cout << "Zinojums no \"Human\": " << vards << " - iznicinats!" << endl;
    }

    string GetVards() const { return vards; }
    void SetVards(string vards) { this->vards = vards; }

    char GetDzimums() const { return dzimums; }
    void SetDzimums(char dzimums) { this->dzimums = dzimums; }

    int GetDzimsanasGads() const;
    void SetDzimsanasGads(int dzimsanas_gads);

    friend ostream& operator<< (ostream& O, const Human& HM);
};

class Employee : public Human {
private:
    double alga;
public:
    Employee() : Human(), alga(500) {
    }
    Employee(string var, char dz, int dzg, double alga);
    virtual ~Employee() {
        cout << "Zinojums no \"Employee\": " << vards << " - iznicinats!" << endl;
    }
    double GetAlga() const { return alga; }
    void SetAlga(double alga) { this->alga = alga; }

    friend ostream& operator<< (ostream& O, const Employee& EM);
};

class Firm {
private:
    typedef Employee* EPointer;
    EPointer* Nodes;
    static const unsigned int DEFAULT_MAX_LENGTH = 8;
    unsigned int MaxLength;
    unsigned int Length;
public:
    Firm() : MaxLength(DEFAULT_MAX_LENGTH), Length(0) {
        Nodes = new EPointer[MaxLength];
    }
    Firm(unsigned int MaxLength) : MaxLength(MaxLength), Length(0) {
        Nodes = new EPointer[MaxLength];
    }
    ~Firm();
    static unsigned int GetDefaultMaxLength() {
        return DEFAULT_MAX_LENGTH;
    }
    int GetMaxLength() const {
        return MaxLength;
    }
    int GetLength() const {
        return Length;
    }
    double GetMaxSalary();
    void operator+= (const Employee&);

    friend ostream& operator<< (ostream& O, const Firm& FR);

};

// Human funkcijas
Human::Human() : vards("Miks"), dzimums('v'), dzimsanas_gads(2000) {
}
Human::Human(string var, char dz, int dzg) : dzimsanas_gads(dzg) {
    vards = var;
    dzimums = dz;
}
inline int Human::GetDzimsanasGads() const {
    return dzimsanas_gads;
}
inline void Human::SetDzimsanasGads(int dzimsanas_gads) {
    this->dzimsanas_gads = dzimsanas_gads;
}

ostream& operator<<(ostream& O, const Human& HM){
    O << "Vards = " << HM.vards << ", Dzimums = " << HM.dzimums << ", Dzimsanas gads = " << HM.dzimsanas_gads;
    return O;
}

// Employee funkcijas
Employee::Employee(string var, char dz, int dzg, double alga) : Human(var, dz, dzg) {
    this->alga = alga;
}

ostream& operator<<(ostream& O, const Employee& EM) {
    O << (Human&) EM << ", Alga = " << EM.alga;
    return O;
}

// Firm funkcijas
Firm::~Firm() {
    for (unsigned int i = 0; i < Length; i++)
        delete Nodes[i];
    delete[] Nodes;
}

double Firm::GetMaxSalary() {
    if (Length == 0) return -1;
    double max = 0.0;
    for (unsigned int i = 0; i < Length; i++) {
        if (Nodes[i]->GetAlga() > max) max = Nodes[i]->GetAlga();
    }
    return max;
}

ostream& operator<<(ostream& O, const Firm& FR) {
    for (unsigned int i = 0; i < FR.Length; i++) {
        O << (i + 1) << ". " << *(FR.Nodes[i]) << endl;
    }
    return O;
}

void Firm::operator+= (const Employee& Node) {
    if (Length == MaxLength)
        throw OverflowException();
    else
        Nodes[Length++] = new Employee(
            Node.GetVards(), Node.GetDzimums(), Node.GetDzimsanasGads(), Node.GetAlga()
        );
}

int main()
{
    Firm* F1 = new Firm(3);
    Employee* E1 = new Employee();
    Employee E2("Rainers", 'v', 1999, 755);
    Employee E3("Daiga", 's', 1998, 765);
    Employee E4("Edijs", 'v', 2000, 620);

    cout << "Max Salary: " << F1->GetMaxSalary() << endl;

    try {
        *F1 += *E1;
        cout << "New node has been added successfully!" << endl;
    }
    catch (...) {
        cout << "Error adding node!" << endl;
    }
    delete E1;

    

    try {
        *F1 += E2;
        cout << "\nNew node has been added successfully!" << endl;
    }
    catch (...) {
        cout << "Error adding node!" << endl;
    }

    try {
        *F1 += E3;
        cout << "New node has been added successfully!" << endl;
    }
    catch (...) {
        cout << "Error adding node!" << endl;
    }

    cout << "Current length: " << F1->GetLength() << endl;

    try {
        *F1 += E4;
        cout << "\nNew node has been added successfully!" << endl;
    }
    catch (...) {
        cout << "Error adding node!" << endl;
    }

    cout << "\nDefault maximal length (from CLASS): " << Firm::GetDefaultMaxLength() << "." << endl;
    cout << "Default maximal length (from OBJECT): " << F1->GetDefaultMaxLength() << "." << endl;
    cout << "Maximal length: " << F1->GetMaxLength() << endl;
    cout << "Current length: " << F1->GetLength() << endl;

    cout << *F1;
    cout << "Max Salary: " << F1->GetMaxSalary() << endl;
    cout << endl;

    delete F1;

    return 0;
}