#ifndef STRINGBST_H_
#define STRINGBST_H_

using namespace std;

class StringBST
{
	private:

	struct Node
	{
		string data;
		int quantity;
		Node* left;
		Node* right;
	};
	Node* root;
	void insert(Node *newNode, Node *current);
	void print(Node *root);
	int size(Node *root);
	Node* delete_node(Node *temp, string target);
	string getMin(Node *temp);
	string getMax(Node *root);
	bool contains(string target, Node *root);

	public:

	StringBST();
	StringBST(string arrayString[], int size);
	~StringBST();
	void clear(Node *root);
	bool isEmpty();
	void print();
	void clear();
	int size();
	void add(string to_add);
	bool remove(string target);
	Node* findMax(Node *temp);
	string getMin();
	string getMax();
	void removeMin();
	void removeMax();
	bool contains(string target);
};
#endif