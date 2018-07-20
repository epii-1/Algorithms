//Leif Eriksson
#include <string>
#include <fstream>
#include <iostream>
#include <set>

using namespace std;

void fileWork(const string& fileName, ofstream& outFile, bool is_h, set<string>& imports) {
	ifstream ifile;
	ifile.open(fileName);
	string s;
	set<string> toImport;
	string name;
	int pos;
	while (getline(ifile, s)) {
		if (s.find("#include ") != -1) {
			if (s.find("#include <") != -1) {
				pos = s.find(">", 10);
				name = s.substr(10, pos - 10);
				if (imports.insert(name).second)
					outFile << s << "\n";
			}
			else{
				pos = s.find("\"", 10);
				name = s.substr(10, pos - 10);
				if (imports.insert(name).second) {
					if (is_h)
						toImport.insert(name);
					else 
						fileWork(name, outFile, name.find(".h") != -1, imports);
				}
			}
		}
		else
			outFile << s << "\n";
	}

	for(const string& file : toImport)
		fileWork(name, outFile, name.find(".h") != -1, imports);

	ifile.close();

}

int main() {
	string fileName;
	getline(cin, fileName);
	ofstream ofile;
	ofile.open("out.cpp");
	set<string> imports;

	fileWork(fileName, ofile, false, imports);

	ofile.close();
}