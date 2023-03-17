template<class Iterator, class Predicate>
bool all_of (Iterator first, Iterator last, Predicate pred)
{
    while (first!=last) {
        if (!pred(*first)) return false;
        ++first;
    }
    return true;
}

template<class Iterator, class Predicate>
bool any_of (Iterator first, Iterator last, Predicate pred)
{
    while (first!=last) {
        if (pred(*first)) return true;
        ++first;
    }
    return false;
}

template<class Iterator, class Predicate>
bool none_of (Iterator first, Iterator last, Predicate pred)
{
    while (first!=last) {
        if (pred(*first)) return false;
        ++first;
    }
    return true;
}

template<class Iterator, class Predicate>
bool one_of (Iterator first, Iterator last, Predicate pred)
{
    bool flag = false;
    while (first!=last) {
        if (pred(*first)) {
            if (flag == false)
                flag = true;
            else
                return false;
        }
        ++first;
    }
    return flag;
}

template <class Iterator, class Predicate>
bool is_sorted (Iterator first, Iterator last, Predicate pred)
{
    if (first==last) return true;
    Iterator next = first;
    while (next!=last) {
        ++next;
        if (!pred(*first, *next))
            return false;
        ++first;
    }
    return true;
}

template <class Iterator, class Predicate>
bool is_partitioned (Iterator first, Iterator last, Predicate pred)
{
    while (first!=last && pred(*first)) {
        ++first;
    }
    while (first!=last) {
        if (pred(*first)) return false;
        ++first;
    }
    return true;
}

template<class Iterator, class T>
Iterator find_not (Iterator first, Iterator last, const T& value)
{
    while (first!=last) {
        if ((*first) != value) return first;
        ++first;
    }
    return last;
}

template<class Iterator, class T>
Iterator find_backward (Iterator first, Iterator last, const T& value)
{
    while (last!=first) {
        if ((*last) == value) return last;
        --last;
    }
    return first;
}

template<class Iterator, class Predicate>
bool is_palindrome(Iterator first, Iterator last, Predicate pred) {
    while (std::distance(first, last) != 0) {
        if (pred(*last) != pred(*first))
            return false;
        --last; ++first;
    }
    return true;
}