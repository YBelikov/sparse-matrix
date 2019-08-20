
#ifndef SPARSEMATRIX_H_INCLUDED
#define SPARSEMATRIX_H_INCLUDED

/*==========================================================================


 This code is just my trying to create simple general sparse matrix 
class which objects should be applyable for some common operations.

Firstly, let's make some requirements which my sparse matrix should meet:
- The class should have default constructor
- Destructor
- Copy constructor for matrixes of the same type
- Copy assignment operator for matrixes of the same type
- Move constructor for matrixes of the same type
- Move assignment operator for matrixes of the same type
===========================================================================
Next requirements meet only matrixes of convertable data types 
- Copy constructor for matrixes of the different types
- Copy assignment operator for matrixes of the different types
- Move constructor for matrixes of the different types
- Move assignment operator for matrixes of the different types
===========================================================================
- Slicing operation
- Addition operation
- Multiplication
- Division
- Subscription
============================================================================*/

#include <map>
#include <utility>      
#include <ostream>
#include <assert.h>
using std::map;
using std::pair;
using std::ostream;
using std::make_pair;


template<typename T, size_t W, size_t H>
class SparseMatrix {
public:

	using map = map<pair<size_t, size_t>, T> ;
	using iterator = typename map::iterator;
	using const_iterator = typename map::const_iterator;
	SparseMatrix() = default;
	SparseMatrix(const SparseMatrix&) = default;
	SparseMatrix& operator=(const SparseMatrix&) = default;
	SparseMatrix(SparseMatrix&&) = default;
	SparseMatrix& operator=(SparseMatrix&&) = default;
	~SparseMatrix() = default;

	

	constexpr size_t getMatrixWidth() const noexcept {
		return W;
	}

	constexpr size_t getMatrixHeight() const noexcept {
		return H;
	}
	void pushElementAtPosition(size_t, size_t, T);
	T getElementAtPosition(size_t, size_t);

	void printMatrix(ostream & os) const;

	
	SparseMatrix& operator +=(const SparseMatrix<T, W, H>&);
	SparseMatrix& operator -=(const SparseMatrix<T, W, H>&);
	
	

	SparseMatrix& operator /=(const SparseMatrix<T, W, H>&);
	SparseMatrix& operator %=(const SparseMatrix<T, W, H>&);

	
	const_iterator searchForPair(size_t row, size_t column) const {
		auto pair = make_pair(row, column);
		return data.find(pair);
	}

	const_iterator searchForPair(pair<size_t, size_t> indexes) const {
		return data.find(indexes);
	}

	
	iterator begin() noexcept{ return data.begin(); }
	iterator end() noexcept { return data.end(); }
	const_iterator cbegin() const noexcept { return data.cbegin();}
	const_iterator cend() const noexcept { return data.cend(); }

private:
	
	map data;
};


template<typename T, size_t W, size_t H>
T SparseMatrix<T, W, H>::getElementAtPosition(size_t row, size_t column) {
	auto pair = make_pair(row, column);
	auto elementPair = data.find(pair);
	if (elementPair == data.end()) {
		std::cout << "Element hasn't found\n";
		return;
	}
	else {
		return elementPair->second;
	}
}

template<typename T, size_t W, size_t H>
void SparseMatrix<T, W, H>::pushElementAtPosition(size_t row, size_t column, T elt) {

	auto pair = make_pair(row, column);
	auto q = data.find(pair);
	if (q == data.end()) {
		data.insert(make_pair(pair, elt));
	}
	else {
		std::cout << "Another element on this position\n";
	}
}



template<typename T, size_t W, size_t H>
void SparseMatrix<T, W, H>::printMatrix(ostream& os) const {

	for (auto p = data.begin(); p != data.end(); ++p) {
		os << '(' << ' ' << p->first.first << ' ' << p->first.second << ' ' <<')' << ' ' << '-' << ' ' << p->second << '\n';
	}
}

template<typename T, size_t W, size_t H>
ostream& operator<<(ostream& os, const SparseMatrix<T, W, H>& matrix) {
	os << "Matrix in form (row index, column index) - element: \n";
	matrix.printMatrix(os);
	return os;
}

template<typename T, size_t W, size_t H>
SparseMatrix<T, W, H>& SparseMatrix<T, W, H>::operator+=(const SparseMatrix<T, W, H>& other) {
	for (auto p = other.data.begin(); p != other.data.end(); ++p) {
		auto q = data.find(p->first);
		if (q == data.end()) {
			data[p->first] = p->second;
		}
		else {
			data[q->first] = p->second + q->second;
		}
	}
	return *this;
}
template<typename T, size_t W, size_t H>
SparseMatrix<T, W, H>& SparseMatrix<T, W, H>::operator-=(const SparseMatrix<T, W, H>& other) {
	
	for (auto p = other.data.begin(); p != other.data.end(); ++p) {
		auto q = data.find(p->first);
		if (q == data.end()) {
			data[p->first] = -p->second;
		}
		else {
			data[q->first] = p->second - q->second;
		}
	}
}


template<typename T, size_t W, size_t H, size_t W1, size_t H1>

SparseMatrix<T, W, H1> operator*(const SparseMatrix<T, W, H>& a, const SparseMatrix<T, W1, H1>& b) {
	assert(W == H1);
	
	auto mult = [&](T a, T b) {return a * b; };

	SparseMatrix<T, W, H1> res{};
	for (auto p = a.cbegin(); p != a.cend(); ++p) {
		auto pair = b.searchForPair(p->first);
		if (pair != b.cend()) {
			res.pushElementAtPosition(p->first.first, p->first.second, mult(p->second, pair->second));
		}
		
	}
	return res;
}


#endif // SPARSEMATRIX_H_INCLUDED

