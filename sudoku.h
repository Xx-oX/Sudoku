/*
 * Sudoku.h
 *
 *  Created on: march_2019
 *      Author: o_0
 */

#ifndef SUDOKU_H_
#define SUDOKU_H_

#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
using namespace std;

class Sudoku {
  public:
    Sudoku() {
    }
    vector<int> mapSudoku;//1d vector
    //transform:
    void swapNum(int x, int y) {
        int i;
        for(i=0; i<mapSudoku.size(); ++i) {
            if(mapSudoku.at(i) == x) {
                mapSudoku.at(i) = y;
            } else if(mapSudoku.at(i) == y) {
                mapSudoku.at(i) = x;
            }
        }
    }
    void swapRow(int x, int y) {
        int i;
        vector<int> tempX(27);
        vector<int> tempY(27);
        for(i=0; i<27; ++i) {
            tempX.at(i) = mapSudoku.at(i+(27*(x)));
        }
        for(i=0; i<27; ++i) {
            tempY.at(i) = mapSudoku.at(i+(27*(y)));
            mapSudoku.at(i+(27*(y))) = tempX.at(i);
        }
        for(i=0; i<27; ++i) {
            mapSudoku.at(i+(27*(x))) = tempY.at(i);
        }
    }

    void swapCol(int x, int y) {
        int i;
        for(i=0; i<3; ++i)
            rotateCounter();//rotate +90degree
        swapRow(x,y);//swap
        rotateCounter();//rotate -90degree
    }

    void rotateCounter() {
        int i,j;
        vector<vector<int> > row;//2d vector
        row.resize(9);//row[9]
        for(i=0; i != 9; ++i) row[i].resize(9);

        vector<vector<int> > col;
        col.resize(9);
        for(i=0; i != 9; ++i) col[i].resize(9);

        for(i=0; i<9; ++i) {
            for(j=0; j<9; ++j)
                row[i].at(j) = mapSudoku.at(j+9*i);
        }
        //row to column
        for(i=0; i<9; ++i) {
            for(j=0; j<9; ++j)
                col[i].at(j) = row[j].at(i);
        }
        for(i=0; i<9; ++i) {
            for(j=0; j<9; ++j)
                mapSudoku.at(j+9*i) = col[8-i].at(j);
        }
    }

    void rotateSudoku(int x) {
        x = x % 4;
        int i;
        switch(x) {
        case 1:
            for(i=0; i<3; ++i)
                rotateCounter();
            break;
        case 2:
            for(i=0; i<2; ++i)
                rotateCounter();
            break;
        case 3:
            rotateCounter();
            break;
        case 0:
            break;
        default:
            cerr << "Invalid instruction!!" << endl;
            exit(1);
            break;
        }
    }

    void rightleftFlip() {
        int i,j;
        vector<vector<int> > matrixSudoku;
        matrixSudoku.resize(9);
        for(i=0; i<9; ++i) matrixSudoku[i].resize(9);

        for(i=0; i<9; ++i) {
            for(j=0; j<9; ++j) {
                matrixSudoku[i].at(j) = mapSudoku.at(j+9*i);
            }
        }
        for(i=0; i<9; ++i) {
            for(j=0; j<9; ++j)
                mapSudoku.at(j+9*i) = matrixSudoku[i].at(8-j);
        }
    }

    void flipSudoku(int x) {
        int i;
        if(x == 0) {
            for(i=0; i<3; ++i) rotateCounter();
            rightleftFlip();
            rotateCounter();
        } else if(x == 1) {
            rightleftFlip();
        } else {
            cerr << "Invalid instruction!!" << endl;
            exit(1);
        }
    }
    //std::out
    void printSudoku() {
        int index = 0;
        for(int i=0; i<sideLength; ++i) {
            for(int j=index; j<(index + sideLength-1); ++j) {
                cout << mapSudoku.at(j) << " ";
            }
            index += (sideLength-1);
            cout << mapSudoku.at(index) << endl;
            index++;
        }
    }
  private:
    static const int sideLength = 9;
};


#endif /* SUDOKU_H_ */
