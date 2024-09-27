//Nicholas Guidice
//CS 375 Program 3 "Binary Search Tree"

//Import Libraries 
#include <iostream>
#include <vector>

using namespace std;

//Create Node
struct Node{
    int value;
    Node* left;
    Node* right;

    //Constructor To Intialize A New Node With A Given Value
    Node(int val) : value(val), left(nullptr), right(nullptr){}
};

class binarySearchTree{
    public:
    //Intialize Root
    binarySearchTree() : root(nullptr){}

    //Insert Function
    void insert(int value){
        root = insert(root,value);
    }

    //Delete Function
    void deleteValue(int value){
        root = deleteNode(root, value);
    }

    //Print Function
    void printTree() const {
        printInOrder(root,0);
    }

    private:
    Node* root;

    //Helper Insert Function
    Node* insert(Node* node, int value){
        if(node ==nullptr){
            return new Node(value); //Create New Node If Current One Is Null
        }
        if(value < node -> value){
            node -> left = insert(node -> left, value); //Recursively Move Left If Value Is Smaller
        } else if (value > node -> value){
            node -> right = insert(node -> right, value); //Recursively Move Right If Value Is Larger
        }
        return node;
     }

    //Helper Delete Function 
    Node* deleteNode(Node* node, int value){
        if (node == nullptr) return node;
        if(value < node -> value){
            node -> left = deleteNode(node->left, value); //Recursivly Move To Left Subtree
        } else if (value > node->value){
            node -> right = deleteNode(node->right, value); //Recursively Mode To Right Subtree
        } else{
            //Node With One Child or No Child
            if(node-> left == nullptr){
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node -> right == nullptr){
                Node* temp = node->left;
                delete node;
                return temp; 
            }

            //Node With Two Children
            Node* temp = minValueNode(node->right);
            node->value = temp->value;
            node->right = deleteNode(node->right, temp->value);
        }
        return node;
    }

    //Helper minValueNode Function
    Node* minValueNode(Node* node){
        //Traverse Down Leftmost Node To FInd The Minimum Value
        Node* current = node;
        while(current && current->left != nullptr){
            current = current -> left;
        }
        return current; //Return Smallest Value Node
    }

    //Helper Print Function
    void printInOrder(Node* node, int depth) const {
        //If Node Is Null, Return
        if (node == nullptr) return;

        printInOrder(node->left, depth + 1); //Recursively Move Through Left Subtree

        //Print The Current Node's Value Along With It's Depth
        cout << node->value << ": " << depth << endl;

        printInOrder(node -> right, depth + 1); //Recursively Move Through Right Subtree
    }
};


int main (int argc, char* argv[]){
    //Create BST
    binarySearchTree bst;
    
    int insertNum;
    int deleteNum;
    int value;

    //Read In Number Of Values To Insert
    cin >> insertNum;
    for (int i = 0; i < insertNum; i++) {
        cin >> value;
        bst.insert(value);
    }

    //Read In Number Of Values To Delete
    cin >> deleteNum;
    for (int i = 0; i < deleteNum; i++) {
        cin >> value;
        bst.deleteValue(value);
    }

    //Print Tree
    bst.printTree();

    // End Main
    return 0;
}