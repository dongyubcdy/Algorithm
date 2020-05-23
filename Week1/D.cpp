#include <stdio.h>
#include <string.h>

#define MAX 50
#define LIMIT 100000
#define WORNG_ANSWER -1

static char problem[MAX * 20 + 5];
static char ret[LIMIT + MAX * 20];
static char str[MAX + 5];
char user[MAX + 5];

char stk[5][60], op[5];
int top, len;

extern void Cal(char ch, char *user);
bool order(char op1, char op2);
void add(char *a, char *b);
void sub(char *a, char *b);
void mul(char *a, char *b);
void div(char *a, char *b);
void encode(char *a, int *A);
void decode(int *A, char *a);
bool chk_sub(int *A,int *B,int idx,int bn);

int main(void) {
    int TC, t;
    scanf("%d", &TC);
    fgets(str, MAX + 5, stdin);
    for (t = 1; t <= TC; ++t) {
        fgets(problem, MAX * 20 + 5, stdin);
        int pLen = strlen(problem);
        while (problem[pLen - 1] == '\n' || problem[pLen - 1] == '\r')
            problem[--pLen] = '\0';
        memset(ret, 0, sizeof(ret));
        int uLen = 0, retIdx = 0;
        Cal('C', user);
        user[MAX + 1] = 0;
        uLen = strlen(user);
        sprintf(ret + retIdx, "%s ", user);
        retIdx += uLen + 1;
        for (int i = 0; i < pLen;) {
            sscanf(problem + i, "%s", str);
            int slen = strlen(str);
            i += slen + 1;
            if (str[0] >= '0' && str[0] <= '9') {
                for (int j = 0; j < slen; ++j) {
                    Cal(str[j], user);
                    user[MAX + 1] = 0;
                    uLen = strlen(user);
                    sprintf(ret + retIdx, "%s ", user);
                    retIdx += uLen + 1;
                }
            } else {
                Cal(str[0], user);
                user[MAX + 1] = 0;
                uLen = strlen(user);
                sprintf(ret + retIdx, "%s ", user);
                retIdx += uLen + 1;
            }
        }
        puts(ret);
    }
    return 0;
}

extern void Cal(char ch, char *user) {
    if (ch == 'C') {
        top = len = 0;
        user[0] = '0';
        return;
    }
    if ('0' <= ch && ch <= '9') {
        stk[top][len++] = ch;
        stk[top][len] = 0;
        strcpy(user, stk[top]);
        return;
    }
    while (top && order(ch, op[top - 1])) {
        top--;
        if (op[top] == '+')
            add(stk[top], stk[top + 1]);
        else if (op[top] == '-')
            sub(stk[top], stk[top + 1]);
        else if (op[top] == '*')
            mul(stk[top], stk[top + 1]);
        else
            div(stk[top], stk[top + 1]);
    }
    strcpy(user, stk[top]);
    if (ch != '=') op[top++] = ch, len = 0;
}
bool order(char op1, char op2) {
    if (op1 == '=' || op1 == '+' || op1 == '-') return true;
    if (op2 == '*' || op2 == '/') return true;
    return false;
}
void add(char *a, char *b) {
    int A[55] = {0}, B[55] = {0};

    encode(a, A), encode(b, B);
    for (int i = 0; i < MAX; i++) {
        A[i] += B[i];
    }
    decode(A, a);
}
void sub(char *a, char *b) {
    int A[55] = {0}, B[55] = {0};

    encode(a, A), encode(b, B);
    for (int i = 0; i < MAX; i++) {
        A[i] -= B[i];
    }
    decode(A, a);
}
void mul(char *a, char *b) {
    int A[55] = {0}, B[55] = {0}, C[55] = {0};

    encode(a, A), encode(b, B);
    for (int i = 0; i < MAX; i++) {
        for (int j = MAX - i; j < MAX; j++) {
            C[i + j - MAX] += A[i] * B[j];
        }
    }

    decode(C, a);
}
void div(char *a, char *b) {
    int A[55] = {0}, B[55] = {0}, C[55] = {0};

    encode(a, A);
    int bn=strlen(b);
    for (int i = 0; i < bn; i++) B[i+1]=b[i]-'0';
    for (int i = bn; i < MAX; i++)
    {
        while(chk_sub(A,B,i,bn))C[i]++;
    }
    
    
    decode(C, a);
}
void encode(char *a, int *A) {
    int len = strlen(a);
    for (int i = 0, j = MAX - 1; i >= 0; i--, j--) {
        A[j] = a[i] - '0';
    }
}
void decode(int *A, char *a) {
    int i, j;
    for (i = MAX - 1; i >= 0; i--) {
        if (A[i] >= 10) {
            A[i - 1] += A[i] / 10;
            A[i] %= 10;
        } else if (A[i] < 0) {
            A[i - 1]--;
            A[i] += 10;
        }
    }

    for (i = 0; i < MAX && A[i] == 0; i++)
        for (j = 0; i < MAX; i++, j++) {
            a[j] = A[i] + '0';
        }
    a[j] = 0;
}
bool chk_sub(int *A,int *B,int idx,int bn){
     if (idx != 0) {
        if (A[idx - 1] > 0) return true;
    }
    for (int i = 0; i < bn; i++) {
        if (A[idx + i] > B[i]) return true;
        if (A[idx + i] < B[i]) return false;
    }
    return true;
}