#pragma once
#include <iostream>
#include <assert.h>
template <class T1, class T2>
struct pair
{
    T1 first;
    T2 second;
    pair(T1 _first, T2 _second)
        : first(_first), second(_second)
    {
    }
};
template <class K, class V>
struct AVLTreeNode
{
    AVLTreeNode<K, V> *_left;
    AVLTreeNode<K, V> *_right;
    AVLTreeNode<K, V> *_parent;
    pair<K, V> _kv;
    int _bf; // balance factor
    AVLTreeNode(const pair<K, V> &kv)
        : _left(nullptr), _right(nullptr), _parent(nullptr), _kv(kv), _bf(0)
    {
    }
};
template <class K, class V>
class AVLTree
{
public:
    bool Insert(const pair<K, V> &kv)
    {
        if (_root == nullptr)
        {
            _root = new AVLTreeNode<K, V>(kv);
            return true;
        }
        AVLTreeNode<K, V> *parent = nullptr;
        AVLTreeNode<K, V> *cur = _root;
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
        cur = new AVLTreeNode<K, V>(kv);
        if (parent->_kv.first < kv.first)
        {
            parent->_right = cur;
        }
        else
        {
            parent->_left = cur;
        }
        cur->_parent = parent;
        // update balance factor
        while (parent)
        {
            if (cur == parent->_left)
            {
                --parent->_bf;
            }
            else
            {
                ++parent->_bf;
            }
            if (parent->_bf == 0)
            {
                break;
            }
            else if (parent->_bf == 1 || parent->_bf == -1)
            {
                // continue update
                cur = parent;
                parent = parent->_parent;
            }
            else if (parent->_bf == 2 || parent->_bf == -2)
            {
                // balance
                if (parent->_bf == -2 && cur->_bf == -1)
                {
                    RotateR(parent);
                }

                else if (parent->_bf == 2 && cur->_bf == 1)
                {
                    RotateL(parent);
                }
                else if (parent->_bf == 2 && cur->_bf == -1)
                {
                    RotateRL(parent);
                }
                else if (parent->_bf == -2 && cur->_bf == 1)
                {
                    RotateLR(parent);
                }
                break;
            }
            else
            {
                // cannot occur this situation
                assert(false);
            }
        }
        return true;
    }
    AVLTreeNode<K, V> *Find(const K &key)
    {
        AVLTreeNode<K, V> *cur = _root;
        while (cur)
        {
            if (cur->_kv.first < key)
            {
                cur = cur->_right;
            }
            else if (cur->_kv.first > key)
            {
                cur = cur->_left;
            }
            else
            {
                return cur;
            }
        }
        return nullptr;
    }
    void InOrder()
    {
        _InOrder(_root);
        std::cout << std::endl;
    }
    void RotateR(AVLTreeNode<K, V> *parent)
    {
        AVLTreeNode<K, V> *subL = parent->_left;
        AVLTreeNode<K, V> *subLR = subL->_right;
        parent->_left = subLR;
        if (subLR)
            subLR->_parent = parent;
        subL->_right = parent;
        AVLTreeNode<K, V> *ppNode = parent->_parent;
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
        parent->_bf = subL->_bf = 0;
    }
    void RotateL(AVLTreeNode<K, V> *parent)
    {
        AVLTreeNode<K, V> *subR = parent->_right;
        AVLTreeNode<K, V> *subRL = subR->_left;

        parent->_right = subRL;
        if (subRL)
            subRL->_parent = parent;

        subR->_left = parent;
        AVLTreeNode<K, V> *ppNode = parent->_parent;

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
        parent->_bf = subR->_bf = 0;
    }
    void RotateRL(AVLTreeNode<K, V> *parent)
    {
        AVLTreeNode<K, V> *subR = parent->_right;
        AVLTreeNode<K, V> *subRL = subR->_left;
        int bf = subRL->_bf;
        RotateR(subR);
        RotateL(parent);
        subRL->_bf = 0;
        if (bf == 1)
        {
            subR->_bf = 0;
            parent->_bf = -1;
        }
        else if (bf == -1)
        {
            parent->_bf = 0;
            subR->_bf = 1;
        }
        else
        {
            parent->_bf = 0;
            subR->_bf = 0;
        }
    }
    void RotateLR(AVLTreeNode<K, V> *parent)
    {
        AVLTreeNode<K, V> *subL = parent->_left;
        AVLTreeNode<K, V> *subLR = subL->_right;
        int bf = subLR->_bf;
        RotateL(parent->_left);
        RotateR(parent);
        if (bf == -1)
        {
            subLR->_bf = 0;
            subL->_bf = 0;
            parent->_bf = 1;
        }
        else if (bf == 1)
        {
            subLR->_bf = 0;
            subL->_bf = -1;
            parent->_bf = 0;
        }
        else if (bf == 0)
        {
            subLR->_bf = 0;
            subL->_bf = 0;
            parent->_bf = 0;
        }
        else
        {
            assert(false);
        }
    }
    bool IsBalance()
    {
        return _IsBalance(_root);
    }
    int Height()
    {
        return _Height(_root);
    }
    int Size()
    {
        return _Size(_root);
    }

private:
    void _InOrder(AVLTreeNode<K, V> *root)
    {
        if (root == nullptr)
        {
            return;
        }
        _InOrder(root->_left);
        std::cout << root->_kv.first << ":" << root->_kv.second << std::endl;
        _InOrder(root->_right);
    }

    int _Size(AVLTreeNode<K, V> *root)
    {
        return root == nullptr ? 0 : _Size(root->_left) + _Size(root->_right) + 1;
    }

    int _Height(AVLTreeNode<K, V> *root)
    {
        if (root == nullptr)
            return 0;
        return std::max(_Height(root->_left), _Height(root->_right)) + 1;
    }

    bool _IsBalance(AVLTreeNode<K, V> *root)
    {
        if (root == nullptr)
            return true;
        int leftHeight = _Height(root->_left);
        int rightHeight = _Height(root->_right);
        if (std::abs(leftHeight - rightHeight) >= 2)
        {
            std::cout << root->_kv.first << std::endl;
            return false;
        }
        if (rightHeight - leftHeight != root->_bf)
        {
            std::cout << root->_kv.first << std::endl;
            return false;
        }
        return _IsBalance(root->_left) && _IsBalance(root->_right);
    }

private:
    AVLTreeNode<K, V> *_root = nullptr;
};