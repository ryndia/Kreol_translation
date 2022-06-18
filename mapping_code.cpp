/*
1. Dindyal Jeevesh Rishi
2. Student ID: 2012397
3. Programme: BSc (Hons) Computer Science L1, Group A
4. Module: Computer Programming, ICT 1017Y
5. Date: 01 June 2021
6. Original code implement by me

improvement to be done:
-remove s from plural word
-remove common word 
-improve verb mapping
-increase mapping number with more data
-decrease the time complexity of the program if possible
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
//i edit the getWord to remove map with white space
//use the getWord to get lowercase

vector<string> Sentences::getWords(){
    int numChars = sentence.length();
    string currentWord;
    words.clear();

    for(int i=0;i<numChars;i++){
        if(sentence[i] == ':' || sentence[i] == ' ' || sentence[i] == '.' || sentence[i] == '!' || sentence[i] == '?'||sentence[i] == ','){
        	if(currentWord != ""){
            words.push_back(currentWord);
            currentWord.clear();}
        }
        else {
            if(sentence[i]>= 65 and sentence[i]<=90)
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
//function use as comparator to implement the sort function , return which one is the greater between a and b(a boolean value return if a > b : 1, a<b : 0)
bool cmp(pair<string, int>& a,
         pair<string, int>& b)
{
    return a.second > b.second;
}

Sentences::~Sentences(){}


int main()
{	
	int total = 0;
    bool found = false;
	string sentenceFromFile;
	vector <Sentences> KreolSent;
	vector <Sentences> EngSent;
    vector < pair <string,int> > mapout;
    //read file for kreol sentence
	ifstream infile;
	infile.open ("1000_KM_A_040521.txt");
    while(!infile.eof()) {
        getline(infile,sentenceFromFile);
        Sentences temp;
    	temp.setSentence(sentenceFromFile);
        KreolSent.push_back(temp);
    }
	infile.close();

    //read file for english sentence
	infile.open ("1000_English_A_040521.txt");
    while(!infile.eof()) {
        getline(infile,sentenceFromFile);
        Sentences temp;
		temp.setSentence(sentenceFromFile);
     EngSent.push_back(temp);
    }
	infile.close();
    //output file for mapping
	ofstream outfile;
	outfile.open("mapping_result.txt");

    //vector <string> output; variable use to cumulate frequency, no more in use now
    for(int i = 0; i<1000; i++)
    {
    	vector <string> kw;
    	kw = KreolSent[i].getWords();

    	vector <string> ew;
    	ew = EngSent[i].getWords();

    	for(auto it = ew.begin();it != ew.end(); ++it)
    	{
    		for(auto ktemp = kw.begin(); ktemp != kw.end(); ++ktemp){
    			string st = *it+" "+*ktemp;// cross multiple the 2 sentence making pair of words
    			for(auto &p : mapout)
                    if(st == p.first){
                    {
                        p.second++;
                        found = true;
                        break;
                    }
                }
                if(!found)
                {
                    mapout.push_back(make_pair(st,1));
                }
                found = false;
    		}

    	}
    }
// first attempt to cumulate frequency, it works
/*
auto j = output.begin();
auto temp1 = output.begin();

while(!output.empty())
{
	auto i = output.front();
	while(j != output.end() && !output.empty())
	{
		if(i == *j)
		{     
            temp1++;
			output.erase(j);
			num++;
            j = temp1;
		}
        else{
        temp1++;
		++j;}
	}
	total = total + num;
    mapout.push_back(make_pair(i,num));
	num = 0;
	if(!output.empty())
		{
			j = output.begin();
            temp1 = output.begin();
		}
}
*/
//sort the mapping
sort(mapout.begin(), mapout.end(), cmp);

//writing into file
for(auto & it : mapout)
{
    outfile<<it.first<<"\t"<<it.second<<endl;
}
outfile.close();

//retrieve first value of the mapout
for(auto & it :mapout)
{
    cout<<"Most use word in english:Kreol : "<<it.first<<"("<<it.second<<" example in map)"<<endl;
    break;
}

cout<<"Total Mapping: "<<mapout.size()<<endl;
return 0;
}
