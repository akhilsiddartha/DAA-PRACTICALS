#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    int cost[10][10];

    cout << "Enter cost matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];

    int selected[10] = {0};
    selected[0] = 1;

    int edges = 0, total = 0;

    cout << "Edges in Minimum Spanning Tree:\n";

    while (edges < n - 1)
    {
        int min = 9999;
        int x = 0, y = 0;

        for (int i = 0; i < n; i++)
        {
            if (selected[i])
            {
                for (int j = 0; j < n; j++)
                {
                    if (!selected[j] && cost[i][j] < min)
                    {
                        min = cost[i][j];
                        x = i;
                        y = j;
                    }
                }
            }
        }

        cout << x << " - " << y << " = " << min << endl;

        total += min;
        selected[y] = 1;
        edges++;
    }

    cout << "Minimum cost = " << total;

    return 0;
}