#include "stack.cpp"
#include <string>


int main(){
    char line[255];
    while(cin >> line){
        Stack<char>* s;
        Stack<char>::Init(s);

        Stack<char>* r;
        Stack<char>::Init(r);

        for(int i=0; line[i];i++){
            switch(line[i]){
            case '#':
                Stack<char>::Pop(s);
                break;
            case '@':
                Stack<char>::Clear(s);
                break;
            default:
                Stack<char>::Push(s, line[i]);
            }
        }

        while(!Stack<char>::Empty(s)){
            char t;
            Stack<char>::GetTop(s, t);
            Stack<char>::Pop(s);
            Stack<char>::Push(r, t);
        }

        while(!Stack<char>::Empty(r)){
            char t;
            Stack<char>::GetTop(r, t);
            printf("%c", t);
            Stack<char>::Pop(r);
        }
        cout << endl;
    }
    return 0;
}
