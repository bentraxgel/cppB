#include "Span.hpp"
#include <algorithm>
#include <cstdlib>

Span::Span(unsigned int n)
 : _capacity(n)
{}
Span::Span(const Span& rhs)
 : _capacity(rhs._capacity)
 , _vector(rhs._vector)
{}
Span& Span::operator=(const Span& rhs)
{
	if (this != &rhs)
	{
		_vector = rhs._vector;
		_capacity = rhs._capacity;
	}
	return *this;
}
Span::~Span() {}

int Span::operator[](const unsigned int idx)
{
	if (idx >= _capacity)
		throw invalid();
	return _vector[idx];
}
void	Span::vectorReserve(int size)
{
	_capacity = size;
	_vector.reserve(size);
}

void	Span::addNumber(int n)
{
	if (_vector.size() >= _capacity)
		throw invalid();
	_vector.push_back(n);
}
void	Span::addManyNumber(int* arr, unsigned int size)
{
	for (unsigned int i = 0; i < size; i++)
		addNumber(arr[i]);
}

std::vector<int> makeVectorNearDiff(std::vector<int> target)
{
	std::vector<int>	result;
	result.reserve(target.size() - 1);
	for (std::vector<int>::iterator	it = target.begin(); it + 1 != target.end(); ++it)
	{
		int a = *it;
		int b = *(it + 1);
		result.push_back(abs(a - b));
	}
	return result;
}
int		Span::shortestSpan() {
	if (_vector.size() <= 1)
		throw invalid();
	std::vector<int> diffVec = makeVectorNearDiff(_vector);
	return *(std::min_element(diffVec.begin(), diffVec.end()));
}
int		Span::longestSpan() {
	if (_vector.size() <= 1)
		throw invalid();
	std::vector<int> diffVec = makeVectorNearDiff(_vector);
	return *(std::max_element(diffVec.begin(), diffVec.end()));
}

const char* Span::invalid::what() const throw()
{
	return "Error: Invalid";
}
