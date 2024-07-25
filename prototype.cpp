/*********************************************************************************************************************
 *
 * prototype.cpp
 *
 * Cpp_design_patterns
 * Ludovic Blache
 *
 *********************************************************************************************************************/

#include <iostream>
#include <vector>
# define _USE_MATH_DEFINES
#include <math.h>


struct Point
{
    double x;
    double y;
};



/*------------------------------------------------------------------------------------------------------------+
|                                                      SHAPE                                                  |
+-------------------------------------------------------------------------------------------------------------*/

// Prototype
class Shape
{
public:
    Shape()
        :m_center()
    {}

    virtual ~Shape() = default;

    virtual void print() const = 0;

    virtual std::unique_ptr<Shape> clone() const = 0;

    void setCenter(Point _center) { m_center = _center; }

protected:
    Point m_center;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      CIRCLE                                                 |
+-------------------------------------------------------------------------------------------------------------*/

// Concrete prototype 1
class Circle : public Shape
{
public:
    explicit Circle(double _radius)
        : m_radius(_radius)
    {}

    void print() const override {
        std::cout << "Circle: center = (" << m_center.x << ", " << m_center.y
                  << "), radius = " << m_radius << std::endl;
    }

    std::unique_ptr<Shape> clone() const override 
    {
        std::cout << "Circle::clone()" << std::endl;
        return std::make_unique<Circle>(*this);
    }

private:
    double m_radius;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      SQUARE                                                 |
+-------------------------------------------------------------------------------------------------------------*/

// Concrete prototype 2
class Square : public Shape
{
public:
    explicit Square(double _side)
        : m_side(_side)
    {}

    void print() const override {
        std::cout << "Square: center = (" << m_center.x << ", " << m_center.y
                 << "), side = " << m_side << std::endl;
    }

    std::unique_ptr<Shape> clone() const override
    {
        std::cout << "Square::clone()" << std::endl;
        return std::make_unique<Square>(*this);
    }

private:
    double m_side;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      MAIN                                                   |
+-------------------------------------------------------------------------------------------------------------*/


int main()
{
    // Instanciate concret prototypes
    std::unique_ptr<Shape> circle1(std::make_unique<Circle>(2.1));
    std::unique_ptr<Shape> square1(std::make_unique<Square>(1.2));
    circle1->print();
    square1->print();

    // clone them
    std::unique_ptr<Shape> circle2(circle1->clone()); // circle2 = circle1
    circle1->setCenter({ 1,2 });                      // change circle1 position
    std::unique_ptr<Shape> circle3(circle1->clone()); // circle3 = circle1
    circle1->print();
    circle2->print();
    circle3->print();

    std::unique_ptr<Shape> square2(square1->clone()); // square2 = square1
    square1 = std::make_unique<Square>(3.0);          // re-create square 1 with different size
    std::unique_ptr<Shape> square3(square1->clone()); // square3 = square1
    square1->print();
    square2->print();
    square3->print();


    return EXIT_SUCCESS;
}
