/*********************************************************************************************************************
 *
 * factory_simple.cpp
 *
 * Cpp_design_patterns
 * Ludovic Blache
 *
 *********************************************************************************************************************/

 // See https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Factory
 //     https://refactoring.guru/design-patterns/factory-comparison

#include <iostream>
# define _USE_MATH_DEFINES
#include <math.h>


struct Point
{
    double x;
    double y;
};


enum class TypeShape
{
    square,
    circle
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      SHAPE                                                  |
+-------------------------------------------------------------------------------------------------------------*/

// Shape interface
class Shape
{
public:
    Shape()
        :m_center()
    {}

    virtual ~Shape() = default;

    virtual double area() const = 0;

    Point  center() const { return m_center; }

protected:
    Point m_center{ 0, 0 };
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      CIRCLE                                                 |
+-------------------------------------------------------------------------------------------------------------*/

class Circle : public Shape
{
public:
    explicit Circle(double _radius)
        : m_radius(_radius)
    {}

    double area() const override {
        return M_PI * pow(m_radius, 2);
    }

private:
    double m_radius;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      SQUARE                                                 |
+-------------------------------------------------------------------------------------------------------------*/

class Square : public Shape
{
public:
    explicit Square(double _side)
        : m_side(_side)
    {}

    double area() const override {
        return pow(m_side, 2);
    }

private:
    double m_side;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                   SHAPEFACTORY                                              |
+-------------------------------------------------------------------------------------------------------------*/

class ShapeFactory
{

public:
    virtual ~ShapeFactory() {};

    static std::shared_ptr<Shape> createShape(const TypeShape _typeShape)
    {

        switch (_typeShape) 
        {
            case TypeShape::circle:
                // Creates a Circle of radius 1
                return std::make_shared<Circle>(1.0);
            case TypeShape::square:
                // Creates a Square of side 1
                return std::make_shared<Square>(1.0);
            default:
                return nullptr;
        }
    }

};


/*------------------------------------------------------------------------------------------------------------+
|                                                      MAIN                                                   |
+-------------------------------------------------------------------------------------------------------------*/

int main()
{
    ShapeFactory factory;

    std::cout << "Circle area = " << factory.createShape(TypeShape::circle)->area() << std::endl;

    std::cout << "Square area = " << factory.createShape(TypeShape::square)->area() << std::endl;

    return EXIT_SUCCESS;
}
