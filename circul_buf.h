
#ifndef CIRCULAR_BUFFER_CIRCUL_BUF_H
#define CIRCULAR_BUFFER_CIRCUL_BUF_H
template<class Iter>
class circul_iterator: public std::iterator<
        std::random_access_iterator_tag,
        Iter,
        int,
        Iter*,
        Iter&
> {
    friend class circul_buf;

public:
    typedef Iter iterator_type;
    typedef std::random_access_iterator_tag iterator_category;
    typedef int difference_type;
    typedef iterator_type& reference;
    typedef iterator_type* pointer;

    pointer value;
    circul_buf<T> buf;

private:
    circul_iterator(circul_buf &buf, pointer p);

public:
    circul_iterator(const circul_iterator& it);

    circul_iterator& operator++();

    circul_iterator& operator--();

    circul_iterator operator+(int n) ;

    circul_iterator& operator+=(int n);

    circul_iterator operator-=(int n);

    circul_iterator operator-(int n);

    iterator_type& operator*();

    iterator_type* operator->() const;

    bool operator==(circul_iterator const& other);

    bool operator!=(circul_iterator const& other);

    bool operator>(circul_iterator const& other) const;

    bool operator>=(circul_iterator const& other) const;

    bool operator<(circul_iterator const& other) const;

    bool operator<=(circul_iterator const& other) const;
    difference_type operator-(circul_iterator const& other) const;
};
template <typename T>
class circul_buf {
private:
    friend class circul_iterator;

public:
    typedef T* pointer_t;
    typedef T value_t;

    circul_buf();

    circul_buf(unsigned n);

    ~circul_buf();

    typedef circul_iterator<T> iterator;
    typedef circul_iterator<const T> const_iterator;

    iterator begin();

    iterator end();

    const_iterator cbegin();

    const_iterator cend();

    void push_back(value_t new_elem);

    void push_front(value_t new_elem);

    void pop_front();

    void pop_back();

    value_t get_start();
    value_t get_end();

    value_t& operator[](const unsigned& n);

    const value_t& operator[](const unsigned& n) const;

    void change_capasity(unsigned n);

    unsigned size();


private:
    pointer_t buffer;
    unsigned size_alloc;
    unsigned count_elem;
    pointer_t start;
    pointer_t end_;
};


#endif //CIRCULAR_BUFFER_CIRCUL_BUF_H
