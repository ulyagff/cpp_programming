#include "circul_buf.h"

template <typename T>
class circul_buf {
private:
    friend class circul_iterator;
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
        circul_iterator(circul_buf &buf, pointer p) :
                value(p),
                buf(buf)
        {}

    public:
        circul_iterator(const circul_iterator& it) :
                value(it.value),
                buf(it.buf)
        {}

        circul_iterator& operator++() {
            if (value == (buf.buffer + buf.size_alloc - 1))
                value = buf.buffer;
            else
                value++;
            return *this;
        }

        circul_iterator& operator--() {
            if (value == buf.buffer) {
                value = buf.buffer + buf.size_alloc - 1;
            }
            else
                value--;
            return *this;
        }

        circul_iterator operator+(int n) {
            circul_buf::iterator it = *this;
            int index;
            if (value >= buf.start)
                index = it.value - buf.start;
            else
                index = ((buf.buffer + buf.size_alloc) - buf.start) + (value - buf.buffer);

            if (n + index < buf.count_elem) {
                it.value = &buf[n + index];
                return it;
            }
        }

        circul_iterator& operator+=(int n) {
            int index;
            if (value >= buf.start)
                index = value - buf.start;
            else
                index = ((buf.buffer + buf.size_alloc) - buf.start) + (value - buf.buffer);

            if (n + index < buf.count_elem) {
                value = &buf[index + n];
                return *this;
            }
        }

        circul_iterator operator-=(int n) {
            int index;
            if (value >= buf.start)
                index = value - buf.start;
            else
                index = ((buf.buffer + buf.size_alloc) - buf.start) + (value - buf.buffer);

            if ((index - n < buf.count_elem) && (index - n >= 0)) {
                value = &buf[index - n];
                return *this;
            }
        }

        circul_iterator operator-(int n) {
            circul_buf::iterator it = *this;
            int index;
            if (value >= buf.start)
                index = it.value - buf.start;
            else
                index = ((buf.buffer + buf.size_alloc) - buf.start) + (value - buf.buffer);

            if ((index - n < buf.count_elem) && (index - n >= 0)) {
                it.value = &buf[index - n];
                return it;
            }
        }

        iterator_type& operator*() {
            if (value != buf.end_)
                return *value;
        }

        iterator_type* operator->() const{
            return value;
        }


        bool operator==(circul_iterator const& other) const {
            return value == other.value;
        }

        bool operator!=(circul_iterator const& other) const {
            if (value)
                return value != other.value;
        }

        bool operator>(circul_iterator const& other) const {
            int index1, index2;
            if (value >= buf.start)
                index1 = value - buf.start;
            else
                index1 = ((buf.buffer + buf.size_alloc) - buf.start) + (value - buf.buffer);

            if (other.value >= buf.start)
                index2 = other.value - buf.start;
            else
                index2 = ((buf.buffer + buf.size_alloc) - buf.start) + (other.value - buf.buffer);

            return index1 > index2;
        }

        bool operator>=(circul_iterator const& other) const {
            int index1, index2;
            if (value >= buf.start)
                index1 = value - buf.start;
            else
                index1 = ((buf.buffer + buf.size_alloc) - buf.start) + (value - buf.buffer);

            if (other.value >= buf.start)
                index2 = other.value - buf.start;
            else
                index2 = ((buf.buffer + buf.size_alloc) - buf.start) + (other.value - buf.buffer);

            return index1 >= index2;
        }

        bool operator<(circul_iterator const& other) const {
            int index1, index2;
            if (value >= buf.start)
                index1 = value - buf.start;
            else
                index1 = ((buf.buffer + buf.size_alloc) - buf.start) + (value - buf.buffer);

            if (other.value >= buf.start)
                index2 = other.value - buf.start;
            else
                index2 = ((buf.buffer + buf.size_alloc) - buf.start) + (other.value - buf.buffer);

            return index1 < index2;
        }

        bool operator<=(circul_iterator const& other) const {
            int index1, index2;
            if (value >= buf.start)
                index1 = value - buf.start;
            else
                index1 = ((buf.buffer + buf.size_alloc) - buf.start) + (value - buf.buffer);

            if (other.value >= buf.start)
                index2 = other.value - buf.start;
            else
                index2 = ((buf.buffer + buf.size_alloc) - buf.start) + (other.value - buf.buffer);

            return index1 <= index2;
        }

        difference_type operator-(circul_iterator const& other) const {
            int n = 0;
            circul_buf::iterator it = *this;
            while (it != other) {
                --it;
                n++;
            }
            return n;
        }
    };

public:
    typedef T* pointer_t;
    typedef T value_t;

    circul_buf() {
        size_alloc = 1;
        buffer = new value_t[1];
        start = buffer;
        end_ = buffer;
        count_elem = 0;
    }

    circul_buf(unsigned n) {
        size_alloc = n;
        buffer = new value_t[n];
        start = buffer;
        end_ = buffer;
        count_elem = 0;
    }

    ~circul_buf() {
    }

    typedef circul_iterator<T> iterator;
    typedef circul_iterator<const T> const_iterator;

    iterator begin() {
        iterator it(*this, start);
        return it;
    }

    iterator end() {
        iterator it(*this, end_);
        return it;
    }

    const_iterator cbegin(){
        const_iterator c_it(*this, start);
        return c_it;
    }

    const_iterator cend(){
        const_iterator c_it(*this, end_);
        return c_it;
    }

    void push_back(value_t new_elem) {
        if (count_elem < size_alloc - 1) {
            if (end_ == (buffer + (size_alloc)))
                end_ = buffer;
            *end_ = new_elem;
            end_++;
            count_elem++;
        }
        else {
            size_alloc *= 2;

            pointer_t buffer2 = new value_t[size_alloc * 2];
            for (int i = 0; i < count_elem; i++) {
                buffer2[i] = (*this)[i];
            }
            delete[] buffer;
            buffer = buffer2;

            start = buffer;
            end_ = buffer + count_elem;
            *end_ = new_elem;
            end_++;
            count_elem++;
        }
    }

    void push_front(value_t new_elem) {
        if (count_elem >= size_alloc - 1) {
            size_alloc *= 2;

            pointer_t buffer2 = new value_t[size_alloc * 2];
            for (int i = 0; i < count_elem; i++) {
                buffer2[i] = (*this)[i];
            }
            delete[] buffer;
            buffer = buffer2;

            start = buffer;
            end_ = buffer + count_elem;

        }

        if (start != buffer)
            start--;
        else
            start = buffer + (size_alloc - 1) ;

        *start = new_elem;
        count_elem++;

    }

    void pop_front() {
        if (count_elem > 0) {
            if (start == buffer + (size_alloc - 1)) {
                start = buffer;
            }
            else
                start++;

            count_elem--;
        }
    }

    void pop_back() {
        if (count_elem > 0) {
            if (end_ == buffer) {
                end_ = buffer + ((size_alloc - 1));
            }
            else
                end_--;
            count_elem--;
        }
    }

    value_t get_start() {
        return *start;
    }
    value_t get_end() {
        if (end_ == buffer) {
            return  *(buffer + (size_alloc - 1));
        }
        else
            return *(end_ - 1);
    }

    value_t& operator[](const unsigned& n) {
        if (n < count_elem) {
            if (start - end_ > 0) {
                if (n < ((buffer + size_alloc) - start))
                    return *(start + n);
                else
                    return *(buffer + n - (buffer + size_alloc - start));
            } else {
                return *(start + n);
            }
        }
    }

    const value_t& operator[](const unsigned& n) const{
        if (n < count_elem) {
            if (start - end_ > 0) {
                if (n < ((buffer + size_alloc) - start))
                    return *(start + n);
                else
                    return *(buffer + n - (buffer + size_alloc - start));
            } else {
                return *(start + n);
            }
        }
    }

    void change_capasity(unsigned n) {
        if (n > size_alloc) {

            pointer_t buffer2 = new value_t[n];
            for (int i = 0; i < count_elem; i++) {
                buffer2[i] = (*this)[i];
            }
            delete[] buffer;
            buffer = buffer2;

            start = buffer;
            end_ = buffer + count_elem;
            size_alloc = n;
        }
    }

    unsigned size() {
        return count_elem;
    }



private:
    pointer_t buffer;
    unsigned size_alloc;
    unsigned count_elem;
    pointer_t start;
    pointer_t end_;
};