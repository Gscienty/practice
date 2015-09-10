/*
    数据结构 : 线性表
    Author : Gscienty
*/


#define _CHAIN_TABLE_
#ifndef _CHAIN_TABLE_
#include <malloc.h>
#endif

#define _DEBUG_
#ifdef _DEBUG_
#include <iostream>
using namespace std;
#endif // _DEBUG_

template<typename T>
class LinearList{


private:
    #ifdef _CHAIN_TABLE_
    struct node_tp{
        T data;
        node_tp* next;
        node_tp* prev;
    };

    struct header_tp{
        node_tp* first;
    }*_header;
    #else
    T* _array;
    int _size;
    #endif

    int _length;

    #ifdef _CHAIN_TABLE_
    LinearList(){
    #else
    LinearList(int size){
    #endif

        #ifndef _CHAIN_TABLE_
        this->_size = size;
        this->_array = (T*)malloc(sizeof(T) * this->_size);
        #else
        this->_header = (header_tp*)malloc(sizeof(header_tp));
        this->_header->first = NULL;
        #endif

        this->_length = 0;
    }

    ~LinearList(){
        #ifndef _CHAIN_TABLE_
        free(this->_array);
        #else
        Clear(this);
        #endif
    }

public:
    void static Init(LinearList* &L){
        #ifndef _CHAIN_TABLE_
        L = new LinearList(100);
        #else
        L = new LinearList();
        #endif
    }

    void static Destroy(LinearList* &L){
        delete(L);
    }

    void static Clear(LinearList* &L){
        L->_length = 0;
        #ifdef _CHAIN_TABLE_
        node_tp* current_node = L->_header->first;
        while(current_node != L->_header->first){
            node_tp* delete_node = current_node;
            current_node = current_node->next;
            free(delete_node);
        }
        L->_header->first = NULL;
        #endif
    }

    bool static Empty(const LinearList* L){
        return L->_length == 0;
    }

    int static Length(const LinearList* L){
        return L->_length;
    }

    void static GetElem(const LinearList* L, const int i, T &e){
        #ifndef _CHAIN_TABLE_
        e = L->_array[i];
        #else
        node_tp* current_node = L->_header->first;
        for(int p = 0; p < i; p++){
            if(current_node != NULL){
                current_node = current_node->next;
            }
        }
        if(current_node != NULL){
            e = current_node->data;
        }
        #endif
    }

    int static LocateElem(const LinearList* L, const T e, const bool(* compare)(T, T)){
        #ifndef _CHAIN_TABLE_
        for(int i = 0; i < L->_length; i++){
            if(compare(e, L->_array[i])){
                return i;
            }
        }
        #else
        node_tp* current_node = L->_header->first;
        for(int i = 0; i < L->_length; i++){
            if(compare(e, current_node->data)){
                return i;
            }
            current_node = current_node->next;
        }
        #endif
    }

    void static PriorElem(const LinearList* L, const T cur_e, T& pre_e){
        #ifndef _CHAIN_TABLE_
        for(int i = 1; i < L->_length; i++){
            if(cur_e == L->_array[i]){
                pre_e = L->_array[i-1];
                return;
            }
        }
        #else
        node_tp* current_node = L->_header->first;
        for(int i = 1; i < L->_length; i++){
            if(cur_e == current_node->data){
                pre_e = current_node->prev->data;
                return;
            }
        }
        #endif
    }

    void static NextElem(const LinearList* L, const T cur_e, T& next_e){
        #ifndef _CHAIN_TABLE_
        for(int i = 0; i < L->_length - 1; i++){
            if(cur_e == L->_array[i]){
                next_e = L->_array[i+1];
                return;
            }
        }
        #else
        node_tp* current_node = L->_header->first;
        for(int i = 1; i < L->_length; i++){
            if(cur_e == current_node->data){
                next_e = current_node->next->data;
                return;
            }
        }
        #endif
    }

    void static Insert(LinearList* &L, const int i, const T e){
        if(1 <= i && i <= L->_length + 1){
            #ifndef _CHAIN_TABLE_
            if(L->_size < L->_length + 1){
                L->_size <<= 1;
                realloc(L->_array, L->_size);   //error
            }
            for(int p = L->_length; p >= i; p--){
                L->_array[p] = L->_array[p - 1];
            }
            L->_array[i - 1] = e;
            #else
            if(i == 1 && !L->_header->first){
                L->_header->first = (node_tp*)malloc(sizeof(node_tp));
                L->_header->first->data = e;
                L->_header->first->prev = L->_header->first;
                L->_header->first->next = L->_header->first;
            }
            else{
                node_tp* current_node = L->_header->first;
                node_tp* new_node = (node_tp*)malloc(sizeof(node_tp));
                new_node->data = e;
                for(int p = 0; p < i - 1; p++){
                    current_node = current_node->next;
                }
                new_node->next = current_node;
                new_node->prev = current_node->prev;
                current_node->prev->next = new_node;
                current_node->prev = new_node;

                if(i == 1){
                    L->_header->first = new_node;
                }
            }
            #endif
            L->_length++;
        }
    }

    void static Delete(LinearList* &L, const int i, T& e){
        #ifndef _CHAIN_TABLE_
        GetElem(L, i, e);
        for(int p = i; p < L->_length - 1; p++){
            L->_array[p] = L->_array[p+1];
        }
        #else
        node_tp* current_node = L->_header->first;
        for(int p = 0; p < i - 1; p++){
            current_node = current_node->next;
        }
        e = current_node->data;
        if(i == 0){
            L->_header->first = L->_header->first->next;
        }
        if(L->_length <= 1){
            L->_header->first = NULL;
        }
        else{
            current_node->prev->next = current_node->next;
            current_node->next->prev = current_node->prev;
        }
        free(current_node);
        #endif
        L->_length--;
    }

    void static Traverse(const LinearList* L, const bool(*visit)(const T)){
        #ifndef _CHAIN_TABLE_
        for(int i = 0; i < L->_length; i++){
            if(!visit(L->_array[i])) return;
        }
        #else
        node_tp* current_node = L->_header->first;
        for(int i = 0; i < L->_length; i++){
            if(!visit(current_node->data)) return;
            current_node = current_node->next;
        }
        #endif
    }
};
