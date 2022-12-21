#include <iostream>
#include <vector>

// this is multiset implementation
// if anyone needs normal sets ask and you will recive
// if i've got time

template <typename TEMPAVL>
class AVL{
		
private:
	
	struct Node{

		Node *left, *right;
		int height, pos, quantity;
		TEMPAVL data;

		Node(TEMPAVL val){

			this->left = NULL;
			this->right = NULL;

			this->data = val;
			this->height = 0;
			this->pos = 1;
			this->quantity = 1;

		}

	};

	size_t sz = 0; bool addOrRemove = 0;
	Node *root = NULL;

	int getHeight(Node *v){
		return (v != NULL ? v->height : -1);
	}

	void countHeight(Node *v){
		v->height = max(getHeight(v->left), getHeight(v->right)) + 1;
	}

	void getPos(Node *v){
		v->pos = (v->left != NULL ? v->left->pos : 0) +
			 	 (v->right != NULL ? v->right->pos : 0) + v->quantity;
	}

	Node* leftRotate(Node *x){

		Node *y = x->right;
		x->right = y->left;
		y->left = x;

		countHeight(x);
		countHeight(y);
		getPos(x);
		getPos(y);

		return y;

	}

	Node* rightRotate(Node *x){

		Node *y = x->left;
		x->left = y->right;
		y->right = x;

		countHeight(x);
		countHeight(y);
		getPos(x);
		getPos(y);

		return y;

	}

	Node* balance(Node *v){

		int bal = getHeight(v->left) - getHeight(v->right);
		
		if(bal < -1){

			int childBal = getHeight(v->right->left) - getHeight(v->right->right);

			if(childBal <= 0) return leftRotate(v);
			else{
				v->right = rightRotate(v->right);
				return leftRotate(v);
			}

		}
		else if(bal > 1){

			int childBal = getHeight(v->left->left) - getHeight(v->left->right);

			if(childBal >= 0) return rightRotate(v);
			else{
				v->left = leftRotate(v->left);
				return rightRotate(v);
			}

		}

		return v;

	}

	Node *addElement(Node *v, TEMPAVL& val){

		if(v == NULL){
			addOrRemove = 1;
			v = new Node(val);
			return v;
		}

		if(v->data > val) v->left = addElement(v->left, val);
		else if(v->data < val) v->right = addElement(v->right, val);
		else{
			addOrRemove = 1;
			v->quantity++;
		}
		
		countHeight(v);
		getPos(v);

		return balance(v);

	}

	Node *findLeast(Node *v, Node *x){

		if(v == NULL) return NULL;

		if(v->left != NULL) v->left = findLeast(v->left, x);
		else{
			x->data = v->data;
			x->quantity = v->quantity;
			Node *ret = v->right;
			delete(v); return ret;
		}

		countHeight(v);
		getPos(v);

		return balance(v);

	}

	Node *deleteElement(Node *v, TEMPAVL& val){

		if(v == NULL)
			return NULL;

		if(v->data > val) v->left = deleteElement(v->left, val);
		else if(v->data < val) v->right = deleteElement(v->right, val);
		else{

			addOrRemove = 1;
			
			if(v->quantity > 1){
				v->quantity--;
				getPos(v);
				return v;
			}

			if(v->right == NULL){
				Node *ret = v->left;
				delete(v); return ret;
			}

			v->right = findLeast(v->right, v);
			
		}
		
		countHeight(v);
		getPos(v);

		return balance(v);

	}

	TEMPAVL searchIdx(Node *v, size_t idx){

		if(v == NULL)
			return TEMPAVL();

		int curPos = (v->left == NULL ? 0 : v->left->pos);
		
		if(idx > curPos && idx <= curPos + v->quantity) return v->data;		
		else if(idx > curPos + v->quantity) return searchIdx(v->right, idx - curPos - v->quantity);
		else if(idx <= curPos) return searchIdx(v->left, idx);
		
	}

	Node *deleteElementIdx(Node *v, size_t idx){

		if(v == NULL)
			return NULL;

		int curPos = (v->left == NULL ? 0 : v->left->pos);
	
		if(idx > curPos && idx <= curPos + v->quantity){
			
			addOrRemove = 1;
			
			if(v->quantity > 1){
				v->quantity--;
				getPos(v);
				return v;
			}

			if(v->right == NULL){
				Node *ret = v->left;
				delete(v); return ret;
			}

			v->right = findLeast(v->right, v);
			
		}	
		else if(idx > curPos + v->quantity) v->right = deleteElementIdx(v->right, idx - curPos - v->quantity);
		else if(idx <= curPos) v->left = deleteElementIdx(v->left, idx);

		countHeight(v);
		getPos(v);

		return balance(v);

	}

	bool findElement(Node *v, TEMPAVL& val){

		if(v == NULL) return false;
		if(v->data == val) return true;

		bool b;

		if(v->data > val) b = findElement(v->left, val);
		else b = findElement(v->right, val);

		return b;

	}

	size_t findBound(Node *v, TEMPAVL& val, bool isUpper, long long pos = 0){

		if(v == NULL) return pos + 1;
		
		size_t curPos = (v->left == NULL ? 0 : v->left->pos);

		if(v->data == val) 
			return pos + curPos + (isUpper ? v->quantity + 1 : 1);

		if(v ->data > val) return findBound(v->left, val, isUpper, pos);
		else return findBound(v->right, val, isUpper, pos + curPos + v->quantity);

	}

	void sortDFS(Node *v, std::vector <TEMPAVL> &a){

		if(v == NULL) return;

		sortDFS(v->left, a);
	
		for(size_t k = 0; k < v->quantity; k++)
			a.pb(v->data);
	
		sortDFS(v->right, a);

	}

public:
	
	// constructor
	
	AVL(){
		sz = 0;
		this->root == NULL;
	}

	// gets the number of elements in the set

	size_t size(){
		return sz;
	}
	
	// insert element

	void insert(TEMPAVL val){
		root = addElement(root, val);
		sz += addOrRemove;
		addOrRemove = 0;
	}
	
	// remove element by value removes all elements of type

	void remove(TEMPAVL val){
		root = deleteElement(root, val);
		sz -= addOrRemove;
		addOrRemove = 0;
	}
	
	// removes element by index only removes one element
	
	void removeByIndex(size_t idx){
		root = deleteElementIdx(root, idx + 1);
		sz -= addOrRemove;
		addOrRemove = 0;
	}
	
	// finds if element exists
	
	bool find(TEMPAVL val){
		return findElement(root, val);
	}
	
	// finds element at a givven index time for search is O(log2(n))
	
	TEMPAVL findByIndex(size_t idx){
		return searchIdx(root, idx + 1);
	}
	
	// works same as lower_bound in std

	size_t lowerBound(TEMPAVL val){
		return findBound(root, val, false) - 1;
	}
	
	// works same as upper_bound in std

	size_t upperBound(TEMPAVL val){
		return findBound(root, val, true) - 1;
	}

	// function fills vector with elements in ascending order

	void sort(std::vector <TEMPAVL>& a){
		sortDFS(root, a);
	}

};

int main(){
	
	return 0;
}
