#include <iostream>
#include <fstream>
#include <cstring>

struct Person {
    char name[23] = ""; //not using dinamic memory
    unsigned int salary = NULL;
};

size_t getFileSize(std::ifstream& file) {
    size_t currentPos = file.tellg();
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();

    file.seekg(currentPos);
    return size;
}

void readFromFile(Person*& p, size_t& personCount, std::ifstream& file) {
    size_t sizeOfFile = getFileSize(file);
    personCount = sizeOfFile / sizeof(Person);
    p = new Person[personCount];
    file.read((char*)p, sizeOfFile);
}

int findAverageSalary(const Person* p, int numPeople) {
    int totalSalary = 0;
    for (int i = 0; i < numPeople; i++) {
        totalSalary += p[i].salary;
    }

    return totalSalary / numPeople;
}

void createPerson(Person& p, const char* name, unsigned int salary) {
    strcpy_s(p.name, name);
    p.salary = salary;
}

void saveToFile(const Person* p, size_t count, std::ofstream& file) {
    file.write((const char*)p, count * sizeof(Person));
}

int main() {
    Person* arr;
    size_t count;
    std::ifstream file("people.dat", std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error!\n";
        return -1;
    }

    readFromFile(arr, count, file);
    std::cout << "People who earn above the average salary:\n";
    for (int i = 0; i < count; i++) {
        if (arr[i].salary > findAverageSalary(arr, count)) {
            std::cout << "name: " << arr[i].name << ", salary: " << arr[i].salary << std::endl;
        }
        //std::cout << "name: " << arr[i].name << ", salary: " << arr[i].salary << std::endl; //print all people data from the file
    }
    delete[] arr;

    size_t counterAdded = 0;
    std::cout << "\n____________________________________________________________" << std::endl << "Add people: \n - number of people you will add: ";
    std::cin >> counterAdded;

    Person* newPersonArray = new Person[counterAdded];
    char name[100];
    int salary;
    for (int i = 0; i < counterAdded; i++) {
        std::cout << "Name: ";
        std::cin.ignore(); //if first cin a number and then cin a whole line you need to add cin.ignore()
        std::cin.getline(name, sizeof(name));
        std::cout << "Salary: ";
        std::cin >> salary;
        createPerson(newPersonArray[i], name, salary);
    }

    std::ofstream fileAdd("people.dat", std::ios::binary | std::ios::app);

    if (!fileAdd.is_open()) {
        std::cout << "Error!\n";
        delete[] newPersonArray;
        return -1;
    }

    saveToFile(newPersonArray, counterAdded, fileAdd);
    std::cout << "New people's data was added to the file successfully!" << std::endl;
    delete[] newPersonArray;

    return 0;
}