#include<bits/stdc++.h>
#define MAXN 1000000
#define L_TYPE 0
#define S_TYPE 1
using namespace std;
inline bool is_lms_char(int *type, int x) {
    return x > 0 && type[x] == S_TYPE && type[x - 1] == L_TYPE;
}
inline bool equal_substring(int *S, int x, int y, int *type) {
    do {
        if (S[x] != S[y])
            return false;
        x++, y++;
    } while (!is_lms_char(type, x) && !is_lms_char(type, y));

    return S[x] == S[y];
}
inline void induced_sort(int *S, int *SA, int *type, int *bucket, int *lbucket,int *sbucket, int n, int SIGMA)
{
    for (int i = 0; i <= n; i++)
        if (SA[i] > 0 && type[SA[i] - 1] == L_TYPE)
            SA[lbucket[S[SA[i] - 1]]++] = SA[i] - 1;
    for (int i = 1; i <= SIGMA; i++)
        sbucket[i] = bucket[i] - 1;
    for (int i = n; i >= 0; i--)
        if (SA[i] > 0 && type[SA[i] - 1] == S_TYPE)
            SA[sbucket[S[SA[i] - 1]]--] = SA[i] - 1;
}
static int *SAIS(int *S, int length, int SIGMA)
{
    int n = length - 1;
    int *type = new int[n + 1];
    int *position = new int[n + 1];
    int *name = new int[n + 1];
    int *SA = new int[n + 1];
    int *bucket = new int[SIGMA];
    int *lbucket = new int[SIGMA];
    int *sbucket = new int[SIGMA];
    memset(bucket, 0, sizeof(int) * (SIGMA + 1));
    for (int i = 0; i <= n; i++)
        bucket[S[i]]++;
    for (int i = 1; i <= SIGMA; i++)
    {
        bucket[i] += bucket[i - 1];
        lbucket[i] = bucket[i - 1];
        sbucket[i] = bucket[i] - 1;
    }
    type[n] = S_TYPE;
    for (int i = n - 1; i >= 0; i--)
    {
        if (S[i] < S[i + 1])
            type[i] = S_TYPE;
        else if (S[i] > S[i + 1])
            type[i] = L_TYPE;
        else
            type[i] = type[i + 1];
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (type[i] == S_TYPE && type[i - 1] == L_TYPE)
            position[cnt++] = i;
    fill(SA, SA + n + 1, -1);
    for (int i = 0; i < cnt; i++)
        SA[sbucket[S[position[i]]]--] = position[i];
    induced_sort(S, SA, type, bucket, lbucket, sbucket, n, SIGMA);
    fill(name, name + n + 1, -1);
    int lastx = -1, namecnt = 1;
    bool flag = false;
    for (int i = 1; i <= n; i++)
    {
        int x = SA[i];

        if (is_lms_char(type, x)) {
            if (lastx >= 0 && !equal_substring(S, x, lastx, type))
                namecnt++;
            if (lastx >= 0 && namecnt == name[lastx])
                flag = true;

            name[x] = namecnt;
            lastx = x;
        }
    }
    name[n] = 0;
    int *S1 = new int[cnt];
    int pos = 0;
    for (int i = 0; i <= n; i++)
        if (name[i] >= 0)
            S1[pos++] = name[i];

    int *SA1;
    if (!flag)
    {
        SA1 = new int[cnt + 1];
        for (int i = 0; i < cnt; i++)
            SA1[S1[i]] = i;
    }
    else
        SA1 = SAIS(S1, cnt, namecnt);
    lbucket[0] = sbucket[0] = 0;
    for (int i = 1; i <= SIGMA; i++)
    {
        lbucket[i] = bucket[i - 1];
        sbucket[i] = bucket[i] - 1;
    }
    fill(SA, SA + n + 1, -1);
    for (int i = cnt - 1; i >= 0; i--)
        SA[sbucket[S[position[SA1[i]]]]--] = position[SA1[i]];
    induced_sort(S, SA, type, bucket, lbucket, sbucket, n, SIGMA);
    return SA;
}
int main()
{
    return 0;
}
