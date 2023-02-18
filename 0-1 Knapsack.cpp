#include "bits/stdc++.h"

using namespace std;

#define endl "\n"
#define int long long int

// Identification -> Choices, Optimal
// Recursion -> Memoization -> Tabulation

int knapsack(int wt[], int val[], int W, int n) // Recursive approach
{
    // Base Condition
    if (n == 0 || W == 0)
        return 0;

    // Choice Diagram
    if (wt[n - 1] <= W)
    {
        return max(val[n - 1] + knapsack(wt, val, W - wt[n - 1], n - 1), knapsack(wt, val, W, n - 1));
    }
    else
    {
        return knapsack(wt, val, W, n - 1);
    }
}

int _lookup[10][10]; // Memoization

void _initialize()
{
    memset(_lookup, -1, sizeof(_lookup));
}

int _knapsack(int wt[], int val[], int W, int n)
{
    // Base Condition
    if (n == 0 || W == 0)
        return 0;

    // Choice Diagram
    if (_lookup[n][W] != -1)
        return _lookup[n][W];

    if (wt[n - 1] <= W)
    {
        return _lookup[n][W] = max(val[n - 1] + _knapsack(wt, val, W - wt[n - 1], n - 1), _knapsack(wt, val, W, n - 1));
    }
    else
    {
        return _lookup[n][W] = _knapsack(wt, val, W, n - 1);
    }
}

int lookup[10][10]; // Tabulation

int tabulation(int wt[], int val[], int W, int n)
{
    for (int i = 0; i <= n; ++i) // Initialization
    {
        for (int j = 0; j <= W; ++j)
        {
            if (i == 0 || j == 0)
            {
                lookup[i][j] = 0;
            }
        }
    }
    for (int i = 1; i <= n; ++i) // Recursive -> Iteration
    {
        for (int j = 1; j <= W; ++j)
        {
            if (wt[i - 1] <= j)
            {
                lookup[i][j] = max(val[i - 1] + lookup[i - 1][j - wt[i - 1]], lookup[i - 1][j]);
            }
            else
            {
                lookup[i][j] = lookup[i - 1][j];
            }
        }
    }
    return lookup[n][W];
}
int32_t main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 3, W = 4;
    int wt[n] = {1, 2, 3};
    int val[n] = {4, 5, 1};
    cout << knapsack(wt, val, W, n) << endl;
    _initialize();
    cout << _knapsack(wt, val, W, n) << endl;
    cout << tabulation(wt, val, W, n) << endl;
    return 0;
}
