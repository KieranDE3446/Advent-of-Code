#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

//The new function of this program is to calculate the simularity score
//The simularity score is defined as the number of times any number in the first vector appears in the second vector
//For example, vector left = 3,4,2,1,3,3 and vector right = 4,3,5,3,9,3
//The number 3 appears 3 times in the right vector, therfore: score += (3 * 3) = 9
//The number 4 appears 1 time in the right vector, therfore: score += (4 * 1) = 13 
//The number 2 appears 0 times in the right vector, therfore: score += (2 * 0) = 13
//The number 1 appears 0 times in the right vector, therfore: score += (1 * 0) = 13
//The number 3 appears 3 times in the right vector, therfore: score += (3 * 3) = 22
//The number 3 appears 3 times in the right vector, therfore: score += (3 * 3) = 31
//The total simularity score is 31

//So the logic is that we want to iterate through the left vector, for each element, count the number of times it appears in the right vector
//Then multiply the element by the count and add it to the score


int main(){

    vector<int> left;
    vector<int> right;
    string line;
    ifstream inFile;

    inFile.open("input.txt");
    while (getline(inFile, line)){
        //split the line into two numbers
        size_t spaceIndex = line.find(' ');
        int leftNum = stoi(line.substr(0, spaceIndex));
        int rightNum = stoi(line.substr(spaceIndex + 1));
        left.push_back(leftNum);
        right.push_back(rightNum);
    }
    
    inFile.close();

    int sameval = 0;
    int simularityScore = 0;
    for (int i = 0; i< left.size(); i++) {
        cout << left[i] << endl;
        for (int j = 0; j < right.size(); j++) {
            if (right[j] == left[i]) {
                //cout << "Found a match for " << left[i] << " in right vector." << right[j] << endl;
                sameval += 1;
            }
            else{
                //cout << right[j] << " does not match " << left[i] << endl;
            }
    }
    simularityScore += left[i] * sameval;
    //cout << "Current simularity score: " << simularityScore << endl;
    sameval = 0;
}
    cout << "Total Simularity Score: " << simularityScore << endl;


    return 0;
}