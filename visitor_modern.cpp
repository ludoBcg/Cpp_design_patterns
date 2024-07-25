/*********************************************************************************************************************
 *
 * visitor_modern.cpp
 *
 * Cpp_design_patterns
 * Ludovic Blache
 *
 *********************************************************************************************************************/

#include <iostream>
#include <cmath>
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
+------------------------------------------------------------------------------------------------------------*/

// only for data storage, avoid virtual functions as much as possible
class ShapeData
{
public:
    ShapeData()
        :m_center()
    {}

    virtual ~ShapeData() = default;

    // no need for accept() function anymore
    // this class could be removed if there were no data to store (here m_center as an example)

    Point  center() const { return m_center; }

protected:
    Point m_center;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      CIRCLE                                                 |
+------------------------------------------------------------------------------------------------------------*/

class Circle : public ShapeData
{
 public:
   explicit Circle( double _radius )
      : m_radius( _radius )
   {}

   double radius() const { return m_radius; }

 private:
   double m_radius;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      SQUARE                                                 |
+------------------------------------------------------------------------------------------------------------*/

class Square : public ShapeData
{
 public:
   explicit Square( double _side )
      : m_side( _side )
   {}

   double side() const { return m_side; }

 private:
   double m_side;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                     TRIANGLE                                                |
+------------------------------------------------------------------------------------------------------------*/

class Triangle : public ShapeData
{
public:
    explicit Triangle(double _base, double _height)
        : m_base(_base), m_height(_height)
    {}

    double base() const { return m_base; }
    double height() const { return m_height; }

private:
    double m_base;
    double m_height;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                   PRINTVISITOR                                              |
+------------------------------------------------------------------------------------------------------------*/

class PrintVisitor
{
public:
    explicit PrintVisitor(){}

    ~PrintVisitor() = default;

    // print Circle data
    void operator()(Circle const& _circle) const
    {
        std::cout << "circle: radius=" << _circle.radius() << std::endl;
    }

    // pprint Square data
    void operator()(Square const& _square) const
    {
        std::cout << "square: side=" << _square.side() << std::endl;
    }

    // pprint Triangle data
    void operator()(Triangle const& _triangle) const
    {
        std::cout << "triangle: base=" << _triangle.base()
                  << ", height=" << _triangle.height() << std::endl;
    }
};


/*------------------------------------------------------------------------------------------------------------+
|                                                   AREAVISITOR                                               |
+------------------------------------------------------------------------------------------------------------*/

class AreaVisitor
{
 public:
   explicit AreaVisitor(double _scale) : m_scale(_scale) {}

   ~AreaVisitor() = default;

   // operator() can return a value

   // compute and return area of a scaled Circle
   double operator()(Circle const& _circle) const
   {
       return std::numbers::pi * pow(_circle.radius() * m_scale , 2);
   }

   // compute and return area of a scaled Square
   double operator()(Square const& _square) const
   {
       return _square.side() * m_scale * _square.side() * m_scale;
   }

   // compute and return area of a scaled Triangle
   double operator()(Triangle const& _triangle) const
   {
       return _triangle.base() * m_scale * _triangle.height() * m_scale * 0.5;
   }

private:
    double m_scale = 1.0;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      MAIN                                                   |
+------------------------------------------------------------------------------------------------------------*/

// a Shape is either a Circle, a Square, or a Triangle
using Shape = std::variant<Circle, Square, Triangle>;
using Shapes = std::vector< Shape >;

void visitAllShapes( Shapes const& _shapes )
{
    for (auto const& shape : _shapes)
    {
        // std::visit calls a callable (visitor) onto a variant (shape)
        // https://en.cppreference.com/w/cpp/utility/variant/visit

        std::visit(PrintVisitor(), shape);

        std::cout << "area = " <<  std::visit(AreaVisitor(2.0), shape) << std::endl;
    }
}


int main()
{
   Shapes shapes{};

   shapes.emplace_back( Circle( 2.3 ) );
   shapes.emplace_back( Square( 1.2 ) );
   shapes.emplace_back( Circle( 4.1 ) );
   shapes.emplace_back( Triangle( 2.1, 1.2 ) );

   visitAllShapes( shapes );

   return EXIT_SUCCESS;
}
