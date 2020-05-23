//======== user.cpp ========
#ifndef NULL
#define NULL 0
#endif


extern int add_lot();
extern void assign(int lot_num, int s, int size, int member_id);
extern void back(int lot_num, int s, int size);
extern void grow(int lot_num, int s, int size, int crop);
void push(int id, int lot, int start, int size);

int bn, space[10010];

class data {
   public:
    int lot, st, size;
    data* next;
    data* alloc(int lot, int st, int size, data* next) {
        this->lot = lot;
        this->st = st;
        this->size = size;
        this->next = next;
        return this;
    }
};

data buf[50005], *mem[10010];

/* void print(data* p){
    if(p==nullptr)return;
    std::cout<<"[lot_num]: "<<p->lot<<" [size]: "<<p->size;
}

void test() {
    for (int i = 0; i <= 10000; i++) {
          int sum=0;
        for (data* p = mem[i]; p; p = p->next) {
            sum+=p->size;
            //print(p);
        }
        if(sum!=0)
        std::cout<<"[member_id]: "<<i<<std::endl<<"  Total size: "<<sum<<std::endl<<std::endl;
    }
}
 */

void init_member() {
    bn = 0;
    for (int i = 0; i < 10001; i++) {
        mem[i] = 0;
        space[i] = 0;
    }
}

void push(int id, int lot, int st, int size) {
    mem[id] = buf[bn++].alloc(lot, st, size, mem[id]);
}
//e가 s의 제일 앞에 노드를 가져간다.
void move(int s, int e) {
    data* tmp = mem[s];
    mem[s] = mem[s]->next;
    tmp->next = mem[e];
    mem[e] = tmp;
}

/* 
void assign_member(int member_id, int size) {
    if (size > space[0]) {
        int lot = add_lot();
        push(0, lot, 0, 10000);
        space[0] += 10000;
    }
    space[0] -= size;
    space[member_id] += size;
    while (size > 0 && mem[0]->size <= size) {
        assign(mem[0]->lot, mem[0]->st, mem[0]->size, member_id);
        move(0, member_id);
        // size-=mem[0]->size;
        // //size를 줄여주줘야댐
    }
    if (size > 0) {
        assign(mem[0]->lot, mem[0]->st, size, member_id);
        push(member_id, mem[0]->lot, mem[0]->st, size);
        mem[0]->st += size, mem[0]->size -= size;
    }
}
 */

void assign_member(int member_id, int size) {
    if (size > space[0]) {
        int lot = add_lot();
        push(0, lot, 0, 100000);
        space[0] += 100000;
    }
    space[0] -= size;
    space[member_id] += size;
    while (size > 0 && mem[0]->size <= size) {
        assign(mem[0]->lot, mem[0]->st, mem[0]->size, member_id);
        size -= mem[0]->size;
        move(0, member_id);
        // size-=mem[0]->size;
        // //size를 줄여주줘야댐
    }
    if (size > 0) {
        assign(mem[0]->lot, mem[0]->st, size, member_id);
        push(member_id, mem[0]->lot, mem[0]->st, size);
        mem[0]->st += size, mem[0]->size -= size;
    }
}

void back_member(int member_id) {
    space[0] += space[member_id];
    space[member_id] = 0;
    while (mem[member_id]) {
        back(mem[member_id]->lot, mem[member_id]->st, mem[member_id]->size);
        move(member_id, 0);
        //    bn--;
    }
}

void grow_member(int member_id, int crop) {
    for (data* p = mem[member_id]; p != 0; p = p->next) {
        grow(p->lot, p->st, p->size, crop);
    }
}