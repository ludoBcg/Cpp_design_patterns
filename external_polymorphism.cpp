/*********************************************************************************************************************
 *
 * external_polymorphism.cpp
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

    void print() const {
        std::cout << "Circle: center = (" << m_center.x << ", " << m_center.y
            << "), radius = " << m_radius << std::endl;
    }
    
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
|                                                   SHAPECONCEPT                                              |
+------------------------------------------------------------------------------------------------------------*/

// Abstract Shape class (defines behavior, e.g., is printable)
class ShapeConcept
{
public:
    virtual ~ShapeConcept() = default;
    virtual void print() const = 0;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                   SHAPEMODEL V1                                             |
+------------------------------------------------------------------------------------------------------------*/

// Collection of print functions
void print_ft(Circle const& _circle)
{
    std::cout << "Circle: center = (" << _circle.center().x << ", " << _circle.center().y
              << "), radius = " << _circle.radius() << std::endl;
}
void print_ft(Square const& _square)
{
    std::cout << "Square: center = (" << _square.center().x << ", " << _square.center().y
              << "), side = " << _square.side() << std::endl;
}


// Template implementation of the ShapeConcept (i.e., can creates a Circle of Square ShapeModel)
template< typename ShapeT >
class ShapeModelv1 : public ShapeConcept
{
public:
    explicit ShapeModelv1(ShapeT _shape)
        : m_shape(_shape)
    {}

    void print() const {
        print_ft(m_shape); // call appropriate print function depending on Shape Type
    }

private:
    ShapeT m_shape;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                   SHAPEMODEL V2                                             |
+------------------------------------------------------------------------------------------------------------*/

// Template implementation of the ShapeConcept, with template print behavior (Strategy)
template< typename ShapeT, typename PrintStrategy >
class ShapeModelv2 : public ShapeConcept
{
public:
    explicit ShapeModelv2(ShapeT _shape, PrintStrategy _print)
        : m_shape(_shape), m_print(_print)
    {}

    void print() const {
        m_print(m_shape); // use provided print strategy
    }

private:
    ShapeT m_shape;
    PrintStrategy m_print;
};


// Collection of print functions, with different options
class PrintStrategy
{
public:
    explicit PrintStrategy(bool _useCap, bool _showDecimals)
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


/*------------------------------------------------------------------------------------------------------------+
|                                                      MAIN                                                   |
+------------------------------------------------------------------------------------------------------------*/



int main()
{
    std::vector< std::unique_ptr<ShapeConcept> > shapes;

    // Test v1
    shapes.push_back( std::make_unique< ShapeModelv1<Circle> >( Circle(Point(0.0, 0.0), 10.0) ) );
    shapes.push_back( std::make_unique< ShapeModelv1<Square> >( Square(Point(1.0, 1.0), 11.0) ) );
    shapes.push_back( std::make_unique< ShapeModelv1<Circle> >( Circle(Point(2.0, 2.0), 12.0) ) );

    for (auto const& shape : shapes) {
        shape->print();
    }

    std::cout << std::endl;

    // Test v2
    shapes.clear();
    shapes.push_back( std::make_unique< ShapeModelv2<Circle, PrintStrategy> >( Circle(Point(3.0, 3.0), 13.0), PrintStrategy(false, true) ) );
    shapes.push_back( std::make_unique< ShapeModelv2<Square, PrintStrategy> >( Square(Point(4.0, 4.0), 14.0), PrintStrategy(true, false) ) );
    shapes.push_back( std::make_unique< ShapeModelv2<Circle, PrintStrategy> >( Circle(Point(5.0, 5.0), 15.0), PrintStrategy(true, true) ) );

    for (auto const& shape : shapes) {
        shape->print();
    }

    return EXIT_SUCCESS;
}
