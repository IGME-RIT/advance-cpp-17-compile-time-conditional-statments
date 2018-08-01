#include <iostream>
using namespace std;

// Example of constexpr
// constexpr is a keyword that marks an
// expression or function as having a compile-time
// constant result
constexpr int square(int x)
{
	return x * x;
}

// Compile time fibonacci example

template<unsigned n>
struct Fibonacci
{
	static const unsigned value = Fibonacci<n - 1>::value + Fibonacci<n - 2>::value;
};

template<>
struct Fibonacci<0>
{
	static const unsigned value = 0;
};

template<>
struct Fibonacci<1>
{
	static const unsigned value = 1;
};

// Compile time fibonacci using constexpr

constexpr unsigned fibonacci(const unsigned x)
{
	return x <= 1 ? 1 : fibonacci(x - 1) + fibonacci(x - 2);
}

// getting the nth-arg using if constexpr

template<unsigned n>
struct Arg
{
	template<class X, class...Xs>
	constexpr auto operator()(X x, Xs...xs)
	{
		return Arg<n - 1>{}(xs...);
	}
};

template<>
struct Arg<0>
{
	template<class X, class...Xs>
	constexpr auto operator()(X x, Xs...)
	{
		return x;
	}
};

template<unsigned n>
constexpr auto arg = Arg<n>{};

// getting the nth-arg using constexpr compile time if statments, using C++17

template<unsigned n>
struct Get
{
	template<class X, class...Xs>
	constexpr auto operator()(X x, Xs...xs)
	{
		if constexpr(n > sizeof...(xs))
		{
			return;
		}
		else if constexpr(n > 0)
		{
			return Get<n - 1>{}(xs...);
		}
		else
		{
			return x;
		}
	}
};

int main()
{
	cout << square(4) << endl;

	cout << "Compile time Fibonacci: " << Fibonacci<6>::value << endl;
	cout << "Compile time Fibonacci using constexpr: " << fibonacci(6) << endl;

	cin.get();
}