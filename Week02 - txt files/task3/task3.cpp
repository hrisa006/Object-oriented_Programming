#include <iostream>
#include <fstream>
#include <cstring>

const int BUFFER_SIZE = 1024;

void reverseFileData(char buff[BUFFER_SIZE]) {
    int counter = 0;
    
    for (int i = strlen(buff) - 1; i >= strlen(buff) / 2;  --i) {
        char letter = buff[counter];
        buff[counter] = buff[i];
        buff[i] = letter;

        counter++;
    }
}

int main() {
    std::ofstream newFile("newFile.txt");
    if (!newFile.is_open()) {
        std::cout << "Error!\n";
        return -1;
    }

    std::ifstream file("file.txt");
    if (!file.is_open()) {
        std::cout << "Error!\n";
        return -1;
    }

    while (!file.eof()) {
        char buff[BUFFER_SIZE];
        file.getline(buff, BUFFER_SIZE);
        reverseFileData(buff);

        newFile << buff << std::endl;
    }

    if (!newFile.eof()) {
        std::cout << "File data has been reversed and pasted to a new '.txt' file!\n";
    }

    return 0;
}