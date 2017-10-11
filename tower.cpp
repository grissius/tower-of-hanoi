#include <iostream>
#include <vector>
#include <iomanip>

#define DISCW 10
#define PADDING 5
using namespace std;

class Hanoi
{
  public:
    Hanoi() : discs(3), startOn(1)
    {
        towers.reserve(3);
        for (int i = 0; i < 3; ++i)
        {
            vector<int>* vec = new vector<int>();
            if(i == startOn) {
                vec->push_back(3);
                vec->push_back(2);
                vec->push_back(1);
            }
            towers.push_back(vec);
        }
    }
    bool canMove(int from, int to) {
        if(from < 0 || to < 0 || from >= towers.size() || to >= towers.size()) {
            return false;
        }
        if((*towers[from]).size() <= 0) {
            return false;
        }
        int disc = (*towers[from]).back();
        if((*towers[to]).size() > 0) {
            int discBellow = (*towers[to]).back();
            if(disc >= discBellow) {
                return false;
            }
        }
        return true;
    }
    void move(int from, int to) {
        if(canMove(from, to)) {
            int disc = (*towers[from]).back();
            (*towers[from]).pop_back();
            (*towers[to]).push_back(disc);
        }
    }
    bool isWon() {
        if(!towers[startOn]->empty()) {
            return false;
        }
        int nonEmptyTowers = 0;
        for (vector<int> *tower : towers) {
            if(!tower->empty()) {
                nonEmptyTowers++;
            }
        }
        return nonEmptyTowers == 1;
    }
    friend std::ostream &operator<<(ostream &os, const Hanoi &hanoi)
    {
        for (vector<int> *tower : hanoi.towers)
        {
            os << setw(PADDING) << "" << setw(DISCW) << ""
               << "|" << setw(DISCW) << "" << setw(PADDING) << "";
        }
        os << endl;
        for (int i = hanoi.discs - 1; i >= 0; --i)
        {
            for (vector<int> *tower : hanoi.towers)
            {
                if (tower->size() > i)
                {
                    int dsize = (*tower)[i] * 2;
                    string discPulp = string(dsize - 1, '#');
                    string discL = "[" + discPulp;
                    string discR = discPulp + "]";
                    os << setw(PADDING) << "" << setw(DISCW - dsize) << "" << discL << "|" << discR << setw(DISCW - dsize) << "" << setw(PADDING) << "";
                }
                else
                {
                    os << setw(PADDING) << "" << setw(DISCW) << ""
                       << "|" << setw(DISCW) << "" << setw(PADDING) << "";
                }
            }
            os << endl;
        }
        for (vector<int> *tower : hanoi.towers)
        {
            string halfDisc = string(DISCW, '=');
            os << setw(PADDING) << "" << halfDisc << "=" << halfDisc << setw(PADDING) << "";
        }
        os << endl;
        for (int i = 1; i < 4; ++i)
        {
            os << setw(DISCW + PADDING) << "" << i << setw(DISCW + PADDING) << "";
        }
        os << endl;
        return os;
    }

  private:
    vector<vector<int> *> towers;
    int discs;
    int startOn;
};

int main(int argc, char **argv)
{
    Hanoi hanoi;
    int from, to;
    cout << hanoi << endl;    
    while(!hanoi.isWon()) {
        cin >> from >> to;
        hanoi.move(from-1, to-1);
        cout << hanoi << endl;
    }
}
