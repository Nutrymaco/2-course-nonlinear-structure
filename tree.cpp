#include <iostream>
using namespace std;

struct Unit{
    Unit *rightBrother = NULL;
    Unit *leftSon = NULL;
    int value = NULL;
};

class Tree{
public:
    Unit *topRoot;
    Tree(int number){
        topRoot = new Unit;
        topRoot -> rightBrother = NULL;
        topRoot -> leftSon = NULL;
        topRoot -> value = number;
    };
    ~Tree(){};
    void addValue(int number){
        Unit *root;
        root = this -> topRoot;
        while (true) {
            if (root -> value != NULL){
                if (number < root -> value){
                    if (root -> leftSon == NULL) {
                        root -> leftSon = new Unit;
                        root -> leftSon -> value = number;
                        break;
                    }
                    else{
                        root = root -> leftSon;
                    }
                }
                else if (number > root -> value){

                    if (root -> leftSon != NULL and root -> leftSon -> rightBrother == NULL){
                        root -> leftSon -> rightBrother = new Unit;
                        root -> leftSon -> rightBrother -> value = number;
                        break;
                    }
                    else if (root -> leftSon == NULL){
                        root -> leftSon = new Unit;

                        root -> leftSon -> rightBrother = new Unit;
                        root -> leftSon -> rightBrother -> value = number;
                        break;
                    }
                    else{
                        root = root -> leftSon -> rightBrother;
                    }
                }
                else{
                    break;
                }
            }
            else{
                root -> value = number;
            }
        }
    }

    void Union(Unit *root) {
        if (root == NULL) return;
        if (root -> leftSon != NULL) {
            Union(root->leftSon);
            Union(root->leftSon->rightBrother);
        }

        if (root -> value != NULL) {
            addValue(root->value);
        }
    }


};

int showTree(Unit *root, int left, int right){
    cout << root -> value << endl;
    if (root -> leftSon != NULL){
        showTree(root -> leftSon, left + 2, 0);
        if (root -> leftSon -> rightBrother != NULL){
            showTree(root -> leftSon -> rightBrother, 0, right);
        }
        cout << endl;
    }
}

void reverseOrder(Unit *root) {
    if (root == NULL) return;
    if (root -> leftSon != NULL) {
        reverseOrder(root->leftSon->rightBrother);
        reverseOrder(root->leftSon);
    }

    if (root -> value == NULL) {
        cout << "no value";
    }
    else{
      cout << root -> value;
    }
}

void print_Tree(Unit *root,int level)
{
    if(root!=NULL)
    {
      if (root->leftSon!= NULL)print_Tree(root->leftSon->rightBrother,level + 1);
        for(int i = 0;i< level;i++) cout<<"   ";
        if (root -> value != NULL) cout << root -> value; else cout << "no"; cout << endl;
        if (root->leftSon!= NULL)print_Tree(root->leftSon,level + 1);

    }
}

void print_straight_tree(Unit *root,int level) {
  if(root!=NULL)
  {
      if (root -> value != NULL) cout << root -> value; else cout << "no"; cout << " ";
      if (root->leftSon!= NULL)print_straight_tree(root->leftSon,level + 1);
      if (root->leftSon!= NULL)print_straight_tree(root->leftSon->rightBrother,level + 1);
  }
}

void print_back_tree(Unit *root,int level) {
  if(root!=NULL)
  {
      if (root->leftSon!= NULL)print_back_tree(root->leftSon,level + 1);
      if (root->leftSon!= NULL)print_back_tree(root->leftSon->rightBrother,level + 1);
      if (root -> value != NULL) cout << root -> value; else cout << "no"; cout << " ";
  }
}

void print_sym_tree(Unit *root,int level) {
  if(root!=NULL)
  {
      if (root->leftSon!= NULL)print_back_tree(root->leftSon,level + 1);
      if (root -> value != NULL) cout << root -> value; else cout << "no"; cout << " ";
      if (root->leftSon!= NULL)print_back_tree(root->leftSon->rightBrother,level + 1);
  }
}
int main() {
    Tree tree1(5);
    Tree tree2(4);

      tree1.addValue(7);
      tree1.addValue(3);
      tree1.addValue(9);
      tree1.addValue(4);
      tree1.addValue(1);
      tree1.addValue(8);
      tree1.addValue(11);
      tree1.addValue(0);
      tree1.addValue(4);
      tree1.addValue(10);

      tree2.addValue(2);
      tree2.addValue(10);
      tree2.addValue(12);
      tree2.addValue(5);
      tree2.addValue(3);
      tree2.addValue(7);


      print_Tree(tree1.topRoot, 0);
      cout << endl << "---------------" << endl;
      print_straight_tree(tree1.topRoot, 0);
      cout << endl;
      print_back_tree(tree1.topRoot, 0);
      cout << endl;
      print_sym_tree(tree1.topRoot, 0);
      //tree1.Union(tree2.topRoot);
      //print_Tree(tree1.topRoot, 0);


  return 0;
}
