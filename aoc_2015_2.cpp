#include <iostream>     // std:cout
#include <fstream>      // std::ifstream
#include <sstream>      // std::ostringstream
#include <string>       // std::string
#include <list>         // std::list
#include <vector>       // std:vectors
#include <algorithm>    // std::transform
#include <functional>   // std::placeholders
#include <numeric>      // std::accumulate

using namespace std;

class PresentDimensions {
    public:
        int x, y, z;
        PresentDimensions(string s) {
            sscanf(s.c_str(), "%dx%dx%d", &x, &y, &z);
        };
        static PresentDimensions* fromString(string s) {
            return new PresentDimensions(s);
        }
        string toString() {
            ostringstream str;
            str << "Present [" << x << " x " << y << " x " << z << "]";
            return str.str();
        }
        int getArea() {
            const int side0 = x*y,
                      side1 = y*z,
                      side2 = x*z;
            return 2*(side0+side1+side2) + min(side0, min(side1, side2));
        }
        int getRibbon() {
            const int perim0 = x+y,
                      perim1 = y+z,
                      perim2 = x+z;  
            return x*y*z + 2*min(perim0, min(perim1, perim2));
        }
};

int main(void) {
    ifstream puzzleInput ("aoc_2015_2.input.txt");

    if(!puzzleInput.is_open()) {
        cout << "Unable to open file" << endl;
        return 1;
    }
    // else...

    list<string> lines = {}; // could really use a vector instead
    string line;
    while(getline(puzzleInput, line)) {
        lines.push_front(line);
    }
       
    cout << lines.size() << " lines read\n";

    list<PresentDimensions*> dims = {};
    transform(lines.begin(), lines.end(), back_inserter(dims), PresentDimensions::fromString);

    cout << dims.size() << " dimensions calulated\n";

    cout << "---" << endl;

    vector<int> areas = {};
    transform(dims.begin(), dims.end(), back_inserter(areas), std::bind(&PresentDimensions::getArea, placeholders::_1));
    int sum = accumulate(areas.begin(), areas.end(), 0);
    cout << "Part 1: " << sum << " sqft wrapping paper" << endl;

    vector<int> ribbon = {};
    transform(dims.begin(), dims.end(), back_inserter(ribbon), std::bind(&PresentDimensions::getRibbon, placeholders::_1));
    sum = accumulate(ribbon.begin(), ribbon.end(), 0);
    cout << "Part 2: " << sum << " ft ribbon" << endl;

    return 0;
}