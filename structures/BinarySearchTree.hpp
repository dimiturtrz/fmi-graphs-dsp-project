#include <iostream>

// -------------------------------- NODE ------------------------------------

template<typename T>
BinarySearchTree<T>::Node::Node(T data, Node* left, Node* right): data(data) {}

// -------------------------------- TREE ------------------------------------

// ---------------------------- CLEAR HELPER

template<typename T>
void BinarySearchTree<T>::clear() {
	clearSubtree(root);
}

template<typename T>
void BinarySearchTree<T>::clearSubtree(Node*& currRoot) {
	if(currRoot == NULL) {
		return;
	}

	if(currRoot->left != NULL) {
		clearSubtree(currRoot->left);
	}

	if(currRoot->right != NULL) {
		clearSubtree(currRoot->right);
	}

	delete currRoot;
	currRoot = NULL;
}

// --------------------------- COPY HELPER

template<typename T>
void BinarySearchTree<T>::copy(const BinarySearchTree& other) {
	clear();
	copySubtree(other.root);
}

template<typename T>
void BinarySearchTree<T>::copySubtree(Node*& currRoot, Node* otherCurrRoot) {
	if(otherCurrRoot == NULL) {
		return;
	}

	currRoot = new Node(otherCurrRoot->data);

	if(otherCurrRoot->left != NULL) {
		copySubtree(currRoot->left, otherCurrRoot->left);
	}

	if(otherCurrRoot->right != NULL) {
		copySubtree(currRoot->right, otherCurrRoot->right);
	}
}

// --------------------------- BIG FOUR

template<typename T>
BinarySearchTree<T>::BinarySearchTree(): root(NULL) {}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& other) {
	copy(other);
}

template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& other) {
	if(this != &other) {
		copy(other);
	}
	return *this;
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
	clear();
}

// ---------------------------- ADD

template<typename T>
void BinarySearchTree<T>::add(const T& data) {
	add(data, root);
}

template<typename T>
void BinarySearchTree<T>::add(const T& data, Node*& currRoot) {
	if(currRoot == NULL) {
		currRoot = new Node(data);
		return;
	}

	if(currRoot->data < data) {
		return add(data, currRoot->right);
	} else {
		return add(data, currRoot->left);
	}
}

// ------------------------- REMOVE

template<typename T>
void BinarySearchTree<T>::remove(const T& data) {
    if(root->data != data) {
        return remove(data, root);
    }

    removeNode(root);
}

template<typename T>
void BinarySearchTree<T>::remove(const T& data, Node*& currRoot) {
	if(currRoot == NULL) {
		throw;
	}

	if(currRoot->left != NULL && currRoot->left->data == data) {
		currRoot->left = removeNode(currRoot->left);
        return;
	} else if(currRoot->right != NULL && currRoot->right->data == data) {
		currRoot->right = removeNode(currRoot->right);
		return;
	}

	if(currRoot->data < data) {
		return remove(data, currRoot->right);
	} else {
		return remove(data, currRoot->left);
	}
}

template<typename T>
typename BinarySearchTree<T>::Node * BinarySearchTree<T>::removeNode(BinarySearchTree<T>::Node* node) {
	if(node->left != NULL && node->right != NULL) {
		node->data = getAndRemoveMin(node->right, node);
		return node;
	}

	if(node->left != NULL || node->right != NULL) {
		BinarySearchTree<T>::Node* newRoot = (node->left != NULL) ? node->left : node->right;
		delete node;
		return newRoot;
	}

	delete node;
	return NULL;
}

template<typename T>
T BinarySearchTree<T>::getAndRemoveMin(Node* node, Node*& parent) {
	if(node->left != NULL) {
		if(node->left->left == NULL) {
			T oldNodeValue = node->left->data;
			node->left = node->left->right;
			delete node->left;
			return oldNodeValue;
		} else {
			return getAndRemoveMin(node->left, node);
		}
	} else {
		T oldNodeValue = node->data;
		parent->right = node->right;
		delete node;
		return oldNodeValue;
	}
}

// ------------------------ PRINT

template<typename T>
void BinarySearchTree<T>::print() {
	if(root != NULL) {
		printSubtree(root);
	}
}

template<typename T>
void BinarySearchTree<T>::printSubtree(Node* currRoot) {
	if(currRoot->left != NULL) {
		printSubtree(currRoot->left);
	}
	std::cout<< currRoot->data<< std::endl;
	if(currRoot->right != NULL) {
		printSubtree(currRoot->right);
	}
}

// ------------------------ FIND

template<typename T>
T* BinarySearchTree<T>::getElement(const T& data) {
	getElement(data, root);
}

template<typename T>
T* BinarySearchTree<T>::getElement(const T& data, Node* currRoot) {
	if(currRoot == NULL) {
		return NULL;
	}

	if(currRoot->data < data) {
		return getElement(data, currRoot->right);
	} else if(currRoot->data > data) {
		return getElement(data, currRoot->left);
	} else {
		return &(currRoot->data);
	}
}
