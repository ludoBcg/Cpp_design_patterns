/*********************************************************************************************************************
 *
 * pimpl.cpp
 *
 * Cpp_design_patterns
 * Ludovic Blache
 *
 *********************************************************************************************************************/

// See https://en.cppreference.com/w/cpp/language/pimpl

#include <iostream>
#include <memory>


/*------------------------------------------------------------------------------------------------------------+
|                                                   CIRCLE.H                                                  |
+-------------------------------------------------------------------------------------------------------------*/

class Circle
{

    private:
        class impl; // not defined here
        std::unique_ptr<impl> m_pImpl;

    public:
        // Public API:
        void draw();
        void translate();
 
        // Defined in the implementation file:
        Circle();
        explicit Circle(int);
        ~Circle();
};
 
 
/*------------------------------------------------------------------------------------------------------------+
|                                                  CIRCLE.CPP                                                 |
+-------------------------------------------------------------------------------------------------------------*/

class Circle::impl
{
    public:
        // Actual implementation of functions
        void draw(const Circle& _c)      { std::cout << "draw a circle of radius " << m_radius << std::endl; }
        void translate(const Circle& _c) { std::cout << "translate a circle of radius " << m_radius << std::endl; }
 
        impl() : m_radius(0) {}
        impl(int _n) : m_radius(_n) {}

    private:
        int m_radius; // private data
};
 
void Circle::draw()      { m_pImpl->draw(*this); }
void Circle::translate() { m_pImpl->translate(*this); }

Circle::Circle() : m_pImpl(std::make_unique<impl>()) {}
Circle::Circle(int _n) : m_pImpl(std::make_unique<impl>(_n)) {}
Circle::~Circle() = default;


/*------------------------------------------------------------------------------------------------------------+
|                                                      MAIN                                                   |
+-------------------------------------------------------------------------------------------------------------*/

int main()
{
    Circle c1;
    Circle c2(10);
    c1.draw();
    c2.draw();
    c1.translate();
    c2.translate();
}