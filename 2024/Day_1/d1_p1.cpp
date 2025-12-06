#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

int main(){

    /*
    //vector left is the left numbers of the input
    vector<int> left = {3,4,2,1,3,3};
    //vector right is the right numbers of the input
    vector<int> right = {4,3,5,3,9,3};
    */

    //Pass the input as the input.txt
    //parse the input into two vectors
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
    

    int diff = 0;
    int sum = 0;

    //now we want to sort the left vector in ascending order
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    for (int i = 0; i < left.size(); i ++){
        cout << left[i] << " " << right[i] << endl;
        diff = abs(left[i] - right[i]);
        cout << "Difference: " << diff << endl;
        sum += diff;
    }
    cout << "Total Sum of Differences: " << sum << endl;



    return 0;
}