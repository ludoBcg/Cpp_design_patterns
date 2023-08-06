/*********************************************************************************************************************
 *
 * bridge.cpp
 *
 * Cpp_design_patterns
 * Ludovic Blache
 *
 *********************************************************************************************************************/


#include <iostream>
# define _USE_MATH_DEFINES
#include <math.h>


/*------------------------------------------------------------------------------------------------------------+
|                                                  IMPLEMENTATION                                             |
+-------------------------------------------------------------------------------------------------------------*/

class Implementation
{

public:
    virtual ~Implementation() {};

    virtual void printArea(double _area) const {};// = 0;

};


/*------------------------------------------------------------------------------------------------------------+
|                                                 IMPLEMENTATION 1                                            |
+-------------------------------------------------------------------------------------------------------------*/

class Implementation1 : public Implementation
{
    // implementation 1 prints area in square meter
public:
    virtual ~Implementation1() {};

    void printArea(double _area) const override {
        std::cout << " area = " << _area << " sq m" << std::endl;
    }
};


/*------------------------------------------------------------------------------------------------------------+
|                                                 IMPLEMENTATION 2                                            |
+-------------------------------------------------------------------------------------------------------------*/

class Implementation2 : public Implementation
{
    // implementation 2 prints area in square feet
public:
    void printArea(double _area) const override {
        std::cout << " area = " << _area * 10.639 << " sq. ft." << std::endl;
    }
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      SHAPE                                                  |
+-------------------------------------------------------------------------------------------------------------*/

// Shape interface
class Shape
{
public:
    Shape() {}

    virtual ~Shape() = default;

    virtual void printArea() const = 0;

protected:

    // ptr to implementation
    std::shared_ptr<Implementation> m_implementation = nullptr;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      CIRCLE                                                 |
+-------------------------------------------------------------------------------------------------------------*/

class Circle : public Shape
{
public:
    explicit Circle(double _radius, std::shared_ptr<Implementation> _impl)
        : m_radius(_radius)
    {
        m_implementation = _impl;
    }

    void printArea() const override {
        if(m_implementation)
            m_implementation->printArea( M_PI * pow(m_radius, 2) );
    }

private:
    double m_radius;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      MAIN                                                   |
+-------------------------------------------------------------------------------------------------------------*/

int main()
{

    Circle circle1(1.0, std::make_shared<Implementation1>() );
    Circle circle2(1.0, std::make_shared<Implementation2>());

    circle1.printArea();
    circle2.printArea();

    return EXIT_SUCCESS;
}
