#include <iostream>
#include <fstream>

const int BUFF_SIZE = 1024;
const int MAX_COUNT_FILES = 3;
const int MAX_FILES_NAME = 20;

int unite(char filenames[MAX_COUNT_FILES][MAX_FILES_NAME]) {
	std::ofstream unitFile("unitFile.txt");
	if (!unitFile.is_open()) {
		std::cout << "Error!";
		return -1;
	}

	for (int i = 0; i < MAX_COUNT_FILES; i++)
	{
		std::ifstream file(filenames[i]);
		if (!file.is_open()) {
			std::cout << "Error!";
			return -1;
		}

		while (!file.eof()) {
			char buff[BUFF_SIZE];
			file.getline(buff, BUFF_SIZE);

			unitFile << buff << std::endl;
		}
	}

	if (!unitFile.eof()) {
		std::cout << "Files have been united to a new file!\n";
	}
}

int main() {
	/*std::ofstream file("file1.txt");
	std::ofstream file1("file2.txt");
	std::ofstream file2("file3.txt");*/

	char filenames[MAX_COUNT_FILES][MAX_FILES_NAME] = {"file1.txt", "file2.txt", "file3.txt"};
	unite(filenames);

    return 0;
}