#include <stdio.h>

class binary_tree{
public:
  int value;
  binary_tree* left;
  binary_tree* right;
  int balance_value;
  binary_tree(int value){
    this->left = this->right = NULL;
    this->balance_value = 0;
    this->value = value;
  }
};

int main(){
  return 0;
}
