/*
1. Dindyal Jeevesh Rishi
2. Student ID: 2012397
3. Programme: BSc (Hons) Computer Science L1, Group A
4. Module: Computer Programming, ICT 1017Y
5. Date: 01 June 2021
6. Original code implement by me
*/

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <ostream>
#include <fstream>
#include <bits/stdc++.h>
#include <map>
using namespace std;

class Sentences {

    private:
        //string variable to store one sentence
        string sentence;
        //integer variable to store the number of words in one sentence
        int numWords;
        //boolean variable to store whether a sentence is a question
        bool isQuestion = false;
        //vector of type string to store the words in a sentence
        vector<string> words;

    public:
        Sentences();
        //Sentences(string s);
        //get and set method to retrieve a sentence and to change it
        string getSentence();
        void setSentence(string s);
        //method to return the number of words in a sentence
        int getNumWords();
        //method to determine whether a sentence is a question
        bool isSentenceAQuestion();
        //method to return all the words in a sentence (as a vector)
        vector<string> getWords();
        //sentences less than n words
        bool isSentenceLessThan(int n);
        //sentences greater than or equal to n words
        bool isSentenceGreaterThanOrEqualTo(int n);
        ~Sentences();
};

Sentences::Sentences(){}

string Sentences::getSentence(){
    return sentence;
}

void Sentences::setSentence(string s){
    sentence = s;
}

int Sentences::getNumWords(){
    int numChars = sentence.length();
    vector<string> setOfWords;
    string currentWord;
    for(int i=0;i<numChars;i++){
        if(sentence[i] == ' ' && !currentWord.empty()){
            setOfWords.push_back(currentWord);
            currentWord.clear();
        }
    else{
        currentWord += sentence[i];
        }
    }

    return (setOfWords.size() + 1);
}

vector<string> Sentences::getWords(){
    int numChars = sentence.length();
    string currentWord;
    words.clear();

    for(int i=0;i<numChars;i++){
        if(sentence[i] == ':' || sentence[i] == '0' || sentence[i] == '1' || sentence[i] == '2' || sentence[i] == '3' || sentence[i] == '4' || sentence[i] == '5' || sentence[i] == '6' || sentence[i] == '7' || sentence[i] == '8' || sentence[i] == '9' || sentence[i] == ' ' || sentence[i] == '.' || sentence[i] == '!' || sentence[i] == '?'||sentence[i] == ','){
        	if(currentWord != ""){
            words.push_back(currentWord);
            currentWord.clear();}
        }
        else {
            if(i == 0)
            {
                sentence[i]+=32;
                currentWord += sentence[i];
            }
            else
            {
                currentWord += sentence[i];
            }

        }
    }

    return words;
}

bool Sentences::isSentenceAQuestion(){
    int numChars = sentence.length();
    if(sentence[numChars-1] == '?')
        isQuestion = true;
    return isQuestion;
}

bool Sentences::isSentenceLessThan(int n){
    int numberWords = getNumWords();

    if(numberWords < n) {
        return true;
    }
    else {
        return false;
    }
}

bool Sentences::isSentenceGreaterThanOrEqualTo(int n){
    int numberWords = getNumWords();

    if(numberWords >= n) {
        return true;
    }
    else {
        return false;
    }
}

Sentences::~Sentences(){}

int main()
{
    double num = 0;
    string sentenceFromFile;
    vector <Sentences> RealValue;
    vector <Sentences> test;

    ifstream infile;
    infile.open ("translation_output.txt");
    while(!infile.eof()) {
        getline(infile,sentenceFromFile);
        Sentences temp;
        temp.setSentence(sentenceFromFile);
        test.push_back(temp);
    }
    infile.close();

    infile.open ("1000_KM_A_110521_Test.txt");
    while(!infile.eof()) {
        getline(infile,sentenceFromFile);
        Sentences temp;
        temp.setSentence(sentenceFromFile);
        RealValue.push_back(temp);
    }
    infile.close();
    double count = 0,rvnum = 0;

    for(int i = 0; i< 1000; i++)
    {
        vector <string> rvword;
        rvword = RealValue[i].getWords();

        vector <string> tword;
        tword = test[i].getWords();
        rvnum = rvnum + rvword.size();
        if(rvword == tword)
        {
            num++;
            cout<<test[i].getSentence()<<endl;
        }

        if(rvword.size() >= tword.size())
            for(int j = 0;j< tword.size();j++)
                if(rvword[j]==tword[j])
                {
                    count++;
                }
        else
        {
            for(int j = 0;j<rvword.size(); j++)
                if(rvword[j]==tword[j])
                {
                    count++;
                }
        }
    }cout<<endl;
    cout<<"Number of kreol word: "<<rvnum<<endl;
    cout<<"Number of correct translated Word: "<<count<<endl;
    double percentage;
    percentage = count/rvnum;
    cout<<"Number of correct sentence: "<<num<<endl;
    cout<<endl;
    cout<<"Percentage of good word: "<<percentage*100<<"%"<<endl;
    cout<<"Percentage of perfect match: "<<((num/RealValue.size())*100)<<"%"<<endl;
    return 0;
}