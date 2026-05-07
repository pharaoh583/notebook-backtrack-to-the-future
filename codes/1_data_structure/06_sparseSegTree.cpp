class Node {
public:
    Node* left;
    Node* right;
    int v, l, r; 
    Node(int val, int l, int r) : v(val), l(l), r(r) {
        left = NULL;
        right = NULL;
    }
};
 
class SegTree {
private: 
    Node* root;
    
    int query(Node* node, int l, int r) {
        if(node == NULL) return 0;
        if(l > r) return 0;
        if(l <= node->l and node->r <= r) return node->v;
        int m = (node->r + node->l)/2;
        return query(node->left, l, min(m, r)) +
               query(node->right, max(l, m + 1), r);
    }
    
    void update(Node* node, int pos, int v) {
        if(node->l == node->r) {
            node->v += v; return;
        }
        int m = (node->r + node->l)/2;
        if(node->l <= pos and pos <= m) {
            if(node->left == NULL) node->left = new Node(0, node->l, m);
            update(node->left, pos, v);
        }
        else {
            if(node->right == NULL) node->right = new Node(0, m + 1, node->r);
            update(node->right, pos, v);
        }
        
        node->v = 0;
        if(node->left != NULL) node->v += node->left->v;
        if(node->right != NULL) node->v += node->right->v;
    }
public:
    SegTree(int l, int r) {
        root = new Node(0, l, r);
    }
    int query(int l, int r) {
        return query(root, l, r);
    }
    void update(int pos, int v) {
        update(root, pos, v);
    }
};
