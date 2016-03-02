#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>

using namespace std;

void main() {
	ofstream file;
	file.open("test.txt", ios::out | ios::binary);
	if (file.is_open())
	{
		//file << "Hello!\n";
		file << 77 << endl;
		file << 3 << endl;
		
		//string s = "Hello!\n";
		//int i = 77;
		//float f = 3.14f;

		//file.write(s.c_str(), s.size());
		//file.write((char *)&i, 4);
		//file.write((char *)&f, 4);

		file.close();
	}
	else
	{
		cout << "Can't open file!\n";
	}


	ifstream read;
	read.open("test.txt", ios::binary);

	while (!read.eof())
	{
		int buf;
		read >> buf;
		if (buf == 77) {
			cout << "INT\n";
			cout << buf << endl;
		}	
	}

	read.close();
}