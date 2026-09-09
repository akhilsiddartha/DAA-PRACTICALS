#include <iostream>
using namespace std;

int main()
{
    // Matrices
    // A1 = 10 x 20
    // A2 = 20 x 30
    // A3 = 30 x 40

    int p[] = {10, 20, 30, 40};
    int n = 3;

    int m[4][4];

    // Cost of multiplying one matrix = 0
    for (int i = 1; i <= n; i++)
    {
        m[i][i] = 0;
    }

    // Chain length
    for (int length = 2; length <= n; length++)
    {
        for (int i = 1; i <= n - length + 1; i++)
        {
            int j = i + length - 1;

            // First split: k = i
            int k = i;

            m[i][j] = m[i][k]
                    + m[k + 1][j]
                    + p[i - 1] * p[k] * p[j];

            // Print first split
            if (i == 1 && j == 3)
            {
                cout << "A1 x A2 x A3" << endl;
                cout << "k = 1 : " << m[i][j] << endl;
            }

            // Remaining split positions
            for (k = i + 1; k < j; k++)
            {
                int cost = m[i][k]
                         + m[k + 1][j]
                         + p[i - 1] * p[k] * p[j];

                if (i == 1 && j == 3)
                {
                    cout << "k = " << k
                         << " : " << cost << endl;
                }

                if (cost < m[i][j])
                {
                    m[i][j] = cost;
                }
            }
        }
    }

    cout << endl;

    // DP values
    cout << "m[1][2] (A1 x A2) = "
         << m[1][2] << endl;

    cout << "m[2][3] (A2 x A3) = "
         << m[2][3] << endl;

    cout << "m[1][3] (A1 x A2 x A3) = "
         << m[1][3] << endl;

    cout << endl;

    cout << "Minimum value = "
         << m[1][3] << endl;

    return 0;
}
