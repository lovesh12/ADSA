#include <bits/stdc++.h>

using namespace std;

void kmp(string text, string pattern)
{
    int n = text.size(), m = pattern.size();
    vector<int> lps = LPS(pattern);
    for (int i = 0, j = 0; i < n;)
    {
        if (text[i] == pattern[j])
        {
            i++, j++;
        }
        if (j == m)
        {
            cout << i - j << " ";
            j = lps[j - 1];
        }
        if (i < n && text[i] != pattern[j])
        {
            if (j > 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

vector<int> LPS(string pattern)
{
    int m = pattern.size();
    vector<int> lps(m, 0);
    for (int i = 1, len = 0; i < m;)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i++] = len;
        }
        else if (len)
        {
            len = lps[len - 1];
        }
        else
        {
            lps[i++] = 0;
        }
    }
    return lps;
}