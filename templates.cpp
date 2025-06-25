/*********************************************************************************************************************
 *
 * templates.cpp
 *
 * Cpp_design_patterns
 * Ludovic Blache
 *
 *********************************************************************************************************************/

#include <cstdlib>
#include <iostream>

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <array>
#include <version>


/*------------------------------------------------------------------------------------------------------------+
|                                               FUNCTION TEMPLATES                                            |
+-------------------------------------------------------------------------------------------------------------*/

template< typename T > // Function template argument deduction
const T max1(const T a, const T b) // Function template instanciation / specialization (note: SFINAE: Substitution Failure Is Not An Error)
{
    std::cout << "max1(" << typeid(T).name() << " " << a 
              << ", "    << typeid(T).name() << " " << b 
              << ") = "  << typeid(T).name() << " ";

    if(a > b)
        return a;
    else
        return b;  
}

// function template specialization
// not recommended, a non template function would be better for special cases: 
// char max(char a, char b){return( a < b ? b : a );}
template< > 
const char max1<const char>(const char a, const char b) 
{
    std::cout << "max1<char>(char " << a << ", char " << b << ") = char ";
    return (a > b) ? a : b;
}

template< typename T1, typename T2 >
const T1 max2(const T1 a, const T2 b)
{
    std::cout << "max2(" << typeid(T1).name() << " " << a 
              << ", "    << typeid(T2).name() << " " << b
              << ") = "  << typeid(T1).name() << " ";

    if(a > b)
        return a;
    else
        return b;  
}

template< typename T1, typename T2 >
const auto max3(const T1 a, const T2 b)
{
    using Tr = std::common_type_t<T1,T2>; // same as std::common_type<T1,T2>::type
    
    std::cout << "max3(" << typeid(T1).name() << " " << a 
              << ", "    << typeid(T2).name() << " " << b
              << ") = "  << typeid(Tr).name() << " ";
    
    if(a > b)
        return static_cast<Tr>(a);
    else
        return static_cast<Tr>(b);  
}

template< typename T1, typename T2 >
auto max4(const T1 a, const T2 b) -> typename std::common_type<T1,T2>::type  // Trailing return type only necessary for C++11
{
    // same as max3()
    std::cout << "max4(" << typeid(T1).name() << " " << a 
              << ", "    << typeid(T2).name() << " " << b
              << ") = ";
    
    return (a > b) ? a : b; 
}


// Best definition of max() (similar to max4() above)
template< typename T1, typename T2 >
constexpr auto max( T1 const& a, T2 const& b ) // constexpr is const AND compile-time   
{
   return (a > b) ? a : b;
}



/*------------------------------------------------------------------------------------------------------------+
|                                               VARIADIC TEMPLATES                                            |
+-------------------------------------------------------------------------------------------------------------*/

// function template for an variable number of arguments:

template< typename T, typename... Ts >
constexpr auto maxV( T const& a, Ts const&... values )
{
    // "sizeof...(Ts)" OR "sizeof...(values)" returns NB OF ELEMENTS in the pack
    // WARNING: "sizeof(Ts)..." returns sizeof(), i.e., BYTESIZE, of each element in the pack
    if constexpr( sizeof...(Ts) > 0) 
    {
        // get common type of T and Ts
        using Tr = std::common_type_t<T,Ts...>;
        // recursive call to find max of remaining values after 1st argument a
        Tr b = maxV(values...);

        return (a > b) ? a : b; //could be return max(a,b);
    }
    else
    {
        // last recursive call simply returns the last value
        return a;
    }
}



/*------------------------------------------------------------------------------------------------------------+
|                                                 CLASS TEMPLATES                                             |
+-------------------------------------------------------------------------------------------------------------*/

template< typename T, size_t Size>
class Buffer
{
public:
    using value_type     = T;
    using iterator       = T*;
    using const_iterator = const T*;

    Buffer()
    {
        std::uninitialized_fill( begin(), end(), T(0) );
    }

    explicit Buffer( const T& _value)
    {
        std::uninitialized_fill( begin(), end(), _value );
    }

    Buffer( Buffer const& _other ) = delete;
    Buffer( Buffer&& _other ) = delete;
    Buffer& operator=( Buffer const& _other ) = delete;
    Buffer& operator=( Buffer&& _other ) = delete;

    ~Buffer() = default;


    size_t size() const noexcept { return Size; }
    size_t bytesize() const noexcept { return sizeof(m_buffer); }
    //size_t bytesize() const noexcept { return sizeof(m_rawBuffer); }

    iterator data() noexcept
    {
        return m_buffer.data();
        //return reinterpret_cast<iterator>( m_rawBuffer );
    }
    const_iterator data() const noexcept
    {
        return m_buffer.data();
        //return reinterpret_cast<const_iterator>( m_rawBuffer );
    }

    T& operator[]( size_t _index ) noexcept
    {
        assert( _index < Size );
        return data()[_index];
    }
    const T& operator[]( size_t _index ) const noexcept
    {
        assert( _index < Size );
        return data()[_index];
    }

    iterator       begin()        noexcept { return data(); }
    const_iterator cbegin() const noexcept { return data(); }
    iterator       end()          noexcept { return data() + Size; }
    const_iterator cend()   const noexcept { return data() + Size; }

    void print()
    {
        std::cout << " Buffer contains " << size() << " * " << typeid(T).name() 
                  << " = " << bytesize() << " bytes" << std::endl ;
        for (const_iterator it = cbegin(); it < cend(); ++it)
        {
            std::cout << " " << *it;
        }
        std::cout << std::endl;
    }

private:

    std::array<T, Size> m_buffer;
    //alignas(T) std::byte m_rawBuffer[Size*sizeof(T)]; //C-style static array version

};



/*------------------------------------------------------------------------------------------------------------+
|                                                      MAIN                                                   |
+-------------------------------------------------------------------------------------------------------------*/


int main()
{
    std::cout << "Function templates - argument deduction:"     << "\n" 
                 " max1( 1, 2 )       = " << max1( 1, 2 )       << "\n" 
                 " max1( 1U, 2U )     = " << max1( 1U, 2U )     << "\n"
                 " max1( 1.1, 2.2 )   = " << max1( 1.1, 2.2 )   << "\n"
                 " max1( 1.1f, 2.2f ) = " << max1( 1.1f, 2.2f ) << "\n" << std::endl;
    std::cout << "Function templates - explicit template instanciation:"              << "\n" 
                 " max1<float>( 1.1, 2 )         = " << max1<float>( 1.1, 2 )         << "\n"
                 " max1<char>( 1, 2 )            = " << max1<char>( 1, 2 )            << "\n"
                 " max2<float, double>( 1.1, 2 ) = " << max2<float, double>( 1.1, 2 ) << "\n" 
                 " max2<float>( 1.1, 2 )         = " << max2<float>( 1.1, 2 )         << "\n" 
                 " max3<float, double>( 1.1, 2 ) = " << max3<float, double>( 1.1, 2 ) << "\n" 
                 " max3<float>( 1.1, 2 )         = " << max3<float>( 1.1, 2 )         << "\n"
                 " max4<float, double>( 1.1, 2 ) = " << max4<float, double>( 1.1, 2 ) << " (" << typeid( max4<float, double>( 1.1, 2 ) ).name() << ")\n" 
                 " max4<float>( 1.1, 2 )         = " << max4<float>( 1.1, 2 )         << " (" << typeid( max4<float>( 1.1, 2 ) ).name() << ")\n" << std::endl;
    std::cout << "Variadic function templates:"     << "\n" 
                 " maxV( 1 )                 = " << maxV( 1 )                 << "\n" 
                 " maxV( 1U, 2.2f )          = " << maxV( 1U, 2.2f )          << "\n"
                 " maxV( 1U, 2.2f, 3.3 )     = " << maxV( 1U, 2.2f, 3.3 )     << "\n"
                 " maxV( 1U, 2.2f, 3.3, -4 ) = " << maxV( 1U, 2.2f, 3.3, -4 ) << "\n" << std::endl;       


    std::cout << "Class templates:" << std::endl;
    Buffer<short, 3> buf;
    buf.print();
    Buffer<int, 4> buf2(1);
    buf2[1] = 1.1;
    buf2.print();
    Buffer<double, 5> buf3(-2);
    buf3[4] = 3.14;
    buf3.print();

   return EXIT_SUCCESS;
}
