//#include "OurCSCE310Tree.h"
#include <iostream>
#include <cmath>
using namespace std;


class OurCSCE310Tree{
 public:
  OurCSCE310Tree(void);
  OurCSCE310Tree(OurCSCE310Tree&);
  ~OurCSCE310Tree(void);
  void operator=(OurCSCE310Tree&);
  OurCSCE310Tree* getParent(void);
  OurCSCE310Tree* getLeft(void);
  OurCSCE310Tree* getRight(void);
  int getValue(void);
  void setParent(OurCSCE310Tree*);
  void setLeft(OurCSCE310Tree*);
  void setRight(OurCSCE310Tree*);
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
  OurCSCE310Tree* parent;
  OurCSCE310Tree* left;
  OurCSCE310Tree* right;
  //helper functions
  void balance();
  int compareTo(int key);
  OurCSCE310Tree* getMax();
  OurCSCE310Tree* getMin();
  void deleteNodeHelper(int);
  bool contains(int key);
};
 

OurCSCE310Tree::OurCSCE310Tree() {
    value = 0;
    parent = NULL;
    left = NULL;
    right = NULL;
}

OurCSCE310Tree::OurCSCE310Tree(OurCSCE310Tree& other) {
    delete parent;
    delete left;
    delete right;
    value = other.getValue();
    parent = other.getParent();
    left = other.getLeft();
    right = other.getRight();
}

void OurCSCE310Tree::operator=(OurCSCE310Tree& other) {
    delete parent;
    delete left;
    delete right;
    value = other.getValue();
    parent = other.getParent();
    left = other.getLeft();
    right = other.getRight();
}

OurCSCE310Tree::~OurCSCE310Tree() {
    delete left;
    left = NULL;
    delete right;
    right = NULL;
    value = 0;
}

OurCSCE310Tree* OurCSCE310Tree::getParent() {
    return parent;
}

OurCSCE310Tree* OurCSCE310Tree::getLeft() {
    return left;
}

OurCSCE310Tree* OurCSCE310Tree::getRight() {
    return right;
}

int OurCSCE310Tree::getValue() {
    return value;
}

void OurCSCE310Tree::setParent(OurCSCE310Tree* par) {
    parent = par;
}

void OurCSCE310Tree::setLeft(OurCSCE310Tree* lft) {
    left = lft;
}

void OurCSCE310Tree::setRight(OurCSCE310Tree* rght) {
    right = rght;
}

void OurCSCE310Tree::setValue(int val) {
    value = val;
}

void OurCSCE310Tree::balance() {
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

void OurCSCE310Tree::insert(int val) {
    if (!getValue()) {
        setValue(val);
    }
    else if ((val < getValue() && !getLeft()) || (val < getValue() && !getLeft()->getValue())) {
        left = new OurCSCE310Tree();
        left->setParent(this);
        left->setValue(val);
    }
    else if ((val > getValue() && !getRight()) || (val > getValue() && !getRight()->getValue())) {
        right = new OurCSCE310Tree();
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

void OurCSCE310Tree::printPreorder() {
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

void OurCSCE310Tree::printInorder() {
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

void OurCSCE310Tree::printPostorder() {
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

int OurCSCE310Tree::getHeight() {
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

void OurCSCE310Tree::rotateLeftRight() {
    getLeft()->rotateLeft();
    rotateRight();
}

void OurCSCE310Tree::rotateRightLeft() {
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
void OurCSCE310Tree::rotateLeft() {
    OurCSCE310Tree* pQ = getRight();
    OurCSCE310Tree* pB = pQ->getLeft();
    OurCSCE310Tree* pParent = getParent();

    bool isLeft = false;
    if(pParent)
        pParent->getLeft() == this ? true : false;

    //perform the rotation.
    setRight(pB);
    setParent(pQ);
    pQ->setLeft(this);
    pQ->setParent(pParent);
    if(pParent)
        isLeft ? pParent->setLeft(pQ) : pParent->setRight(pQ);

    OurCSCE310Tree* temp = new OurCSCE310Tree(*this);
    //this should point to Q
    setValue(pQ->getValue());
    setLeft(temp);
    setRight(pQ->getRight());
    setParent(pQ->getParent());
    if(pParent)
        isLeft ? pParent->setLeft(this) : pParent->setRight(this);
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
void OurCSCE310Tree::rotateRight() {
    OurCSCE310Tree* pP = getLeft();
    OurCSCE310Tree* pB = pP->getRight();
    OurCSCE310Tree* pQParent = getParent();
    OurCSCE310Tree* pQ = this;
    bool isLeft = false;
    if(pQParent)
        pQParent->getLeft() == this ? true : false;
    
    //perform the rotation.
    pQ->setLeft(pB);
    pQ->setParent(pP);
    pP->setRight(pQ);
    pP->setParent(pQParent);
    if(pQParent)
        isLeft ? pQParent->setLeft(pP) : pQParent->setRight(pP);

    OurCSCE310Tree* pQTemp = new OurCSCE310Tree(*pQ);
    //this should point to P
    setValue(pP->getValue());
    setLeft(pQTemp);
    setRight(pP->getRight());
    setParent(pP->getParent());
    if(pQParent)
        isLeft ? pQParent->setLeft(this) : pQParent->setRight(this);
    pQTemp->setParent(this);

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
int OurCSCE310Tree::compareTo(int key) {
    if (key == getValue())
        return 0;
    return key > getValue() ? 1 : -1;
}

bool OurCSCE310Tree::contains(int key) {
    int compare = compareTo(key);
    if (compare == 0)
        return true;
    else if (compare == -1 && getLeft())
        return getLeft()->contains(key);
    else if (compare == 1 && getRight())
        return getRight()->contains(key);
    return false;
}

void OurCSCE310Tree::deleteNode(int key) {
    if (contains(key))
        deleteNodeHelper(key);
}

void OurCSCE310Tree::deleteNodeHelper(int key) {
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
            delete this;
            return;
        }
        else if (getLeft() == nullptr) 
        {
            OurCSCE310Tree* right = getRight();
            setLeft(right->getLeft());
            setRight(right->getRight());
            setValue(right->getValue());
            //prepare to delete the right.
            right->setLeft(nullptr);
            right->setRight(nullptr);
            delete right;
        }
        else if (getRight() == nullptr)
        {
            OurCSCE310Tree* left = getLeft();
            setLeft(left->getLeft());
            setRight(left->getRight());
            setValue(left->getValue());
            //prepare to delete the left.
            left->setLeft(nullptr);
            left->setRight(nullptr);
            delete left;
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
                OurCSCE310Tree* largest = getLeft()->getMax();
                setValue(largest->getValue());
                getLeft()->deleteNodeHelper(largest->getValue());
            }
            else
            {
                OurCSCE310Tree* smallest = getRight()->getMin();
                setValue(smallest->getValue());
                getRight()->deleteNodeHelper(smallest->getValue());
            }
        }
    }
    balance();
}

OurCSCE310Tree* OurCSCE310Tree::getMax()
{
    OurCSCE310Tree* retNode = nullptr;
    OurCSCE310Tree* curr = this;
    while (curr) {
        retNode = curr;
        curr = curr->getRight();
    }
    return retNode;
}

OurCSCE310Tree* OurCSCE310Tree::getMin()
{
    OurCSCE310Tree* retNode = nullptr;
    OurCSCE310Tree* curr = this;
    while (curr) {
        retNode = curr;
        curr = curr->left;
    }
    return retNode;
}

int main() {
    cout << "\nTest 1" << endl;

    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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
    cout << "\nTest 2" << endl;

    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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
    cout << "\nTest 3" << endl;

    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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
    cout << "\nTest 4" << endl;

    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
        avltree->insert(22);
        avltree->insert(36);
        avltree->insert(39);

        avltree->printPreorder();
        cout << "\n";
        avltree->printInorder();
        cout << "\n";
        avltree->printPostorder();
    }
    cout << "\nTest 5" << endl;

    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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
    cout << "\nTest 6" << endl;

    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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
    cout << "\nTest 7" << endl;

    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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
    cout << "\nTest 8" << endl;


    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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
    cout << "\nTest 9" << endl;

    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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
    cout << "\nTest 10" << endl;

    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
        avltree->insert(15);
        avltree->printPreorder();
        cout << "\n";
        avltree->printInorder();
        cout << "\n";
        avltree->printPostorder();
    }
    cout << "\nTest 11" << endl;

    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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
    cout << "\nTest 12" << endl;

    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
        avltree->insert(27);
        
        avltree->printPreorder();
        cout << "\n";
        avltree->printInorder();
        cout << "\n";
        avltree->printPostorder();
    }
    cout << "\nTest 13" << endl;

    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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
    cout << "\nTest 14" << endl;

    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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
    cout << "\nTest 15" << endl;
    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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
    cout << "----------------DELETE CASES-----------------" << endl;
    cout << "test 1" << endl;
    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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
        
    }

    cout << "test 2" << endl;
    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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

    }
    cout << "test 3" << endl;
    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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

    }
    cout << "test 4" << endl;
    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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

    }

    cout << "test 5" << endl;
    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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

    }

    cout << "test 6" << endl;
    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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

    }

    cout << "test 7" << endl;
    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();
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

    }

    cout << "test 5" << endl;
    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();


        avltree->printInorder();

    }
    cout << "test 5" << endl;
    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();


        avltree->printInorder();

    }
    cout << "test 5" << endl;
    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();


        avltree->printInorder();

    }
    cout << "test 5" << endl;
    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();


        avltree->printInorder();

    }
    cout << "test 5" << endl;
    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();


        avltree->printInorder();

    }
    cout << "test 5" << endl;
    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();


        avltree->printInorder();

    }
    cout << "test 5" << endl;
    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();


        avltree->printInorder();

    }
    cout << "test 5" << endl;
    {
        OurCSCE310Tree* avltree = new OurCSCE310Tree();


        avltree->printInorder();

    }
    return 0;
}
