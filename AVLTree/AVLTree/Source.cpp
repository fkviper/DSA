//#include "AVLTreeNode.h"
#include <iostream>
#include <cmath>
using namespace std;


class AVLTreeNode {
public:
  AVLTreeNode(void);
  AVLTreeNode(AVLTreeNode&);
  ~AVLTreeNode(void);
  void operator=(AVLTreeNode&);
  AVLTreeNode* getParent(void);
  AVLTreeNode* getLeft(void);
  AVLTreeNode* getRight(void);
  int getValue(void);
  void setParent(AVLTreeNode*);
  void setLeft(AVLTreeNode*);
  void setRight(AVLTreeNode*);
  void setValue(int);
  void insert(int);
  void printPreorder(void);
  void printInorder(void);
  void printPostorder(void);
  void rotateLeft(void);
  void rotateRight(void);
  void rotateLeftRight(void);
  void rotateRightLeft(void);
  void deleteNode(int);
  int getHeight();

private:
  int value;
  AVLTreeNode* parent;
  AVLTreeNode* left;
  AVLTreeNode* right;
  //helper functions
  void balance();
  int compareTo(int key);
  AVLTreeNode* getMax();
  AVLTreeNode* getMin();
  void deleteNodeHelper(int);
  bool contains(int key);
};


AVLTreeNode::AVLTreeNode() {
  value = 0;
  parent = NULL;
  left = NULL;
  right = NULL;
}

AVLTreeNode::AVLTreeNode(AVLTreeNode& other) {
  delete parent;
  delete left;
  delete right;
  value = other.getValue();
  parent = other.getParent();
  left = other.getLeft();
  right = other.getRight();
}

void AVLTreeNode::operator=(AVLTreeNode& other) {
  delete parent;
  delete left;
  delete right;
  value = other.getValue();
  parent = other.getParent();
  left = other.getLeft();
  right = other.getRight();
}

AVLTreeNode::~AVLTreeNode() {
  delete left;
  left = NULL;
  delete right;
  right = NULL;
  value = 0;
}

AVLTreeNode* AVLTreeNode::getParent() {
  return parent;
}

AVLTreeNode* AVLTreeNode::getLeft() {
  return left;
}

AVLTreeNode* AVLTreeNode::getRight() {
  return right;
}

int AVLTreeNode::getValue() {
  return value;
}

void AVLTreeNode::setParent(AVLTreeNode* par) {
  parent = par;
}

void AVLTreeNode::setLeft(AVLTreeNode* lft) {
  left = lft;
}

void AVLTreeNode::setRight(AVLTreeNode* rght) {
  right = rght;
}

void AVLTreeNode::setValue(int val) {
  value = val;
}

void AVLTreeNode::balance() {
  if (getLeft() && getLeft()->getRight() && !getRight() || getLeft() && getLeft()->getRight() && getRight() && getLeft()->getHeight() > getRight()->getHeight() + 1 && getLeft()->getRight()->getHeight() > getLeft()->getLeft()->getHeight() + 1) {
    rotateLeftRight();
  }
  else if (getRight() && getRight()->getLeft() && !getLeft() || getRight() && getRight()->getLeft() && getLeft() && getRight()->getHeight() > getLeft()->getHeight() + 1 && getRight()->getLeft()->getHeight() > getRight()->getRight()->getHeight() + 1) {
    rotateRightLeft();
  }
  else if (getLeft() && !getRight() && getLeft()->getHeight() > 1 || getLeft() && getRight() && getLeft()->getHeight() > getRight()->getHeight() + 1) {
    rotateRight();
  }
  else if (getRight() && !getLeft() && getRight()->getHeight() > 1 || getRight() && getLeft() && getRight()->getHeight() > getLeft()->getHeight() + 1) {
    rotateLeft();
  }
}

void AVLTreeNode::insert(int val) {
  if (!getValue()) {
    setValue(val);
  }
  else if ((val < getValue() && !getLeft()) || (val < getValue() && !getLeft()->getValue())) {
    left = new AVLTreeNode();
    left->setParent(this);
    left->setValue(val);
  }
  else if ((val > getValue() && !getRight()) || (val > getValue() && !getRight()->getValue())) {
    right = new AVLTreeNode();
    right->setParent(this);
    right->setValue(val);
  }
  else if (val < getValue()) {
    getLeft()->insert(val);
  }
  else {
    getRight()->insert(val);
  }
  balance();
}

void AVLTreeNode::printPreorder() {
  if (getValue()) {
    cout << getValue();
  }
  if (getLeft() && getLeft()->getValue()) {
    cout << ",";
    getLeft()->printPreorder();
  }
  if (getRight() && getRight()->getValue()) {
    cout << ",";
    getRight()->printPreorder();
  }
}

void AVLTreeNode::printInorder() {
  if (getLeft() && getLeft()->getValue()) {
    getLeft()->printInorder();
    cout << ",";
  }
  if (getValue()) {
    cout << getValue();
  }
  if (getRight() && getRight()->getValue()) {
    cout << ",";
    getRight()->printInorder();
  }
}

void AVLTreeNode::printPostorder() {
  if (getLeft() && getLeft()->getValue()) {
    getLeft()->printPostorder();
    cout << ",";
  }
  if (getRight() && getRight()->getValue()) {
    getRight()->printPostorder();
    cout << ",";
  }
  if (getValue()) {
    cout << getValue();
  }
}

int AVLTreeNode::getHeight() {
  if (getLeft() && getLeft()->getValue() && (!getRight() || !getRight()->getValue())) {
    return getLeft()->getHeight() + 1;
  }
  else if (getRight() && getRight()->getValue() && (!getLeft() || !getLeft()->getValue())) {
    return getRight()->getHeight() + 1;
  }
  else if (getRight() && getLeft() && getRight()->getValue() && getLeft()->getValue()) {
    return max(getRight()->getHeight(), getLeft()->getHeight()) + 1;
  }
  else if (getValue() && (!getLeft() || !getLeft()->getValue()) && (!getRight() || !getRight()->getValue())) {
    return 1;
  }
  return 0;
}

void AVLTreeNode::rotateLeftRight() {
  getLeft()->rotateLeft();
  rotateRight();
}

void AVLTreeNode::rotateRightLeft() {
  getRight()->rotateRight();
  rotateLeft();
}

//Implementation Note: There are a variety of ways to implement a binary tree.
//  With our implementation "this" points to 'P', however after the rotation
//  is completed "this" points to 'Q'.
/*
          Q                 P
         / \               / \
        /   \             /   \
       P     C    <==    A     Q
      / \                     / \
     /   \                   /   \
    A     B                 B     C

*/
void AVLTreeNode::rotateLeft(){
  AVLTreeNode* pQ = getRight();
  AVLTreeNode* pB = pQ->getLeft();
  AVLTreeNode* pParent = getParent();
  // do the rotation.
  setRight(pB);
  setParent(pQ);
  pQ->setLeft(this); // this is P here
  pQ->setParent(pParent); // pParent is null for Q

  // now take a copy of current(this). i.e P 
  AVLTreeNode* temp = new AVLTreeNode(*this);
  // now current(this) should point to Q
  setValue(pQ->getValue()); // Q
  setLeft(temp); // set left of Q as P
  setRight(pQ->getRight()); // maintain right of Q , i.e. C
  setParent(pQ->getParent()); 
  temp->setParent(this);
  //delete Q node. Since data is already moved to the current this pointer.
  pQ->setLeft(nullptr);
  pQ->setRight(nullptr);
  delete pQ;
  pQ = nullptr;
}

//Implementation Note: There are a variety of ways to implement a binary tree.
//  With our implementation "this" points to 'Q', however after the rotation
//  is completed "this" points to 'P'.
/*
          Q                 P
         / \               / \
        /   \             /   \
       P     C    ==>    A     Q
      / \                     / \
     /   \                   /   \
    A     B                 B     C

*/
void AVLTreeNode::rotateRight(){
  AVLTreeNode* pP = getLeft();
  AVLTreeNode* pB = pP->getRight();
  AVLTreeNode* pParent = getParent();

  //do the rotation.
  setLeft(pB);
  setParent(pP);
  pP->setRight(this); // this is Q here
  pP->setParent(pParent); // pParent is null for P

  // now take a copy of current(this). i.e Q 
  AVLTreeNode* temp = new AVLTreeNode(*this);

  // this should point to P
  setValue(pP->getValue());
  setLeft(pP->getLeft()); // set left of P as Q
  setRight(temp); // maintain right of P to Q
  setParent(pP->getParent()); 
  temp->setParent(this);

  //delete P node.Since data is already moved to this pointer.
  pP->setLeft(nullptr);
  pP->setRight(nullptr);
  delete pP;
  pP = nullptr;
}
/*
    returns
    0  if key and value is same.
    -1 if key is less than the value. i.e. key exist in the left subtree.
    1   if key is greater than the value i.e. key exist in the right subtree.
*/
int AVLTreeNode::compareTo(int key) {
  if (key == getValue())
    return 0;
  return key > getValue() ? 1 : -1;
}

bool AVLTreeNode::contains(int key) {
  int compare = compareTo(key);
  if (compare == 0)
    return true;
  else if (compare == -1 && getLeft())
    return getLeft()->contains(key);
  else if (compare == 1 && getRight())
    return getRight()->contains(key);
  return false;
}

void AVLTreeNode::deleteNode(int key) {
  if (contains(key))
    deleteNodeHelper(key);
}

void AVLTreeNode::deleteNodeHelper(int key) {
  int compare = compareTo(key);
  if (compare == -1)
    getLeft()->deleteNodeHelper(key);
  else if (compare == 1)
    getRight()->deleteNodeHelper(key);
  // node to be deleted is found
  else
  {
    if (getLeft() == nullptr && getRight() == nullptr)
    {
      AVLTreeNode* parent = this->getParent();
      if (parent->getLeft() == this)
        parent->setLeft(nullptr);
      else
        parent->setRight(nullptr);
      delete this;
      return;
    }
    else if (getLeft() == nullptr)
    {
      AVLTreeNode* right = getRight();
      setLeft(right->getLeft());
      setRight(right->getRight());
      setValue(right->getValue());
      //prepare to delete the right.
      right->setLeft(nullptr);
      right->setRight(nullptr);
      delete right;
      right = nullptr;
    }
    else if (getRight() == nullptr)
    {
      AVLTreeNode* left = getLeft();
      setLeft(left->getLeft());
      setRight(left->getRight());
      setValue(left->getValue());
      //prepare to delete the left.
      left->setLeft(nullptr);
      left->setRight(nullptr);
      delete left;
      left = nullptr;
    }
    /*
    Since both the left and right subtree are present, we need to find the successor to replace it.
    we can choose either the largest in the left subtree or smallest in the right subtree.
    We will choose whichever subtree is more heavy.
    */
    else
    {
      if (getLeft()->getHeight() > getRight()->getHeight())
      {
        AVLTreeNode* largest = getLeft()->getMax();
        setValue(largest->getValue());
        getLeft()->deleteNodeHelper(largest->getValue());
      }
      else
      {
        AVLTreeNode* smallest = getRight()->getMin();
        setValue(smallest->getValue());
        getRight()->deleteNodeHelper(smallest->getValue());
      }
    }
  }
  balance();
}

AVLTreeNode* AVLTreeNode::getMax()
{
  AVLTreeNode* retNode = nullptr;
  AVLTreeNode* curr = this;
  while (curr) {
    retNode = curr;
    curr = curr->getRight();
  }
  return retNode;
}

AVLTreeNode* AVLTreeNode::getMin()
{
  AVLTreeNode* retNode = nullptr;
  AVLTreeNode* curr = this;
  while (curr) {
    retNode = curr;
    curr = curr->left;
  }
  return retNode;
}

int main() {
  cout << "\n\nTest 1" << endl;

  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(14);
    avltree->insert(15);
    avltree->insert(18);
    avltree->insert(21);
    avltree->insert(22);
    avltree->insert(25);
    avltree->insert(30);
    avltree->insert(35);

    avltree->printPreorder();
    cout << "\n";
    avltree->printInorder();
    cout << "\n";
    avltree->printPostorder();
  }
  cout << "\n\nTest 2" << endl;

  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(22);
    avltree->insert(24);
    avltree->insert(27);
    avltree->insert(30);
    avltree->insert(34);

    avltree->printPreorder();
    cout << "\n";
    avltree->printInorder();
    cout << "\n";
    avltree->printPostorder();
  }
  cout << "\n\nTest 3" << endl;

  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(15);
    avltree->insert(20);
    avltree->insert(21);
    avltree->insert(23);
    avltree->insert(25);
    avltree->insert(26);
    avltree->insert(29);
    avltree->insert(35);
    avltree->insert(36);
    avltree->insert(39);

    avltree->printPreorder();
    cout << "\n";
    avltree->printInorder();
    cout << "\n";
    avltree->printPostorder();
  }
  cout << "\n\nTest 4" << endl;

  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(22);
    avltree->insert(36);
    avltree->insert(39);

    avltree->printPreorder();
    cout << "\n";
    avltree->printInorder();
    cout << "\n";
    avltree->printPostorder();
    
    delete avltree;
  }
  cout << "\n\nTest 5" << endl;

  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(13);
    avltree->insert(14);
    avltree->insert(18);
    avltree->insert(35);
    avltree->insert(37);
    avltree->insert(39);

    avltree->printPreorder();
    cout << "\n";
    avltree->printInorder();
    cout << "\n";
    avltree->printPostorder();
  }
  cout << "\n\nTest 6" << endl;

  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(19);
    avltree->insert(22);
    avltree->insert(25);
    avltree->insert(27);
    avltree->insert(28);
    avltree->insert(31);
    avltree->insert(32);
    avltree->insert(33);
    avltree->insert(35);
    avltree->insert(37);
    avltree->printPreorder();
    cout << "\n";
    avltree->printInorder();
    cout << "\n";
    avltree->printPostorder();
  }
  cout << "\n\nTest 7" << endl;

  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(22);
    avltree->insert(24);
    avltree->insert(26);
    avltree->insert(36);
    avltree->insert(37);

    avltree->printPreorder();
    cout << "\n";
    avltree->printInorder();
    cout << "\n";
    avltree->printPostorder();
  }
  cout << "\n\nTest 8" << endl;


  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(17);
    avltree->insert(22);
    avltree->insert(24);
    avltree->insert(33);
    avltree->printPreorder();
    cout << "\n";
    avltree->printInorder();
    cout << "\n";
    avltree->printPostorder();
  }
  cout << "\n\nTest 9" << endl;

  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(15);
    avltree->insert(28);
    avltree->insert(29);
    avltree->insert(39);
    avltree->printPreorder();
    cout << "\n";
    avltree->printInorder();
    cout << "\n";
    avltree->printPostorder();
  }
  cout << "\n\nTest 10" << endl;

  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(15);
    avltree->printPreorder();
    cout << "\n";
    avltree->printInorder();
    cout << "\n";
    avltree->printPostorder();
  }
  cout << "\n\nTest 11" << endl;

  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(12);
    avltree->insert(16);
    avltree->insert(23);
    avltree->insert(27);
    avltree->insert(28);
    avltree->insert(29);

    avltree->printPreorder();
    cout << "\n";
    avltree->printInorder();
    cout << "\n";
    avltree->printPostorder();
  }
  cout << "\n\nTest 12" << endl;

  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(27);

    avltree->printPreorder();
    cout << "\n";
    avltree->printInorder();
    cout << "\n";
    avltree->printPostorder();
  }
  cout << "\n\nTest 13" << endl;

  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(12);
    avltree->insert(20);
    avltree->insert(23);
    avltree->insert(24);
    avltree->insert(31);
    avltree->insert(34);
    avltree->printPreorder();
    cout << "\n";
    avltree->printInorder();
    cout << "\n";
    avltree->printPostorder();
  }
  cout << "\n\nTest 14" << endl;

  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(13);
    avltree->insert(20);
    avltree->insert(24);
    avltree->insert(29);
    avltree->insert(35);
    avltree->insert(36);
    avltree->insert(37);
    avltree->insert(38);
    avltree->insert(40);
    avltree->printPreorder();
    cout << "\n";
    avltree->printInorder();
    cout << "\n";
    avltree->printPostorder();
  }
  cout << "\n\nTest 15" << endl;
  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(20);
    avltree->insert(28);
    avltree->insert(30);
    avltree->insert(35);
    avltree->insert(39);
    avltree->printPreorder();
    cout << "\n";
    avltree->printInorder();
    cout << "\n";
    avltree->printPostorder();
  }

  cout << "----------------ROTATE RIGHT-----------------" << endl;

  cout << "\n\nTest 1" << endl;
  {
      AVLTreeNode* avltree = new AVLTreeNode();
        avltree->insert(35);
        avltree->insert(30);
        avltree->insert(27);
        avltree->insert(23);
        avltree->insert(19);
        avltree->insert(12);
      avltree->printPreorder();
      cout << "\n";
      avltree->printInorder();
      cout << "\n";
      avltree->printPostorder();
  }

  cout << "\n\nTest 2" << endl;
  {
      AVLTreeNode* avltree = new AVLTreeNode();
          avltree->insert(36);
          avltree->insert(32);
          avltree->insert(29);
          avltree->insert(27);
          avltree->insert(26);
          avltree->insert(22);
          avltree->insert(21);
          avltree->insert(19);
          avltree->insert(17);
          avltree->insert(14);
      avltree->printPreorder();
      cout << "\n";
      avltree->printInorder();
      cout << "\n";
      avltree->printPostorder();
  }
  cout << "\n\nTest 3" << endl;
  {
      AVLTreeNode* avltree = new AVLTreeNode();
          avltree->insert(40);
          avltree->insert(36);
          avltree->insert(33);

      avltree->printPreorder();
      cout << "\n";
      avltree->printInorder();
      cout << "\n";
      avltree->printPostorder();
  }
  cout << "\n\nTest 4" << endl;
  {
      AVLTreeNode* avltree = new AVLTreeNode();
          avltree->insert(40);
          avltree->insert(37);
          avltree->insert(36);
          avltree->insert(34);
          avltree->insert(32);
          avltree->insert(30);
          avltree->insert(25);
          avltree->insert(24);
          avltree->insert(18);
          avltree->insert(15);
      avltree->printPreorder();
      cout << "\n";
      avltree->printInorder();
      cout << "\n";
      avltree->printPostorder();
  }
  cout << "\n\nTest 5" << endl;
  {
      AVLTreeNode* avltree = new AVLTreeNode();
          avltree->insert(39);
          avltree->insert(38);
          avltree->insert(35);
          avltree->insert(34);
          avltree->insert(30);
          avltree->insert(28);
          avltree->insert(26);
          avltree->insert(23);
          avltree->insert(21);
      avltree->printPreorder();
      cout << "\n";
      avltree->printInorder();
      cout << "\n";
      avltree->printPostorder();
  }
  cout << "\n\nTest 6" << endl;
  {
      AVLTreeNode* avltree = new AVLTreeNode();
          avltree->insert(36);
          avltree->insert(30);
          avltree->insert(27);
          avltree->insert(25);
          avltree->insert(23);
          avltree->insert(21);
          avltree->insert(17);
          avltree->insert(15);
      avltree->printPreorder();
      cout << "\n";
      avltree->printInorder();
      cout << "\n";
      avltree->printPostorder();
  }
  cout << "\n\nTest 7" << endl;
  {
      AVLTreeNode* avltree = new AVLTreeNode();
          avltree->insert(36);
          avltree->insert(35);
          avltree->insert(29);
          avltree->insert(25);
          avltree->insert(21);
          avltree->insert(20);
          avltree->insert(19);
      avltree->printPreorder();
      cout << "\n";
      avltree->printInorder();
      cout << "\n";
      avltree->printPostorder();
  }
  cout << "\n\nTest 8" << endl;
  {
      AVLTreeNode* avltree = new AVLTreeNode();
          avltree->insert(37);
          avltree->insert(36);
          avltree->insert(31);
          avltree->insert(29);
          avltree->insert(26);
          avltree->insert(20);
          avltree->insert(19);
          avltree->insert(17);
          avltree->insert(14);
      avltree->printPreorder();
      cout << "\n";
      avltree->printInorder();
      cout << "\n";
      avltree->printPostorder();
  }
  cout << "\n\nTest 9" << endl;
  {
      AVLTreeNode* avltree = new AVLTreeNode();
          avltree->insert(40);
          avltree->insert(36);
          avltree->insert(34);
          avltree->insert(33);
          avltree->insert(23);
          avltree->insert(16);
          avltree->insert(15);
          avltree->insert(13);
      avltree->printPreorder();
      cout << "\n";
      avltree->printInorder();
      cout << "\n";
      avltree->printPostorder();
  }
  cout << "\n\nTest 10" << endl;
  {
      AVLTreeNode* avltree = new AVLTreeNode();
          avltree->insert(39);
          avltree->insert(33);
          avltree->insert(32);
          avltree->insert(28);
          avltree->insert(27);
          avltree->insert(26);
          avltree->insert(20);
          avltree->insert(19);
          avltree->insert(12);
      avltree->printPreorder();
      cout << "\n";
      avltree->printInorder();
      cout << "\n";
      avltree->printPostorder();
  }
  cout << "\n\nTest 11" << endl;
  {
      AVLTreeNode* avltree = new AVLTreeNode();
          avltree->insert(34);
          avltree->insert(32);
          avltree->insert(31);
          avltree->insert(22);
          avltree->insert(16);

      avltree->printPreorder();
      cout << "\n";
      avltree->printInorder();
      cout << "\n";
      avltree->printPostorder();
  }
  cout << "\n\nTest 12" << endl;
  {
      AVLTreeNode* avltree = new AVLTreeNode();
          avltree->insert(37);
          avltree->insert(31);
          avltree->insert(29);
          avltree->insert(23);
          avltree->insert(21);
          avltree->insert(18);
          avltree->insert(16);
      avltree->printPreorder();
      cout << "\n";
      avltree->printInorder();
      cout << "\n";
      avltree->printPostorder();
  }
  cout << "\n\nTest 13" << endl;
  {
      AVLTreeNode* avltree = new AVLTreeNode();
      avltree->insert(33);
      avltree->printPreorder();
      cout << "\n";
      avltree->printInorder();
      cout << "\n";
      avltree->printPostorder();
  }
  cout << "\n\nTest 14" << endl;
  {
      AVLTreeNode* avltree = new AVLTreeNode();
          avltree->insert(39);
          avltree->insert(32);
          avltree->insert(30);
          avltree->insert(28);
          avltree->insert(27);
          avltree->insert(21);
          avltree->insert(19);
          avltree->insert(18);
          avltree->insert(15);
      avltree->printPreorder();
      cout << "\n";
      avltree->printInorder();
      cout << "\n";
      avltree->printPostorder();
  }
  cout << "\n\nTest 15" << endl;
  {
      AVLTreeNode* avltree = new AVLTreeNode();
          avltree->insert(36);
          avltree->insert(35);
          avltree->insert(18);
          avltree->insert(14);
          avltree->insert(12);
      avltree->printPreorder();
      cout << "\n";
      avltree->printInorder();
      cout << "\n";
      avltree->printPostorder();
  }

  cout << "----------------DELETE CASES-----------------" << endl;
  cout << "\nTest 1" << endl;
  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(31);
    avltree->insert(34);
    avltree->insert(33);
    avltree->deleteNode(17);
    avltree->deleteNode(13);
    avltree->deleteNode(19);
    avltree->deleteNode(16);
    avltree->deleteNode(26);
    avltree->deleteNode(31);
    avltree->deleteNode(27);

    avltree->printInorder();

    delete avltree;
    avltree = nullptr;
  }

  cout << "\nTest 2" << endl;
  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(39);
    avltree->insert(13);
    avltree->insert(27);
    avltree->deleteNode(31);
    avltree->deleteNode(34);
    avltree->deleteNode(25);
    avltree->deleteNode(28);
    avltree->deleteNode(36);
    avltree->deleteNode(15);
    avltree->deleteNode(21);

    avltree->printInorder();

    delete avltree;
    avltree = nullptr;

  }
  cout << "\nTest 3" << endl;
  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(23);
    avltree->insert(14);
    avltree->deleteNode(33);
    avltree->deleteNode(26);
    avltree->deleteNode(29);
    avltree->deleteNode(25);
    avltree->deleteNode(14);
    avltree->deleteNode(34);
    avltree->deleteNode(32);

    avltree->printInorder();

    delete avltree;
    avltree = nullptr;

  }
  cout << "\nTest 4" << endl;
  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(32);
    avltree->insert(30);
    avltree->insert(33);
    avltree->insert(21);
    avltree->deleteNode(37);
    avltree->deleteNode(16);
    avltree->deleteNode(20);
    avltree->deleteNode(34);
    avltree->deleteNode(32);
    avltree->deleteNode(31);
    avltree->deleteNode(23);

    avltree->printInorder();

    delete avltree;
    avltree = nullptr;

  }

  cout << "\nTest 5" << endl;
  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(34);
    avltree->insert(32);
    avltree->deleteNode(33);
    avltree->deleteNode(18);
    avltree->deleteNode(21);
    avltree->deleteNode(20);
    avltree->deleteNode(12);
    avltree->deleteNode(31);
    avltree->deleteNode(15);
    avltree->deleteNode(28);
    avltree->deleteNode(27);

    avltree->printInorder();

    delete avltree;
    avltree = nullptr;

  }

  cout << "\nTest 6" << endl;
  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(40);
    avltree->deleteNode(14);
    avltree->deleteNode(29);
    avltree->deleteNode(25);
    avltree->deleteNode(18);
    avltree->deleteNode(15);
    avltree->deleteNode(23);
    avltree->deleteNode(27);
    avltree->deleteNode(13);

    avltree->printInorder();

    delete avltree;
    avltree = nullptr;

  }

  cout << "\nTest 7" << endl;
  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(34);
    avltree->insert(16);
    avltree->insert(24);
    avltree->insert(13);
    avltree->deleteNode(22);
    avltree->deleteNode(32);
    avltree->deleteNode(17);
    avltree->deleteNode(15);
    avltree->deleteNode(31);
    avltree->deleteNode(38);

    avltree->printInorder();

    delete avltree;
    avltree = nullptr;

  }

  cout << "\nTest 8" << endl;
  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(15);
    avltree->insert(26);
    avltree->insert(12);

    avltree->deleteNode(33);
    avltree->deleteNode(16);
    avltree->deleteNode(30);
    avltree->deleteNode(29);
    avltree->deleteNode(38);
    avltree->deleteNode(24);
    avltree->deleteNode(15);
    avltree->deleteNode(23);
    avltree->deleteNode(37);
   
    avltree->printInorder();

    delete avltree;
    avltree = nullptr;

  }

  cout << "\nTest 9" << endl;
  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(31);
    avltree->insert(21);
    avltree->insert(25);

    avltree->deleteNode(12);
    avltree->deleteNode(28);
    avltree->deleteNode(26);
    avltree->deleteNode(32);
    avltree->deleteNode(29);
    avltree->deleteNode(31);
    avltree->deleteNode(25);
    avltree->deleteNode(27);
    avltree->deleteNode(16);

    avltree->printInorder();

    delete avltree;
    avltree = nullptr;

  }

  cout << "\nTest 10" << endl;
  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(32);
    avltree->insert(26);
    avltree->insert(34);

    avltree->deleteNode(39);
    avltree->deleteNode(28);
    avltree->deleteNode(12);
    avltree->deleteNode(24);
    avltree->deleteNode(16);
    avltree->deleteNode(22);      

    avltree->printInorder();

    delete avltree;
    avltree = nullptr;

  }

  cout << "\nTest 11" << endl;
  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(16);
    avltree->insert(37);
    avltree->insert(20);

    avltree->deleteNode(23);
    avltree->deleteNode(22);
    avltree->deleteNode(39);
    avltree->deleteNode(36);
    avltree->deleteNode(34);
    avltree->deleteNode(19);
    avltree->deleteNode(31);
    avltree->deleteNode(21);
      
    avltree->printInorder();

    delete avltree;
    avltree = nullptr;

  }

  cout << "\nTest 12" << endl;
  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(29);
    avltree->insert(24);
    avltree->insert(26);
    avltree->insert(12);

    avltree->deleteNode(25);
    avltree->deleteNode(19);
    avltree->deleteNode(33);
    avltree->deleteNode(29);
    avltree->deleteNode(37);
    avltree->deleteNode(40);
    avltree->deleteNode(23);

    avltree->printInorder();

    delete avltree;
    avltree = nullptr;

  }

  cout << "\nTest 13" << endl;
  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(25);
    avltree->insert(23);
    avltree->insert(18);

    avltree->deleteNode(16);
    avltree->deleteNode(33);
    avltree->deleteNode(30);
    avltree->deleteNode(21);
    avltree->deleteNode(35);
    avltree->deleteNode(38);
    avltree->deleteNode(19);
    avltree->deleteNode(25);

    avltree->printInorder();

    delete avltree;
    avltree = nullptr;

  }

  cout << "\nTest 14" << endl;
  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(33);
    avltree->insert(40);

    avltree->deleteNode(27);
    avltree->deleteNode(38);
    avltree->deleteNode(20);
    avltree->deleteNode(18);
    avltree->deleteNode(34);
    avltree->deleteNode(13);
    avltree->deleteNode(14);
    avltree->deleteNode(31);
    avltree->deleteNode(21);
    avltree->printInorder();

    delete avltree;
    avltree = nullptr;

  }

  cout << "\nTest 15" << endl;
  {
    AVLTreeNode* avltree = new AVLTreeNode();
    avltree->insert(18);
    avltree->insert(12);

    avltree->deleteNode(35);
    avltree->deleteNode(32);
    avltree->deleteNode(28);
    avltree->deleteNode(21);
    avltree->deleteNode(24);
    avltree->deleteNode(30);
    avltree->deleteNode(23);
    avltree->deleteNode(14);

    avltree->printInorder();

    delete avltree;
    avltree = nullptr;

  }
  return 0;
}
