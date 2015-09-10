#include "linear_list.cpp"

template<typename T>
class Stack{
private:
    LinearList<T>* _linearList;
public:
    void static Init(Stack* &S){
        S = new Stack();
        LinearList<T>::Init(S->_linearList);
    }

    void static Destory(Stack* &S){
        delete(S->_linearList);
    }

    bool static Empty(Stack* S){
        return S->_linearList->Empty();
    }

    int static Length(Stack* S){
        return S->_linearList->Length();
    }

    void static GetTop(const Stack* S, T& e){
        #ifdef _CHAIN_TABLE_
        T temp;
        LinearList<T>::GetElem(S->_linearList, 0, temp);
        LinearList<T>::PriorElem(S->_linearList, temp, e);
        #else
        LinearList<T>::GetElem(S->_linearList, LinearList<T>::Length(S->_linearList), e);
        #endif // _CHAIN_TABLE_
    }

    void static Push(Stack* &S, const T e){
        LinearList<T>::Insert(S->_linearList, 1, e);
    }

    void static Pop(Stack * &S){
        T e;
        LinearList<T>::Delete(S->_linearList, 0, e);
    }

    void static Traverse(const Stack* S, const bool(*visit)(const T)){
        LinearList<T>::Traverse(S->_linearList, visit);
    }
};
