#include <iostream>
#include "StringBST.h"


using namespace std;


StringBST::StringBST()
{
	// initalize troot
	root = NULL;
}

StringBST::StringBST(string arrayString[], int size)
{
	// initalize root
	root = NULL;
	// current node used to add things to bst
	Node *current = root;
	for(int i = 0; i < size; i++)
	{

		// create a new node and add to list
		Node *newNode = new Node;
		// initialize it
		newNode->data = arrayString[i];
		newNode->quantity = 1;
		newNode->left = NULL;
		newNode->right = NULL;
		// if it is the first node in a list
		// it is the root
		// this is the edge case
		if(i == 0)
		{
			root = newNode;
			current = root;
		}
		// otherise insert it as normal recursively
		else
		{	
			insert(newNode, current);
		}
	}
}

void StringBST::insert(Node *newNode, Node *current)
{
	// if the node is bigger than the current node
	// check the node to the right
	if((newNode->data) > (current->data))
	{
		// if we have reached the end of the tree
		// insert it at the very right
		if((current->right) == NULL)
		{
			current->right = newNode;
			return;
		}
		insert(newNode, current->right);
	}
	// if the current node is the same as the new node
	// increase the number of instances in the current node
	else if((newNode->data) == (current->data))
	{
		(current->quantity)++;
		delete newNode;

	}
	// otherwise, the node is less than the current node
	// so recursively check if it is equal to anything
	// on the left
	else
	{
		// if we are at the end of the tree, insert it
		// at the end
		if((current->left) == NULL)
		{
			current->left = newNode;
			return;
		}
		insert(newNode, current->left);
	}
}


// destructor just called the clear function
StringBST::~StringBST()
{
	clear();
}

void StringBST::clear(Node *root)
{
	// if it is an empty tree, exit
	if(root == NULL)
	{
		return;
	}
	// otherwise clear the tree using
	// a post order traversal
	clear(root->left);
	clear(root->right);
	delete root;
}

bool StringBST::isEmpty()
{
	// if the root is null it is empty
	// otherwise it isn't
	if(root == NULL)
	{
		return true;
	}
	return false;
}

void StringBST::print()
{
	// recursive print function
	print(root);
	cout << endl;
}

void StringBST::print(Node *root)
{
	// print function, 
	// base case: if the current node
	// points to null, then return
	cout << "[";
	if(root == NULL)
	{
		cout << "]";
		return;
	}
	else
	{
		// otherwise print everything
		// using an inorder traversal
		print(root->left);
		cout << " " << root->data;
		cout << " " << root->quantity << " ";
		print(root->right);
		cout << "]";
	}


}

void StringBST::clear()
{
	// recursive clear function
	clear(root);
}


int StringBST::size()
{
	// recursive size function
	return size(root);
}

int StringBST::size(Node *root)
{
	// base case: if we are at the end of the list
	// return nothing, since there is no node
	if(root == NULL)
	{
		return 0;
	}
	// checks nodes like an in order traversal, but also returns
	// the number of elements within each node
	return size(root->left) + (root->quantity) + size(root->right);
}

void StringBST::add(string to_add)
{
	// create new node pointer to iterate through and make
	// sure the parent pointers point to the new
	// node in the correct location
	Node *current = root;
	// new node to insert
	Node *newNode = new Node;
	// fill it with data
	newNode->data = to_add;
	newNode->quantity = 1;
	newNode->left = NULL;
	newNode->right = NULL;
	// edge case, need to update root pointer;
	if(isEmpty())
	{
		root = newNode;
		current = root;
		return;
	}
	else
	{	
		// call recursive insert function
		insert(newNode, current);
	}
}

bool StringBST::remove(string target)
{
	// edge case for empty tree
	if(isEmpty())
	{
		return false;
	}
	// if the tree doesn't contain
	// what we want to remove, we won't be
	// able to remove it, so return false
	if(!contains(target))
	{
		return false;
	}
	// otherwise call recursive delete node function
	delete_node(root, target);
	return true;

}

StringBST::Node* StringBST::delete_node(Node *temp, string target)
{
	// if the data is bigger than the target
	// call the functino on the node to the left of it
	// returning a pointer to a node will update the 
	// parent pointer when it returns
	if(temp->data > target)
	{
		temp->left = delete_node(temp->left, target);
	}
	// same with if the data is less than the target
	else if(temp->data < target)
	{
		// cerr << "second if statement" << endl;
		// parent = temp;
		temp->right = delete_node(temp->right, target);
		// return temp;
	}
	// we must have found the node if it isn't bigger than
	// or less than the the current node
	else
	{
		// deletes one instance, so if the quantity
		// is bigger than one, this just decrements the quantity
		if((temp->quantity) > 1)
		{
			(temp->quantity)--;
			return temp;
		}
		// edge case for if the temp is the root of the tree and we need 
		// to update root
		if((temp == root) and (((temp->left) == NULL) 
			and (temp->right) == NULL))
		{
			delete temp;
			temp = NULL;
			return temp;

		}
		// if the node we want to delete is a leaf
		if(((temp->left) == NULL) and (temp->right) == NULL)
		{
			delete temp;
			temp = NULL;
			return temp;
		}
		// if the node we want to delete had one child
		// these two if statements handle the case
		// within each is the edge case if temp is the root
		if(((temp->left != NULL)) and (temp->right == NULL))
		{
			if(temp == root)
			{
				root = temp->left;
			}
			Node *nodey = temp;
			temp = temp->left;
			delete nodey;
			return temp;
		}
		if(((temp->left == NULL)) and (temp->right != NULL))
		{
			if(temp == root)
			{

				root = temp->right;
			}
			Node *nodey = temp;
			temp = temp->right;
			delete nodey;
			return temp;
		}
		// if the node has two children, we need to take the max node
		// on the left subtree of this node, and swap the values, then delete
		// the original node we wanted to delete at its new position
		if(((temp->left != NULL)) and (temp->right != NULL))
		{

			Node *nodey = findMax(temp->left);
			temp->data = nodey->data;
			temp->quantity = nodey->quantity;
			temp->left = delete_node(temp->left, nodey->data);
			if(temp == root)
			{
				root = temp;
			}
			return temp;
		}
	}
	return temp;
}
StringBST::Node* StringBST::findMax(Node *temp)
{
	if((temp->left)== NULL)
	{
		return temp;
	}
	return findMax(temp->left);
}


string StringBST::getMin()
{
	// get the minimum value of the tree recursively
	return getMin(root);
}

string StringBST::getMin(Node *temp)
{
	// base case, if there is nothing to the left
	// of the current node, return the current data
	if(isEmpty())
	{
		throw runtime_error("empty_tree");
	}
	if((temp->left) == NULL)
	{
		// cerr << "base case"<< endl;
		return (temp->data);
	}
	// otherwise try again with the node
	// to the left of the current node
	return getMin(temp->left);

}
  
string StringBST::getMax()
{
	// get the maximum value of the tree recursively
	return getMax(root);
}

string StringBST::getMax(Node *root)
{
	if(isEmpty())
	{
		throw runtime_error("empty_tree");
	}
	// base case, if there is nothing
	// to the right of the root it must be
	// the largest value in the bst
	if((root->right) == NULL)
	{
		return root->data;
	}
	// otherwise try again with the node
	// on the right of the current node
	return getMax(root->right);
}


void StringBST::removeMin()
{
	// edge case for empty tree
	if(isEmpty())
	{
		throw runtime_error("empty_tree");
	}
	// edge case if it is a tree of size one
	// because we need to update the root pointer
	if(size() == 1)
	{
		delete root;
		root = NULL;
		return;
	}
	// set target to the value at getmin
	string target = getMin();
	// call recursive remove function
	remove(target);

	return;

}


void StringBST::removeMax()
{
	// edge case for empty tree
	if(isEmpty())
	{
		throw runtime_error("empty_tree");
	}
	// edge case if it is a tree of size one
	// because we need to update the root pointer
	if(size() == 1)
	{
		delete root;
		root = NULL;
		return;
	}
	// otherwise remove the max value
	remove(getMax());
	
}



bool StringBST::contains(string target)
{
	// call to recursive function
	return contains(target, root);
}

// traverses the tree to see if value is present
// compares value to current node to have a run time
// of logn instead of traversing through the whole list
bool StringBST::contains(string target, Node *root)
{
	if(isEmpty())
	{
		return false;
	}
	else if(root == NULL)
	{
		return false;
	}
	else if(target < root->data)
	{
		return contains(target, root->left);
	}
	else if(target > root->data)
	{
		return contains(target, root->right);
	}
	else
	{
		return true;
	}
	
}











