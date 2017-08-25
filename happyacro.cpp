#include <iostream>
#include <fstream>
#include <string>
#include <time.h> 

using namespace std;

int main(int argc, char * argv[]) {
	if (argc != 3) {
		cout << "USAGE: happyacro <acronymn> <word file>" << endl;
		return 1;
	}

	string acronym(argv[1]);
	string wordFile(argv[2]);

	cout << "Welcome to HAPPY:/ACRO!!!!" << endl << endl;
	cout << "Your motivational acronym: " << acronym << endl;
	cout << "Word file: " << wordFile << endl;


	string line; 
	ifstream wordFileStream(wordFile);
	if (!wordFileStream.is_open()) {
		cout << "Can't read word file: " << wordFile << endl;
		return 1;
	}

	cout << "Sorting words into files per letter." << endl;

	ofstream letterFiles[acronym.length()];
	for (int i = 0; i < acronym.length(); i++) {
		string filename = string(1,acronym.at(i)) + ".txt";
		cout << "Opening letter file: " << filename << endl;
		letterFiles[i].open(filename.c_str());		
		if (!letterFiles[i].is_open()) {
			cout << "Can't open letter file: " << filename << endl;
			return 1;
		}
	}

	int wordcount[acronym.length()];
	for (int i = 0; i < acronym.length(); i++) {
		wordcount[i] = 0;
	}
	string::size_type index = 0;
	while (getline(wordFileStream,line)) {
		if (line.length() == 0) {
			continue;
		}
		char firstCharacter = line.at(0);		
		//see if our acronym has this letter in it
		index = acronym.find(firstCharacter);
		if (index == std::string::npos) { 
			continue;
		}
		letterFiles[index] << line << endl;
		wordcount[index]++;
	}

	for (int i = 0; i < acronym.length(); i++) {
		letterFiles[i].close();
	}

    wordFileStream.close();

    cout << "Finished sorting words into files per letter." << endl;
    for (int i = 0; i < acronym.length(); i++) {
    	cout << "Words that start with the letter '" << acronym.at(i) << "': " << wordcount[i] << endl;
    }

    time_t startTime;
    time(&startTime);
    double seconds = difftime(startTime,time(NULL));
    cout << "Seconds elapsed: " << seconds << endl;

	return 0;
}