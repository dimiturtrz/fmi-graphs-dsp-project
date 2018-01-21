#include <iostream>

// -------------------------------- NODE ------------------------------------

template<typename T>
TrenarySearchTree<T>::Node::Node(char character, T* data): character(character), data(data) {}

// -------------------------------- TREE ------------------------------------

// ---------------------------- CLEAR HELPER

template<typename T>
void TrenarySearchTree<T>::clear() {
	clearSubtree(root);
}

template<typename T>
void TrenarySearchTree<T>::clearSubtree(Node*& currRoot) {

	if(currRoot->lo != NULL) {
		clearSubtree(currRoot->lo);
	}

	if(currRoot->hi != NULL) {
		clearSubtree(currRoot->hi);
	}

	if(currRoot->equal != NULL) {
		clearSubtree(currRoot->equal);
	}

	delete currRoot;
	currRoot = NULL;
}

// --------------------------- COPY HELPER

template<typename T>
void TrenarySearchTree<T>::copy(const TrenarySearchTree& other) {
	clear();
	if(other.root != NULL) {
        copySubtree(other.root);
	}
}

template<typename T>
void TrenarySearchTree<T>::copySubtree(Node*& currRoot, Node* otherCurrRoot) {

	currRoot = new Node(otherCurrRoot->character, otherCurrRoot->data);

	if(otherCurrRoot->left != NULL) {
		copySubtree(currRoot->left, otherCurrRoot->left);
	}

	if(otherCurrRoot->right != NULL) {
		copySubtree(currRoot->right, otherCurrRoot->right);
	}

	if(otherCurrRoot->equal != NULL) {
		copySubtree(currRoot->equal, otherCurrRoot->equal);
	}
}

// --------------------------- BIG FOUR

template<typename T>
TrenarySearchTree<T>::TrenarySearchTree(): root(NULL) {}

template<typename T>
TrenarySearchTree<T>::TrenarySearchTree(const TrenarySearchTree& other) {
	copy(other);
}

template<typename T>
TrenarySearchTree<T>& TrenarySearchTree<T>::operator=(const TrenarySearchTree& other) {
	if(this != &other) {
		copy(other);
	}
	return *this;
}

template<typename T>
TrenarySearchTree<T>::~TrenarySearchTree() {
	clear();
}

// ---------------------------- ADD

template<typename T>
void TrenarySearchTree<T>::add(const char* key, const T& data) {
	if(root != NULL) {
        add(key, data, root);
	} else {
		root = new Node(*key);
		if(*key == '\0') {
            root->data = new T(data);
            return;
		}
        add(key + 1, data, root);
	}
}

template<typename T>
void TrenarySearchTree<T>::add(const char* key, const T& data, Node*& currRoot) {
	if(*key == '\0') {
		delete currRoot->data;
		currRoot->data = new T(data);
		return;
	}


	if(currRoot->equal == NULL) {
        if(currRoot->data != NULL) {
            key += 1;
        }
		currRoot->equal = new Node(*key);
        return add(key + 1, data, currRoot->equal);
	}

	if(*key == currRoot->character){
        if(*(key + 1) != '\0') {
            return add(key + 1, data, currRoot->equal);
        } else {
            return add(key + 1, data, currRoot);
        }
    } else if(*key > currRoot->character) {
		if(currRoot->hi == NULL) {
			currRoot->hi = new Node(*key);
            return add(key + 1, data, currRoot->hi);
		} else {
            return add(key, data, currRoot->hi);
		}
	} else if (*key < currRoot->character) {
		if(currRoot->lo == NULL) {
			currRoot->lo = new Node(*key);
            return add(key + 1, data, currRoot->lo);
		} else {
            return add(key, data, currRoot->lo);
		}
	}
}

// ------------------------- REMOVE

template<typename T>
void TrenarySearchTree<T>::remove(const char* key) {
    return remove(key, root);
}

template<typename T>
void TrenarySearchTree<T>::remove(const char* key, Node*& currRoot) {
    if(currRoot == NULL) {
        return;
    }

	if(*key == '\0') {
		delete currRoot->data;
        currRoot->data = NULL;
		if(currRoot->hi == NULL && currRoot->lo == NULL && currRoot->equal == NULL) {
			delete currRoot;
			currRoot = NULL;
		}
		return;
	}

	if(*key == currRoot->character){
        if(*(key + 1) != '\0') {
            remove(key + 1, currRoot->equal);
        } else {
            return remove(key + 1, currRoot);
        }
    } else if(*key > currRoot->character) {
        remove(key, currRoot->hi);
	} else if (*key < currRoot->character) {
		remove(key, currRoot->lo);
	}

	if(currRoot->equal == NULL) {
        if(currRoot->lo != NULL) {
            currRoot->equal = currRoot->lo;
            currRoot->lo = NULL;
        } else if(currRoot->hi != NULL) {
            currRoot->equal = currRoot->hi;
            currRoot->hi = NULL;
        } else if(currRoot->data == NULL) {
            delete currRoot;
            currRoot = NULL;
        }
	}
}

// ------------------------ PRINT

template<typename T>
void TrenarySearchTree<T>::print() {
	if(root != NULL) {
		char accumWord[51] = { '\0' };
		printSubtree(root, accumWord, 0);
	}
}

template<typename T>
void TrenarySearchTree<T>::printSubtree(Node* currRoot, char* accumWord, int accumWordIndex) {
    if(currRoot == NULL) {
        return;
    }

    printSubtree(currRoot->lo, accumWord, accumWordIndex);
    accumWord[accumWordIndex] = currRoot->character;

    if(currRoot->data != NULL) {
        accumWord[accumWordIndex + 1] = '\0';
        std::cout<< accumWord<< std::endl;
    }

    printSubtree(currRoot->equal, accumWord, accumWordIndex + 1);
    printSubtree(currRoot->hi, accumWord, accumWordIndex);
}

// ------------------------ FIND

template<typename T>
T* TrenarySearchTree<T>::getElement(const char* key) {
	getElement(key, root);
}

template<typename T>
T* TrenarySearchTree<T>::getElement(const char* key, Node* currRoot) {
	if(currRoot == NULL) {
		return NULL;
	}

	if(*key == '\0') {
		return currRoot->data;
	}

	if(*key > currRoot->character) {
		return getElement(key, currRoot->hi);
	} else if(*key < currRoot->character) {
		return getElement(key, currRoot->lo);
	} else {
        if(*(key + 1) != '\0') {
            return getElement(key + 1, currRoot->equal);
        } else {
            return getElement(key + 1, currRoot);
        }
	}
}
