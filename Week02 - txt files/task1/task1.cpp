#include <iostream>
#include <fstream>

const int BUFF_SIZE = 1024;
//const char FILE_NAME[] = "file.txt";

int main()
{
	//std::ofstream file(FILE_NAME); - create a file /in the "task1" folder/

	std::ifstream file("file.txt"); //(FILE_NAME);
	if (!file.is_open()) {
		std::cout << "Error!" << std::endl;
		return -1;
	}

	std::ofstream file1("newFile.txt");
	if (!file1.is_open()) {
		std::cout << "Error!" << std::endl;
		return -1;
	}

	while (!file.eof()) {
		char buff[BUFF_SIZE];
		file.getline(buff, BUFF_SIZE);

		file1 << buff << std::endl;
	}

	if (!file1.eof()) {
		std::cout << "File data has been copied to a new file!\n";
	}

	file.close();
	file1.close();

    return 0;
}