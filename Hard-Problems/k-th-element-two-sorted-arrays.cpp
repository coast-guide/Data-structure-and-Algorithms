// https://www.codingninjas.com/codestudio/problems/ninja-and-ladoos_1112629

#include <bits/stdc++.h>
using namespace std;

int ninjaAndLadoos(vector<int> &row1, vector<int> &row2, int row1_size, int row2_size, int k)
{
    if (row1_size > row2_size)
        //         Apply the algorithm on smaller search space
        return ninjaAndLadoos(row2, row1, row2_size, row1_size, k);

    int low = max(0, k - row2_size);
    int high = min(k, row1_size);

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int cut1 = mid;
        int cut2 = k - mid;
        int l1 = (cut1 == 0) ? INT_MIN : row1[cut1 - 1];
        int l2 = (cut2 == 0) ? INT_MIN : row2[cut2 - 1];
        int r1 = (cut1 == row1_size) ? INT_MAX : row1[cut1];
        int r2 = (cut2 == row2_size) ? INT_MAX : row2[cut2];

        if (l1 <= r2 && l2 <= r1)
            return max(l1, l2);
        else if (l1 > r2)
            high = mid - 1;
        else
            low = mid + 1;
    }

    return -1; // Invalid test case
}