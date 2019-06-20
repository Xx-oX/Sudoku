#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
using namespace std;

class Sudoku {
  public:
    Sudoku() {

    }
    struct pos {
        vector<int> value;
    };
    struct pos possible[9][9];
    int question[9][9];
    int puzzle[9][9];
    int savepuzzle[81][9][9];
    int copy[9][9];
    void print() {
        int i,j;
        for(i=0; i<9; ++i) {
            for(j=0; j<8; ++j) {
                cout<<puzzle[i][j] << " ";
            }
            cout<<puzzle[i][j++]<<endl;
        }
    }
    void find() {
        for(int x=0; x<9; ++x) {
            for(int y=0; y<9; ++y) {
                if(puzzle[x][y] == 0) {
                    for(int i=1; i<=9; ++i)
                        possible[x][y].value.push_back(i);

                    rowClear(x,possible[x][y].value);
                    colClear(y,possible[x][y].value);
                    boxClear(boxFind(x),boxFind(y),possible[x][y].value);

                    if(possible[x][y].value.size() == 1) {
                        puzzle[x][y] == possible[x][y].value[0];
                    }

                } else {
                    possible[x][y].value.clear();
                }
            }
        }
    }

    void P() {
        for(int x=0; x<9; ++x) {
            for(int y=0; y<9; ++y) {
                if(!possible[x][y].value.empty()) {
                    for(vector<int>::iterator it=possible[x][y].value.begin(); it!=possible[x][y].value.end(); ++it) {
                        inhan(*it,x,y);
                    }
                }
            }
        }
    }


    void inhan(int p,int x,int y) {
        int same = 0;
        for(int i=0; i<9; ++i) {
            if(i!=y) {
                for(vector<int>::iterator it=possible[x][i].value.begin(); it!=possible[x][i].value.end(); ++it) {
                    if(p == *it) same++;
                }
            }
        }
        if(same == 0) {
            puzzle[x][y] = p;
            //cout<<"row("<<x<<","<<y<<") "<<p<<endl;
            return;
        }
        same = 0;
        for(int i=0; i<9; ++i) {
            if(i!=x) {
                for(vector<int>::iterator it=possible[i][y].value.begin(); it!=possible[i][y].value.end(); ++it) {
                    if(p == *it) same++;
                }
            }
        }
        if(same == 0) {
            puzzle[x][y] = p;
            //cout<<"col("<<x<<","<<y<<") "<<p<<endl;
            return;
        }
        same = 0;
        int a = boxFind(x);
        int b = boxFind(y);
        for(int i=0; i<3; ++i) {
            for(int j=0; j<3; ++j) {
                if((a+i)==x && (b+j)==y) {
                } else {
                    for(vector<int>::iterator it=possible[a+i][b+j].value.begin(); it!=possible[a+i][b+j].value.end(); ++it) {
                        if(p == *it) same++;
                    }
                }
            }
        }
        if(same == 0) {
            puzzle[x][y] = p;
            //cout<<"box("<<x<<","<<y<<") "<<p<<endl;
            return;
        }
        return;
    }

    bool solve() {
        int x,y;
        if(!findZero(&x,&y)) return true;//find 0
        for(vector<int>::iterator it = possible[x][y].value.begin() ; it != possible[x][y].value.end() ; ++it) {
            if(!rowCheck(x,*it) && !colCheck(y,*it) && !boxCheck(boxFind(x),boxFind(y),*it)) {
                puzzle[x][y] = *it;
                if(solve()) return true;
            }
            puzzle[x][y] = 0;
        }
        return false;
    }

    bool multi() {
        for(int i=0; i<9; ++i) {
            for(int j=0; j<9; ++j) {
                copy[i][j] = puzzle[i][j];
                puzzle[i][j] = question[i][j];
            }
        }
        if(resol()) return true;
        else {
            for(int i=0; i<9; ++i) {
                for(int j=0; j<9; ++j)
                    puzzle[i][j] = copy[i][j];
            }
            return false;
        }
    }

    bool resol() {
        int x,y;
        if(!findZero(&x,&y)) return true;
        for(vector<int>::iterator it = possible[x][y].value.end()-1 ; it >= possible[x][y].value.begin() ; --it) {
            if(*it!=copy[x][y]) {
                if(!rowCheck(x,*it) && !colCheck(y,*it) && !boxCheck(boxFind(x),boxFind(y),*it)) {
                    puzzle[x][y] = *it;
                    if(resol()) return true;
                }
            }
            puzzle[x][y] = 0;
        }
        return false;
    }

  private:
    int boxFind(int x) {
        if(x<3) return 0;
        else if(x<6) return 3;
        else return 6;
    }
    void rowClear(int x,vector<int> &value) {
        for(int i=0; i<9; ++i) {
            for(vector<int>::iterator it=value.begin(); it!=value.end();) {
                if(*it == puzzle[x][i]) {
                    it = value.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }
    void colClear(int y,vector<int> &value) {
        for(int i=0; i<9; ++i) {
            for(vector<int>::iterator it=value.begin(); it!=value.end();) {
                if(*it == puzzle[i][y]) {
                    it = value.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }
    void boxClear(int x,int y,vector<int> &value) {
        for(int i=0; i<3; ++i) {
            for(int j=0; j<3; ++j) {
                for(vector<int>::iterator it=value.begin(); it!=value.end();) {
                    if(*it == puzzle[i+x][j+y]) {
                        it = value.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
        }
    }

    //solve
    bool findZero(int *x,int *y) {
        for(int i=0; i<9; ++i) {
            for(int j=0; j<9; ++j) {
                if(puzzle[i][j] == 0) {
                    *x = i;
                    *y = j;
                    return true;
                }
            }
        }
        return false;
    }

    bool rowCheck(int x,int value) {
        for(int i=0; i<9; ++i) {
            if(value == puzzle[x][i]) return true;
        }
        return false;
    }

    bool colCheck(int y,int value) {
        for(int i=0; i<9; ++i) {
            if(value == puzzle[i][y]) return true;
        }
        return false;
    }

    bool boxCheck(int x,int y,int value) {
        for(int i=0; i<3; ++i) {
            for(int j=0; j<3; ++j) {
                if(value == puzzle[i+x][j+y]) return true;
            }
        }
        return false;
    }
};

int main() {
    Sudoku problem;
    double ST,ED;
    for(int i=0; i<9; ++i) {
        for(int j=0; j<9; ++j) {
            cin>>problem.puzzle[i][j];
        }
    }

    ST = clock();

    problem.find();
    problem.P();
    for(int i=0; i<9; ++i) {
        for(int j=0; j<9; ++j) {
            problem.question[i][j] = problem.puzzle[i][j];
#ifdef DEBUG
            for(vector<int>::iterator it = problem.possible[i][j].value.begin(); it != problem.possible[i][j].value.end(); ++it)
                cout<<"("<<i<<","<<j<<"): "<<*it<<" ";
            cout<<endl;
#endif
        }
    }
    //cout<<endl;
    //problem.print();
    if(problem.solve()) {
        if(problem.multi()) {
            cout<<"2"<<endl;
        } else {
            cout<<"1"<<endl;
            problem.print();
        }
    } else {
        cout<<"0"<<endl;
        //problem.print();
    }
    ED = clock();
#ifdef TIME
    cout<<"execution time: "<<(ED-ST)/CLOCKS_PER_SEC<<"s"<<endl;
#endif
}
