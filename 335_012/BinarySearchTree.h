#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <vector>
#include <map>
#include "Matrix.h"

class BinarySearchTree {
  struct Node {
    int64_t key;
    struct Node *left, *right;
  } *root;

public:
  BinarySearchTree() {
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

  template<class T>
  int ancestorMatrix(Matrix<T> &m)
  {
	std::vector<T> anc;
	return ancestorMatrixRec(root, anc, m);
  }
  
  template<class T>
  int ancestorTree(Matrix<T> &m)
  {
    T parent[m.getN()] = {0};
    std::multimap<T, int> mm;
	int count = 0;
	
    for (int i = 0; i < m.getN(); i++)
    {
        T sum = 0; // Initialize sum of this row
        for (int j = 0; j < m.getN(); j++)
            sum += m[i][j];
 
        mm.insert(std::pair<T, int>(sum, i));
    }
    Node* node[m.getN()];
 
    for (auto it = mm.begin(); it != mm.end(); ++it)
    {
	  Node* tmp = NULL;
      node[it->second] = write(tmp, it->second);
      root = node[it->second];
      if (it->first != 0)
      {
        for (int i = 0; i < m.getN(); i++)
        {
           if (!parent[i] && m[it->second][i])
           {
			 count++;
             if (!node[it->second]->left)
               node[it->second]->left = node[i];
             else
               node[it->second]->right = node[i];
 
             parent[i] = 1;
           }
        }
      }
    }
    return count+1;
  }
  
private:

  template<class T>
  int ancestorMatrixRec(Node *node, std::vector<T> &anc, Matrix<T> & m)
  {
    if (node == NULL) return 0;

    int data = node->key;

    for (int i=0; i<anc.size(); i++)
       m[anc[i]][data] = true;

    anc.push_back(data);
 
    int l = ancestorMatrixRec(node->left, anc, m);
    int r = ancestorMatrixRec(node->right, anc, m);

    anc.pop_back();

    return l+r+1;
  }
  
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

    return t;
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

};

#endif // BINARYSEARCHTREE_H
