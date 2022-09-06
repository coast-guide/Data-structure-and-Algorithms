#include <bits/stdc++.h>
using namespace std;

class Solution
{

    bool canRun(long long mid, long long n, vector<int> &batteries)
    {

        long long run_time = 0;

        for (long long battery : batteries)
            run_time += min(mid, battery);

        return run_time >= mid * n;
    }

public:
    long long maxRunTime(int n, vector<int> &batteries)
    {

        long long low = 0, high = 0;

        for (int battery : batteries)
            high += battery;

        high /= (long long)n;

        long long ans = 0;

        while (low <= high)
        {

            long long mid = low + (high - low) / 2;

            if (canRun(mid, n, batteries))
            {
                ans = mid;
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }

        return ans;
    }
};
