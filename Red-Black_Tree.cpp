// Red-Black_Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
template <typename T>
class RBTree {
    struct Node {
        T data;
        bool color;
        Node* left;
        Node* right;
        Node* parent=NULL;
        Node(T data, bool color, Node* left, Node* right, Node* parent) :
          data(data),color(color),left(left),right(right),parent(parent) {};
    };
    Node* root;
    
    void insert(Node*& root, Node*& node) {
        Node* x = root;
        Node* y = NULL;
        while (x != NULL) {
            y = x;
            if (node->data > x->data) {
                x = x->right;
            }
            else {
                x = x->left;    //opportunity warning! node->data= x->data
            }
        }
        node->parent = y;
        if (y != NULL) {
            if (node->data > y->data) {
                y->right = node;
            }
            else {
                y->left = node;
            }
        }
        else {
            root = node;
        }
        node->color = 1;
        inalance(root, node);
    }
    void leftrotate(Node*& root, Node* node) {
        Node* y = node->right;
        node->right = y->left;
        if (y->left != NULL) {
            y->left->parent = node;
        }
        y->parent = node->parent;
        if (node->parent==NULL) {
            root = y;
        }
        else {
            if (node == node->parent->left)
                node->parent->left = y;
            else
                node->parent->right = y;
        }
        y->left = node;
        node->parent = y;
    }
    void rightrotate(Node*& root, Node* node) {
        Node* y = node->left;
        node->left = y->right;
        if (y->right != NULL) {
            y->right->parent = node;
        }
        y->parent = node->parent;
        if (node->parent == NULL) {
            root = y;
        }
        else {
            if (node == node->parent->right)
                node->parent->right = y;
            else
                node->parent->left = y;
        }
        y->right = node;
        node->parent = y;
    }
    void inalance(Node*& root, Node*& node) {
        Node* parent = node->parent;
        while (node != root && parent->color) {
            Node* granf = parent->parent;
            if (granf->left == parent) {
                Node* uncle = granf->right;
                if (uncle!=NULL && uncle->color) {
                    uncle->color = 0;
                    granf->color = 1;
                    parent->color = 0;
                    node = granf;
                    parent = node->parent;
                }
                else {
                    if (parent->right == node) {
                        leftrotate(root,parent);
                        std::swap(parent, node);
                    }
                    rightrotate(root, granf);
                    parent->color = 0;
                    granf->color = 1;
                    break;
                }
            }
            else {
                Node* uncle = granf->left;
                if (uncle != NULL && uncle->color) {
                    uncle->color = 0;
                    granf->color = 1;
                    parent->color = 0;
                    node = granf;
                    parent = node->parent;
                }
                else {
                    if (parent->left == node) {
                        rightrotate(root, parent);
                        std::swap(parent, node);
                    }
                    leftrotate(root, granf);
                    parent->color = 0;
                    granf->color = 1;
                    break;
                }
            }
        }
        root->color = 0;
    }
    void remove(Node*& root, Node* node)
    {
        Node* child, * parent;
        bool color;
        // Ћевый и правый узлы удаленного узла не пусты (не конечные узлы)
        if (node->left != NULL && node->right != NULL)
        {
            Node* replace = node;
            // Ќайти узел-преемник (самый нижний левый узел правого поддерева текущего узла)
            replace = node->right;
            while (replace->left != NULL)
            {
                replace = replace->left;
            }
            // —лучай, когда удаленный узел не €вл€етс€ корневым узлом
            if (node->parent != NULL)
            {
                if (node->parent->left == node)
                    node->parent->left = replace;
                else
                    node->parent->right = replace;
            }
            // —итуаци€ с корневым узлом
            else
                root = replace;
            // child - это правильный узел, который замен€ет узел и €вл€етс€ узлом, который требует последующей корректировки
            // ѕоскольку замена €вл€етс€ преемником, он не может иметь левого дочернего узла
            // јналогично, у узла-предшественника не может быть правого дочернего узла
            child = replace->right;
            parent = replace->parent;
            color = replace->color;

            // ”даленный узел €вл€етс€ родительским узлом замещающего узла (repalce)
            if (parent == node)
                parent = replace;
            else
            {
                // —уществование дочернего узла
                if (child != NULL)
                    child->parent = parent;
                parent->left = child;

                replace->right = node->right;
                node->right->parent = replace;
            }
            replace->parent = node->parent;
            replace->color = node->color;
            replace->left = node->left;
            node->left->parent = replace;
            if (color == 0)
                removeFixUp(root, child, parent);//replace  remove(replace)???

            delete node;
            return;
        }
        //  огда в удаленном узле только левый (правый) узел пуст, найдите дочерний узел удаленного узла
        if (node->left != NULL)
            child = node->left;
        else
            child = node->right;

        parent = node->parent;
        color = node->color;
        if (child)
        {
            child->parent = parent;
        }
        // ”даленный узел не €вл€етс€ корневым узлом
        if (parent)
        {
            if (node == parent->left)
                parent->left = child;
            else
                parent->right = child;
        }
        // ”даленный узел €вл€етс€ корневым узлом
        else {
           
            Node* replace = node;

            replace = node->right;
            if (replace == NULL && node->left == NULL) {
                root->data = NULL;
                root == NULL;
                
                return;
            }
            if (replace == NULL) {
               
                root = root->left;
                delete root->parent;
                root->parent = NULL;
                root->color = 0;
                return;
            }
            while (replace->left != NULL)
            {
                replace = replace->left;
            }
            T sek = root->data;
            root->data = replace->data;
            replace->data = sek;
            remove(sek);
            return;
            
        }

        if (color == 0)
        {
            removeFixUp(root, child, parent);
        }
        delete node;

    }
    void removeFixUp(Node*& root, Node*& node, Node*& parent)
    {
        Node* brother;
        if (parent == NULL) {
            node->color = 0;
            return;
        }
        if (parent->left == node) {
            brother = parent->right;
            if (brother == NULL) { removeFixUp(root, parent, parent->parent); return; }
            if (brother->color == 1)
            {
                brother->color = 0;
                parent->color = 1;
                leftrotate(root, parent);
                brother = parent->right;
            }
            if (brother->color = 0) {
                if ((brother->right == NULL && brother->left == NULL) || (brother->right->color = 0 && brother->left->color == 0)) {
                    parent->color = 0;
                    brother->color = 1;
                    removeFixUp(root, parent, parent->parent);
                }
                if (brother->left&& brother->left->color == 1) {
                    rightrotate(root, brother);

                }
                if (brother->right&& brother->right->color == 1) {
                    brother->color = parent->color;
                    leftrotate(root, parent);
                    brother->right->color = 0;
                    parent->color = 0;

                }
            }
        }
        else {
            brother = parent->left;

            if (brother->color == 1)
            {
                brother->color = 0;
                parent->color = 1;
                rightrotate(root, parent);
                brother = parent->left;
            }
            if (brother->color = 0) {
                if ((brother->left == NULL && brother->right == NULL) || (brother->right->color == 0 && brother->left->color == 0)) {
                    parent->color = 0;
                    brother->color = 1;
                    removeFixUp(root, parent, parent->parent);
                }
                if (brother->right&& brother->right->color == 1) {
                    leftrotate(root, brother);

                }
                if (brother->left&& brother->left->color == 1) {
                    brother->color = parent->color;
                    rightrotate(root, parent);
                    brother->right->color = 0;
                    parent->color = 0;

                }
            }
        }
        //Node* othernode;
        //while ((!node) || node->color == 0 && node != root)
        //{
        //    if (parent->left == node)
        //    {
        //        othernode = parent->right;
        //        if (othernode->color == 1)
        //        {
        //            othernode->color = 0;
        //            parent->color = 1;
        //            leftrotate(root, parent);
        //            othernode = parent->right;
        //        }
        //        else
        //        {   

        //            if (!(othernode->right) || othernode->right->color == 0  )//HERE MISTAKE!!!!
        //            {
        //                othernode->left->color = 0;
        //                othernode->color = 1;
        //                rightrotate(root, othernode);
        //                othernode = parent->right;
        //            }
        //            
        //                
        //                    othernode->color = parent->color;
        //                    parent->color = 0;
        //                    othernode->right->color = 0;
        //                    leftrotate(root, parent);
        //                    node = root;
        //                    break;
        //                
        //        }
        //    }
        //    else
        //    {
        //        othernode = parent->left;
        //        if (othernode->color == 1)
        //        {
        //            othernode->color = 0;
        //            parent->color = 1;
        //            rightrotate(root, parent);
        //            othernode = parent->left;
        //        }
        //        if ((!othernode->left || othernode->left->color == 0) && (!othernode->right || othernode->right->color == 0))
        //        {
        //            othernode->color = 1;
        //            node = parent;
        //            parent = node->parent;
        //        }
        //        else
        //        {
        //            if (!(othernode->left) || othernode->left->color == 0)
        //            {
        //                othernode->right->color = 0;
        //                othernode->color = 1;
        //                leftrotate(root, othernode);
        //                othernode = parent->left;
        //            }
        //            othernode->color = parent->color;
        //            parent->color = 0;
        //            othernode->left->color = 0;
        //            rightrotate(root, parent);
        //            node = root;
        //            break;
        //        }
        //    }
        //}
        //if (node)
        //    node->color = 0;
    }
    void destory(Node*& node)
    {
        if (node == NULL)
            return;
        destory(node->left);
        destory(node->right);
        delete node;
        node = nullptr;
    }
    Node* search(Node* node, T key) const
    {
        if (node == NULL || node->data == key)
            return node;
        else
            if (key > node->data)
                return search(node->right, key);
            else
                return search(node->left, key);
    }

    bool color(Node* t) {
        if (t == NULL) {
            return 0;
        }
        return t->color;
    }
    void inorder(Node* t)
    {
        if (t == NULL)
            return;
        inorder(t->left);
        std::cout << t->data << " ";
        inorder(t->right);
    }
public:
    void remove(T key)
    {
        Node* deletenode = search(root, key);
        if (deletenode != NULL)
            remove(root, deletenode);
    }
    RBTree() :root(NULL) {
        root = nullptr;
    }
    
    void insert(T val) {
        Node* d=new Node(val,1,NULL,NULL,NULL);
        insert(root, d);
    }
    void display() {
        inorder(root);
        std::cout << "\n";
        
    }

};

int main()
{
    RBTree<int> tree;
    
    auto begin = std::chrono::steady_clock::now();
    for (int i = 1000000; i >=0; --i) {
        tree.insert(i);
    }
    for (int i = 0; i < 1000000; ++i) {
        tree.remove(i);
    }

    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms\n";
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
