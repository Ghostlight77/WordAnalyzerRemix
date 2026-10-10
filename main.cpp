#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct FileNotFound {
	string message;
	string filename;
};

vector<string> load_words(string filename);

void display(pair<string, int> p) {
    cout << p.first << "=" << p.second << " ";
}

bool over_1(pair<string, int> p) {
    return p.second > 1;
}

int main()
{
	cout << "Welcome to my Word Analyzer App!\n\n";

	string filename = "";
	cout << "Enter a File name: ";
	cin >> filename;

	vector<string> words;

	try
	{
		words = load_words(filename);
	}
	catch (const FileNotFound e)
	{
		cout << e.message << "\n";
		cout << "You entered: " << e.filename << "!\n"
			<< "Closing program...\n\n";
		return 0;
	}

	cout << words.size() << " WORDS:\n";
	for (string word : words){
		cout << word << ' ';
	}


	cout << "\n\n";

	//find logest word
	string longestWord = "";
	for (string word : words)
	{
		if (word.length() > longestWord.length()){
			longestWord = word;
		}
	}

	cout << "Longest Word: " << longestWord << "\n\n";

	map<string, int> word_counts;
    	for (string word : words) {
        	word_counts[word]++;
    	}

	//steep5
	cout << "COUNT PER WORD: ";
    	for_each(word_counts.begin(), word_counts.end(), display);
    	cout << "\n\n";

	//step6
	int duplicate_count = count_if(word_counts.begin(), word_counts.end(), over_1);
    	cout << duplicate_count << " DUPLICATE WORDS\n\n";

	//ask the user for a word to search for
	string searchWord = "";

	cout << "Enter a word to search for: ";
	cin >> searchWord;

	int count = 0;

	for (string word : words)
	{
		if (word.find(searchWord) != string::npos){
			count++;
		}
	}

	cout << searchWord << " appears " << count << " time(s)\n\n";

	return 0;
}

// load words from the file into a vector
vector<string> load_words(string filename)
{
	vector<string> words;
	ifstream inputfile(filename);

	if (inputfile){
		string word;
		while (inputfile >> word){
			words.push_back(word);
		}
		inputfile.close();
		return words;
	} else
	{
		FileNotFound error;
		error.message = "File not found!";
		error.filename = filename;
		throw error;
	}
}
