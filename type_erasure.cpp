/*********************************************************************************************************************
 *
 * type_erasure.cpp
 *
 * Cpp_design_patterns
 * Ludovic Blache
 *
 *********************************************************************************************************************/

#include <iostream>
#include <iomanip>
#include <vector>
# define _USE_MATH_DEFINES
#include <math.h>


struct Point
{
    double x;
    double y;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      CIRCLE                                                 |
+------------------------------------------------------------------------------------------------------------*/

// Circle class (data only)
class Circle
{
public:
    explicit Circle(Point _center, double _radius)
        : m_center(_center), m_radius(_radius)
    {}

    Point  center() const { return m_center; }
    double radius() const { return m_radius; }

private:
    Point  m_center;
    double m_radius;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      SQUARE                                                 |
+------------------------------------------------------------------------------------------------------------*/

// Square class (data only)
class Square
{
public:
    explicit Square(Point _center, double _side)
        : m_center(_center), m_side(_side)
    {}

    Point  center() const { return m_center; }
    double side() const { return m_side; }

private:
    Point  m_center;
    double m_side;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                  PRINTSTRATEGIES                                            |
+------------------------------------------------------------------------------------------------------------*/

// Collection of print functions, with different options
class PrintStrategy1
{
public:
    explicit PrintStrategy1(bool _useCap, bool _showDecimals)
        : m_useCap(_useCap), m_showDecimal(_showDecimals)
    {}

    void operator()(Circle const& _circle) const
    {
        if (m_useCap) { std::cout << "CIRCLE: "; }
        else { std::cout << "circle: "; }

        if (m_showDecimal) { std::cout << std::setprecision(2) << std::fixed; }
        else { std::cout << std::setprecision(0) << std::fixed; }

        std::cout << "center = (" << _circle.center().x << ", " << _circle.center().y
            << "), radius = " << _circle.radius() << std::endl;

    }

    void operator()(Square const& _square) const
    {
        if (m_useCap) { std::cout << "SQUARE: "; }
        else { std::cout << "square: "; }

        if (m_showDecimal) { std::cout << std::setprecision(2) << std::fixed; }
        else { std::cout << std::setprecision(0) << std::fixed; }

        std::cout << "center = (" << _square.center().x << ", " << _square.center().y
            << "), side = " << _square.side() << std::endl;
    }

private:
    bool m_useCap;
    bool m_showDecimal;
};


class PrintStrategy2
{
public:
    PrintStrategy2() {}

    void operator()(Circle const& _circle) const
    {
        std::cout << "circle: " << std::endl;
        std::cout << "     center = (" << _circle.center().x << ", " << _circle.center().y << ")" << std::endl;
        std::cout << "     radius = " << _circle.radius() << std::endl;

    }

    void operator()(Square const& _square) const
    {
        std::cout << "square: " << std::endl;
        std::cout << "     center = (" << _square.center().x << ", " << _square.center().y << ")" << std::endl;
        std::cout << "     side = " << _square.side() << std::endl;
    }

private:
    bool m_useCap;
    bool m_showDecimal;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      SHAPE                                                  |
+------------------------------------------------------------------------------------------------------------*/

// Shape class, with a ShapeType (data) and a PrintStrategy (behavior)
class Shape
{
public:

    template< typename ShapeT, typename DrawStrategy >
    Shape(ShapeT const& _shape, DrawStrategy const& _drawer)
        : m_pImpl{ std::make_unique< Model< ShapeT,DrawStrategy > >(_shape, _drawer) }
    {}

    Shape(Shape const& other)
        : m_pImpl{ other.m_pImpl->clone() }
    {}

    Shape& operator=(const Shape& other)
    {
        // Copy-and-swap idiom
        Shape tmp(other);
        std::swap(m_pImpl, tmp.m_pImpl);
        return *this;
    }

    ~Shape() = default;
    Shape(Shape&&) = default;
    Shape& operator=(Shape&&) = default;

    void print() const { m_pImpl->print_ft(); }

private:

    // External Polymorphism design pattern:

    // Abstract Shape class (defines behavior, e.g., is printable)
    struct Concept 
    {
        virtual ~Concept() = default;
        virtual void print_ft() const = 0;

        virtual std::unique_ptr<Concept> clone() const = 0;  // Prototype design pattern
    };

    // Template implementation of the ShapeConcept
    template< typename ShapeT, typename PrintStrategy >
    struct Model : public Concept
    {
        explicit Model(ShapeT _shape, PrintStrategy _print)
            : m_shape(_shape), m_print(_print)
        {}

        void print_ft() const {
            m_print(m_shape); // use provided print strategy
        }

        std::unique_ptr<Concept> clone() const final { return std::make_unique<Model>(*this); }

        ShapeT m_shape;
        PrintStrategy m_print;
    };

    std::unique_ptr<Concept> m_pImpl;  // Bridge design pattern (pimpl idiom)
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      MAIN                                                   |
+------------------------------------------------------------------------------------------------------------*/


int main()
{
    std::vector<Shape> shapes;

    Shape circle1(Circle(Point(1.0, 1.0), 11.0), PrintStrategy1(false, true));
    Shape circle2(Circle(Point(2.0, 2.0), 12.0), PrintStrategy1(true, false));
    Shape circle3(Circle(Point(3.0, 3.0), 13.0), PrintStrategy2());

    Shape square1(Square(Point(4.0, 4.0), 14.0), PrintStrategy1(true, true));
    Shape square2(Square(Point(5.0, 5.0), 15.0), PrintStrategy2());

    shapes.insert(shapes.end(), { circle1, circle2, circle3, square1, square2 });

    Shape circle4(circle1);
    Shape square3(square2);
    shapes.insert(shapes.end(), { circle4, square3 });
 

    for (auto const& shape : shapes) {
        shape.print();
    }

    return EXIT_SUCCESS;
}
