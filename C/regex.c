#include <stdio.h>
#include <malloc.h>

char input_string[256];
char input_regex[256];

int main(){
    scanf("%s", input_string);
    scanf("%s", input_regex);

    char* string_pointer = input_string;
    char* regex_pointer = input_regex;

    char* start = 0;
    int length = 0;

    while(*string_pointer & *regex_pointer){
        switch(*regex_pointer){
        case '.':
            regex_pointer++;
            length++;
            break;
        default:
            if(*regex_pointer == *string_pointer){
                if(regex_pointer[1] != '*') regex_pointer++;
                length++;
            }
            else{
                if(regex_pointer[1] == '*'){
                    regex_pointer += 2;
                    length++;
                }
                else length = -1;
            }
        }
        if(length == -1){
            regex_pointer = input_regex;
            length = 0;
            start = 0;
        }
        else if(length == 1 && !start){
            start = string_pointer;
        }
        string_pointer++;
    }
    printf("%d\n", length);
    while(length--){
        printf("%c", *start++);
    }

    return 0;
}
