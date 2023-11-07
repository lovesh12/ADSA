#include <iostream>
#include <math.h>

using namespace std;

void rabinKarp(string patt, string txt, int m, int n)
{
    int d = 5;
    int patWin = 0;
    int textWin = 0;
    for (int i = 0; i < m; i++)
    {
        patWin = patWin * d + patt[i];  // pattern window
        textWin = textWin * d + txt[i]; // initial text window
    }

    for (int i = 0; i <= n - m; i++)
    {
        cout << textWin << endl;
        if (patWin == textWin)
        {
            bool flag = true;
            for (int j = 0; j < m; j++)
            {
                if (patt[j] != txt[i + j])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                cout << i << " ";
        }
        // slide window
        textWin = (textWin - txt[i] * pow(d, m - 1)) * d + txt[i + m];
    }
}

int main()
{
    string pattern, text;
    getline(cin, text);
    getline(cin, pattern);

    rabinKarp(pattern, text, pattern.length(), text.length());
}