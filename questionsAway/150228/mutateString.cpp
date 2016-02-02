/* 
 ___  ___  ___  ___      ___ _______
|\  \|\  \|\  \|\  \    /  /|\  ___ \
\ \  \\\  \ \  \ \  \  /  / | \   __/|
 \ \   __  \ \  \ \  \/  / / \ \  \_|/
  \ \  \ \  \ \  \ \    / /   \ \  \_|\ \ ___
   \ \__\ \__\ \__\ \__/ /     \ \_______\\__\
 ___\|__|\|__|\|__|\|__|/_____  \|_______\|__|
|\___   ___\\  ___ \ |\   ____\|\  \|\  \
\|___ \  \_\ \   __/|\ \  \___|\ \  \\\  \
     \ \  \ \ \  \_|/_\ \  \    \ \   __  \
      \ \  \ \ \  \_|\ \ \  \____\ \  \ \  \
       \ \__\ \ \_______\ \_______\ \__\ \__\
        \|__|  \|_______|\|_______|\|__|\|__|                
        
        Copyright © 2015 - Hive.Tech - Tyler McKay Hall
            tyler@hive.technology
			       www.hive.technology

	This software is not intended for redistribution, as such it is not fully
  documented or gaurenteed. All rights reserved for use and publication. Permission 
  will be given to those who reasonably request.

    ** More information can be found at www.hive.technology/copywright ** 

	Please contact, any questions will be gladly answered.


Find all permutations of a string
===================================================
- Use Recursion


Explore
============
string ab
ab ba

abc
bac bca
bac abc acb

split up string to parts - insert next letter into each possible position in string
- Recursion


*/

/* Preprocessing */
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

/* Function Prototype */

vector<string> permutate(string s);
string insertCharAt(string word, char c, int i);
int computeIterations(int i);

/* function main begins program execution */
int main(int argc, char const *argv[]) // Grab inputs from command line
{
	/* code */
  for (int i = 1; i < argc; ++i) // For all inputs from command line
  {
    vector<string> listResult = permutate(argv[i]); // Preform all permutations
    string inputClean = argv[i];
    cout << "Total Permutations: " << computeIterations(inputClean.length()) << endl;
    int l = 0;
    for (string result : listResult){
      cout << "Permuated iteration[" << l++ << "]: " << result << endl;
    }
  }

	return 0; /* indicate that program ended successfully */
} /* End Main */

vector<string> permutate(string stringIn){
  std::vector<string> permutations;

  if (stringIn.length() == 0){ // Terminating stack case
      permutations.push_back("");;
      //cout << "End Stack" << endl;
      return permutations;
  }
  
  char firstChar = stringIn.at(0);
  string restOf (stringIn.begin()+1, stringIn.end());

  //cout << "firstChar: " << firstChar << endl << "restOf: " << restOf << endl;

  vector<string> words = permutate(restOf);
  for (string word : words) {
    //cout << "New Chunk: \n\n";
    for (int i = 0; i <= word.length(); i++)
    {
      string newWord = insertCharAt(word, firstChar, i);
      //cout << "NewWord: " << newWord << endl;
      permutations.push_back(newWord);
    }
  }
}

string insertCharAt(string word, char c, int i){
  string start (word.begin(), word.begin() + i);
  string end (word.begin() + i, word.end());
  return start + c + end;
}

int computeIterations(int x) {
  return (x == 1 ? x : x * computeIterations(x - 1));
}