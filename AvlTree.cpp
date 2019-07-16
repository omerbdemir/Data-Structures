#include <iostream>
#include <functional>
using namespace std;
template <typename Comparable>
class AvlTree{
public:
  AvlTree(){
    root = nullptr;
  }
  void insert(const Comparable &x){
    insert(x, root);
  }
  void remove(const Comparable &x){
    remove(x, root);
  }
  void print(){
      int c = 0;
      print(root, c);
  }
private:
  struct AvlNode{
    Comparable element;
    AvlNode *left;
    AvlNode *right;
    int height;
    AvlNode(const Comparable &elm, AvlNode *lt, AvlNode *rt, int h = 0)
    : element{elm}, left{lt}, right{rt}, height{h}{}
    AvlNode(const Comparable && elm, AvlNode *lt, AvlNode *rt, int h = 0)
    : element{move(elm)}, left{lt}, right{rt}, height{h}{}
    friend class iterator;
  };
  AvlNode *root;
  AvlNode * findMin(AvlNode * & t)const{
    if(t==nullptr)
      return nullptr;
    if(t->left == nullptr)
      return t;
    else
      return findMin(t->left);
  }
  void print(AvlNode *&p, int c){
    if(p == nullptr)return;
    for(int i = 0; i < c; i++){
      cout << "   ";
    }
    cout << p->element << endl;
    if(p->left != nullptr){
      c++;
      print(p->left, c);
    }
      print(p->right,c);
  }
  int height(AvlNode *t)const{

      return t == nullptr ? -1 : t->height;
  }
  void insert(const Comparable &x, AvlNode * &t){
    if(t == nullptr){
      t = new AvlNode(x, nullptr, nullptr);
    }
    else if(x < t->element){
      insert(x, t->left);
    }
    else if(t->element < x){
      insert(x, t->right);
    }
      balance(t);
  }
  static const int ALLOWED_IMBALANCE = 1;
  void balance(AvlNode * &t){
    if(t == nullptr) return;
    if(height(t->left) - height(t->right) > ALLOWED_IMBALANCE){
      if(height(t->left->left) >= height(t->left->right)){
        rotateLeftChild(t);
      }
      else{
        doubleLeftChild(t);
      }
    }
    else if(height(t->right) - height(t->left) > ALLOWED_IMBALANCE){
      if(height(t->right->right) >= height(t->right->left)){
        rotateRightChild(t);
      }
      else
      doubleRightChild(t);
    }
    t->height = max(height(t->left), height(t->right)) + 1;
  }
  /*void makeThreaded(AvlNode * & p){
    if(p == nullptr) return;
    if(p->right == nullptr){
      return p;
    }
    else if(p->left!= nullptr){

      makeThreaded(p->left)->right = p;
    }

  }*/
  void rotateLeftChild(AvlNode * &k2){

    AvlNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
  }
  void rotateRightChild(AvlNode * & k2){

    AvlNode *k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->right), k2->height) + 1;
    k2 = k1;
  }
  void doubleLeftChild(AvlNode * & k3){

    rotateRightChild(k3->left);
    rotateLeftChild(k3);
  }
  void doubleRightChild(AvlNode *& k3){
    rotateLeftChild(k3->right);
    rotateRightChild(k3);
  }
  void remove(const Comparable &x, AvlNode *& t){
    if(t == nullptr){
      return ;
      }
    if(x < t->element){
      remove(x , t->left);
    }
    else if(t->element < x){
      remove(x, t->right);
    }
    else if(t->left != nullptr && t->right != nullptr){

      t->element = findMin(t->right)->element;
      remove(t->element, t->right);
    }
    else{
      AvlNode *oldNode = t;
      t = (t->left != nullptr) ? t->left:t->right;
      delete oldNode;
    }
    balance(t);
  }
  int height(AvlNode *t){
    return t == nullptr ? -1 : t->height;
  }
};
int main(){
  AvlTree<int> a;
  a.insert(3);
  a.insert(2);
  a.insert(1);
  a.insert(4);
  a.insert(5);
  a.insert(6);
  a.insert(7);
  a.insert(16);
  a.insert(15);
  a.insert(14);
  a.insert(13);
  a.insert(12);
  a.insert(11);
  a.insert(10);
  a.insert(8);
  a.insert(9);

  a.print();
  return 0;
}
