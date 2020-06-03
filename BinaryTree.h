#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <string>

//using namespace std;

template <class T>
struct BTNode 
{
	T   data;
	BTNode *left, *right;
};

template <class T>
class BinaryTree 
{
	BTNode<T> *root;

public:
	BinaryTree();
	~BinaryTree();
	bool       insert(T data);
	BTNode<T>* search(T data);
        bool       remove(T key);
	int        size();
        BTNode<T>* getRoot();	
	void       setRoot(BTNode<T>* root);
	template<class U> friend std::ostream& operator<<(std::ostream& ostr, BinaryTree<U> & tree);
private:
	static BTNode<T>* newNode(T data);
	int height(BTNode<T> *n);
	void destroy(BTNode<T> *tree);
	bool insert(T data, BTNode<T> *tree);
	BTNode<T> *search(T data, BTNode<T> *tree);
        BTNode<T>* minValueNode(BTNode<T>* BTNode);
	BTNode<T>* maxValueNode(BTNode<T>* BTNode);
        BTNode<T>* remove(T key,BTNode<T>* root,bool &ok);
	int size(BTNode<T> *node);
	void streamInorder(BTNode<T> *tree,std::ostream& out);
	void streamInorder(std::ostream& out);
};

template <class T>
BinaryTree<T>::BinaryTree() 
{
	root = NULL;
}

template <class T>
BTNode<T>* BinaryTree<T>::getRoot()
{
	return root;
}

template <class T>
void BinaryTree<T>::setRoot(BTNode<T>* root)
{
	this->root=root;
}

template <class T>
void BinaryTree<T>::destroy(BTNode<T> *tree)
{
	if(tree!=NULL)
	{
		destroy(tree->left);
		destroy(tree->right);
		delete tree;
	}
	
}

template <class T>
int BinaryTree<T>::size(BTNode<T> *node)
{
	int count=1;
	if(node->left!=NULL)
		count+=size(node->left);
	if(node->right!=NULL)
		count+=size(node->right);
	return count;
}

template <class T>
int BinaryTree<T>:size()
{
	int count=0;
	if(root!=NULL)
		count=size(root);
	return count;
}

template <class T>
BTNode<T>* BinaryTree<T>::newNode(T data) {
	BTNode<T> *n;
	n = new BTNode<T>;
	n->data = data;
	n->left = NULL;
	n->right = NULL;
	return n;
}

template <class T>
int BinaryTree<T>::height(BTNode<T> *n)
{
	if(n==NULL)
		return 0;
	return (1+std::max(height(n->left),height(n->right)));
}

template <class T>
int BinaryTree<T>::height()
{
	return height(root);
}

template <class T>
bool BinaryTree<T>::insert(T data, BTNode<T> *tree) 
{
	if (data < tree->data) 
	{
		if (tree->left != NULL)
			return insert(data, tree->left);
		else
		{
			tree->left = newNode(data);
			return true;
		}
	}
	else if (data > tree->data) 
	{
		if (tree->right != NULL)
			return insert(data, tree->right);
		else
		{
			tree->right = newNode(data);
			return true;
		}
	}
	return false;
}

template <class T>
BTNode<T>* BinaryTree<T>::search(T data, BTNode<T> *tree) 
{
	if (tree != NULL) 
	{
		if (data == tree->data)
			return tree;
		else if(data < tree->data)
			return search(data, tree->left);
		else  //if (data > tree->data)
			return search(data, tree->right);
	}
	else
		return NULL;
}

template <class T>
bool BinaryTree<T>::insert(T data) 
{
	if (root != NULL)
		return insert(data, root);
	else
	{
		root = newNode(data);
		return true;
	}
}

template <class T>
BTNode<T> *BinaryTree<T>::search(T data) 
{
	return search(data, root);
}

template <class T>
BTNode<T>* BinaryTree<T>::minValueNode(BTNode<T>* n)
{
	BTNode<T>* current=n;
	while(current->left!=NULL)
		current=current->left;
	return current;
}

template <class T>
BTNode<T>* BinaryTree<T>::maxValueNode(BTNode<T>* n)
{
	BTNode<T>* current=n;
	while(current->right!=NULL)
		current=current->right;
	return current;
}

template <class T>
BTNode<T>* BinaryTree<T>::remove(T key,BTNode<T>* root,bool &ok)
{
    if (root == NULL) 
        return NULL;
    if (key < root->data)
        root->left = remove(key,root->left,ok); 
    else if (key > root->data)
        root->right = remove(key,root->right,ok);
    else
    {
        ok=true;
        if (root->left == NULL)
        {
            BTNode<T> *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            BTNode<T> *temp = root->left;
            delete root;
            return temp;
        }
        BTNode<T>* temp = minValueNode(root->right);
        root->data = temp->data; 
        root->right = remove(temp->data,root->right,ok);
    }
    return root;
}
 
template <class T>
bool BinaryTree<T>::remove(T key)
{
    bool ok=false;
    remove(key,root,ok);
    return ok;
} 

template <class T>
void BinaryTree<T>::streamInorder(BTNode<T> *tree,std::ostream& out)
{
	if(tree==NULL)
		return;
        out<<tree->data<<std::endl;
	streamInorder(tree->left,out);
	streamInorder(tree->right,out);
}

template <class T>
void BinaryTree<T>::streamInorder(std::ostream& out)
{
	streamInorder(root,out);
}

template <class T>
std::ostream& operator<<(std::ostream& ostr, BinaryTree<T> & tree)
{
	tree.streamInorder(tree.getRoot(),ostr);
	return ostr;
}


#endif
