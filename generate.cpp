/*
 *input file: sample.iii
 *input format: value*81
 *		use ' ' or '\n' to seperate
 * */
#include"sudoku.h"
#include<fstream>
#include<cmath>
#include<ctime>
using namespace std;

int main() {
    Sudoku newSudoku;
    ifstream fin("sample.iii",ios::in);
    if(!fin) {
        cerr << "Fail opening!!" << endl;
        exit(1);
    }
    int input;
    vector<int> inputSudoku;
    while(inputSudoku.size()<81 && fin >> input) {
        inputSudoku.push_back(input);
    }
    newSudoku.mapSudoku = inputSudoku;
    srandom(time(NULL));
    int choose;
    for(int i=0; i<(random()%9999+999); ++i) {
        choose = random()%6;
        switch(choose) {
        case 0:
            newSudoku.swapNum(random()%9, random()%9);
            break;
        case 1:
            newSudoku.swapRow(random()%2, random()%2);
            break;
        case 2:
            newSudoku.swapCol(random()%2, random()%2);
            break;
        case 3:
            newSudoku.rotateCounter();
            break;
        case 4:
            newSudoku.flipSudoku(1);
            break;
        case 5:
            newSudoku.rightleftFlip();
            break;
        }
    }
    //dig hole(9~21)
    for(int i=0; i<(random()%21+9); ++i) {
        newSudoku.mapSudoku.at(random()%81) = 0;
    }
    newSudoku.printSudoku();
    return 0;
}
