#include <bits/stdc++.h>

using namespace std;

struct node {
    node *leftNode, *rightNode, *parentNode;
    int data;
};

class splayTree {
   private:
    node* rootNode;

    void rotateLeft(node* Node) {
        node* curr = Node->rightNode;

        if (curr != NULL) {
            Node->rightNode = curr->leftNode;

            if (curr->leftNode != NULL) {
                curr->leftNode->parentNode = Node;
            }

            curr->parentNode = Node->parentNode;
        }

        if (Node->parentNode == NULL) {
            this->rootNode = curr;
        } else if (Node == Node->parentNode->leftNode) {
            Node->parentNode->leftNode = curr;
        } else {
            Node->parentNode->rightNode = curr;
        }

        if (curr != NULL) {
            curr->leftNode = Node;
        }

        Node->parentNode = curr;
    }

    void rotateRight(node* Node) {
        node* curr = Node->leftNode;

        if (curr != NULL) {
            Node->leftNode = curr->rightNode;

            if (curr->rightNode != NULL) {
                curr->rightNode->parentNode = Node;
            }

            curr->parentNode = Node->parentNode;
        }

        if (Node->parentNode == NULL) {
            this->rootNode = curr;
        } else if (Node == Node->parentNode->leftNode) {
            Node->parentNode->leftNode = curr;
        } else {
            Node->parentNode->rightNode = curr;
        }

        if (curr != NULL) {
            curr->rightNode = Node;
        }

        Node->parentNode = curr;
    }

    void splay(node* node) {
        while (node->parentNode != NULL) {
            // ZIG
            if (node->parentNode->parentNode == NULL) {
                if (node->parentNode->leftNode == node) {
                    rotateRight(node->parentNode);
                } else {
                    rotateLeft(node->parentNode);
                }
            }

            // ZIG-ZIG or ZAG-ZAG
            else if (node->parentNode->leftNode == node && node->parentNode->parentNode->leftNode == node->parentNode) {
                rotateRight(node->parentNode->parentNode);
                rotateRight(node->parentNode);
            } else if (node->parentNode->rightNode == node && node->parentNode->parentNode->rightNode == node->parentNode) {
                rotateLeft(node->parentNode->parentNode);
                rotateLeft(node->parentNode);
            }

            // ZIG-ZAG or ZAG-ZIG
            else if (node->parentNode->leftNode == node && node->parentNode->parentNode->rightNode == node->parentNode) {
                rotateRight(node->parentNode);
                rotateLeft(node->parentNode);
            } else {
                rotateLeft(node->parentNode);
                rotateRight(node->parentNode);
            }
        }
    }

    void inOrderPrint(node* node) {
        if (node->leftNode != NULL) {
            inOrderPrint(node->leftNode);
        }
        cout << node->data << " ";

        if (node->rightNode != NULL) {
            inOrderPrint(node->rightNode);
        }
    }

    int getMin(node* node) {
        if (node->leftNode != NULL) {
            return getMin(node->leftNode);
        } else {
            return node->data;
        }
    }

    int getMax(node* node) {
        if (node->rightNode != NULL) {
            return getMax(node->rightNode);
        } else {
            return node->data;
        }
    }

   public:
    splayTree() { rootNode = NULL; }

    void insertNode(int data) {
        node* newNode = new node;
        newNode->data = data;
        newNode->leftNode = NULL;
        newNode->rightNode = NULL;
        newNode->parentNode = NULL;

        if (this->rootNode == NULL) {
            this->rootNode = newNode;
        } else {
            node* temp = this->rootNode;
            node* parent = NULL;
            while (temp != NULL) {
                parent = temp;
                if (data > temp->data) {
                    temp = temp->rightNode;
                } else {
                    temp = temp->leftNode;
                }
            }

            newNode->parentNode = parent;
            if (parent->data < data) {
                parent->rightNode = newNode;
            } else {
                parent->leftNode = newNode;
            }
        }
        splay(newNode);
    }

    node* searchNode(int data) {
        node* temp = this->rootNode;

        while (temp != NULL) {
            if (data > temp->data) {
                temp = temp->rightNode;
            } else if (data < temp->data) {
                temp = temp->leftNode;
            } else {
                cout << "Found" << endl;
                splay(temp);
                return temp;
            }
        }
        cout << "Not Found" << endl;
        return NULL;
    }

    void deleteNode(int data) {
        // Search for nodeToDelete and splay it to the root
        node* nodeToDelete = searchNode(data);
        if (nodeToDelete == NULL) {
            return;
        }
        cout << "Deleted";
        splay(nodeToDelete);

        // If the node has both left and right children, find its successor
        // and replace it with nodeToDelete
        if (nodeToDelete->leftNode != NULL && nodeToDelete->rightNode != NULL) {
            node* successor = nodeToDelete->rightNode;
            while (successor->leftNode != NULL) {
                successor = successor->leftNode;
            }
            nodeToDelete->data = successor->data;
            nodeToDelete = successor;
        }

        // Get the child node of nodeToDelete
        node* child = NULL;
        if (nodeToDelete->leftNode != NULL) {
            child = nodeToDelete->leftNode;
        } else if (nodeToDelete->rightNode != NULL) {
            child = nodeToDelete->rightNode;
        }

        // Remove nodeToDelete
        if (nodeToDelete->parentNode == NULL) {
            // nodeToDelete is the root node
            rootNode = child;
        } else if (nodeToDelete == nodeToDelete->parentNode->leftNode) {
            nodeToDelete->parentNode->leftNode = child;
        } else {
            nodeToDelete->parentNode->rightNode = child;
        }
        if (child != NULL) {
            child->parentNode = nodeToDelete->parentNode;
        }

        delete nodeToDelete;
    }

    void inOrderPrint() {
        if (this->rootNode != NULL) {
            inOrderPrint(rootNode);
        }
    }

    int getMin() {
        if (this->rootNode != NULL) {
            return getMin(rootNode);
        }
        return NULL;
    }

    int getMax() {
        if (this->rootNode != NULL) {
            return getMax(rootNode);
        }
        return NULL;
    }
};

void Options() {
    cout << "\nPress 1 to add a new node";
    cout << "\nPress 2 to delete a node";
    cout << "\nPress 3 to print in order";
    cout << "\nPress 4 to search for a node";
    cout << "\nPress 5 to get the max value";
    cout << "\nPress 6 to get the min value";
    cout << "\nPress anything else to EXIT";
}

int main() {
    splayTree* tree = new splayTree;
    int option, x;

    do {
        Options();

        cout << "\n\nType your task: ";
        cin >> option;

        switch (option) {
            case 1: {
                cout << "\nNode to insert: ";
                cin >> x;
                tree->insertNode(x);
                break;
            }
            case 2: {
                cout << "\nNode to delete: ";
                cin >> x;
                tree->deleteNode(x);
                break;
            }
            case 3: {
                tree->inOrderPrint();
                break;
            }
            case 4: {
                cout << "\nNode to search for: ";
                cin >> x;
                tree->searchNode(x);
                break;
            }
            case 5: {
                cout << tree->getMax();
                break;
            }
            case 6: {
                cout << tree->getMin();
                break;
            }
        };
    } while (option == 1 || option == 2 || option == 3 || option == 4 || option == 5 || option == 6);

    cout << "\nYou exited\n";
    return 0;
}
