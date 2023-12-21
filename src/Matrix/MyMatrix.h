//
// Created by Master on 22.11.2023.
//

#ifndef MYMATRIX_MYMATRIX_H
#define MYMATRIX_MYMATRIX_H

#include <memory>
#include <functional>
#include <thread>
#include <future>

namespace MatrixNS {


    template<typename T>
    class MyMatrix;

    /*!
     *  @brief iterator class
     */
    template<typename T, bool is_const>
    class MyMatrixIterator {
    public:
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef std::conditional_t<is_const, const T, T> *pointer;
        typedef std::conditional_t<is_const, const T, T> &reference;
        typedef std::random_access_iterator_tag iterator_category;

        MyMatrixIterator() noexcept;

        template<bool other_const>
        MyMatrixIterator(const MyMatrixIterator<T, other_const> &o) noexcept
        // нельзя из неконстантного в константный
        requires (is_const >= other_const);

        template<bool other_const>
        MyMatrixIterator &operator=(const MyMatrixIterator<T, other_const> &o) noexcept
        // нельзя из неконстантного в константный
        requires (is_const >= other_const);

        MyMatrixIterator &operator++() noexcept;

        MyMatrixIterator operator++(int) noexcept;

        MyMatrixIterator &operator--() noexcept;

        MyMatrixIterator operator--(int) noexcept;

        MyMatrixIterator &operator+=(difference_type n) noexcept;

        MyMatrixIterator &operator-=(difference_type n) noexcept;

        MyMatrixIterator operator+(difference_type n) const noexcept;

        MyMatrixIterator operator-(difference_type n) const noexcept;

        reference operator[](difference_type n) const noexcept;

        reference operator*() const noexcept;

        pointer operator->() const noexcept;

        template<bool other_const>
        bool operator==(const MyMatrixIterator<T, other_const> &o) const noexcept;

        template<bool other_const>
        bool operator!=(const MyMatrixIterator<T, other_const> &o) const noexcept;

        template<bool other_const>
        bool operator<(const MyMatrixIterator<T, other_const> &rhs) const noexcept;

        template<bool other_const>
        bool operator>(const MyMatrixIterator<T, other_const> &rhs) const noexcept;

        template<bool other_const>
        bool operator<=(const MyMatrixIterator<T, other_const> &rhs) const noexcept;

        template<bool other_const>
        bool operator>=(const MyMatrixIterator<T, other_const> &rhs) const noexcept;

        template<bool other_const>
        difference_type operator-(const MyMatrixIterator<T, other_const> &o) const noexcept {
            return (CurrentElement_ - o.CurrentElement_);
        }

        friend MyMatrixIterator operator+(difference_type n, const MyMatrixIterator<T, is_const> &o) noexcept {
            return MyMatrixIterator(o.CurrentElement_ + n);
        }

    private:
        typedef std::conditional_t<is_const, const T, T> *ptr_t;
        ptr_t CurrentElement_;

        MyMatrixIterator(ptr_t currentElement) : CurrentElement_(currentElement) {}

        friend MyMatrix<T>;
        friend MyMatrixIterator<T, !is_const>;
    };

    template<typename T>
    class MyMatrix {
    public:
        MyMatrix(size_t rowCount, size_t columnCount);

        explicit MyMatrix(size_t rowCount = 0) : MyMatrix(rowCount, rowCount) {}

        MyMatrix(const MyMatrix &matrix);

        MyMatrix(MyMatrix &&matrix) noexcept;

        MyMatrix<T> &operator=(const MyMatrix &matrix);

        MyMatrix<T> &operator=(MyMatrix &&matrix) noexcept;

        const T *operator[](size_t i) const;

        T *operator[](size_t i);

        [[nodiscard]] size_t getRowCount() const;

        [[nodiscard]] size_t getColumnCount() const;

        T &at(size_t i, size_t j);

        const T &at(size_t i, size_t j) const;


        typedef MyMatrixIterator<T, false> iterator;
        typedef MyMatrixIterator<T, true> const_iterator;

        iterator begin() noexcept {
            return iterator(&Elements_[0]);
        }

        iterator end() noexcept {
            return iterator(&Elements_[RowCount_ * ColumnCount_]);
        };

        const_iterator begin() const noexcept {
            return const_iterator(&Elements_[0]);
        }

        const_iterator end() const noexcept {
            return const_iterator(&Elements_[RowCount_ * ColumnCount_]);
        }

        const_iterator cbegin() const noexcept {
            return const_iterator(&Elements_[0]);
        }

        const_iterator cend() const noexcept {
            return const_iterator(&Elements_[RowCount_ * ColumnCount_]);
        }

        std::pair<iterator, std::pair<int, int>>
        oneThreadFind(iterator first, iterator last, std::function<bool(T)> unary_functor);

        std::pair<iterator, std::pair<int, int>>
        multiThreadFind(iterator first, iterator last, std::function<bool(T)> unary_functor);

    private:
        std::pair<iterator, std::pair<int, int>>
        sub_find(iterator first, iterator last, std::function<bool(T)> unary_functor, std::atomic_bool &flag);

        size_t RowCount_ = 0;
        size_t ColumnCount_ = 0;
        std::unique_ptr<T[]> Elements_;
    };

    template<typename T>
    MyMatrix<T>::MyMatrix(size_t rowCount, size_t columnCount): RowCount_(rowCount), ColumnCount_(columnCount),
                                                                Elements_(
                                                                        std::make_unique<T[]>(
                                                                                RowCount_ * ColumnCount_)) {}

    template<typename T>
    size_t MyMatrix<T>::getRowCount() const {
        return RowCount_;
    }

    template<typename T>
    size_t MyMatrix<T>::getColumnCount() const {
        return ColumnCount_;
    }

    template<typename T>
    MyMatrix<T>::MyMatrix(const MyMatrix &matrix):RowCount_(matrix.RowCount_), ColumnCount_(matrix.ColumnCount_) {
        auto new_ptr = new T[matrix.RowCount_ + matrix.ColumnCount_];
        std::copy(matrix.Elements_.get(), matrix.Elements_.get() + matrix.RowCount_ + matrix.ColumnCount_, new_ptr);
        Elements_.reset(new_ptr);
    }

    template<typename T>
    MyMatrix<T>::MyMatrix(MyMatrix &&matrix) noexcept: RowCount_(matrix.RowCount_), ColumnCount_(matrix.ColumnCount_),
                                                       Elements_(std::move(matrix.Elements_)) {
        matrix.RowCount_ = matrix.ColumnCount_ = 0;
    }

    template<typename T>
    MyMatrix<T> &MyMatrix<T>::operator=(const MyMatrix &matrix) {
        if (this != &matrix) {
            RowCount_ = matrix.RowCount_;
            ColumnCount_ = matrix.ColumnCount_;
            auto new_ptr = new T[matrix.RowCount_ + matrix.ColumnCount_];
            std::copy(matrix.Elements_.get(), matrix.Elements_.get() + matrix.RowCount_ + matrix.ColumnCount_, new_ptr);
            Elements_.reset(new_ptr);
        }
        return *this;
    }

    template<typename T>
    MyMatrix<T> &MyMatrix<T>::operator=(MyMatrix &&matrix) noexcept {
        RowCount_ = matrix.RowCount_;
        ColumnCount_ = matrix.ColumnCount_;
        Elements_ = std::move(matrix.Elements_);
        matrix.RowCount_ = matrix.ColumnCount_ = 0;
        return *this;
    }

    template<typename T>
    const T *MyMatrix<T>::operator[](size_t i) const {
        return (Elements_.get() + i * ColumnCount_);
    }

    template<typename T>
    T *MyMatrix<T>::operator[](size_t i) {
        return (Elements_.get() + i * ColumnCount_);
    }

    template<typename T>
    T &MyMatrix<T>::at(size_t i, size_t j) {
        if (i >= RowCount_ || j >= ColumnCount_) {
            throw std::out_of_range("Invalid index.");
        }
        return (*this)[i][j];
    }

    template<typename T>
    const T &MyMatrix<T>::at(size_t i, size_t j) const {
        if (i >= RowCount_ || j >= ColumnCount_) {
            throw std::out_of_range("Invalid index.");
        }
        return (*this)[i][j];
    }

    template<typename T>
    std::pair<MyMatrixIterator<T, false>, std::pair<int, int>>
    MyMatrix<T>::oneThreadFind(MyMatrix::iterator first, MyMatrix::iterator last,
                               std::function<bool(T)> unary_functor) {

        while (first <= last) {
            if (unary_functor(*first)) {
                auto diff = std::distance(begin(), first);
                return {first, {(diff - (diff % ColumnCount_)) / ColumnCount_, diff % ColumnCount_}};
            }
            first++;
        }
        return {end(), {-1, -1}};

    }

    template<typename T>
    std::pair<MyMatrixIterator<T, false>, std::pair<int, int>>
    MyMatrix<T>::multiThreadFind(MyMatrix::iterator first, MyMatrix::iterator last,
                                 std::function<bool(T)> unary_functor) {
        auto elements_num = std::distance(first, last);
        if (elements_num <= 100) {
            return oneThreadFind(first, last, unary_functor);
        }
        auto nThreads = std::thread::hardware_concurrency();

        std::vector<std::future<std::pair<MyMatrixIterator<T, false>, std::pair<int, int>>>> futures;
        std::atomic_bool first_block_flag = false;
        for (size_t i = 0; i < nThreads; i++) {
            size_t start_pos = i * elements_num / nThreads, end_pos = (i + 1) * elements_num / nThreads;
            auto start_it = first + start_pos;
            auto end_it = first + end_pos;
            if (i == 0) {
                futures.push_back(
                        std::async([&first_block_flag, start_it, end_it, &unary_functor, this] {
                            auto result = this->oneThreadFind(start_it, end_it, unary_functor);
                            if (result.first != this->end()) {
                                first_block_flag.store(true);
                            }
                            return result;
                        })
                );
            } else {
                futures.push_back(
                        std::async([&first_block_flag, start_it, end_it, &unary_functor, this] {
                            return this->sub_find(start_it, end_it, unary_functor, first_block_flag);
                        })
                );
            }

        }

        for (auto &future: futures) {
            auto result = future.get();
            if (result.first != end()) {
                return result;
            }
        }
        return {end(), {-1, -1}};
    }

    template<typename T>
    std::pair<MyMatrixIterator<T, false>, std::pair<int, int>>
    MyMatrix<T>::sub_find(MyMatrix::iterator first, MyMatrix::iterator last, std::function<bool(T)> unary_functor,
                          std::atomic_bool &flag) {
        for (; first != last; ++first) {
            if (flag.load())
                return {this->end(), {-1, -1}};
            if (unary_functor(*first)) {
                auto diff = std::distance(begin(), first);
                // return {first, {diff, diff}};
                return {first, {(diff - (diff % ColumnCount_)) / ColumnCount_, diff % ColumnCount_}};
            }
        }
        return {end(), {-1, -1}};
    }

    template<typename T, bool is_const>
    template<bool other_const>
    MyMatrixIterator<T, is_const>::MyMatrixIterator(const MyMatrixIterator<T, other_const> &o) noexcept
    // нельзя из неконстантного в константный
    requires (is_const >= other_const)
            : CurrentElement_(o.CurrentElement_) {}

    template<typename T, bool is_const>
    template<bool other_const>
    MyMatrixIterator<T, is_const> &
    MyMatrixIterator<T, is_const>::operator=(const MyMatrixIterator<T, other_const> &o) noexcept
    // нельзя из неконстантного в константный
    requires (is_const >= other_const) {
        CurrentElement_ = o.node;
        return *this;
    }

    template<typename T, bool is_const>
    MyMatrixIterator<T, is_const> &MyMatrixIterator<T, is_const>::operator++() noexcept {
        CurrentElement_++;
        return *this;
    }

    template<typename T, bool is_const>
    MyMatrixIterator<T, is_const> MyMatrixIterator<T, is_const>::operator++(int) noexcept {
        MyMatrixIterator res(CurrentElement_);
        CurrentElement_++;
        return res;
    }

    template<typename T, bool is_const>
    typename MyMatrixIterator<T, is_const>::reference MyMatrixIterator<T, is_const>::operator*() const noexcept {
        return *CurrentElement_;
    }

    template<typename T, bool is_const>
    MyMatrixIterator<T, is_const>::MyMatrixIterator() noexcept:CurrentElement_(nullptr) {}

    template<typename T, bool is_const>
    typename MyMatrixIterator<T, is_const>::pointer MyMatrixIterator<T, is_const>::operator->() const noexcept {
        return &CurrentElement_;
    }

    template<typename T, bool is_const>
    template<bool other_const>
    bool MyMatrixIterator<T, is_const>::operator==(const MyMatrixIterator<T, other_const> &o) const noexcept {
        return CurrentElement_ == o.CurrentElement_;
    }

    template<typename T, bool is_const>
    template<bool other_const>
    bool MyMatrixIterator<T, is_const>::operator!=(const MyMatrixIterator<T, other_const> &o) const noexcept {
        return CurrentElement_ != o.CurrentElement_;
    }

    template<typename T, bool is_const>
    MyMatrixIterator<T, is_const> MyMatrixIterator<T, is_const>::operator--(int) noexcept {
        MyMatrixIterator res(CurrentElement_);
        CurrentElement_--;
        return res;
    }

    template<typename T, bool is_const>
    MyMatrixIterator<T, is_const> &MyMatrixIterator<T, is_const>::operator--() noexcept {
        CurrentElement_--;
        return *this;
    }

    template<typename T, bool is_const>
    template<bool other_const>
    bool MyMatrixIterator<T, is_const>::operator<(const MyMatrixIterator<T, other_const> &rhs) const noexcept {
        return CurrentElement_ < rhs.CurrentElement_;
    }

    template<typename T, bool is_const>
    template<bool other_const>
    bool MyMatrixIterator<T, is_const>::operator<=(const MyMatrixIterator<T, other_const> &rhs) const noexcept {
        return CurrentElement_ <= rhs.CurrentElement_;
    }

    template<typename T, bool is_const>
    template<bool other_const>
    bool MyMatrixIterator<T, is_const>::operator>(const MyMatrixIterator<T, other_const> &rhs) const noexcept {
        return CurrentElement_ > rhs.CurrentElement_;
    }

    template<typename T, bool is_const>
    template<bool other_const>
    bool MyMatrixIterator<T, is_const>::operator>=(const MyMatrixIterator<T, other_const> &rhs) const noexcept {
        return CurrentElement_ >= rhs.CurrentElement_;
    }

    template<typename T, bool is_const>
    MyMatrixIterator<T, is_const> &MyMatrixIterator<T, is_const>::operator+=(difference_type n) noexcept {
        CurrentElement_ += n;
        return *this;
    }

    template<typename T, bool is_const>
    MyMatrixIterator<T, is_const> &MyMatrixIterator<T, is_const>::operator-=(difference_type n) noexcept {
        CurrentElement_ -= n;
        return *this;
    }

    template<typename T, bool is_const>
    MyMatrixIterator<T, is_const> MyMatrixIterator<T, is_const>::operator+(difference_type n) const noexcept {
        MyMatrixIterator res(CurrentElement_ + n);
        return res;
    }

    template<typename T, bool is_const>
    MyMatrixIterator<T, is_const> MyMatrixIterator<T, is_const>::operator-(difference_type n) const noexcept {
        MyMatrixIterator res(CurrentElement_ - n);
        return res;
    }

    template<typename T, bool is_const>
    typename MyMatrixIterator<T, is_const>::reference
    MyMatrixIterator<T, is_const>::operator[](MyMatrixIterator::difference_type n) const noexcept {
        return *(CurrentElement_ + n);
    }


} // MatrixNS

#endif //MYMATRIX_MYMATRIX_H
