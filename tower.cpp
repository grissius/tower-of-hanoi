#include <iostream>
#include <vector>
#include <iomanip>

#define DISCW 10
#define PADDING 5
using namespace std;

class Hanoi
{
  public:
    Hanoi() : discs(3)
    {
        towers.reserve(3);
        for (int i = 0; i < 3; ++i)
        {
            towers.push_back(new vector<int>());
        }
        towers[0]->push_back(3);
        towers[0]->push_back(2);
        towers[0]->push_back(1);

        towers[1]->push_back(2);
        towers[1]->push_back(1);

        towers[2]->push_back(1);
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
};

int main(int argc, char **argv)
{
    Hanoi hanoi;
    cout << hanoi << endl;
}