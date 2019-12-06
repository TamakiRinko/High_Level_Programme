#pragma once
#include <functional>
#include <iostream>
#include "Complex.h"
#include <stack>
using namespace std;

template <class T>
struct Node{
	T data;
	Node* left;
	Node* right;
	Node(const T& value){
		data = value;
		left = NULL;
		right = NULL;
	}
	Node<T>& operator=(const Node<T>& c) {
		data = c.data;
		return *this;
	}
};

template <class T>
class Tree{
private:
	Node<T>* tree;
public:
	Tree(int K, const T& value);
	void preorder_show();
	void postorder_show();
	void midorder_show();
	T accumulate(T init_value);
	T accumulate(std::function<T(T t, T val)> f, T init_value);
	void for_each(std::function<T(T t)> f);
	int count(T init_value);

	void preOrder(Node<T>* root);
	void postOrder(Node<T>* root);
	void midOrder(Node<T>* root);
	void create(int m, const T& value, Node<T>*& root);
	int count2(T init_value, Node<T>*& root);
	void for_each2(std::function<T(T t)> f, Node<T>*& root);
};

template <class T>
Tree<T>::Tree(int K, const T& value) {
	tree = new Node<T>(value);
	create(K, value, tree->left);
	create(K, value, tree->right);
}

template <class T>
void Tree<T>::create(int m, const T& value, Node<T>*& root) {
	if (m <= 0) {
		return;
	}
	root = new Node<T>(value);
	create(m - 1, value, root->left);
	create(m - 1, value, root->right);
}

template <class T>
int Tree<T>::count2(T init_value, Node<T>*& root){
	if (root == NULL) {
		return 0;
	}
	int count = 0;
	if (root->data == init_value){
		count = 1;
	}
	count += count2(init_value, root->left);
	count += count2(init_value, root->right);
	return count;
}

template <class T>
void Tree<T>::for_each2(std::function<T(T t)> f, Node<T>*& root){
	if (root == NULL) {
		return;
	}
	root->data = f(root->data);
	for_each2(f, root->left);
	for_each2(f, root->right);
}

template <class T>
void Tree<T>::preorder_show() {
	preOrder(tree);
	cout << endl;
}

template <class T>
void Tree<T>::postorder_show(){
	postOrder(tree);
	cout << endl;
}

template <class T>
void Tree<T>::midorder_show(){
	midOrder(tree);
	cout << endl;
}

template <class T>
T Tree<T>::accumulate(T init_value){
	stack< Node<T>* > mystack;
	mystack.push(tree);

	while (!mystack.empty()){
		Node<T>* temp = mystack.top();
		mystack.pop();
		if (temp->right != NULL) {
			mystack.push(temp->right);
		}
		if (temp->left != NULL) {
			mystack.push(temp->left);
		}
		if (temp != NULL){
			// delete temp;
			init_value = init_value + temp->data;
			Node<T>* n = new Node<T>(init_value);
			*temp = *n;
		}
	}
	return init_value;
}

template <class T>
T Tree<T>::accumulate(std::function<T(T t, T val)> f, T init_value){
	stack< Node<T>* > mystack;
	mystack.push(tree);

	while (!mystack.empty()) {
		Node<T>* temp = mystack.top();
		mystack.pop();
		if (temp->right != NULL) {
			mystack.push(temp->right);
		}
		if (temp->left != NULL) {
			mystack.push(temp->left);
		}
		if (temp != NULL) {
			// delete temp;
			init_value = f(temp->data, init_value);
			Node<T>* n = new Node<T>(init_value);
			*temp = *n;
		}
	}
	return init_value;
}

template <class T>
void Tree<T>::for_each(std::function<T(T t)> f){
	for_each2(f, tree);
}

template <class T>
int Tree<T>::count(T init_value){
	int count = 0;
	count += count2(init_value, tree);
	return count;
}

template <class T>
void Tree<T>::preOrder(Node<T>* root) {
	if (root == NULL) {
		return;
	}
	cout << root->data << " ";
	preOrder(root->left);
	preOrder(root->right);
}

template <class T>
void Tree<T>::postOrder(Node<T>* root){
	if (root == NULL) {
		return;
	}
	postOrder(root->left);
	postOrder(root->right);
	cout << root->data << " ";
}

template <class T>
void Tree<T>::midOrder(Node<T>* root){
	if (root == NULL) {
		return;
	}
	midOrder(root->left);
	cout << root->data << " ";
	midOrder(root->right);
}
