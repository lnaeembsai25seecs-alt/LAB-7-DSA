#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <stdexcept>
#include <algorithm>
using namespace std;

struct Node {
	char data;
	Node* left;
	Node* right;

	Node(char value) {
		data = value;
		left = nullptr;
		right = nullptr;
	}
};

// ==================================================
// TASK 1: BUILD BINARY TREE FROM STRING
// ==================================================

Node* parseTree(const string& s, int& i) {
	if (i >= (int)s.size() ||
		s[i] == ',' || s[i] == ')') {
		throw runtime_error("Invalid tree string");
	}

	char value = s[i++];

	if (value == '(')
		throw runtime_error("Invalid node");

	Node* root = new Node(value);

	if (i < (int)s.size() && s[i] == '(') {
		++i;

		if (i < (int)s.size() && s[i] != ',')
			root->left = parseTree(s, i);

		if (i >= (int)s.size() || s[i] != ',')
			throw runtime_error("Missing comma");

		++i;


		if (i < (int)s.size() && s[i] != ')')
			root->right = parseTree(s, i);

		if (i >= (int)s.size() || s[i] != ')')
			throw runtime_error("Missing closing parenthesis");

		++i;
	}

	return root;
}

Node* buildTree(const string& s) {
	int i = 0;
	Node* root = parseTree(s, i);

	if (i != (int)s.size())
		throw runtime_error("Extra characters in tree string");

	return root;
}

// ==================================================
// TASK 2: RECURSIVE PREORDER TRAVERSAL
// Root -> Left -> Right
// ==================================================

void preorder(Node* root) {
	if (root == nullptr)
		return;

	cout << root->data;
	preorder(root->left);
	preorder(root->right);
}

// ==================================================
// TASK 3: ITERATIVE INORDER USING STACK
// Left -> Root -> Right
// ==================================================

void inorderIterative(Node* root) {
	stack<Node*> st;
	Node* current = root;

	while (current != nullptr || !st.empty()) {
		while (current != nullptr) {
			st.push(current);
			current = current->left;
		}

		current = st.top();
		st.pop();

		cout << current->data;

		current = current->right;
	}
}

// ==================================================
// TASK 4: ITERATIVE POSTORDER USING TWO STACKS
// Left -> Right -> Root
// ==================================================

void postorderIterative(Node* root) {
	if (root == nullptr)
		return;

	stack<Node*> s1, s2;
	s1.push(root);

	while (!s1.empty()) {
		Node* current = s1.top();
		s1.pop();

		s2.push(current);

		if (current->left != nullptr)
			s1.push(current->left);

		if (current->right != nullptr)
			s1.push(current->right);
	}

	while (!s2.empty()) {
		cout << s2.top()->data;
		s2.pop();
	}
}

// ==================================================
// TASK 5: VALIDATE STRING WITHOUT BUILDING A TREE
// ==================================================

bool validNode(const string& s, int& i) {

	if (i >= (int)s.size() ||
		s[i] == '(' || s[i] == ')' || s[i] == ',') {
		return false;
	}

	++i;


	if (i >= (int)s.size() || s[i] != '(')
		return true;

	++i;


	if (i < (int)s.size() && s[i] != ',') {
		if (!validNode(s, i))
			return false;
	}


	if (i >= (int)s.size() || s[i] != ',')
		return false;

	++i;


	if (i < (int)s.size() && s[i] != ')') {
		if (!validNode(s, i))
			return false;
	}


	if (i >= (int)s.size() || s[i] != ')')
		return false;

	++i;

	return true;
}

bool isValidTreeString(const string& s) {
	if (s.empty())
		return false;

	int i = 0;

	return validNode(s, i) && i == (int)s.size();
}

// ==================================================
// TASK 6: HEIGHT AND DEPTH OF TREE
// Height is measured in nodes.
// Root depth is 0.
// ==================================================

int height(Node* root) {
	if (root == nullptr)
		return 0;

	int leftHeight = height(root->left);
	int rightHeight = height(root->right);

	return 1 + max(leftHeight, rightHeight);
}

void printDepths(Node* root, int depth = 0) {
	if (root == nullptr)
		return;

	cout << "Node " << root->data
		<< " : depth = " << depth << endl;

	printDepths(root->left, depth + 1);
	printDepths(root->right, depth + 1);
}

// ==================================================
// TASK 7: BUILD BINARY SEARCH TREE (BST)
// ==================================================

struct BSTNode {
	int data;
	BSTNode* left;
	BSTNode* right;

	BSTNode(int value) {
		data = value;
		left = nullptr;
		right = nullptr;
	}
};

BSTNode* insertBST(BSTNode* root, int value) {
	if (root == nullptr)
		return new BSTNode(value);

	if (value < root->data) {
		root->left = insertBST(root->left, value);
	}
	else if (value > root->data) {
		root->right = insertBST(root->right, value);
	}

	// Duplicate values are ignored
	return root;
}

BSTNode* buildBST(const vector<int>& values) {
	BSTNode* root = nullptr;

	for (int value : values)
		root = insertBST(root, value);

	return root;
}

void inorderBST(BSTNode* root) {
	if (root == nullptr)
		return;

	inorderBST(root->left);
	cout << root->data << " ";
	inorderBST(root->right);
}

// ==================================================
// MAIN FUNCTION
// ==================================================

int main() {
	string treeString = "a(b(d,e),c(,f(g,)))";

	try {

		cout << boolalpha;
		cout << "Valid tree string: "
			<< isValidTreeString(treeString) << endl;


		Node* root = buildTree(treeString);


		cout << "\nPreorder: ";
		preorder(root);
		cout << endl;


		cout << "Inorder: ";
		inorderIterative(root);
		cout << endl;

		cout << "Postorder: ";
		postorderIterative(root);
		cout << endl;


		cout << "\nTree height: "
			<< height(root) << endl;

		cout << "Node depths:" << endl;
		printDepths(root);

		vector<int> values = {
			50, 30, 70, 20, 40, 60, 80
		};

		BSTNode* bstRoot = buildBST(values);

		cout << "\nBST inorder traversal: ";
		inorderBST(bstRoot);
		cout << endl;
	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
		return 1;
	}

	return 0;
}
