#include <iostream>
#include <malloc.h>
template<typename T>
class LinearList{
private:
    T* _array;
    int _length;
    int _size;

    LinearList(int size){
        this->_size = size;
        this->_array = (T*)malloc(sizeof(T) * this->_size);
        this->_length = 0;
    }

    ~LinearList(){
        free(this->_array);
    }

public:
    void static Init(LinearList* &L, int size){
        L = new LinearList(size);
    }

    void static Destroy(LinearList* &L){
        delete(L);
    }

    void static Clear(LinearList* &L){
        L->_length = 0;
    }

    bool static Empty(const LinearList* L){
        return L->_length == 0;
    }

    int static Length(const LinearList* L){
        return L->_length;
    }

    void static GetElem(const LinearList* L, const int i, T &e){
        e = L->_array[i];
    }

    int static LocateElem(const LinearList* L, const T e, const bool(* compare)(T, T)){
        for(int i = 0; i < L->_length; i++){
            if(compare(e, L->_array[i])){
                return i;
            }
        }
    }

    void static PriorElem(const LinearList* L, const T cur_e, T& pre_e){
        for(int i = 1; i < L->_length; i++){
            if(cur_e == L->_array[i]){
                pre_e = L->_array[i-1];
                return;
            }
        }
    }

    void static NextElem(const LinearList* L, const T cur_e, T& next_e){
        for(int i = 0; i < L->_length - 1; i++){
            if(cur_e == L->_array[i]){
                next_e = L->_array[i+1];
                return;
            }
        }
    }

    void static Insert(LinearList* &L, const int i, const T e){
        if(1 <= i && i <= L->_length + 1){
            if(L->_size < L->_length + 1){
                L->_size <<= 1;
                realloc(L->_array, L->_size);   //error
            }
            for(int p = L->_length; p >= i; p--){
                L->_array[p] = L->_array[p - 1];
            }
            L->_length++;
            L->_array[i - 1] = e;
        }
    }

    void static Delete(LinearList* &L, const int i, T& e){
        GetElem(L, i, e);
        for(int p = i; p < L->_length - 1; p++){
            L->_array[p] = L->_array[p+1];
        }
        L->_length--;
    }

    void static Traverse(const LinearList* L, const bool(*visit)(const T)){
        for(int i = 0; i < L->_length; i++){
            if(!visit(L->_array[i])) return;
        }
    }
};
