// https://leetcode.com/problems/smallest-k-length-subsequence-with-occurrences-of-a-letter/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string smallestSubsequence(string s, int k, char letter, int needed)
    {

        int cnt_letter = 0;

        for (char ch : s)
            if (letter == ch)
                ++cnt_letter;

        stack<char> st;

        for (int i = 0; i < s.size(); ++i)
        {

            while (!st.empty() && (st.top() > s[i]) && (st.size() - 1 + s.size() - i) >= k && (st.top() != letter || cnt_letter > needed))
            {
                if (letter == st.top())
                    ++needed;
                st.pop();
            }

            if (st.size() < k)
            {
                if (s[i] == letter)
                {
                    st.push(s[i]);
                    --needed;
                }
                else if (k - (int)st.size() > needed)
                {
                    st.push(s[i]);
                }
            }

            if (letter == s[i])
                --cnt_letter;
        }

        string ans;

        while (!st.empty())
        {
            ans.push_back(st.top());
            st.pop();
        }

        reverse(ans.begin(), ans.end());

        return ans;
    }
};

int main()
{
    Solution s;
    cout << s.smallestSubsequence("leet", 3, 'e', 1) << endl;

    return 0;
}