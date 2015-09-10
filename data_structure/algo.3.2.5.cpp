#include "stack.cpp"
#include <string>

void calcu(Stack<int>* n, Stack<char>* c){
    char op;
    Stack<char>::GetTop(c, op);
    if(op == '(') return;
    Stack<char>::Pop(c);
    int temp_a, temp_b;
    Stack<int>::GetTop(n, temp_b);
    Stack<int>::Pop(n);
    Stack<int>::GetTop(n, temp_a);
    Stack<int>::Pop(n);
    switch(op){
    case '+':
        Stack<int>::Push(n, temp_a + temp_b);
        break;
    case '-':
        Stack<int>::Push(n, temp_a - temp_b);
        break;
    case '*':
        Stack<int>::Push(n, temp_a * temp_b);
        break;
    case '/':
        Stack<int>::Push(n, temp_a / temp_b);
    }
}

int main(){
    Stack<int>* n;
    Stack<int>::Init(n);
    Stack<char>* c;
    Stack<char>::Init(c);
    string line;
    cin >> line;

    int temp = 0;
    bool num_flag = false;
    for(int i=0; i < line.length(); i++){
        char op;
        switch(line[i]){
        case '+':
            if(num_flag){
                Stack<int>::Push(n, temp);
                temp = 0;
                num_flag = false;
            }
            if(!Stack<char>::Empty(c)){
                calcu(n,c);
            }
            Stack<char>::Push(c, '+');
            break;
        case '-':
            if(num_flag){
                Stack<int>::Push(n, temp);
                temp = 0;
                num_flag = false;
            }
            if(!Stack<char>::Empty(c)){
                calcu(n,c);
            }
            Stack<char>::Push(c, '-');
            break;
        case '*':
            if(num_flag){
                Stack<int>::Push(n, temp);
                temp = 0;
                num_flag = false;
            }
            char op;
            Stack<char>::GetTop(c, op);
            if(!Stack<char>::Empty(c) && (op == '*' || op == '/')){
                calcu(n,c);
            }
            Stack<char>::Push(c, '*');
            break;
        case '/':
            if(num_flag){
                Stack<int>::Push(n, temp);
                temp = 0;
                num_flag = false;
            }
            Stack<char>::GetTop(c, op);
            if(!Stack<char>::Empty(c) && (op == '*' || op == '/')){
                calcu(n,c);
            }
            Stack<char>::Push(c, '/');
            break;
        case '(':
            Stack<char>::Push(c, '(');
            break;
        case ')':
            if(num_flag){
                Stack<int>::Push(n, temp);
                temp = 0;
                num_flag = false;
            }
            Stack<char>::GetTop(c, op);
            while(op != '('){
                calcu(n, c);
                Stack<char>::GetTop(c, op);
            }
            Stack<char>::Pop(c);
            break;
        default:
            num_flag = true;
            temp *= 10;
            temp += line[i] - 48;
        }
    }

    if(num_flag){
        Stack<int>::Push(n, temp);
    }

    while(!Stack<char>::Empty(c)){
        calcu(n,c);
    }

    int answer;
    Stack<int>::GetTop(n, answer);
    cout << answer;


    return 0;
}
