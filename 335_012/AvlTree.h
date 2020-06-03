#ifndef AVLTREE_H
#define AVLTREE_H

class AvlTree {
  struct Node {
    int64_t key;
    struct Node *left, *right;
    int height;
  } *root;

public:
  AvlTree() {
    root = NULL;
  }

  bool isEmpty() {
    if(root == NULL)
      return true;
    return false;
  }

  int64_t findMin() {
    if(isEmpty()) {
      return -1;
    }

    return findMin(root)->key;
  }

  int64_t findMax() {
    if(isEmpty()) {
      return -1;
    }

    return findMax(root)->key;
  }

  bool read(int64_t key) {
    return read(root, key);
  }

  bool write(int64_t key) {
    if(read(key) == true)
      return false;

    write(root, key);
    return true;
  }

  bool remove(int64_t key) {
    return remove(root, key);
  }

private:
  Node *findMin(Node *t) {
    if(t == NULL)
      return NULL;
    else if(t->left == NULL)
      return t;
    else return findMin(t->left);
  }

  Node *findMax(Node *t) {
    if(t == NULL)
      return NULL;
    else if(t->right == NULL)
      return t;
    else return findMax(t->right);
  }

  bool read(Node *t, int64_t key) {
    if(t == NULL)
      return false;
    else if(key < t->key)
      return read(t->left, key);
    else if(key > t->key)
      return read(t->right, key);

    // key == t->key
    return true;
  }

  Node *write(Node*&t, int64_t key) {
    if(t == NULL) {
      t = new Node;
      t->key = key;
      t->left = t->right = NULL;
    } else if(key < t->key)
      t->left = write(t->left, key);
    else if(key > t->key)
      t->right = write(t->right, key);

    balance(t);

    return t;
  }

  int height(Node *t) {
    return t == NULL ? -1 : t->height;
  }

  int max(int a, int b) {
    return a > b ? a : b;
  }

  bool remove(Node*&t, int64_t key) {
    if(t == NULL)
      return false;
    else if(key < t->key)
      return remove(t->left, key);
    else if(key > t->key)
      return remove(t->right, key);
    else if(t->left && t->right) {
      // two children
      t->key = findMin(t->right)->key;
      return remove(t->right, t->key);
    } else {
      Node *temp = t;
      if(t->left != NULL)
        t = t->left;
      else t = t->right;
      delete temp;
      return true;
    }
  }

  void balance(Node*&t) {
    if(t == NULL)
      return;
    if(height(t->left) - height(t->right) > 1) {
      if(height(t->left->left) >= height(t->left->right))
        rotateWithLeftChild(t);
      else doubleWithLeftChild(t);
    } else if(height(t->right) - height(t->left) > 1) {
      if(height(t->right->right) - height(t->right->left) > 1)
        rotateWithRightChild(t);
      else doubleWithRightChild(t);
    }

    t->height = max(height(t->left), height(t->right)) + 1;
  }

  void rotateWithLeftChild(Node*&k2) {
    Node *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2 = k1;
  }

  void rotateWithRightChild(Node*&k1) {
    Node *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1 = k2;
  }

  void doubleWithLeftChild(Node*&k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
  }

  void doubleWithRightChild(Node*&k1) {
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
  }

};

#endif // AVLTREE_H
