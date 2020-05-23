/**************************************************************
    Problem: 3115
    User: dysoft.choi
    Language: C++
    Result: Wrong Answer
****************************************************************/
 
 
#include <iostream>
#include <string>
 
#define MAX_LEN 205
 
using namespace std;
 
void Big(string *a, string *b);
void encode(string s, int *S);
void div(int* A,int* B,int* C);
bool sub(int* A,int *B,int idx);
 
string a, b;
int dif_len;
int a_len,b_len;
 
int main()
{
    while (true)
    {
        cin>>a>>b;
        if (a == "0" || b == "0")
            return 0;
        
        Big(&a,&b);
        
        a_len=a.length(),b_len=b.length();
        dif_len=a_len-b_len;
        dif_len++;
 
        int A[MAX_LEN] = {0}, B[MAX_LEN] = {0};
 
        int DIV[MAX_LEN] = {0};
 
        encode(a, A);
        encode(b, B);
        div(A,B,DIV);
 
        for (int i = 0; i <dif_len; i++){
            if(DIV[i]==0&&i==0)continue;
            cout << DIV[i];
        }
        cout << endl;
    }
    return 0;
}
 
void Big(string *a, string *b)
{
    if ((*a).length() > (*b).length())
    {
        return;
    }
    else if ((*a).length() < (*b).length())
    {
        string tmp = *a;
        *a = *b;
        *b = tmp;
        return;
    }
    else
    {
        for (int i = 0; i < (*a).length(); i++)
        {
            if ((*a)[i] > (*b)[i])
            {
                return;
            }
            else if ((*a)[i] < (*b)[i])
            {
                string tmp = *a;
                *a = *b;
                *b = tmp;
                return;
            }
        }
    }
}
 
void encode(string s, int *S) //string to int*
{
    for (int i = 0; i < s.length(); i++)
    {
        if ('0' <= s[i] && s[i] <= '9')
            S[i] = s[i] - '0';
    }
}
 
void div(int* A,int* B,int* C){
    /*
    1. 해당 자리에서 뺄 수 있는지 확인
    2. 뺄 수 있다면 뺀다.
    */
    for (int d = 0; d < dif_len; d++)
    {
        while (sub(A, B, d))
        {
            for (int bl = b_len - 1 ; bl >= 0; bl--)
            {
                A[d+bl]-=B[bl];
                if(A[d+bl]<0){
                    A[d+bl-1]--;
                    A[d+bl]+=10;
                }
            }
            C[d]++;
        }
    }
}
 
bool sub(int* A,int *B,int idx){
    if(idx!=0){
        if(A[idx-1]>0) return true;
    }
    for (int i = 0; i < b_len; i++)
    {
        if(A[idx+i]>B[i]) return true;
        if(A[idx+i]<B[i]) return false;
    }
    return true;
     
}