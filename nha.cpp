#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <set>
#include <stack>
#include <vector>
#include <cmath>

using namespace std;

/* Hang chuoi de in ra hanh dong */
const char* action[] = { "First State", "pour Water Full Cup1",
    "pour Water Cup1 to Cup2", "pour Water Cup2 to Cup1", "pour Water Cup1 to Cup3", "pour Water Cup3 to Cup1", "pour Water Cup2 to Cup3", "pour Water Cup3 to Cup2" };

/* Khai bao cau truc Cup*/
typedef struct {
    int AmountOfWater; // Luong nuoc co trong Cup
    int TotalAmountOfWater; // Tong luong nuoc trong Cup
} Cup;

/* Khai bao cau truc Cups */
typedef struct {
    Cup Cup[3]; // Cac Cup chua nuoc
    int Goal; // Trang thai dich
} Cups;

/* Khai bao cau truc Node*/
struct Node {
    Cups CupWater;
    Node* parent;
    int no_funtion;
    int g; // Luu gia tri duong di tu nut goc den nut hien tai
    int h; // Luu ket qua uoc luong cua ham heuristic cua nut hien tai den trang thai dich
    int f; // = sum(g+h)
};

/* Dinh nghia phep toan so sanh trong multiset*/
struct node_cmp {
    bool operator()(Node* a, Node* b)
    {
        return a->f < b->f;
    }
};

/* Ham GTLN*/
int max(int X, int Y)
{
    if (X >= Y) {
        return X;
    }
    else {
        return Y;
    }
}

/* Ham GTNN*/
int min(int X, int Y)
{
    if (X <= Y) {
        return X;
    }
    else {
        return Y;
    }
}

/* Ham kiem tra muc tieu */
bool checkSameGoal(Cups Cupwater)
{
    for (int i = 0; i <= 2; i++) {
        if (Cupwater.Cup[i].AmountOfWater == Cupwater.Goal) {
            return true;
        }
    }
    return false;
}

/* Khoi tao Cup*/
void initCups(Cups* CupsWater, int Goal, int X, int Y, int Z)
{
    for (int i = 0; i <= 2; i++) {
        CupsWater->Cup[i].AmountOfWater = 0;
    }
    CupsWater->Cup[0].AmountOfWater = X;
    CupsWater->Cup[0].TotalAmountOfWater = X;
    CupsWater->Cup[1].TotalAmountOfWater = Y;
    CupsWater->Cup[2].TotalAmountOfWater = Z;
    CupsWater->Goal = Goal;
}

/* In trang thai Cup*/
void printCupWater(Cups CupWater)
{

 //   printf("Goal: %d \n", CupWater.Goal);
    int no_action = 0;
    for (int i = 0; i <= 2; i++) {
        printf("Cup %d: Total (%d)--- Water (%d) \n", i + 1, CupWater.Cup[i].TotalAmountOfWater, CupWater.Cup[i].AmountOfWater);
        no_action++;
    }
}
/* Kiem tra Cup da day chua? */
bool checkFullWater(Cup Cupwater)
{
    if (Cupwater.AmountOfWater == Cupwater.TotalAmountOfWater) {
        return true;
    }
    else {
        return false;
    }
}

/* Kiem tra Cup co rong khong?*/
bool checkEmpty(Cup Cupwater)
{
    // printf("%d\n",Cupwater.AmountOfWater);
    if (Cupwater.AmountOfWater == 0) {
        return true;
    }
    else {
        return false;
    }
}

/* Kiem tra 2 Cup co giong nhau khong? */
bool SameCup(Cups CupA, Cups CupB)
{
    for (int i = 0; i <= 2; i++) {
        if (CupA.Cup[i].AmountOfWater != CupB.Cup[i].AmountOfWater) {
            return false;
        }
        if (CupA.Cup[i].TotalAmountOfWater != CupB.Cup[i].TotalAmountOfWater) {
            return false;
        }
    }
    return true;
}
/* Lam day Cup1 */
bool fullWaterCup1(Cups Cupwater, Cups* result)
{
    if (Cupwater.Cup[0].AmountOfWater < Cupwater.Cup[0].TotalAmountOfWater) {
        result->Cup[0].AmountOfWater = Cupwater.Cup[0].TotalAmountOfWater;
        result->Cup[1].AmountOfWater = Cupwater.Cup[1].AmountOfWater;
        result->Cup[2].AmountOfWater = Cupwater.Cup[2].AmountOfWater;
        return true;
    }
    else {
        return false;
    }
}
/* Lam day Cup2 */
bool fullWaterCup2(Cups Cupwater, Cups* result)
{
    if (Cupwater.Cup[1].AmountOfWater < Cupwater.Cup[1].TotalAmountOfWater) {
        result->Cup[0].AmountOfWater = Cupwater.Cup[0].AmountOfWater;
        result->Cup[1].AmountOfWater = Cupwater.Cup[1].TotalAmountOfWater;
        result->Cup[2].AmountOfWater = Cupwater.Cup[2].AmountOfWater;
        return true;
    }
    else {
        return false;
    }
}
/* Lam day Cup3 */
bool fullWaterCup3(Cups Cupwater, Cups* result)
{
    if (Cupwater.Cup[2].AmountOfWater < Cupwater.Cup[2].TotalAmountOfWater) {
        result->Cup[0].AmountOfWater = Cupwater.Cup[0].AmountOfWater;
        result->Cup[1].AmountOfWater = Cupwater.Cup[1].AmountOfWater;
        result->Cup[2].AmountOfWater = Cupwater.Cup[2].TotalAmountOfWater;
        return true;
    }
    else {
        return false;
    }
}
/* Lam rong Cup1 */
bool EmptyWaterCup1(Cups Cupwater, Cups* result)
{
    if (Cupwater.Cup[0].AmountOfWater > 0) {
        result->Cup[0].AmountOfWater = 0;
        result->Cup[1].AmountOfWater = Cupwater.Cup[1].AmountOfWater;
        result->Cup[2].AmountOfWater = Cupwater.Cup[2].AmountOfWater;
        return true;
    }
    else {
        return false;
    }
}
/* Lam rong Cup2 */
bool EmptyWaterCup2(Cups Cupwater, Cups* result)
{
    if (Cupwater.Cup[1].AmountOfWater > 0) {
        result->Cup[0].AmountOfWater = Cupwater.Cup[0].AmountOfWater;
        result->Cup[1].AmountOfWater = 0;
        result->Cup[2].AmountOfWater = Cupwater.Cup[2].AmountOfWater;
        return true;
    }
    else {
        return false;
    }
}
/* Lam rong Cup3 */
bool EmptyWaterCup3(Cups Cupwater, Cups* result)
{
    if (Cupwater.Cup[2].AmountOfWater > 0) {
        result->Cup[0].AmountOfWater = Cupwater.Cup[0].AmountOfWater;
        result->Cup[1].AmountOfWater = Cupwater.Cup[1].AmountOfWater;
        result->Cup[2].AmountOfWater = 0;
        return true;
    }
    else {
        return false;
    }
}

/* Chuyen nuoc tu binh X sang bình Y */
bool PourCupXtoCupY(Cups CupWater, Cups* result)
{
    if (CupWater.Cup[0].AmountOfWater > 0 && CupWater.Cup[1].AmountOfWater < CupWater.Cup[1].TotalAmountOfWater) {
        result->Cup[0].AmountOfWater = max(CupWater.Cup[0].AmountOfWater - (CupWater.Cup[1].TotalAmountOfWater - CupWater.Cup[1].AmountOfWater), 0);
        result->Cup[1].AmountOfWater = min(CupWater.Cup[0].AmountOfWater + CupWater.Cup[1].AmountOfWater, CupWater.Cup[1].TotalAmountOfWater);
        result->Cup[2].AmountOfWater = CupWater.Cup[2].AmountOfWater;
        return true;
    }
    return false;
}
/* Chuyen nuoc tu binh Y sang bình X */
bool PourCupYtoCupX(Cups CupWater, Cups* result)
{
    if (CupWater.Cup[1].AmountOfWater > 0 && CupWater.Cup[0].AmountOfWater < CupWater.Cup[0].TotalAmountOfWater) {
        result->Cup[1].AmountOfWater = max(CupWater.Cup[1].AmountOfWater - (CupWater.Cup[0].TotalAmountOfWater - CupWater.Cup[0].AmountOfWater), 0);
        result->Cup[0].AmountOfWater = min(CupWater.Cup[1].AmountOfWater + CupWater.Cup[0].AmountOfWater, CupWater.Cup[0].TotalAmountOfWater);
        result->Cup[2].AmountOfWater = CupWater.Cup[2].AmountOfWater;
        return true;
    }
    return false;
}
/* Chuyen nuoc tu binh X sang bình Z */
bool PourCupXtoCupZ(Cups CupWater, Cups* result)
{
    if (CupWater.Cup[0].AmountOfWater > 0 && CupWater.Cup[2].AmountOfWater < CupWater.Cup[2].TotalAmountOfWater) {
        result->Cup[0].AmountOfWater = max(CupWater.Cup[0].AmountOfWater - (CupWater.Cup[2].TotalAmountOfWater - CupWater.Cup[2].AmountOfWater), 0);
        result->Cup[2].AmountOfWater = min(CupWater.Cup[0].AmountOfWater + CupWater.Cup[2].AmountOfWater, CupWater.Cup[2].TotalAmountOfWater);
        result->Cup[1].AmountOfWater = CupWater.Cup[1].AmountOfWater;
        return true;
    }
    return false;
}
/* Chuyen nuoc tu binh Z sang bình X */
bool PourCupZtoCupX(Cups CupWater, Cups* result)
{
    if (CupWater.Cup[2].AmountOfWater > 0 && CupWater.Cup[0].AmountOfWater < CupWater.Cup[0].TotalAmountOfWater) {
        result->Cup[2].AmountOfWater = max(CupWater.Cup[2].AmountOfWater - (CupWater.Cup[0].TotalAmountOfWater - CupWater.Cup[0].AmountOfWater), 0);
        result->Cup[0].AmountOfWater = min(CupWater.Cup[2].AmountOfWater + CupWater.Cup[0].AmountOfWater, CupWater.Cup[0].TotalAmountOfWater);
        result->Cup[1].AmountOfWater = CupWater.Cup[1].AmountOfWater;
        return true;
    }
    return false;
}
/* Chuyen nuoc tu binh Y sang bình Z */
bool PourCupYtoCupZ(Cups CupWater, Cups* result)
{
    if (CupWater.Cup[1].AmountOfWater > 0 && CupWater.Cup[2].AmountOfWater < CupWater.Cup[2].TotalAmountOfWater) {
        result->Cup[1].AmountOfWater = max(CupWater.Cup[1].AmountOfWater - (CupWater.Cup[2].TotalAmountOfWater - CupWater.Cup[2].AmountOfWater), 0);
        result->Cup[2].AmountOfWater = min(CupWater.Cup[1].AmountOfWater + CupWater.Cup[2].AmountOfWater, CupWater.Cup[2].TotalAmountOfWater);
        result->Cup[0].AmountOfWater = CupWater.Cup[0].AmountOfWater;
        return true;
    }
    return false;
}
/* Chuyen nuoc tu binh Z sang bình Y */
bool PourCupZtoCupY(Cups CupWater, Cups* result)
{
    if (CupWater.Cup[2].AmountOfWater > 0 && CupWater.Cup[1].AmountOfWater < CupWater.Cup[1].TotalAmountOfWater) {
        result->Cup[2].AmountOfWater = max(CupWater.Cup[2].AmountOfWater - (CupWater.Cup[1].TotalAmountOfWater - CupWater.Cup[1].AmountOfWater), 0);
        result->Cup[1].AmountOfWater = min(CupWater.Cup[2].AmountOfWater + CupWater.Cup[1].AmountOfWater, CupWater.Cup[1].TotalAmountOfWater);
        result->Cup[0].AmountOfWater = CupWater.Cup[0].AmountOfWater;
        return true;
    }
    return false;
}

/* Goi cac phep toan tren trang thai */
bool call_action(Cups Cupwater, Cups* result, int option)
{
    switch (option) {
    case 1:
        return fullWaterCup1(Cupwater, result);
    case 2:
        return PourCupXtoCupY(Cupwater, result);
    case 3:
        return PourCupYtoCupX(Cupwater, result);
    case 4:
        return PourCupXtoCupZ(Cupwater, result);
    case 5:
        return PourCupZtoCupX(Cupwater, result);
    case 6:
        return PourCupYtoCupZ(Cupwater, result);
    case 7:
        return PourCupZtoCupY(Cupwater, result);
    default:
        return false;
    }
}

/* Tim kiem phan tu da co trong explore? */
bool findCups(Cups Cupwater, vector<Cups>* explored)
{
    for (Cups Cup : *explored) {
        if (SameCup(Cupwater, Cup)) {
            return true;
        }
    }
    return false;
}

/* Tim kiem phan tu da co trong frontier? */
Node* findNode(Cups Cupwater, multiset<Node*, node_cmp> list)
{
    for (Node* n : list) {
        if (SameCup(Cupwater, n->CupWater)) {
            return n;
        }
    }
    return NULL;
}

/* Giai thuat A-start */
Node* A_start(Cups Cupwater, int Goal, vector<Cups>* explored)
{
    // Khoi tao
    Node* root = new Node();
    root->CupWater = Cupwater;
    root->parent = NULL;
    root->no_funtion = 0;
    root->g = 0;
    root->h = 1;
    root->f = root->g + root->h;
    // frontiers la tap Open duoc sap xep thu tu
    multiset<Node*, node_cmp> frontiers;
    frontiers.insert(root);
    while (!frontiers.empty()) {
        Node* node = *frontiers.begin();
        frontiers.erase(frontiers.begin());
        explored->push_back(node->CupWater);
        if (checkSameGoal(node->CupWater)) {
            return node;
        }
    	node->no_funtion = 0;
        // Khoi tao cac trang thai
        for (int op = 1; op <= 7; op++) {
            Cups new_Cup;
            new_Cup.Goal = Goal;
            for (int i = 0; i <= 2; i++) {
                new_Cup.Cup[i].TotalAmountOfWater = Cupwater.Cup[i].TotalAmountOfWater;
                new_Cup.Cup[i].AmountOfWater = 0;
            }
            new_Cup.Cup[0].AmountOfWater = new_Cup.Cup[0].TotalAmountOfWater;

            if (call_action(node->CupWater, &new_Cup, op)) {
                if (findCups(new_Cup, explored)) {
                    continue;
                }
                Node* n = findNode(new_Cup, frontiers);
                if (n == NULL) {
                    n = new Node();
                    n->parent = node;
                    n->CupWater = new_Cup;
                    n->no_funtion = op;	
                    n->h = 1;
                    n->g = node->g + 1;
                    n->f = n->g + n->h;
                    frontiers.insert(n);
                }
                else {
                    /*
					Neu nut con moi da thuoc duong bien
					Kiem tra gia tri f cua nut con co nho hon cac nut da nam trong frontier khong?
					Neu nho hon thi cap nhat lai, neu lon hon thi khong cap nhat
					*/
                    n->g = node->g + 1;
                    n->f = n->g + n->h;
                }
                n->no_funtion = op;
            }
        }
    }
    return NULL;
}

/* In trang thai*/
void print_State(Cups Cupwater){
	printf("\nCup1: %d --- Cup2: %d --- Cup3: %d\n", Cupwater.Cup[0].AmountOfWater,Cupwater.Cup[1].AmountOfWater,Cupwater.Cup[2].AmountOfWater);
}

/* In ket qua*/
void print_path(Node* r)
{
    int i = 0;
    stack<Cups> q; // Them nut goc vao Stack
//	printf("duong di: \n");
    while (r->parent != NULL) { 
        q.push(r->CupWater);
        r = r->parent;
    }
    q.push(r->CupWater);
    while (!q.empty()) {
        printf("Trang thai thu %d: ", i++);
    //    printf("\nAction %d: %s",i,action[i]);
        print_State(q.top()); 
        printCupWater(q.top());
        q.pop();
    }
}

int main()
{
    Node* a;
    vector<Cups> trangthai;
    Cups CupWater, result;
    int X, Y, Z, Goal;
    freopen("data.txt", "r", stdin);
    scanf("%d%d%d%d", &Goal, &X, &Y, &Z);
    initCups(&CupWater, Goal, X, Y, Z);
    a = A_start(CupWater, Goal, &trangthai);
    print_path(a);
    return 0;
}