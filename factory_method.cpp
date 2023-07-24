/*********************************************************************************************************************
 *
 * factory.cpp
 *
 * Cpp_design_patterns
 * Ludovic Blache
 *
 *********************************************************************************************************************/

 // See https://refactoring.guru/design-patterns/factory-method/cpp/example

#include <iostream>
# define _USE_MATH_DEFINES
#include <math.h>
#include <variant>
#include <vector>
#include <numbers>


struct Point
{
    double x;
    double y;
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
|                                                   SHAPECREATOR                                              |
+-------------------------------------------------------------------------------------------------------------*/

// Creator interface
class ShapeCreator 
{

public:
    virtual ~ShapeCreator() {};

    // Factory method
    // To be implemented by derived classes (may then return different types of Shapes)
    virtual std::shared_ptr<Shape> FactoryMethod() const = 0;
    
    double shapeArea() const 
    {
        // Call the factory method to create a Shape object.
        std::shared_ptr<Shape> shape(this->FactoryMethod());
        // Now, use the Shape.
        return shape->area();
    }
};


/*------------------------------------------------------------------------------------------------------------+
|                                                  CIRCLECREATOR                                              |
+-------------------------------------------------------------------------------------------------------------*/

class CircleCreator : public ShapeCreator 
{

public:
    std::shared_ptr<Shape> FactoryMethod() const override
    {
        // Creates a Circle of radius 1
        return std::make_shared<Circle>(1.0);
    }
};


/*------------------------------------------------------------------------------------------------------------+
|                                                  SQUARECREATOR                                              |
+-------------------------------------------------------------------------------------------------------------*/

class SquareCreator : public ShapeCreator 
{
public:
    std::shared_ptr<Shape> FactoryMethod() const override
    {
        // Creates a Square of side 1
        return std::make_shared<Square>(1.0);
    }
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      MAIN                                                   |
+-------------------------------------------------------------------------------------------------------------*/

int main()
{
    CircleCreator creator1;
    std::cout << "Circle area = " << creator1.shapeArea() << std::endl;

    SquareCreator creator2;
    std::cout << "Square area = " << creator2.shapeArea() << std::endl;

    return EXIT_SUCCESS;
}
