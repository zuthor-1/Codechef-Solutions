Prefix as a Substring Problem Code: SSTRPREF
Given 3 string S1, S2 and X, find the number of non-empty substrings of X which can expressed as P+Q i.e. concatenation of strings P and Q, where P is some prefix of S1 (possibly empty) and Q is some prefix of S2 (possibly empty).

A substring of a string is a contiguous subsequence of that string. For example, "chef" is a substring of "codechef", but "def" is not.

A prefix of a string S is a substring of S that occurs at the beginning of S. For example, "code" is a prefix of "codechef", but "chef" is not. Also, an empty string is a prefix of any string.

Input Format
First line of the input contains T, the number of test cases. Then the test cases follow.
Each test case contains three lines, string S1 in the first line, string S2 in the second line and string X in the third line. All strings consist of only lowercase Latin letters.
Output Format
For each test case, print a single line containing one integer denoting the number of substrings of X that satisfy the above conditions.

Constraints
1≤T≤105
1≤|X|,|S1|,|S2|≤106
Sum of |X| over all test cases doesn't exceed 106.
Sum of |S1| over all test cases doesn't exceed 106.
Sum of |S2| over all test cases doesn't exceed 106.
Sample Input 1 
3
ab
bc
abc
aa
bb
ab
aab
acb
bcaabacbc
Sample Output 1 
5
3
10
Explanation
Test case 1:

There are 6 substrings of X=abc namely [a,b,c,ab,bc,abc].

Observe that a is a prefix of S1=ab and an empty string is a prefix of S2=bc. By concatenating them, we get the string a.
Now an empty string is a prefix of S1 and b is a prefix of S2. And by concatenating them, we get the string b.
Observe that there is no prefix of S1 starting with c and also no prefix of S2 starting with c. So we cannot express the string c as a concatenation of prefixes.
The string ab is a prefix of S1 and an empty string is a prefix of S2. And by concatenation, we get ab.
Similarly, an empty string is a prefix of S1 and bc is a prefix of S2. And by concatenating them, we get bc.
Finally, by taking the prefix a of S1 and the prefix bc of S2, we get abc when we concatenate them.
So all substrings of X except for the substring c can be expressed as a concatenation of some prefix of S1 and some prefix of S2. Therefore, the answer for this test case is 5.

Test case 2:

There are 3 substrings of X=ab namely [a,b,ab].

Observe that a is a prefix of S1=aa and an empty string is a prefix of S2=bb. By concatenating them, we get the string a.
An empty string is a prefix of S1 and b is a prefix of S2. And by concatenating them, we get the string b.
Finally, by taking the prefix a of S1 and the prefix b of S2, we get ab when we concatenate them.
So all substrings of X can be expressed as a concatenation of some prefix of S1 and some prefix of S2. Therefore, the answer for this test case is 3.



#include <bits/stdc++.h>

using namespace std;

#define FIO                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
#define ll long long
#define ii pair<int, int>
#define vi vector<int>
#define vvi vector<vi>

vi Z_function(string s)
{
    int n = s.length();
    vi z(n);
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; i++)
    {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
                z[i]++;
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

struct SparseTable
{
    vvi spt;
    int n, k;

    SparseTable(vi &arr)
    {
        n = (int)arr.size();
        k = (int)log2(n);
        spt.assign(n, vi(k + 1, -1));
        for (int i = 0; i < n; i++)
            spt[i][0] = arr[i] + i;
        build();
    }
    void build()
    {
        for (int j = 1; j <= k; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                spt[i][j] = max(spt[i][j - 1], spt[i + (1 << (j - 1))][j - 1]);
    }
    int query(int l, int r)
    {
        int j = (int)log2(r - l + 1);
        return max(spt[l][j], spt[r - (1 << j) + 1][j]);
    }
};

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        string s1, s2, x;
        cin >> s1 >> s2 >> x;
        x = x + '@';
        int n1 = s1.length(), n2 = s2.length(), nx = x.length();
        vi z1 = Z_function(s1 + '?' + x);
        vi z2 = Z_function(s2 + '?' + x);
        z1 = vi(z1.begin() + n1 + 1, z1.end());
        z2 = vi(z2.begin() + n2 + 1, z2.end());
        SparseTable st = SparseTable(z2);
        ll res = 0;
        for (int i = 0; i < nx; i++){
            int v = i + z1[i];
            res += st.query(i, v) - i;
        }
        cout << res << endl;
    }
}