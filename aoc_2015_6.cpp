#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <regex>

using namespace std;

enum ACTION {TURN_ON, TURN_OFF, TOGGLE};

long int part1(list<string>);
long int part2(list<string>);
bool parseLine(string, uint*, uint*, uint*, uint*, ACTION*);
string action_str(ACTION);

int main(void);

int main(void) {
    ifstream puzzleInput ("aoc_2015_6.input.txt");

    if(!puzzleInput.is_open()) {
        cout << "Unable to open file" << endl;
        return 1;
    }
    list<string> lines;
    string line;
    while(getline(puzzleInput, line)) {
        lines.push_back(line);
    }

    lines.push_front("turn off 0,0 through 999,999");

    cout << "Part 1: " << part1(lines) << endl; 
    cout << "Part 2: " << part2(lines) << endl; 
    return 0;
}

long int part1(list<string> lines) {

    bool lights[1000][1000] = {0}; // initialise all elements to 0
    uint beginX, beginY, endX, endY;
    ACTION action;
    
    for(string line : lines) {
        if(!parseLine(line, &beginX, &beginY, &endX, &endY, &action)) {
            cout << "Error parsing line: " << line << endl;
        }
        for(size_t x=beginX; x<=endX; x++) {
            for(size_t y=beginY; y<=endY; y++) {
                switch(action) {
                    case TURN_ON:
                        lights[x][y] = true;
                    break;
                    case TURN_OFF:
                        lights[x][y] = false;
                    break;
                    case TOGGLE:
                        lights[x][y] = !lights[x][y];
                    break;
                }
            }    
        }

    }

    long int count = 0;
    for(size_t x=0; x<=999; x++) {
        for(size_t y=0; y<=999; y++) {
            if(lights[x][y]) {
                count++;
            }
        }    
    }

    return count;
}

long int part2(list<string> lines) {

    int lights[1000][1000] = {0}; // initialise all elements to 0
    uint beginX, beginY, endX, endY;
    ACTION action;
    
    for(string line : lines) {
        if(!parseLine(line, &beginX, &beginY, &endX, &endY, &action)) {
            cout << "Error parsing line: " << line << endl;
        }
        for(size_t x=beginX; x<=endX; x++) {
            for(size_t y=beginY; y<=endY; y++) {
                switch(action) {
                    case TURN_ON:
                        lights[x][y]++;
                    break;
                    case TURN_OFF:
                        if(lights[x][y]>0) lights[x][y]--;
                    break;
                    case TOGGLE:
                        lights[x][y]+=2;
                    break;
                }
            }    
        }

    }

    long int count = 0;
    for(size_t x=0; x<=999; x++) {
        for(size_t y=0; y<=999; y++) {
            count += lights[x][y];
        }    
    }

    return count;
}

const regex line_regex ("(turn on|turn off|toggle) (\\d+),(\\d+) through (\\d+),(\\d+)");
bool parseLine(string line, uint *beginX, uint *beginY, uint *endX, uint *endY, ACTION *action) {
    smatch match;
    if(!regex_match(line, match, line_regex)) {
        cout << "Line didn't match: \"" << line << "\"\n";
        return false;
    }

    *beginX = stoi(match[2].str());
    *beginY = stoi(match[3].str());
    *endX =   stoi(match[4].str());
    *endY =   stoi(match[5].str());

    string actionStr = match[1].str();
    if(!actionStr.compare("turn on")) {
        *action = TURN_ON;
    }
    else if(!actionStr.compare("turn off")) {
        *action = TURN_OFF;
    }
    else if(!actionStr.compare("toggle")) {
        *action = TOGGLE;
    }
    else {
        // literally can't reach this case
        return false;
    }

    return true;
}

string action_str(ACTION a) {
    switch(a) {
        case TURN_ON:
            return "turn on";
        case TURN_OFF:
            return "turn off";
        case TOGGLE:
            return "toggle";
    }
    return NULL;
}