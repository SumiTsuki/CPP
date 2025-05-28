#pragma once
template <class K, class V>
struct pair
{
    K first;
    V second;
    pair(K _first, V _second)
        : first(_first), second(_second)
    {
    }
};
enum Color
{
    RED,
    BLACK
};
template <class K, class V>
struct RBTreeNode
{
    RBTreeNode<K, V> *_left;
    RBTreeNode<K, V> *_right;
    RBTreeNode<K, V> *_parent;
    pair<K, V> _kv;
    Color _col;
    RBTreeNode(const pair<K, V> &kv)
        : _left(nullptr), _right(nullptr), _parent(nullptr), _kv(kv), _col(RED)
    {
    }
};
template <class K, class V>
class RBTree
{
public:
    bool Insert(const pair<K, V> &kv)
    {
        if (_root == nullptr)
        {
            _root = new RBTreeNode<K, V>(kv);
            _root->_col = BLACK;
            return true;
        }
        RBTreeNode<K, V> *parent = nullptr;
        RBTreeNode<K, V> *cur = _root;
        while (cur)
        {
            if (cur->_kv.first < kv.first)
            {
                parent = cur;
                cur = cur->_right;
            }
            else if (cur->_kv.first > kv.first)
            {
                parent = cur;
                cur = cur->_left;
            }
            else
            {
                return false;
            }
        }
        cur = new RBTreeNode<K, V>(kv);
        cur->_col = RED;
        if (parent->_kv.first < kv.first)
        {
            parent->_right = cur;
        }
        else
        {
            parent->_left = cur;
        }
        cur->_parent = parent;
        while (parent && parent->_col == RED)
        {
            RBTreeNode<K, V> *grandfather = parent->_parent;
            if (parent == grandfather->_left)
            {
                RBTreeNode<K, V> *uncle = grandfather->_right;
                if (uncle && uncle->_col == RED)
                {
                    parent->_col = uncle->_col = BLACK;
                    grandfather->_col = RED;
                    cur = grandfather;
                    parent = cur->_parent;
                }
                else
                {
                    if (cur == parent->_left)
                    {
                        RotateR(grandfather);
                        parent->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    else
                    {
                        RotateL(parent);
                        RotateR(grandfather);
                        cur->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    break;
                }
            }
            else
            {
                RBTreeNode<K, V> *uncle = grandfather->_left;
                if (uncle && uncle->_col == RED)
                {
                    parent->_col = uncle->_col = BLACK;
                    grandfather->_col = RED;
                    cur = grandfather;
                    parent = cur->_parent;
                }
                else
                {
                    if (cur == parent->_right)
                    {
                        RotateL(grandfather);
                        parent->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    else
                    {
                        RotateR(parent);
                        RotateL(grandfather);
                        cur->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    break;
                }
            }
        }
        _root->_col = BLACK;
        return true;
    }
    void RotateR(RBTreeNode<K, V> *parent)
    {
        RBTreeNode<K, V> *subL = parent->_left;
        RBTreeNode<K, V> *subLR = subL->_right;
        parent->_left = subLR;
        if (subLR)
            subLR->_parent = parent;
        subL->_right = parent;
        RBTreeNode<K, V> *ppNode = parent->_parent;
        parent->_parent = subL;
        if (parent == _root)
        {
            _root = subL;
            _root->_parent = nullptr;
        }
        else
        {
            if (ppNode->_left == parent)
            {
                ppNode->_left = subL;
            }
            else
            {
                ppNode->_right = subL;
            }
            subL->_parent = ppNode;
        }
    }
    void RotateL(RBTreeNode<K, V> *parent)
    {
        RBTreeNode<K, V> *subR = parent->_right;
        RBTreeNode<K, V> *subRL = subR->_left;
        parent->_right = subRL;
        if (subRL)
            subRL->_parent = parent;
        subR->_left = parent;
        RBTreeNode<K, V> *ppNode = parent->_parent;
        parent->_parent = subR;
        if (parent == _root)
        {
            _root = subR;
            _root->_parent = nullptr;
        }
        else
        {
            if (ppNode->_right == parent)
            {
                ppNode->_right = subR;
            }
            else
            {
                ppNode->_left = subR;
            }
            subR->_parent = ppNode;
        }
    }
    void InOrder()
    {
        _InOrder(_root);
        std::cout << std::endl;
    }
    bool IsBalance()
    {
        if (_root->_col == RED)
        {
            return false;
        }
        int refNum = 0;
        RBTreeNode<K, V> *cur = _root;
        while (cur)
        {
            if (cur->_col == BLACK)
            {
                ++refNum;
            }

            cur = cur->_left;
        }

        return Check(_root, 0, refNum);
    }

private:
    bool Check(RBTreeNode<K, V> *root, int blackNum, const int refNum)
    {
        if (root == nullptr)
        {
            // cout << blackNum << endl;
            if (refNum != blackNum)
            {
                std::cout << "The paths with an unequal number of black nodes." << std::endl;
                return false;
            }
            return true;
        }

        if (root->_col == RED && root->_parent->_col == RED)
        {
            std::cout << root->_kv.first << "There are consecutive red nodes." << std::endl;
            return false;
        }
        if (root->_col == BLACK)
        {
            blackNum++;
        }
        return Check(root->_left, blackNum, refNum) && Check(root->_right, blackNum, refNum);
    }

    void _InOrder(RBTreeNode<K, V> *root)
    {
        if (root == nullptr)
        {
            return;
        }
        _InOrder(root->_left);
        std::cout << root->_kv.first << ":" << root->_kv.second << std::endl;
        _InOrder(root->_right);
    }

private:
    RBTreeNode<K, V> *_root = nullptr;
};