#include <stdio.h>
#include <malloc.h>

char input_string[256];
char input_regex[256];

int main(){
    scanf("%s", input_string);
    scanf("%s", input_regex);

    char* string_pointer = input_string;
    char* regex_pointer = input_regex;

    int length = 0;

    unsigned char match = 0;

    char* start_pointer = 0;

    while(*regex_pointer){
        unsigned char origin_match = match;
        if(!match && regex_pointer == input_regex) start_pointer = string_pointer;
        switch (*regex_pointer){
        case '^':
            match = string_pointer == input_string;
            break;
        case '$':
            match = !*string_pointer;
            break;
        case '*':
            if(match){
                regex_pointer -= 2;
            }
            string_pointer--;
            match = 1;
            break;
        case '+':
            if(match){
                regex_pointer -= 2;
            }
            else regex_pointer = input_regex - 1;
            string_pointer--;
            match = 1;
            break;
        case '?':
            string_pointer--;
            match = 1;
            break;
        default:
            match = *string_pointer == *regex_pointer;
            if(!origin_match && !match) regex_pointer = input_regex - 1;
        }
        regex_pointer++;
        if(*string_pointer) string_pointer++;
        else break;
    }
    if(*string_pointer) *(string_pointer - 1) = 0;

    printf("%s\n", start_pointer);
    return 0;
}
