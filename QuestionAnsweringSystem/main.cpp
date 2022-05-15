#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdlib.h>
using namespace std;

void splitToWords(string words, string finalArr[], int size, int* index);
void printAnswer(string arrScript[], string arrQuestion[], int indexScript, int indexQuestion);
bool porterStemmer(string wordFirst, string wordSecond);

int main(void) {
	ifstream script, questions;
	int i, k = 0, averageSize, indexQ = 0, indexS = 0, count = 0, index = 0, numberofQuestions = 1;
	string str, questionSentence, answerWords;
	string questionWordsArray[300], scriptWordsArray[300];

	string questionFileName, scriptFileName;
	cout << "Enter the name of the script's file(.txt): ";
	cin >> scriptFileName;
	cout << "Enter the name of the question's file(.txt): ";
	cin >> questionFileName;

	system("cls");

	clock_t baslangic = clock(), bitis;
	questions.open(questionFileName);

	while (getline(questions, str)) {//Getting questions one by one
		for (i = 0; i < str.size(); i++) {
			if (str[i] == ',') // If the character is a coma, loop continues.
				continue;
			if (str[i] != '?') { // Retrieves all characters until the character has a question mark
				questionSentence += tolower(str[i]); // Saves all characters until the character has a question mark
			}
			else { // If the character is a question mark then the loop stops.
				break;
			}
		}
		cout << numberofQuestions << ")" << questionSentence << "?" << endl;// Print the question that the loop takes.
		averageSize = (questionSentence.size() / 6) + 6; //Average number of common characters between question and script
		str = "";
		script.open(scriptFileName);
		i = 0;
		while (getline(script, str)) {//Getting characters from the script
			for (k = 0; k <= questionSentence.size(); k++) {//The characters of question. One by one
				while (str[i] == questionSentence[k]) {//Match common characters between the question and the text
					count++;
					i++;
					k++;
				}
				if (count >= averageSize) { // Is common characters greater than averageSize
					i -= 1;
					while (1) { //Go to starting character to the letter.
						if (str[i] == '.' || str[i] == ' ? ' || str[i] == '!') {
							break;
						}
						i--;
					}
					index = (i + 2);
					while (1) {//Saves the matching senteces
						if (str[index] == '.' || str[index] == '?' || str[index] == '!')
							break;
						answerWords += tolower(str[index]);
						index++;
					}
					break;
				}
				else {
					count = 0;
				}
				if (k == questionSentence.size()) {//Skip the character of the script if k is equal to size of the question.
					k = 0;
					i++;
				}
			}

		}
		script.close();

		splitToWords(answerWords, scriptWordsArray, answerWords.size(), &indexS);
		splitToWords(questionSentence, questionWordsArray, questionSentence.size(), &indexQ);
		printAnswer(scriptWordsArray, questionWordsArray, indexS, indexQ);
		cout << "\n" << endl;

		numberofQuestions++;
		//Reseting the needed parts below
		answerWords = "";
		questionSentence = "";
		str = "";
		count = 0;
		index = 0;
		indexQ = 0;
		indexS = 0;
	}

	questions.close();
	bitis = clock();
	float time;
	time = (float)(bitis - baslangic) / CLOCKS_PER_SEC;
	cout << "Per question found in " << time / numberofQuestions << " second" << endl;
	cout << "All questions found in " << time << " second";
}

void splitToWords(string words, string finalArr[], int size, int* index)//Saves the words in an array
{
	int i;
	string word;
	for (i = 0; i <= size; i++) {
		if (words[i] != ' ') {
			if (words[i] == ',')
				continue;
			if (i == size) {
				finalArr[*index] = word;
				*index += 1;
				word = "";
				break;
			}
			word += words[i];
		}
		else
		{
			finalArr[*index] = word;
			*index += 1;
			word = "";
		}
	}
}

void printAnswer(string arrScript[], string arrQuestion[], int indexScript, int indexQuestion)//Prints the answer
{
	int i, k, counter;
	cout << "Answer: ";
	for (i = 0; i < indexScript; i++) {
		counter = 0;
		for (k = 0; k <= indexQuestion; k++) {
			if (arrScript[i] == arrQuestion[k]) {
				counter++;
			}
			else {
				if (porterStemmer(arrScript[i], arrQuestion[k]))
					counter++;
			}
		}
		if (counter == 0) {
			cout << arrScript[i] << " ";
		}
	}
}

bool porterStemmer(string wordFirst, string wordSecond)//Checks for only 1 extra letter not common in two words
{
	int sizeBig, sizeLow, counter = 0;
	if (wordFirst.size() > wordSecond.size()) {
		sizeLow = wordSecond.size();
		sizeBig = wordFirst.size();
	}
	else if (wordFirst.size() < wordSecond.size()) {
		sizeBig = wordSecond.size();
		sizeLow = wordFirst.size();
	}
	else {
		sizeBig = 0;
		sizeLow = 0;
	}
	if (sizeBig - sizeLow == 1) {
		for (int i = 0; i < sizeLow; i++) {
			if (wordFirst[i] == wordSecond[i])
				counter++;
		}
		if (counter >= sizeLow)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}
