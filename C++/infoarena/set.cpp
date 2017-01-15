#include <bits/stdc++.h>
#include <pthread.h>

using namespace std;

template<typename T>
class Set {
    public:
        Set() {
            srand(time(0));
            Root = nil = new Node(-1, 0, T(), 0, 0);
            nil->left = nil->right = nil;
        }

        int size() const {
            return Root->size;
        }

        bool count(const T &value) {
            return (Find(Root, value) != nil);
        }

        void insert(const T &value) {
            if (count(value))
                return;
            return Insert(Root, value);
        }

        void erase(const T &value) {
            //if (count(value) == 0)
            //    return;
            return Erase(Root, value);
        }

        T operator[](int index) {
            ++index;
            if (index > Root->size)
                throw 1337;
            return kth(Root, index);
        }

    private:
        struct Node {
            int priority, size;
            T value;
            Node *left, *right;

            Node(int priority, int size, const T &value, Node *left, Node *right):
                priority(priority),
                size(size),
                value(value),
                left(left),
                right(right) {
            }
        };

        Node *Root, *nil;

        inline int random() const {
            return (rand() << 16) ^ rand();
        }

        void Update(Node *current) {
            if (current == nil)
                return;
            current->size = current->left->size + current->right->size + 1;
        }

        void RotateLeft(Node *&current) {
            Node *temp = current->left;
            current->left = temp->right;
            temp->right = current;
            current = temp;
        }

        void RotateRight(Node *&current) {
            Node *temp = current->right;
            current->right = temp->left;
            temp->left = current;
            current = temp;
        }

        void Balance(Node *&current) {
            if (current == nil)
                return;
            if (current->left->priority >= current->right->priority && current->left->priority > current->priority) {
                RotateLeft(current);
                Update(current->right);
            } else if (current->left->priority < current->right->priority && current->right->priority > current->priority) {
                RotateRight(current);
                Update(current->left);
            }
            Update(current);
        }

        void Insert(Node *&current, const T &value) {
            if (current == nil) {
                current = new Node(random(), 1, value, nil, nil);
                return;
            }
            if (value < current->value)
                Insert(current->left, value);
            else
                Insert(current->right, value);
            Update(current);
            Balance(current);
        }

        T kth(Node *current, int pos) {
            if (current == nil)
                throw 1337;
            if (pos == current->left->size + 1)
                return current->value;
            else if (pos <= current->left->size)
                return kth(current->left, pos);
            return kth(current->right, pos - current->left->size - 1);
        }

        void Erase(Node *&current, const T &value) {
            if (current == nil)
                return;

            if (current->value == value) {
                if (current->left == nil && current->right == nil) {
                    delete current;
                    current = nil;
                    return;
                }

                if (current->left->priority >= current->right->priority) {
                    RotateLeft(current);
                    Update(current->right);
                    Update(current);
                    Erase(current->right, value);
                } else {
                    RotateRight(current);
                    Update(current->left);
                    Update(current);
                    Erase(current->left, value);
                }
            } else if (value < current->value)
                Erase(current->left, value);
            else
                Erase(current->right, value);
            Update(current);
            Balance(current);
        }

        Node *Find(Node *current, const T &value) {
            if (current == nil || current->value == value)
                return current;

            if (value < current->value)
                return Find(current->left, value);
            return Find(current->right, value);
        }
};

int main() {
    //ifstream cin("hashuri.in");
    ofstream cout("hashuri.out");

    int N, op, x;
    Set<int> S;

    srand(time(0));
    for (int i = 0; i < 1000000; ++i) {
        S.insert((rand() << 16) ^ rand());
    }

    for (int i = 0; i < S.size(); ++i)
        cout << S[i];

    //cerr << RAND_MAX;
    return 0;
}
