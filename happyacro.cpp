#include <iostream>
#include <fstream>
#include <string>
#include <time.h> 

using namespace std;

void generateAcronyms(string &acronym, time_t &startTime, int index, string &acronymSoFar, long &count, long reportingInterval);

int main(int argc, char * argv[]) {
	if (argc != 4) {
		cout << "USAGE: happyacro <acronymn> <word file> <reporting interval>" << endl;
		return 1;
	}

	string acronym(argv[1]);
	string wordFile(argv[2]);
	long reportingInterval = atol(argv[3]);

	cout << "Welcome to HAPPY:/ACRO!!!!" << endl << endl;
	cout << "Your motivational acronym: " << acronym << endl;
	cout << "Word file: " << wordFile << endl;
	cout << "Reporting interval: Report every " << reportingInterval << " acronymns generated" << endl << endl;

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
		//cout << "Opening letter file: " << filename << endl;
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

    cout << "Finished sorting words into files per letter." << endl << endl;
    for (int i = 0; i < acronym.length(); i++) {
    	cout << "Words that start with the letter '" << acronym.at(i) << "': " << wordcount[i] << endl;
    }

    cout << endl << "Now generating acronyms!" << endl;

    time_t startTime;
    time(&startTime);

    string acronymSoFar("");
    long count = 0;
    generateAcronyms(acronym, startTime, 0, acronymSoFar, count, reportingInterval);

	return 0;
}

void generateAcronyms(string &acronym, time_t &startTime, int index, string &acronymSoFar, long &count, long reportingInterval) {
	string filename = string(1, acronym.at(index)) + ".txt";
	//cout << "Opening letter file: " << filename << endl;
	ifstream fileStream(filename);
	if (!fileStream.is_open()) {
		cout << "Can't open letter file: " << filename << endl;
		return;
	}

	string line;
	long acroCount = 0;
	while (getline(fileStream,line)) {
		string currentAcronym(acronymSoFar);
		currentAcronym += " " + line; 
		acroCount++;
		if (index == (acronym.length() - 1)) {
			count++;
			if (count % reportingInterval == 0) {
				double seconds = difftime(time(NULL), startTime);
				long perSecond = 0;
				if (seconds > 0) {
					perSecond = (long) ((double)count) / seconds;
				}
	    		cout << "Seconds elapsed: " << seconds << ", count: " << count << ", per second: " << perSecond << endl;
	    		cout << "Last acronym: " << currentAcronym << endl; 
			}
			//cout << currentAcronym << endl;
		} else {
			generateAcronyms(acronym, startTime, index + 1, currentAcronym, count, reportingInterval);
		}
	}

	//cout << "Closing letter file: " << filename << endl;
	fileStream.close();
}