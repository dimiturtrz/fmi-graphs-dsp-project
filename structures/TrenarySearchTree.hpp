#include <iostream>

// -------------------------------- NODE ------------------------------------

template<typename T>
void TrenarySearchTree<T>::TSTNode::clear() {
	delete data;
	data = NULL;

	hi = lo = equal = NULL;
}

template<typename T>
void TrenarySearchTree<T>::TSTNode::copy(const TrenarySearchTree<T>::TSTNode& other) {
	clear();
	data = (other.data != NULL) ? new T(*(other.data)) : NULL;
}

// ------------------------------ ITERATOR ----------------------------------

template<typename T>
TrenarySearchTree<T>::Iterator::Iterator(TSTNode* root) {
    iterationStack.push(Pair<TSTNode*, bool>(root, false));
	reachTreeBottom();
}

template<typename T>
void TrenarySearchTree<T>::Iterator::reachTreeBottom() {
    TSTNode* root = iterationStack.getTop().first;
	while(root->lo != NULL || root->equal != NULL) {
        iterationStack.pop();
		if(root->hi != NULL) {
			iterationStack.push(Pair<TSTNode*, bool>(root->hi, false));
		}

        iterationStack.push(Pair<TSTNode*, bool>(root, true));
		if(root->equal != NULL) {
            iterationStack.push(Pair<TSTNode*, bool>(root->equal, false));
		}

		if(root->lo != NULL) {
			root = root->lo;
            word.pop();
            word.push(root->character);
            iterationStack.push(Pair<TSTNode*, bool>(root, false));
		} else {
			root = root->equal;
			word.push(root->character);
		}
	}
}

template<typename T>
T& TrenarySearchTree<T>::Iterator::operator*() {
	TSTNode* topTSTNode = iterationStack.getTop().first;
	return *(topTSTNode->data);
}

template<typename T>
typename TrenarySearchTree<T>::Iterator& TrenarySearchTree<T>::Iterator::operator++() {
	TSTNode *terminal, *top;
	while(!isFinished()) {
		terminal = iterationStack.getTop().first;
		iterationStack.pop();
        top = iterationStack.getTop().first;
		while(!isFinished() && terminal == top->equal) {
			if(top->data != NULL) {
				return *this;
			}
			word.pop();
            terminal = top;
			iterationStack.pop();
            if(!isFinished()) { // for empty stack
                top = iterationStack.getTop().first;
            }
		}
		if(isFinished()) {
            break;
		}

		word.pop();
        if(!iterationStack.getTop().second) {
            reachTreeBottom();
            return *this;
        }
	}
}

template<typename T>
typename TrenarySearchTree<T>::Iterator& TrenarySearchTree<T>::Iterator::operator++(int) {
	Iterator currValue(*this);
	*this = ++(*this);
	return currValue;
}

template<typename T>
bool TrenarySearchTree<T>::Iterator::isFinished() {
	return iterationStack.isEmpty();
}
// ----------------------------- BIG FOUR

template<typename T>
TrenarySearchTree<T>::TSTNode::TSTNode(char character, T* data): character(character), data(NULL), hi(NULL), lo(NULL), equal(NULL) {
	if(data != NULL) {
		this->data = new T(*data);
	}
}

template<typename T>
TrenarySearchTree<T>::TSTNode::TSTNode(const TrenarySearchTree<T>::TSTNode& other): hi(NULL), lo(NULL), equal(NULL) {
	copy(other);
}

template<typename T>
typename TrenarySearchTree<T>::TSTNode& TrenarySearchTree<T>::TSTNode::operator=(const TrenarySearchTree<T>::TSTNode& other) {
	if(this != &other) {
		copy(other);
	}
	return* this;
}

template<typename T>
TrenarySearchTree<T>::TSTNode::~TSTNode() {
	delete data;
}

// -------------------------------- TREE ------------------------------------

// ---------------------------- CLEAR HELPER

template<typename T>
void TrenarySearchTree<T>::clear() {
	if(root != NULL) {
		clearSubtree(root);
	}
}

template<typename T>
void TrenarySearchTree<T>::clearSubtree(TSTNode*& currRoot) {

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
        copySubtree(root, other.root);
	}
}

template<typename T>
void TrenarySearchTree<T>::copySubtree(TSTNode*& currRoot, TSTNode* otherCurrRoot) {

	currRoot = new TSTNode(*otherCurrRoot);

	if(otherCurrRoot->hi != NULL) {
		copySubtree(currRoot->hi, otherCurrRoot->hi);
	}

	if(otherCurrRoot->lo != NULL) {
		copySubtree(currRoot->lo, otherCurrRoot->lo);
	}

	if(otherCurrRoot->equal != NULL) {
		copySubtree(currRoot->equal, otherCurrRoot->equal);
	}
}

// --------------------------- BIG FOUR

template<typename T>
TrenarySearchTree<T>::TrenarySearchTree(): root(NULL) {}

template<typename T>
TrenarySearchTree<T>::TrenarySearchTree(const TrenarySearchTree& other): root(NULL) {
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

// -------------------------- INTERATOR

template<typename T>
typename TrenarySearchTree<T>::Iterator TrenarySearchTree<T>::begin() {
	return Iterator(root);
}

// ---------------------------- ADD

template<typename T>
void TrenarySearchTree<T>::add(const char* key, const T& data) {
	if(root != NULL) {
        add(key, data, root);
	} else {
		root = new TSTNode(*key);
		if(*key == '\0') {
            root->data = new T(data);
            return;
		}
        add(key + 1, data, root);
	}
}

template<typename T>
void TrenarySearchTree<T>::add(const char* key, const T& data, TSTNode*& currRoot) {
	if(*key == '\0') {
		delete currRoot->data;
		currRoot->data = new T(data);
		return;
	}


	if(currRoot->equal == NULL) {
        if(currRoot->data != NULL) {
            key += 1;
        }
		currRoot->equal = new TSTNode(*key);
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
			currRoot->hi = new TSTNode(*key);
            return add(key + 1, data, currRoot->hi);
		} else {
            return add(key, data, currRoot->hi);
		}
	} else if (*key < currRoot->character) {
		if(currRoot->lo == NULL) {
			currRoot->lo = new TSTNode(*key);
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
void TrenarySearchTree<T>::remove(const char* key, TSTNode*& currRoot) {
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
void TrenarySearchTree<T>::printSubtree(TSTNode* currRoot, char* accumWord, int accumWordIndex) {
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
T* TrenarySearchTree<T>::getElement(const char* key, TSTNode* currRoot) {
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
