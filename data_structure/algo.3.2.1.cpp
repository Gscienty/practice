/*
  ÊýÖÆ×ª»»
  Author: Gscienty
*/

#include "stack.cpp"

int main(){
    int n, k;
    cin >> n >> k;
    Stack<int>* s;
    Stack<int>::Init(s);
    while(n){
        Stack<int>::Push(s, n % k);
        n /= k;
    }
    while(!Stack<int>::Empty(s)){
        int top;
        Stack<int>::GetTop(s, top);
        switch(top){
        case 10: cout << 'A'; break;
        case 11: cout << 'B'; break;
        case 12: cout << 'C'; break;
        case 13: cout << 'D'; break;
        case 14: cout << 'E'; break;
        case 15: cout << 'F'; break;
        default:
            cout << top;
        }

        Stack<int>::Pop(s);
    }
    return 0;
}
