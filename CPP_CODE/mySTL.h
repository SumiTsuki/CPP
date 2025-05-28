#pragma once
#include <iostream>
#include <stdlib.h>
#include <assert.h>
namespace mySTL
{
    //--------- Iterator ---------
    template <class Iterator, class Ref, class Ptr>
    struct ReverseIterator
    {
        Iterator _it;
        ReverseIterator(Iterator it)
            : _it(it)
        {
        }
        Ref operator*()
        {
            Iterator tmp = _it;
            return *(--tmp);
        }
        Ptr operator->()
        {
            return &(operator*());
        }
        ReverseIterator<Iterator, Ref, Ptr> &operator++()
        {
            --_it;
            return *this;
        }
        ReverseIterator<Iterator, Ref, Ptr> &operator--()
        {
            ++_it;
            return *this;
        }
        bool operator!=(const ReverseIterator<Iterator, Ref, Ptr> &s)
        {
            return _it != s._it;
        }
    };
    //--------- vector ---------
    template <class T>
    class vector
    {
    public:
        typedef T *iterator;
        typedef const T *const_iterator;
        typedef ReverseIterator<iterator, T &, T *> reverse_iterator;
        typedef ReverseIterator<const_iterator, const T &, const T *> const_reverse_iterator;
        vector()
        {
        }
        vector(const vector<T> &v)
        {
            reserve(v.capacity());
            for (auto &e : v)
            {
                push_back(e);
            }
        }
        vector(std::initializer_list<T> il)
        {
            reserve(il.size());
            for (auto &e : il)
            {
                push_back(e);
            }
        }

        ~vector()
        {
            delete[] _start;
            _start = _finish = _endofstorage = nullptr;
        }

        iterator begin()
        {
            return _start;
        }

        iterator end()
        {
            return _finish;
        }

        const_iterator begin() const
        {
            return _start;
        }

        const_iterator end() const
        {
            return _finish;
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }

        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }

        size_t size() const
        {
            return _finish - _start;
        }

        bool empty()
        {
            return _start == _finish;
        }

        T &operator[](size_t pos)
        {
            assert(pos < size());
            return _start[pos];
        }

        const T &operator[](size_t pos) const
        {
            assert(pos < size());
            return _start[pos];
        }

        size_t capacity() const
        {
            return _endofstorage - _start;
        }

        void reserve(size_t n)
        {
            if (n > capacity())
            {
                T *tmp = new T[n];
                size_t old_size = size();
                for (size_t i = 0; i < old_size; i++)
                {
                    tmp[i] = _start[i];
                }
                delete[] _start;
                _start = tmp;
                _finish = tmp + old_size;
                _endofstorage = tmp + n;
            }
        }

        void resize(size_t n, const T &val = T())
        {
            if (n > size())
            {
                reserve(n);
                while (_finish < _start + n)
                {
                    *_finish = val;
                    ++_finish;
                }
            }
            else
            {
                _finish = _start + n;
            }
        }

        void push_back(const T &val)
        {
            // if (_finish == _endofstorage)
            //{
            //	reserve(capacity() == 0 ? 4 : capacity() * 2);
            // }
            //*_finish = val;
            //++_finish;
            insert(end(), val);
        }

        void pop_back()
        {
            erase(end() - 1);
        }

        void insert(iterator pos, const T &val)
        {
            assert(pos >= _start);
            assert(pos <= _finish);
            if (_finish == _endofstorage)
            {
                size_t len = pos - _start;
                reserve(capacity() == 0 ? 4 : capacity() * 2);
                pos = _start + len;
            }
            iterator it = _finish - 1;
            while (it >= pos)
            {
                *(it + 1) = *it;
                --it;
            }
            *pos = val;
            ++_finish;
        }

        iterator erase(iterator pos)
        {
            assert(pos >= _start);
            assert(pos < _finish);
            iterator it = pos + 1;
            while (it < _finish)
            {
                *(it - 1) = *it;
                ++it;
            }
            --_finish;
            return pos;
        }

    private:
        iterator _start = nullptr;
        iterator _finish = nullptr;
        iterator _endofstorage = nullptr;
    };
    //--------- list ---------
    template <class T>
    struct ListNode
    {
        ListNode<T> *_next;
        ListNode<T> *_prev;
        T _data;
        ListNode(const T &x = T())
            : _next(nullptr),
              _prev(nullptr),
              _data(x)
        {
        }
    };

    template <class T, class Ref, class Ptr>
    struct ListIterator
    {
        typedef ListNode<T> Node;
        typedef ListIterator<T, Ref, Ptr> Self;
        Node *_node;
        ListIterator(Node *node)
            : _node(node)
        {
        }
        Ref operator*()
        {
            return _node->_data;
        }
        Ptr operator->()
        {
            return &_node->_data;
        }
        Self &operator++() //++it
        {
            _node = _node->_next;
            return *this;
        }
        Self operator++(int) // it++
        {
            Self tmp(*this);
            _node = _node->_next;
            return tmp;
        }
        Self &operator--()
        {
            _node = _node->_prev;
            return *this;
        }
        Self operator--(int)
        {
            Self tmp(*this);
            _node = _node->_prev;
            return tmp;
        }
        bool operator!=(const Self &it)
        {
            return _node != it._node;
        }
        bool operator==(const Self &it)
        {
            return _node == it._node;
        }
    };

    template <class T>
    class list
    {
        typedef ListNode<T> Node;

    public:
        typedef ListIterator<T, T &, T *> iterator;
        typedef ListIterator<T, const T &, const T *> const_iterator;
        typedef ReverseIterator<iterator, T &, T *> reverse_iterator;
        typedef ReverseIterator<const_iterator, const T &, const T *> const_reverse_iterator;
        list()
        {
            empty_init();
        }
        list(const list<T> &lt)
        {
            empty_init();
            for (auto &e : lt)
            {
                push_back(e);
            }
        }
        list(std::initializer_list<T> il)
        {
            empty_init();
            for (auto &e : il)
            {
                push_back(e);
            }
        }
        ~list()
        {
            clear();
            delete _head;
            _head = nullptr;
        }

        iterator begin()
        {
            return _head->_next;
        }
        iterator end()
        {
            return _head;
        }
        const_iterator begin() const
        {
            return _head->_next;
        }
        const_iterator end() const
        {
            return _head;
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }
        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }

        list<T> &operator=(list<T> &lt)
        {
            swap(lt);
            return *this;
        }

        void empty_init()
        {
            _head = new Node;
            _head->_next = _head;
            _head->_prev = _head;
            _size = 0;
        }
        void swap(list<T> &lt)
        {
            std::swap(_head, lt._head);
            std::swap(_size, lt._size);
        }
        void clear()
        {
            iterator it = begin();
            while (it != end())
            {
                it = erase(it);
            }
        }
        void push_back(const T &x)
        {
            insert(end(), x);
        }
        void push_front(const T &x)
        {
            insert(begin(), x);
        }
        void pop_back()
        {
            erase(--end());
        }
        void pop_front()
        {
            erase(begin());
        }
        void insert(iterator pos, const T &val)
        {
            Node *cur = pos._node;
            Node *newnode = new Node(val);
            Node *prev = cur->_prev;
            prev->_next = newnode;
            newnode->_prev = prev;
            newnode->_next = cur;
            cur->_prev = newnode;
            _size++;
        }
        iterator erase(iterator pos)
        {
            Node *cur = pos._node;
            Node *prev = cur->_prev;
            Node *next = cur->_next;
            prev->_next = next;
            next->_prev = prev;
            delete cur;
            _size--;
            return iterator(next);
        }
        size_t size() const
        {
            return _size;
        }
        bool empty()
        {
            return _size == 0;
        }

    private:
        Node *_head;
        size_t _size;
    };
    //--------- stack ---------
    // stack<int,vector<int>> st;
    // stack<int,list<int>> st;
    template <class T, class Container>
    class stack
    {
    public:
        void push(const T &x)
        {
            _con.push_back(x);
        }
        void pop()
        {
            _con.pop_back();
        }
        size_t size()
        {
            return _con.size();
        }
        bool empty()
        {
            return _con.empty();
        }
        const T &top()
        {
            return _con.back();
        }

    private:
        Container _con;
    };
    //--------- queue ---------
    template <class T>
    class queue
    {
    public:
        queue()
        {
        }
        void push(const T &x)
        {
            _c.push_back(x);
        }
        void pop()
        {
            _c.pop_front();
        }
        T &back() { return _c.back(); }
        const T &back() const { return _c.back(); }
        T &front() { return _c.front(); }
        const T &front() const { return _c.front(); }
        size_t size() const { return _c.size(); }
        bool empty() const { return _c.empty(); }

    private:
        list<T> _c;
    };
    //--------- less ---------
    template <class T>
    class less
    {
    public:
        bool operator()(const T &left, const T &right)
        {
            return left < right;
        }
    };
    //--------- Greater ---------
    template <class T>
    class greater
    {
    public:
        bool operator()(const T &left, const T &right)
        {
            return left > right;
        }
    };
    //--------- priority_queue ---------
    template <class T, class Container = vector<T>, class Compare = less<T>>
    class priority_queue
    {
    public:
        void swap(int &left, int &right)
        {
            left = left ^ right;
            right = left ^ right;
            left = left ^ right;
        }
        void adjust_up(size_t child)
        {
            Compare com;
            size_t parent = (child - 1) / 2;
            while (child > 0)
            {
                if (com(_con[parent], _con[child]))
                {
                    swap(_con[child], _con[parent]);
                    child = parent;
                    parent = (child - 1) / 2;
                }
                else
                {
                    break;
                }
            }
        }
        void adjust_down(size_t parent)
        {
            Compare com;
            size_t child = parent * 2 + 1;
            while (child < _con.size())
            {
                if (child + 1 < _con.size() && com(_con[child], _con[child + 1]))
                {
                    ++child;
                }
                if (com(_con[parent], _con[child]))
                {
                    swap(_con[child], _con[parent]);
                    parent = child;
                    child = parent * 2 + 1;
                }
                else
                {
                    break;
                }
            }
        }
        void push(const T &x)
        {
            _con.push_back(x);
            adjust_up(_con.size() - 1);
        }
        void pop()
        {
            swap(_con[0], _con[_con.size() - 1]);
            _con.pop_back();
            adjust_down(0);
        }
        bool empty()
        {
            return _con.empty();
        }
        size_t size()
        {
            return _con.size();
        }
        const T &top()
        {
            return _con[0];
        }

    private:
        Container _con;
    };

}