/*********************************************************************************************************************
 *
 * functional_programming.cpp
 *
 * Cpp_design_patterns
 * Ludovic Blache
 *
 *********************************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <array>
#include <ranges>
#include <list>
#include <vector>
#include <numeric>
#include <cassert>


/*------------------------------------------------------------------------------------------------------------+
|                                                    FUNCTIONS                                                |
+-------------------------------------------------------------------------------------------------------------*/

namespace myAlgo
{

	/*!
	* \fn accumulate
	* \brief : re-implementation of std::accumulate
	*	       https://en.cppreference.com/w/cpp/algorithm/accumulate.html
	* \param _first, _last : the pair of iterators defining the range of elements to accumulate
	* \param _init : initial value of the accumulate
	* \param _op : binary operation function object that will be applied 
	* \return : result of accumulation
	*/
	template< typename InputIt, typename T, typename BinaryOperation >
	T accumulate(InputIt _first, InputIt _last, T _init, BinaryOperation _op)
	{
		for (; _first != _last; ++_first)
		{
			_init = _op(std::move(_init), *_first);
		}
		return _init;
	}


	/*!
	* \fn accumulate
	* \brief : overload of the 'accumulate()' algorithm that uses 'std::plus' as the default
	*          binary operation.
	* \param _first, _last : the pair of iterators defining the range of elements to accumulate
	* \param _init : initial value of the accumulate
	* \return : result of accumulation
	*/
	template< typename InputIt, typename T >
	T accumulate(InputIt _first, InputIt _last, T _init)
	{
		return myAlgo::accumulate(_first, _last, _init, std::plus<>{});
	}


	/*!
	* \fn accumulate
	* \brief : overload of the 'accumulate()' algorithm that uses the default vqlue of the
	*          underlying data type as initial value and 'std::plus' as the default binary operation.
	* \param _first, _last : the pair of iterators defining the range of elements to accumulate
	* \return : result of accumulation
	*/
	template< typename InputIt >
	auto accumulate(InputIt _first, InputIt _last)
	{
		using value_type = typename std::iterator_traits<InputIt>::value_type;
		std::cout << "value_type : " << typeid(value_type).name() << std::endl;

		return myAlgo::accumulate(_first, _last, value_type{});
	}


	/*!
	* \fn SumOfSquares
	* \brief : example of a custom binary operation
	*          Sum of squares = a^2 + b^2 + c^2 + ...
	*/
	struct SumOfSquares
	{
		template< typename T1, typename T2 >
		auto operator()(T1&& _a, T2&& _b) const
		{
			return _a + _b * _b;
		}
	};

	template< typename T1 >
	auto Square(T1 _a)
	{
		return std::pow(_a , 2);
	};

	template< typename T1 >
	auto Sqrt(T1 _a)
	{
		return std::sqrt(_a);
	};

} // namespace myAlgo

	/*------------------------------------------------------------------------------------------------------------+
	|                                                      MAIN                                                   |
	+-------------------------------------------------------------------------------------------------------------*/


int main()
{
	std::cout << "INIT: " << std::endl << std::endl;

	const std::vector<int> vecInput{ 1, 2, 3, 4 };
	std::cout << " vecInput: ";
	for (auto val : vecInput) { std::cout << val << ' '; }
    std::cout << std::endl;
	std::vector<int> vecOutput(vecInput.size(), 2);
	std::cout << " vecOutput: ";
	for (auto val : vecOutput) { std::cout << val << ' '; }
    std::cout << std::endl;
	const std::list<float> listInput{ 1.1f, 2.2f, 3.3f, 4.4f };
	std::cout << " listInput: ";
	for (auto val : listInput) { std::cout << val << ' '; }
    std::cout << std::endl;
	std::list<float> listOutput(listInput.size(), 2.2f);
	std::cout << " listOutput: ";
	for (auto val : listOutput) { std::cout << val << ' '; }
    std::cout << std::endl;

	

	// Test std::transform() with unary operators (i.e., operates on one operand)
	std::cout << "\nUNARY OPERATORS: " << std::endl << std::endl;

	std::transform(vecInput.cbegin(), vecInput.cend(), vecOutput.begin(), myAlgo::Square<int>);
	std::cout << "  vecOutput = vecInput^2 : ";
	for (auto val : vecOutput) { std::cout << val << ' '; }
	std::cout << std::endl;

	std::transform(listInput.cbegin(), listInput.cend(), listOutput.begin(), myAlgo::Sqrt<float>);
	std::cout << "  listOutput = sqrt(listInput) : ";
	for (auto val : listOutput) { std::cout << val << ' '; }
	std::cout << std::endl;

	// use of lambda function
	std::transform( listOutput.cbegin(), listOutput.cend(), listOutput.begin(),
                    []( float _x ) { return ++_x; } );
	std::cout << "  listOutput++ : ";
	for (auto val : listOutput) { std::cout << val << ' '; }
	std::cout << std::endl;
	


	// Test std::transform() with binary operators (i.e., operates on two operands)
	std::cout << "\nBINARY OPERATORS: " << std::endl << std::endl;

	std::transform(vecInput.cbegin(), vecInput.cend(), vecOutput.cbegin(), 
	               vecOutput.begin(), std::plus<>{});
	std::cout << "  vecOutput += vecInput : ";
	for (auto val : vecOutput) { std::cout << val << ' '; }
	std::cout << std::endl;



	// Test accumulate() with binary operators
	std::cout << "\nACCUMULATE: " << std::endl << std::endl;

	const auto sum = myAlgo::accumulate(vecInput.begin(), vecInput.end());
	std::cout << "  vecInput sum = " << sum << std::endl;

	const auto prod = myAlgo::accumulate(vecInput.begin(), vecInput.end(), 1, std::multiplies<>{});
	assert(prod == std::accumulate(vecInput.begin(), vecInput.end(), 1, std::multiplies<>{}));
	std::cout << "  vecInput product = " << prod << std::endl;
	
	const auto sumsquare = myAlgo::accumulate(vecInput.begin(), vecInput.end(), 0, myAlgo::SumOfSquares{});
	assert(sumsquare == std::accumulate(vecInput.begin(), vecInput.end(), 0, myAlgo::SumOfSquares{}));
	std::cout << "  vecInput sum of squares = " << sumsquare << std::endl;


	const auto diff = myAlgo::accumulate(listInput.begin(), listInput.end(), 10.0, std::minus<>{});
	assert(diff == std::accumulate(listInput.begin(), listInput.end(), 10.0, std::minus<>{}));
	std::cout << "  vecInput difference = " << diff << std::endl;

	const auto quot = myAlgo::accumulate(listInput.begin(), listInput.end(), 100.0, std::divides<>{});
	assert(quot == std::accumulate(listInput.begin(), listInput.end(), 100.0, std::divides<>{}));
	std::cout << "  vecInput quotient = " << quot << std::endl;

	return EXIT_SUCCESS;
}
