/*
1. Dindyal Jeevesh Rishi
2. Student ID: 2012397
3. Programme: BSc (Hons) Computer Science L1, Group A
4. Module: Computer Programming, ICT 1017Y
5. Date: 01 June 2021
6. Original code implement by me

i wish i had more time

Work well:
-remove common and prevent translation being bias on 100 common words
-implement a verb recognizer in the program
-implement a part which determine how "this" can be translated




improvement to be done:
-implement a part for phrase which are question(same as verb recognizer)
-implement a punctuation system
-implement a function which reset to capital
-recognize name
*/


#include <iostream>
#include <string.h>
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
        if(sentence[i] == ':' || sentence[i] == ' ' || sentence[i] == '.' || sentence[i] == '!' || sentence[i] == '?'||sentence[i] == ','){
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
// class use to store mapping and get access to it
class mapping
{
private:
    string eng;
    string kr;
    int freq;
public:
    mapping(){}
    void setFreq(int f){freq = f;return;}
    void setEng(string e){eng = e;return;}
    void setKr(string k){kr = k;return;}
    int getFreq(){return freq;}
    string getEng(){return eng;}
    string getKr(){return kr;}
    ~mapping(){}
};


//function use to check if english word is a common word and return the equivalent, if not a common word retrun "" to be able to check in the main
string redundant(string w, vector <mapping> cw)
{
    for(int i = 0; i<cw.size();i++)
    {
        if(cw[i].getEng()==w)
        {
            return cw[i].getKr();
        }
    }
    return "";
}

//function use to check if the equivalent english word in kreol is not a common word, if yes it return true then use it in main,
//else return false then allow to be use as translation
bool checkcommon(string w, vector <mapping> cw)
{
    for(int j = 0; j < cw.size();j++)
    {
        if(cw[j].getKr() == w)
            return true;
    }
    return false;
}


int main()
{	
    string x,y,sentenceFromFile;
    bool verb = true;
    int z;
    vector <mapping> m;
    
    //reading from file of mapping//
	ifstream infile;
    infile.open("mapping_result.txt",ios::in);
    while(infile>>x>>y>>z){
        mapping temp;
        temp.setEng(x);
        temp.setKr(y);
        temp.setFreq(z);
        m.push_back(temp);
    }
    infile.close();
    int index;

    //readinf from file of common word//
    vector <mapping> commonWord;
    infile.open("common_Word.txt",ios::in);
    while(infile>>x>>y){
        mapping cw;
        cw.setEng(x);
        cw.setKr(y);
        cw.setFreq(0);
        commonWord.push_back(cw);
    }
    infile.close();
//creat file for outputing the translated sentences
    ofstream outtrans;
    outtrans.open("translation_output.txt");
    vector <string> outphrase;
//retrieve each sentence in the english file then translate it in the same loop
    infile.open("1000_English_A_110521_Test.txt");
    while(!infile.eof()){
        //retrieve sentence and store in temp1 as temporary memory
        getline(infile,sentenceFromFile);
        Sentences temp1;
        temp1.setSentence(sentenceFromFile);

        //split sentence into word
        vector <string> EngWord;
        EngWord = temp1.getWords();

        //loop throught the vector EngWord
        for(auto i = EngWord.begin(); i != EngWord.end(); ++i)
        {
            if(temp1.isSentenceAQuestion() == true && i == EngWord.begin() && (*i == "are" || *i == "is"))
            {
                outphrase.push_back("eski");
            }
            //variable is use for check constraint, moreover vector template doesnt have some build in function which string give
            string wordtemp = *i;
            z=0;//z is used as counter to check if word is number

            //increment z for each number in the word
            for(char c : wordtemp)
            {
                if(c>=48 && c<=57)
                {z++;}
            }
            //if z is equal to the world length hence the word is completely a number
            //there is some collision with hexadecimal
            //sometime give 1 for word
            if(z == wordtemp.length())
            {
                outphrase.push_back(wordtemp);
            }
            //i try to implement a verb recognizer where it pop the previous word and store the appriopriate translation of english conjugation to kreol
            else if(wordtemp.length() >=  3){
                if(i != EngWord.begin() && wordtemp.substr(wordtemp.length() - 3) == "ing"){
                    if(*(i- 1) == "was" || *(i - 1) == "were"){
                        outphrase.pop_back();
                        outphrase.push_back("ti");
                        outphrase.push_back("pe");
                        }
                    else if(*(i - 1)== "be" && (i-1)!=EngWord.begin() && *(i-2) == "will"){
                        outphrase.pop_back();
                        outphrase.pop_back();
                        outphrase.push_back("pe");
                        }
                    else if(*(i-1) == "been"){
                        if(*(i - 2) == "have" || *(i-2) == "has"){
                            if(*(i - 3) == "will"){
                                outphrase.pop_back();outphrase.pop_back();outphrase.pop_back();
                                outphrase.push_back("pou");outphrase.push_back("inn");
                            }
                            else
                            {
                                outphrase.pop_back();outphrase.pop_back();
                                outphrase.push_back("finn");
                            }
                        }
                    }
                    else if(*(i-1 ) == "is"|| *(i-1) == "are")
                    {
                        outphrase.push_back("pe");
                    }
                }
                else if(i != EngWord.begin() && (wordtemp.substr(wordtemp.length() - 2) == "ed" || wordtemp.substr(wordtemp.length() - 2) == "ied")){
                    if( *(i-1) == "have" || *(i-1) == "has"){
                        if(*(i - 2) == "will"){
                            outphrase.pop_back();outphrase.pop_back();
                            outphrase.push_back("pou");
                            outphrase.push_back("finn");
                        }
                        else{
                            outphrase.pop_back();
                            outphrase.push_back("finn");
                        }
                    }        
                }   
                else if(i != EngWord.begin() && *(i-1) == "will")
                {
                    outphrase.pop_back();
                    outphrase.push_back("pou");
                }
                else{
                    verb = false;
                    y = redundant(wordtemp,commonWord);
                    if(y == "."){
                        outphrase.push_back(y);
                        outphrase.pop_back();
                    }
                    else if(y != "")
                    {
                        outphrase.push_back(y);
                    }
                    else{
                        for(int j = 0; j < m.size(); j++)
                        {
                            if(*i == m[j].getEng() && !checkcommon(m[j].getKr(),commonWord))
                            {
                                index = j;
                                break;
                            }
                        }
                    //check if previous word is a this, if yes then -la is added
                    if(i != EngWord.begin() && *(i - 1) == "this")
                    {
                        string addthis = m[index].getKr();
                        addthis = addthis + "-la";
                        cout<<addthis<<endl;
                        outphrase.push_back(addthis);
                    }
                    else
                    {
                        outphrase.push_back(m[index].getKr());
                    }
                    }
                }
            }
            //till here everything above is a block of code to determine verb conjugation
            else{
                //if the word is not a verb it will enter here
                verb = false;
                //state word not verb to prevent from adding a word( there is code which add the verb below the upward code was use to push back the correct word before the word)
                y = redundant(wordtemp,commonWord);//send the english word to check if it is a common word 
                if(y == "."){//if a dot is received hence it is a is or are
                    //check if the previous word is a this and push "se" for correct syntax of kreol 
                    if(i != EngWord.begin() && *(i - 1) == "this")
                    {
                        outphrase.push_back("se");
                    }
                    else
                    {
                        //there is no is or are in kreol hence pop the translation from the vector 
                        outphrase.push_back(y);
                        outphrase.pop_back();
                    }
                }
                else if(y == "/")
                {
                    //if condition to discard this word which is / use as check 
                    outphrase.push_back(y);
                    outphrase.pop_back();
                }
                else if(y != "")
                {
                    outphrase.push_back(y);
                    //if common word is obtain it is push in the translation
                }
                else{
                    //if not found then it is not a common word so search in map and determine if it is not a common word in kreol
                    for(int j = 0; j < m.size(); j++)
                    {
                        if(*i == m[j].getEng() && !checkcommon(m[j].getKr(),commonWord))
                        {
                            index = j;
                            break;
                        }
                    }
                    //check if previous word is a this, if yes then -la is added
                    if(i != EngWord.begin() && *(i - 1) == "this")
                    {
                        string addthis = m[index].getKr();
                        addthis = addthis + "-la";
                        cout<<addthis<<endl;
                        outphrase.push_back(addthis);
                    }
                    else
                    {
                        outphrase.push_back(m[index].getKr());
                    }
                }
            }
            //if verb is true hence the verb conjugation has work and we need to add the verb in kreol 
            //same process as above, search in mapping then check if not a common word it is push 
            if(verb)
            {
                y = redundant(wordtemp,commonWord);
                cout<<y<<endl;
                if(y == "."){
                    outphrase.push_back(y);
                    outphrase.pop_back();
                }
                else if(y != "")
                {
                    outphrase.push_back(y);
                }
                else{
                    for(int j = 0; j < m.size(); j++)
                    {
                        if(*i == m[j].getEng() && !checkcommon(m[j].getKr(),commonWord))
                        {
                            index = j;
                            break;
                        }
                    }
                outphrase.push_back(m[index].getKr());
                }
            }

        } 
        //the loop push every element in the file 
        //check if it is first in the vector and -32 to it to become capital 
        //then add a punctuation at the back
        for(auto j = outphrase.begin(); j != outphrase.end(); ++j){
            if(j == outphrase.begin())
            {
                string kword = *j;
                kword[0] = kword[0] - 32;
                outtrans<<kword<<" ";
            }
            else if(j == outphrase.end()-1)
            {
                outtrans<<*j;
            }
            else
            {
                outtrans<<*j<<" ";
            }
        }
        outtrans<<"."<<endl;
        verb = true;
        outphrase.clear();

    }

    infile.close();
    outtrans.close();
    return 0;
}