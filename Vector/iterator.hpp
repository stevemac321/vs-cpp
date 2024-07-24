#pragma once
#include <iterator>

namespace stevemac
{
	template <typename Container>
	class vector_iterator : public std::iterator<std::random_access_iterator_tag,
		typename Container::value_type> {
	public:
		using value_type = typename Container::value_type;
		using pointer = typename Container::pointer;
		using reference = typename Container::reference;
		using difference_type = std::ptrdiff_t;

	protected:
		pointer pointee;

	public:
		vector_iterator() : pointee(nullptr) {}
		explicit vector_iterator(const pointer ptr) : pointee(ptr) {}
		~vector_iterator() {}

		reference operator*() { return *pointee; }
		const reference operator*() const { return *pointee; }

		pointer operator->() { return pointee; }
		const pointer operator->() const { return pointee; }

		vector_iterator& operator++() {
			++pointee;
			return *this;
		}

		vector_iterator operator++(int) {
			vector_iterator tmp = *this;
			++pointee;
			return tmp;
		}

		vector_iterator& operator--() {
			--pointee;
			return *this;
		}

		vector_iterator operator--(int) {
			vector_iterator tmp = *this;
			--pointee;
			return tmp;
		}

		// Non-const overload
		difference_type operator-(vector_iterator& other) {
			return pointee - other.pointee;
		}

		// Const overload
		difference_type operator-(const vector_iterator& other) const {
			return pointee - other.pointee;
		}

		vector_iterator operator+(difference_type n) const {
			return vector_iterator(pointee + n);
		}

		vector_iterator operator-(difference_type n) const {
			return vector_iterator(pointee - n);
		}

		vector_iterator& operator+=(difference_type n) {
			pointee += n;
			return *this;
		}

		vector_iterator& operator-=(difference_type n) {
			pointee -= n;
			return *this;
		}

		bool operator==(const vector_iterator& other) const {
			return pointee == other.pointee;
		}

		bool operator!=(const vector_iterator& other) const {
			return pointee != other.pointee;
		}

		bool operator<(const vector_iterator& other) const {
			return pointee < other.pointee;
		}

		bool operator>(const vector_iterator& other) const {
			return pointee > other.pointee;
		}

		bool operator<=(const vector_iterator& other) const {
			return pointee <= other.pointee;
		}

		bool operator>=(const vector_iterator& other) const {
			return pointee >= other.pointee;
		}
	};
} // end stevemac
