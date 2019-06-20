#include"sudoku.h"
using namespace std;

int main() {
    Sudoku transSudoku;
    vector<int> inputSudoku;
    int input;
    while(inputSudoku.size()<81 && cin >> input) {
        inputSudoku.push_back(input);
    }
    transSudoku.mapSudoku = inputSudoku;

    int inst;//instruction
    int x,y;
    while( cin >> inst) {
        switch(inst) {
        case 0:
            transSudoku.printSudoku();
            break;

        case 1:
            cin >> x >> y;
            transSudoku.swapNum(x,y);
            break;

        case 2:
            cin >> x >> y;
            transSudoku.swapRow(x,y);
            break;

        case 3:
            cin >> x >> y;
            transSudoku.swapCol(x,y);
            break;

        case 4:
            cin >> x;
            transSudoku.rotateSudoku(x);
            break;

        case 5:
            cin >> x;
            transSudoku.flipSudoku(x);
            break;

        default:
            cerr << "Invalid instruction!!" << endl;
            exit(1);
        }
        if(inst == 0) break;
    }
    return 0;
}
