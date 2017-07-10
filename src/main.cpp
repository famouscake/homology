// Copyright 2017 Peter Hristov
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
#include <cassert>

using namespace std;

vector<vector<int>> readData()
{
    int iDim, jDim;

    cin >> iDim >> jDim;

    vector<vector<int>> data(iDim, vector<int>(jDim));

    for (int i = 0 ; i < iDim ; i++)
    {
        for (int j = 0 ; j < jDim ; j++)
        {
            cin >> data[i][j];
        }
    }

    return data;
}

/**
 * Write tree grid to STDIN
 */
void printData(const vector<vector<int> > &data)
{
    for (int i = 0 ; i < data.size() ; i++)
    {
        cout << endl;
        for (int j = 0 ; j < data[i].size() ; j++)
        {
            cout << setw(4) << data[i][j];
        }
    }

    cout << endl;
}

pair<int, int> findOne(vector<vector<int>> &d, int r)
{
    for (int i = r ; i < d.size() ; i++)
    {
        for (int j = r ; j < d[i].size() ; j++)
        {
            if (1 == d[i][j])
            {
                return {i, j};
            }
        }
    }

    return {-1, -1};
}

void swapRow(vector<vector<int>> &d, int i1, int i2)
{
    for (int j = 0 ; j < d[i1].size() ; j++)
    {
        swap(d[i1][j], d[i2][j]);
    }
}

void swapColumn(vector<vector<int>> &d, int j1, int j2)
{
    for (int i = 0 ; i < d.size() ; i++)
    {
        swap(d[i][j1], d[i][j2]);
    }
}

void sumRow(vector<vector<int>> &d, int i1, int i2)
{
    for (int j = 0 ; j < d[i1].size() ; j++)
    {
        d[i1][j] = (d[i1][j] + d[i2][j]) % 2;
    }
}

void sumColumn(vector<vector<int>> &d, int j1, int j2)
{
    for (int i = 0 ; i < d.size() ; i++)
    {
        d[i][j1] = (d[i][j1] + d[i][j2]) % 2;
    }
}



void reduce(vector<vector<int>> &d, vector<vector<int>> &p, vector<vector<int>> &q)
{
    int r = 0;

    while (r < d.size() && r < d[0].size())
    {
        // Find a 1
        auto t = findOne(d, r);
        if (t.first == t.second == -1) { return; }

        //printf("\nFound: %d - %d\n", t.first, t.second);

        // Swap it
        swapRow(d, r, t.first);
        swapColumn(d, r, t.second);

        // Mirror it
        swapRow(p, r, t.first);
        swapColumn(q, r, t.second);


        //cout << "After Swap : " << endl;
        //printData(d);

        // Eliminate Rows
        if (r < d.size() - 1)
        {
            for (int i = r + 1 ; i < d.size() ; i++)
            {
                if (1 == d[i][r])
                {
                    sumRow(d, i, r);
                    sumRow(p, i, r);
                }
            }
        }

        //cout << "After Rows : " << endl;
        //printData(d);

        // Eliminate Columns
        if (r < d[r].size() - 1)
        {
            for (int j = r + 1 ; j < d[r].size() ; j++)
            {
                if (1 == d[r][j])
                {
                    sumColumn(d, j, r);
                    sumColumn(q, j, r);
                }
            }
        }
        //cout << "After Cols : " << endl;
        //printData(d);

        //cout << "--------------------" << endl;

        // Move it to the pivot position

        r++;
    }
}

int main(int argc, char *argv[])
{
    auto d1 = readData();

    // For Row Operations
    vector<vector<int>> p(d1.size(), vector<int>(d1.size()));
    
    // For Column Operations
    vector<vector<int>> q(d1[0].size(), vector<int>(d1[0].size()));

    // Make identity matrix
    for (int i = 0 ; i < p.size() ; i++)
    {
        p[i][i] = 1;
    }

    for (int i = 0 ; i < q.size() ; i++)
    {
        q[i][i] = 1;
    }

    reduce(d1, p, q);

    printData(d1);
    printData(p);
    printData(q);



    return 0;
}
