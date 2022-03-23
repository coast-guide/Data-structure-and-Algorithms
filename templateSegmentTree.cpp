#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{

    vector<int> segmentTree;
    vector<int> arr;
    void build(int segmentTree_index, int start, int end)
    {

        if (start == end)
        {
            segmentTree[segmentTree_index] = arr[start];
            return;
        }

        int mid = start + (end - start) / 2;

        build(2 * segmentTree_index + 1, start, mid);
        build(2 * segmentTree_index + 2, mid + 1, end);

        segmentTree[segmentTree_index] = min(segmentTree[2 * segmentTree_index + 1], segmentTree[2 * segmentTree_index + 2]);
    }

public:
    SegmentTree(vector<int> &arr1)
    {
        arr = arr1;
        segmentTree.resize(4 * arr1.size());
        build(0, 0, arr.size() - 1);
    }

    int query(int query_left, int query_right, int start, int end, int segmentTree_index)
    {

        // No overlap
        if (query_right < start || query_left > end)
            return INT_MAX;

        // Complete overlap
        if (start >= query_left && end <= query_right)
            return segmentTree[segmentTree_index];

        // partial overlap
        int mid = start + (end - start) / 2;
        int left = query(query_left, query_right, start, mid, 2 * segmentTree_index + 1);

        int right = query(query_left, query_right, mid + 1, end, 2 * segmentTree_index + 2);

        return min(left, right);
    }

    void update(int start, int end, int target_index, int target, int segmentTree_index)
    {

        if (start == end)
        {
            segmentTree[segmentTree_index] = target;
            return;
        }

        int mid = start + (end - start) / 2;

        if (target_index <= mid)
            update(start, mid, target_index, target, 2 * segmentTree_index + 1);
        else
            update(mid + 1, end, target_index, target, 2 * segmentTree_index + 2);

        segmentTree[segmentTree_index] = min(segmentTree[2 * segmentTree_index + 1], segmentTree[2 * segmentTree_index + 2]);
    }
};

void solve2()
{

    int n1;
    cin >> n1;
    vector<int> arr1(n1);

    for (int i = 0; i < n1; i++)
        cin >> arr1[i];

    int n2;
    cin >> n2;
    vector<int> arr2(n2);
    for (int i = 0; i < n2; i++)
        cin >> arr2[i];

    int q;
    cin >> q;

    while (q--)
    {

        int type;
        cin >> type;
        SegmentTree st1(arr1), st2(arr2);
        if (type == 1)
        {

            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;

            cout << min(st1.query(l1, r1, 0, n1 - 1, 0), st2.query(l2, r2, 0, n2 - 1, 0)) << endl;
        }
        else
        {
            int arr_number, index, val;
            cin >> arr_number >> index >> val;

            if (arr_number == 1)
            {
                st1.update(0, n1 - 1, index, val, 0);
                arr1[index] = val;
            }
            else
            {
                st2.update(0, n2 - 1, index, val, 0);
                arr2[index] = val;
            }
        }
    }
}

int main()
{

    solve2();

    return 0;
}

// void solve()
// {
//     int n;
//     cin >> n;

//     vector<int> arr(n);

//     for (int i = 0; i < n; i++)
//         cin >> arr[i];

//     vector<int> segmentTree(4 * n);

//     build(arr, segmentTree, 0, 0, n - 1);

//     int q;
//     cin >> q;

//     while (q--)
//     {
//         int type = 1;
//         cin >> type;

//         if (type == 1)
//         {
//             int l, r;
//             cin >> l >> r;

//             cout << query(l, r, 0, n - 1, 0, segmentTree, arr) << endl;
//         }
//         else
//         {
//             int i, val;
//             cin >> i >> val;
//             update(arr, segmentTree, 0, n - 1, i, val, 0);
//             arr[i] = val;
//         }
//     }
// }