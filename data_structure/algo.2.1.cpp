#include <iostream>

#include "linear_list.cpp"

void init(LinearList<int>* &A, LinearList<int>* &B, LinearList<int>* &C){

#ifndef _CHAIN_TABLE_
    LinearList<int>::Init(A,4);
    LinearList<int>::Init(B,11);
    LinearList<int>::Init(C,20);
#else
    LinearList<int>::Init(A);
    LinearList<int>::Init(B);
    LinearList<int>::Init(C);
#endif
    LinearList<int>::Insert(A, 1, 11);
    LinearList<int>::Insert(A, 1, 8);
    LinearList<int>::Insert(A, 1, 5);
    LinearList<int>::Insert(A, 1, 3);


    LinearList<int>::Insert(B, 1, 20);
    LinearList<int>::Insert(B, 1, 15);
    LinearList<int>::Insert(B, 1, 11);
    LinearList<int>::Insert(B, 1, 9);
    LinearList<int>::Insert(B, 1, 8);
    LinearList<int>::Insert(B, 1, 6);
    LinearList<int>::Insert(B, 1, 2);
}

bool display(int i){
    std::cout << i << ' ';
    return true;
}

int main(){
    LinearList<int>* LA;
    LinearList<int>* LB;
    LinearList<int>* LC;

    init(LA, LB, LC);
    LinearList<int>::Traverse(LA, (const bool(*)(const int))display);
    std::cout << std::endl;
    LinearList<int>::Traverse(LB, (const bool(*)(const int))display);
    std::cout << std::endl;

    while(!LinearList<int>::Empty(LA) || !LinearList<int>::Empty(LB)){
        bool choose_a;
        if(LinearList<int>::Empty(LA)){
            choose_a = false;
        }
        else if(LinearList<int>::Empty(LB)){
            choose_a = true;
        }
        else{
            int temp_a, temp_b;
            LinearList<int>::GetElem(LA, 0, temp_a);
            LinearList<int>::GetElem(LB, 0, temp_b);

            if(temp_a < temp_b){
                choose_a = true;
            }
            else{
                choose_a = false;
            }
        }

        int temp;
        if(choose_a){
            LinearList<int>::Delete(LA, 0, temp);
            LinearList<int>::Insert(LC, LinearList<int>::Length(LC) + 1, temp);
        }
        else{
            LinearList<int>::Delete(LB, 0, temp);
            LinearList<int>::Insert(LC, LinearList<int>::Length(LC) + 1, temp);
        }
    }

    LinearList<int>::Traverse(LC, (const bool(*)(const int))display);

    return 0;
}
