#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>

using namespace std;

// function to read file and put maze into 2D vector
vector <vector <char>> parseMaze(const string& file_name) {

    ifstream fin(file_name);
    vector <vector <char>> maze;

    // check if file is open
    if (!fin) {
        cerr << "Error: Unable to open file " << file_name << std::endl;
        return {};
    }

    char ch;
    vector <char> row;

    while (fin.get(ch)) {
        if (ch == '\n') {
            if (!row.empty()) {
                maze.push_back(row);
                row.clear();
            }
        } else {
            row.push_back(ch);
        }
    }

    if (!row.empty()) {
        maze.push_back(row);
    }

    return maze;

}

void printMaze(vector <vector <char>> maze_to_print) {

    for (const auto& row : maze_to_print) {
        for (const auto& cell : row) {
            cout << cell;
        }
        cout << endl;
    }
    
}

// possible functions to write

// opposite of - char oppositeOf(char direction)
// deadend - bool deadend(vector <int> point, char direction)
// vector nextLeft, nextRight, etc. (maze, point)

vector <vector <int>> generatePath(vector <vector <char>> maze) {


    
}

int main() {

    string filename = "maze.txt";

    vector <vector <char>> maze = parseMaze(filename);

    printMaze(maze);

    int x = 2;
    int y = 1;

    

}