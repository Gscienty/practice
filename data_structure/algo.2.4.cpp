#include "linear_list.cpp"

struct node{
    int coeff;
    int pointer;
};

node create(int c, int p){
    node result;
    result.coeff = c;
    result.pointer = p;
    return result;
}

bool tt(node n){
    cout << n.coeff << ' ' << n.pointer << '\n';
    return true;
}

void init(LinearList<node>* &A, LinearList<node>* &B){
    LinearList<node>::Init(A);
    LinearList<node>::Init(B);

    LinearList<node>::Insert(A, 1, create(5, 17));
    LinearList<node>::Insert(A, 1, create(9, 8));
    LinearList<node>::Insert(A, 1, create(3, 1));
    LinearList<node>::Insert(A, 1, create(7, 0));


    LinearList<node>::Insert(B, 1, create(-9, 8));
    LinearList<node>::Insert(B, 1, create(22, 7));
    LinearList<node>::Insert(B, 1, create(8, 1));
}

int main(){
    LinearList<node>* A;
    LinearList<node>* B;
    LinearList<node>* C;

    init(A,B);

    LinearList<node>::Init(C);

    while(!LinearList<node>::Empty(A) || !LinearList<node>::Empty(B)){
        bool choose_a;
        if(LinearList<node>::Empty(A)){
            choose_a = false;
        }
        else if(LinearList<node>::Empty(B)){
            choose_a = true;
        }
        else{
            node temp_a, temp_b;
            LinearList<node>::GetElem(A, 0, temp_a);
            LinearList<node>::GetElem(B, 0, temp_b);
            if(temp_a.pointer == temp_b.pointer){
                LinearList<node>::Delete(A, 0, temp_a);
                LinearList<node>::Delete(B, 0, temp_b);

                if(temp_a.coeff + temp_b.coeff){
                    LinearList<node>::Insert(C, LinearList<node>::Length(C)+1, create(temp_a.coeff + temp_b.coeff, temp_a.pointer));
                }
                continue;
            }
            else if(temp_a.pointer < temp_b.pointer){
                choose_a = true;
            }
            else{
                choose_a = false;
            }
        }

        node temp;
        if(choose_a){
            LinearList<node>::Delete(A, 0, temp);
        }
        else{
            LinearList<node>::Delete(B, 0, temp);
        }
        LinearList<node>::Insert(C, LinearList<node>::Length(C)+1, temp);
    }
    LinearList<node>::Traverse(C, (const bool(*)(const node))tt);
    return 0;
}
