
//======== main.cpp ========
 
#include <stdio.h>
#include <stdlib.h>
#define MAX_LOT_COUNT 100
#define MAX_LOT_SIZE 100000
#define MAX_MEMBER_ID 10000
#define MAX_CROP 100
 
enum DEMAND{
    ASSIGN = 1,
    BACK = 2,
    GROW = 3
};
 
extern void init_member();
extern void assign_member(int member_id, int size);
extern void back_member(int member_id);
extern void grow_member(int member_id, int crop);
 
static int N;
static int lot[MAX_LOT_COUNT + 1][MAX_LOT_SIZE];
static int member[MAX_LOT_COUNT + 1][MAX_LOT_SIZE];
static int lot_cnt;
static int chk_sum;
static int chk_sum_res;
static int chk_size[MAX_MEMBER_ID + 1];
static int chk_crop[MAX_MEMBER_ID + 1];
 
int add_lot(){
    int i;
    if (lot_cnt == MAX_LOT_COUNT)
        return MAX_LOT_COUNT;
    lot_cnt++;
    for (i = 0; i < MAX_LOT_SIZE; i++)
        lot[lot_cnt][i] = member[lot_cnt][i] = 0;
    return lot_cnt;
}
 
void assign(int lot_num, int s, int size, int member_id){
    int i;
    int end;
    if (lot_num < 1 || lot_num > lot_cnt || size < 0)
        return;
    if (s < 0)
        s = 0;
    end = s + size;
    if (end > MAX_LOT_SIZE)
        end = MAX_LOT_SIZE;
    for (i = s; i < end; i++){
        chk_sum -= lot[lot_num][i];
        lot[lot_num][i] = 0;
        member[lot_num][i] = member_id;
    }
}
 
void back(int lot_num, int s, int size){
    int i;
    int end;
    if (lot_num < 1 || lot_num > lot_cnt || size < 0)
        return;
    if (s < 0)
        s = 0;
    end = s + size;
    if (end > MAX_LOT_SIZE)
        end = MAX_LOT_SIZE;
    for (i = s; i < end; i++){
        chk_sum -= lot[lot_num][i];
        lot[lot_num][i] = 0;
        member[lot_num][i] = 0;
    }
}
 
void grow(int lot_num, int s, int size, int crop){
    int i;
    int end;
    if (lot_num < 1 || lot_num > lot_cnt || crop < 1 || crop > MAX_CROP || size < 0)
        return;
    if (s < 0)
        s = 0;
    end = s + size;
    if (end > MAX_LOT_SIZE)
        end = MAX_LOT_SIZE;
    for (i = s; i < end; i++){
        chk_sum -= lot[lot_num][i];
        lot[lot_num][i] = crop;
        chk_sum += lot[lot_num][i];
    }
}
 
static void init(){
    int i;
    lot_cnt = 0;
    chk_sum = 0;
    chk_sum_res = 0;
    for (i = 1; i <= MAX_MEMBER_ID; i++)
        chk_size[i] = chk_crop[i] = 0;
}
 
static int confirm(){
    int i, j;
    for (i = 1; i <= lot_cnt; i++)
    {
        for (j = 0; j < MAX_LOT_SIZE; j++)
        {
            if (chk_crop[member[i][j]] != lot[i][j])
                return 0;
            chk_size[member[i][j]]--;
        }
    }
    for (i = 1; i <= MAX_MEMBER_ID; i++)
    {
        if (chk_size[i] != 0)
            return 0;
    }
    return 1;
}
 
static int run(){
    int i;
    int demand;
    int member_id, size, crop;
    init_member();
    for (i = 0; i < N; i++)    {
        scanf("%d", &demand);
        switch (demand)
        {
        case ASSIGN:
            scanf("%d %d", &member_id, &size);
            assign_member(member_id, size);
            chk_size[member_id] = size;
            break;
        case BACK:
            scanf("%d", &member_id);
            back_member(member_id);
            chk_sum_res -= chk_size[member_id] * chk_crop[member_id];
            chk_size[member_id] = chk_crop[member_id] = 0;
            break;
        case GROW:
            scanf("%d %d", &member_id, &crop);
            grow_member(member_id, crop);
            chk_sum_res -= chk_size[member_id] * chk_crop[member_id];
            chk_crop[member_id] = crop;
            chk_sum_res += chk_size[member_id] * chk_crop[member_id];
            break;
        }
        if (chk_sum != chk_sum_res)
            lot_cnt = MAX_LOT_COUNT;
    }
    if (confirm() == 0)
        lot_cnt = MAX_LOT_COUNT;
    return lot_cnt;
}
 
int main(){
    setbuf(stdout, NULL);
    int total_score = 0, T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; ++tc)    {
        scanf("%d", &N);
        init();
        int score = run();
        printf("#%d %d\n", tc, score);
        total_score += score;
    }
    printf("Total score: %d\n", total_score);
    return 0;
}
