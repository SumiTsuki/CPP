#pragma once
template <class K>
struct BinarySearchTreeNode
{
    BinarySearchTreeNode<K> *_left;
    BinarySearchTreeNode<K> *_right;
    K _key;
    BinarySearchTreeNode(const K &key)
        : _left(nullptr), _right(nullptr), _key(key)
    {
    }
};
template <class K>
class BinarySearchTree
{
public:
    bool Find(const K &key)
    {
        BinarySearchTreeNode<K> *cur = _root;
        while (cur)
        {
            if (cur->_key < key)
            {
                cur = cur->_right;
            }
            else if (cur->_key > key)
            {
                cur = cur->_left;
            }
            else
            {
                return true;
            }
        }
        return false;
    }
    bool Insert(const K &key)
    {
        if (_root == nullptr)
        {
            _root = new BinarySearchTreeNode<K>(key);
            return true;
        }
        BinarySearchTreeNode<K> *parent = nullptr;
        BinarySearchTreeNode<K> *cur = _root;
        while (cur)
        {
            if (cur->_key < key)
            {
                parent = cur;
                cur = cur->_right;
            }
            else if (cur->_key > key)
            {
                parent = cur;
                cur = cur->_left;
            }
            else
            {
                return false;
            }
        }
        cur = new BinarySearchTreeNode<K>(key);
        if (parent->_key < key)
        {
            parent->_right = cur;
        }
        else
        {
            parent->_left = cur;
        }
        return true;
    }
    bool Erase(const K &key)
    {
        BinarySearchTreeNode<K> *parent = nullptr;
        BinarySearchTreeNode<K> *cur = _root;
        while (cur)
        {
            if (cur->_key < key)
            {
                parent = cur;
                cur = cur->_right;
            }
            else if (cur->_key > key)
            {
                parent = cur;
                cur = cur->_left;
            }
            else
            {
                if (cur->_left == nullptr)
                {
                    if (cur == _root)
                    {
                        _root = cur->_right;
                    }
                    else
                    {
                        if (cur == parent->_left)
                        {
                            parent->_left = cur->_right;
                        }
                        else
                        {
                            parent->_right = cur->_right;
                        }
                    }
                    delete cur;
                }
                else if (cur->_right == nullptr)
                {
                    if (cur == parent->_left)
                    {
                        parent->_left = cur->_left;
                    }
                    else
                    {
                        parent->_right = cur->_left;
                    }
                    delete cur;
                }
                else
                {
                    BinarySearchTreeNode<K> *rightMinParent = cur;
                    BinarySearchTreeNode<K> *rightMin = cur->_right;
                    while (rightMin->_left)
                    {
                        rightMinParent = rightMin;
                        rightMin = rightMin->_left;
                    }
                    cur->_key = cur->_key ^ rightMin->_key;
                    rightMin->_key = cur->_key ^ rightMin->_key;
                    cur->_key = cur->_key ^ rightMin->_key;
                    if (rightMinParent->_left == rightMin)
                    {
                        rightMinParent->_left = rightMin->_right;
                    }
                    else
                    {
                        rightMinParent->_right = rightMin->_right;
                    }
                    delete true;
                }
            }
            return false;
        }
    }
    void InOrder()
    {
        _InOrder(_root);
    }

private:
    void _InOrder(BinarySearchTreeNode<K> *root)
    {
        if (root == nullptr)
        {
            return;
        }
        _InOrder(root->_left);
        std::cout << root->_key << " ";
        _InOrder(root->_right);
    }
    BinarySearchTreeNode<K> *_root = nullptr;
};