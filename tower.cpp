#include <iostream>
#include <vector>
#include <iomanip>

#define DISCW 10
#define PADDING 5
using namespace std;

class Hanoi
{
  public:
    Hanoi(int towersCount = 2) : discs(3), startOn(1)
    {
        towers.reserve(towersCount + 1);
        for (int i = 0; i < towersCount + 1; ++i)
        {
            vector<int> *vec = new vector<int>();
            if (i == startOn)
            {
                for (int d = discs; d > 0; d--)
                {
                    vec->push_back(d);
                }
            }
            towers.push_back(vec);
        }
    }
    bool canMove(int from, int to)
    {
        if (from < 0 || to < 0 || from >= towers.size() || to >= towers.size())
        {
            return false;
        }
        if ((*towers[from]).size() <= 0)
        {
            return false;
        }
        int disc = (*towers[from]).back();
        if ((*towers[to]).size() > 0)
        {
            int discBellow = (*towers[to]).back();
            if (disc >= discBellow)
            {
                return false;
            }
        }
        return true;
    }
    void move(int from, int to)
    {
        if (canMove(from, to))
        {
            int disc = (*towers[from]).back();
            (*towers[from]).pop_back();
            (*towers[to]).push_back(disc);
        }
    }
    bool isWon()
    {
        if (!towers[startOn]->empty())
        {
            return false;
        }
        int nonEmptyTowers = 0;
        for (vector<int> *tower : towers)
        {
            if (!tower->empty())
            {
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
        for (int i = 1; i < hanoi.towers.size() + 1; ++i)
        {
            os << setw(DISCW + PADDING) << "" << i << setw(DISCW + PADDING) << "";
        }
        os << endl;
        return os;
    }
    int countTowers()
    {
        return towers.size();
    }
    int countDisks()
    {
        return discs;
    }
    int startedOn()
    {
        return startOn;
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
    cout << string(100, '\n');
    cout << hanoi << endl;
    cout << "Na terminalu vidis " << hanoi.countTowers() << " veze. Na " << hanoi.startedOn() + 1 << " z nich jsou " << hanoi.countDisks() << " disky. Tvym ukolem je premistit vsechny disky z pocatecni veze na jinou." << endl;
    cout << " * Vzdy muzes premistit disk pouze z vrcholu veze." << endl;
    cout << " * Muzes premistit v jednom tahu pouze jeden disk." << endl;
    cout << " * Disk muzes umistit na volnou vez, nebo na vez, jejiz vrchni disk je vetsi, nez disk ktery presouvas." << endl;
    cout << "Pro presunuti disku napis dve cisla oddelena mezerou. Prvni cislo udava cislo veze odkud presouvas disk, druhe cislo cilovou vez." << endl;
    cout << "Napriklad \"2 1\" (bez uvozovek, potrvrzeno klavesou Enter) premisti vrchni disk z veze cislo 2 na vez cislo 1, bude-li to mozne." << endl;
    while (!hanoi.isWon())
    {
        cout << endl
             << "Zadej dve cisla oddelena mezerou > ";
        if (cin >> from >> to)
        {
            cout << string(100, '\n');
            if (hanoi.canMove(from - 1, to - 1))
            {
                hanoi.move(from - 1, to - 1);
                cout << hanoi << endl;
            }
            else
            {
                cout << hanoi << endl;
                cout << "ERR LOGIC:\n * Prvni vez musi mit disk\n * Cilova vez musi byt prazdna, nebo mit navrchu disk mensi\n * Cisla musi byt v rozsahu vezi." << endl;
            }
        }
        else
        {
            cin.clear();
            cin.ignore();
            cout << "ERR INPUT: Zadej dve cisla oddelena mezerou, potvrd Enterem." << endl;
        }
    }
    cout << string(100, '\n');
    cout << "    ___________________________." << endl;
    cout << "    |;;|                     |;;||" << endl;
    cout << "    |[]|---------------------|[]||" << endl;
    cout << "    |;;|                     |;;||" << endl;
    cout << "    |;;|                     |;;||" << endl;
    cout << "    |;;|                     |;;||" << endl;
    cout << "    |;;|                     |;;||" << endl;
    cout << "    |;;|                     |;;||" << endl;
    cout << "    |;;|                     |;;||" << endl;
    cout << "    |;;|_____________________|;;||" << endl;
    cout << "    |;;;;;;;;;;;;;;;;;;;;;;;;;;;||" << endl;
    cout << "    |;;;;;;_______________ ;;;;;||" << endl;
    cout << "    |;;;;;|  ___          |;;;;;||" << endl;
    cout << "    |;;;;;| |;;;|         |;;;;;||" << endl;
    cout << "    |;;;;;| |;;;|         |;;;;;||" << endl;
    cout << "    |;;;;;| |;;;|         |;;;;;||" << endl;
    cout << "    |;;;;;| |;;;|         |;;;;;||" << endl;
    cout << "    |;;;;;| |___|         |;;;;;||" << endl;
    cout << "    \\_____|_______________|_____||" << endl;
    cout << "    ~~~~~^^^^^^^^^^^^^^^^^~~~~~~" << endl;
}
