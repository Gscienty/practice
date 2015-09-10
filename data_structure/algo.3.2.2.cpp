#include "stack.cpp"
#include <string>
int main(){
    Stack<char>* s;
    Stack<char>::Init(s);
    string line;
    cin >> line;
    for(int i=0; i<line.length(); i++){
        char top;
        switch(line[i]){
        case '(':
            Stack<char>::Push(s, '(');
            break;
        case ')':
            Stack<char>::GetTop(s, top);
            if(top == '('){
                Stack<char>::Pop(s);
            }
            else{
                cout << "Error" << endl;
                return 0;
            }
            break;

        case '[':
            Stack<char>::Push(s, '[');
            break;

        case ']':
            Stack<char>::GetTop(s, top);
            if(top == '['){
                Stack<char>::Pop(s);
            }
            else{
                cout << "Error" << endl;
                return 0;
            }
            break;

        case '{':
            Stack<char>::Push(s, '{');
            break;

        case '}':
            Stack<char>::GetTop(s, top);
            if(top == '{'){
                Stack<char>::Pop(s);
            }
            else{
                cout << "Error" << endl;
                return 0;
            }
            break;
        }
    }

    if(Stack<char>::Empty(s)){
        cout << "Success" << endl;
    }
    else{
        cout << "Error" << endl;
    }

    return 0;
}
