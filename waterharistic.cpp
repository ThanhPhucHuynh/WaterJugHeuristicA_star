#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <set>
#include <stack>
#include <vector>
#include <cmath>

using namespace std;

// struct for Cuo include:
// cau truc cua mot Cuo nuoc
typedef struct{ 
    int AmountOfWater; //luong nuoc hien tai Cup dang chua
    int TotalAmountOfWater;// Luong nhuoc toi da ma cup co the chua
}Cup;

typedef struct {
    // Cup Cup1;
    // Cup Cup2;
    // Cup Cup3;
    Cup Cup[3]; // array cup (we have tree cup)
    int Goal; // var save status final
}Cups;



struct Node{   
    Cups CupWater;
    Node* parent;
    int no_function; // save parent Node
    int g; // value router root to node
    int h; // value heuristic of node to root
    int f; // sum(g+h)
};

struct node_cmp{
    bool operator()(Node* a,Node* b){
        return a->f < b->f;
    }
};
// array action String
const char*  action[] = {"first State", "pour Water X-Y", "pour Water X-Z","pour Water Y-X", "pour Water Z-X", "pour Water Y to Z", "pour Water Z to Y"
};

//get value max a and b 
int max(int X,int Y){
    if(X>=Y){
        return X;
    }else{
        return Y;
    }
}
//kget value min a and b
int min(int X, int Y){
    if(X<=Y){
        return X;
    }else{
        return Y;
    }
}

// check exist cup in Cups same with goal
 bool checkSameGoal(Cups Cupwater){
     for(int i = 0; i <= 2; i++){
         if(Cupwater.Cup[i].AmountOfWater == Cupwater.Goal){
             return true;
         }
     }
     return false;
 }


// init list Cups (3 cup) and set Goal
void initCups(Cups *CupsWater,int Goal,int X,int Y,int Z){

    // CupsWater->Cup1.AmountOfWater = 0;
    // CupsWater->Cup2.AmountOfWater = 0;
    // CupsWater->Cup3.AmountOfWater = 0;

    // CupsWater->Cup1.TotalAmountOfWater = 16;
    // CupsWater->Cup2.TotalAmountOfWater =  7;
    // CupsWater->Cup3.TotalAmountOfWater =  3;
    for(int i=0;i<=2;i++){
        CupsWater->Cup[i].AmountOfWater = 0;
    }
    CupsWater->Cup[0].AmountOfWater = X; // first Cup full water
    
    CupsWater->Cup[0].TotalAmountOfWater = X;
    CupsWater->Cup[1].TotalAmountOfWater = Y;
    CupsWater->Cup[2].TotalAmountOfWater = Z;

    CupsWater->Goal = Goal;
}

// function used save fist status for Cups
void initCups1(Cups *CupsWater,int Goal,int X,int Y,int Z){

    // CupsWater->Cup1.AmountOfWater = 0;
    // CupsWater->Cup2.AmountOfWater = 0;
    // CupsWater->Cup3.AmountOfWater = 0;

    // CupsWater->Cup1.TotalAmountOfWater = 16;
    // CupsWater->Cup2.TotalAmountOfWater =  7;
    // CupsWater->Cup3.TotalAmountOfWater =  3;
   
    for(int i=0;i<=2;i++){
        CupsWater->Cup[i].AmountOfWater = 0;
    }
    CupsWater->Cup[0].TotalAmountOfWater = X;
    CupsWater->Cup[1].TotalAmountOfWater = Y;
    CupsWater->Cup[2].TotalAmountOfWater = Z;

    CupsWater->Goal = Goal;
}

//show now status Cups
void printCupWater(Cups CupWater){
    printf("Goal: %d \n",CupWater.Goal);
    for(int i=0;i<=2;i++){
        printf("Cup %d: total( %d ) -- Water( %d ) \n",i+1,CupWater.Cup[i].TotalAmountOfWater, CupWater.Cup[i].AmountOfWater);
    }
    
}

//check full
bool checkFullWater(Cup Cupwater){
    if(Cupwater.AmountOfWater == Cupwater.TotalAmountOfWater){
        return true;
    }else{
        return false;
    }
}
bool checkEmpty(Cup Cupwater){
    // printf("%d\n",Cupwater.AmountOfWater);
    if(Cupwater.AmountOfWater==0){
        return true;
    }else{
        return false;
    }
}


bool SameCup(Cups CupA,Cups CupB){
    for(int i=0;i<=2;i++){
        if(CupA.Cup[i].AmountOfWater!=CupB.Cup[i].AmountOfWater){
            return false;
        }
        if(CupA.Cup[i].TotalAmountOfWater!=CupB.Cup[i].TotalAmountOfWater){
            return false;
        }
    }
    return true;
}
// fill and empty
void fillWaterCup1(Cups Cupwater,Cups *result){
    result->Cup[0].AmountOfWater = Cupwater.Cup[0].TotalAmountOfWater;
    result->Cup[1].AmountOfWater = Cupwater.Cup[1].AmountOfWater;
    result->Cup[2].AmountOfWater = Cupwater.Cup[2].AmountOfWater;
}
void fillWaterCup2(Cups Cupwater,Cups *result){
    result->Cup[1].AmountOfWater = Cupwater.Cup[1].TotalAmountOfWater;
    result->Cup[0].AmountOfWater = Cupwater.Cup[0].AmountOfWater;
    result->Cup[2].AmountOfWater = Cupwater.Cup[2].AmountOfWater;


}
void fillWaterCup3(Cups Cupwater, Cups *result){
    result->Cup[1].AmountOfWater = Cupwater.Cup[1].AmountOfWater;
    result->Cup[0].AmountOfWater = Cupwater.Cup[0].AmountOfWater;
    result->Cup[2].AmountOfWater = Cupwater.Cup[2].TotalAmountOfWater;
}
void EmptyWaterCup1(Cups Cupwater, Cups *result){
    result->Cup[0].AmountOfWater = 0;
    result->Cup[1].AmountOfWater = Cupwater.Cup[1].AmountOfWater;
    result->Cup[2].AmountOfWater = Cupwater.Cup[2].AmountOfWater;
}
void EmptyWaterCup2(Cups Cupwater, Cups *result){
    result->Cup[1].AmountOfWater = 0;
    result->Cup[0].AmountOfWater = Cupwater.Cup[0].AmountOfWater;
    result->Cup[2].AmountOfWater = Cupwater.Cup[2].AmountOfWater;
}
void EmptyWaterCup3(Cups Cupwater, Cups *result){
    result->Cup[2].AmountOfWater = 0;
    result->Cup[1].AmountOfWater = Cupwater.Cup[1].AmountOfWater;
    result->Cup[0].AmountOfWater = Cupwater.Cup[0].AmountOfWater;
}
// pour
bool PourCupXtoCupY(Cups CupWater,int X, int Y,Cups *result,int CupNoPour){
    //save staus for cup which not change
    result->Cup[CupNoPour].AmountOfWater = CupWater.Cup[CupNoPour].AmountOfWater;

    if(!checkFullWater(CupWater.Cup[Y])&&!checkEmpty(CupWater.Cup[X])){
        result->Cup[Y].AmountOfWater = min((CupWater.Cup[X].AmountOfWater+CupWater.Cup[Y].AmountOfWater),CupWater.Cup[Y].TotalAmountOfWater);
        result->Cup[X].AmountOfWater = max(0,CupWater.Cup[X].AmountOfWater-(CupWater.Cup[Y].TotalAmountOfWater - CupWater.Cup[Y].AmountOfWater));
        //  printf("%d-%d\n",CupWater.Cup[X].AmountOfWater,CupWater.Cup[Y].AmountOfWater);
        return true;// return true if pour successfully
    }else{
        if(checkFullWater(CupWater.Cup[Y])){
            // printf("Can't pour %d to %d because cup %d: full\n",X,Y,Y);
        }else{
            // printf("Can't pour %d to %d because cup %d: empty\n",X,Y,X);
        }
        return false;// return false if erro
    }
}

bool call_action(Cups Cupwater, Cups *result, int option){
   
    switch(option){
    
        // case 1 : fillWaterCup1(Cupwater,result); return true;
        // case 2 : fillWaterCup2(Cupwater,result); return true;
        // case 3 : fillWaterCup3(Cupwater,result); return true;
        // case 4 : EmptyWaterCup1(Cupwater,result);return true;
        // case 5 : EmptyWaterCup2(Cupwater,result);return true;
        // case 6 : EmptyWaterCup3(Cupwater,result);return true;

        case 1: return PourCupXtoCupY(Cupwater,0,1,result,2);
        case 2: return PourCupXtoCupY(Cupwater,0,2,result,1);
        case 3: return PourCupXtoCupY(Cupwater,1,0,result,2);
        case 4: return PourCupXtoCupY(Cupwater,2,0,result,1);
        case 5: return PourCupXtoCupY(Cupwater,1,2,result,0);
        case 6: return PourCupXtoCupY(Cupwater,2,1,result,0);

        default: return false;


    }
}

int h1(Cups Cupwater, int Goal){
    return 1;
}

bool findCups(Cups Cupwater,vector<Cups> *explored){
    for(Cups Cup: *explored){
        if(SameCup(Cupwater,Cup)){
            return true;
        }
    }
    return false;
}
Node* findNode(Cups Cupwater, multiset<Node*,node_cmp> list){
    for(Node* n: list){
        if(SameCup(Cupwater,n->CupWater)){
            return n;
        }
    }
    return NULL;
}

Node* A_start(Cups Cupwater,int Goal,vector<Cups> *explored){

    Node* root =  new Node();
    root->CupWater = Cupwater;
    root->parent = NULL;
    root->g = 0;
    // root->h = 1;
    root ->h = h1(Cupwater,Goal);
    root->f = root->g + root->h;
  
    multiset<Node*,node_cmp> frontiers;
    frontiers.insert(root);
    
    while(!frontiers.empty()){
        Node *node = *frontiers.begin();
        frontiers.erase(frontiers.begin());
        explored->push_back(node->CupWater);
        if(checkSameGoal(node->CupWater)){
            return node;
        }
        for(int op=1;op<=6;op++){
            Cups new_Cup;
            
            new_Cup.Goal = Goal;
            
            for(int i=0;i<=2;i++){
                new_Cup.Cup[i].TotalAmountOfWater = Cupwater.Cup[i].TotalAmountOfWater;
                new_Cup.Cup[i].AmountOfWater = 0;
            }
            new_Cup.Cup[0].AmountOfWater = new_Cup.Cup[0].TotalAmountOfWater;

            if(call_action(node->CupWater,&new_Cup,op)) {
                if(findCups(new_Cup,explored)){
                    continue;
                }
                Node* n = findNode(new_Cup,frontiers);
                if(n==NULL){
                    n=new Node();
                    n->parent = node;
                    n->CupWater = new_Cup;
                    // n->h = 1 ;
                    n->h = h1(new_Cup,Goal);
                    n->no_function = op;
                  
                    n->g = node->g + n->h;  
                    n->f=n->g+n->h;
                  
                    frontiers.insert(n);
                }
                else{
                    n->g = node->g+ 1 ;
                    n->f = n->g + n->h;
                }
            }
            
        }
    }
    return NULL;
}

void print_path(Node*r){
    int i = 0;
    stack<Cups> q;
    stack<int> index;
    printf("duong di: \n");
    while(r->parent !=NULL){
        q.push(r->CupWater);
        index.push(r->no_function);
        r=r->parent;
    }
    index.push(r->no_function);
    q.push(r->CupWater);
    int no_action = 0;
    while(!q.empty()){
        printf("TRang thai thu %d: \n",i+1);
        i++;
        printf("\nAction %d: %s\n", index.top(), action[index.top()]);
        printCupWater(q.top());

        no_action++;
        q.pop();
        index.pop();
    }
}

int main(){

    Node *a;
    vector<Cups> hihi;
    Cups CupWater,result;
    int X,Y,Z,Goal;
    freopen("data.txt","r",stdin);

    // input value by finger hihi
    // printf("Goal: ");scanf("%d",&Goal);
    // printf("Cup1: ");scanf("%d",&X);
    // printf("Cup2: ");scanf("%d",&Y);
    // printf("Cup3: ");scanf("%d",&Z);

    // input auto from file data.txt
    scanf("%d%d%d%d",&Goal,&X,&Y,&Z);
    //init Cup list
    initCups(&CupWater,Goal,X,Y,Z);
    // fillWaterCup1(CupWater,&CupWater);

    initCups1(&result,Goal,X,Y,Z);
    printCupWater(result);
    a = A_start(CupWater,Goal,&hihi);
    print_path(a);
   
    return 0;
}


