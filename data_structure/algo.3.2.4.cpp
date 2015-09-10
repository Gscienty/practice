#include "stack.cpp"

bool map[10][10] = {
    {0,0,0,0,0,0,0,0,0,0},
    {0,1,1,0,1,1,1,0,1,0},
    {0,1,1,0,1,1,1,0,1,0},
    {0,1,1,1,1,0,0,1,1,0},
    {0,1,0,0,0,1,1,1,1,0},
    {0,1,1,1,0,1,1,1,1,0},
    {0,1,0,1,1,1,0,1,1,0},
    {0,1,0,0,0,1,0,0,1,0},
    {0,0,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0}
};

struct node{
    int x;
    int y;
};

node create(int x, int y){
    node result;
    result.x = x;
    result.y = y;
    return result;
}

node create(node ori){
    node result;
    result.x = ori.x;
    result.y = ori.y;
    return result;
}

bool mapping(int x, int y, Stack<node>* s){
    Stack<node>::Push(s,create(x,y));
    map[x][y] = false;
    if(x == 8 && y == 8){
        return true;
    }
    else{
        if(map[x][y+1]){
            if(mapping(x,y+1,s)){
                return true;
            }
        }
        if(map[x][y-1]){
            if(mapping(x,y-1,s)){
                return true;
            }
        }
        if(map[x+1][y]){
            if(mapping(x+1,y,s)){
                return true;
            }
        }
        if(map[x-1][y]){
            if(mapping(x-1,y,s)){
                return true;
            }
        }

        Stack<node>::Pop(s);
        return false;
    }
}

bool tt(node n){
    cout << '(' << n.x << ',' <<n.y << ')' <<endl;
    return true;
}

int main(){
    Stack<node>* s;
    Stack<node>::Init(s);

    mapping(1,1,s);

    Stack<node>::Traverse(s,(const bool(*)(const node))tt);

    return 0;
}
