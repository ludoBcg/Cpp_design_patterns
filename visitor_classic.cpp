/*********************************************************************************************************************
 *
 * visitor_classic.cpp
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
|                                                  SHAPEVISITOR                                               |
+-------------------------------------------------------------------------------------------------------------*/

class Circle;
class Square;

class ShapeVisitor
{
 public:
   virtual ~ShapeVisitor() = default;

   // visit Circle
   virtual void visit( Circle const& ) const = 0;
   // visit Square
   virtual void visit( Square const& ) const = 0;
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

   // accept visitor
   virtual void accept( ShapeVisitor const& _v ) = 0;

   Point  center() const { return m_center; }

protected:
    Point m_center;
};

using Shapes = std::vector< std::unique_ptr<Shape> >;


/*------------------------------------------------------------------------------------------------------------+
|                                                      CIRCLE                                                 |
+-------------------------------------------------------------------------------------------------------------*/

class Circle : public Shape
{
 public:
   explicit Circle( double _radius )
      : m_radius( _radius )
   {}

   // calls visitor visit() function for Circle
   void accept( ShapeVisitor const& _v ) override { _v.visit(*this); }

   double radius() const { return m_radius; }

 private:
   double m_radius;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      SQUARE                                                 |
+-------------------------------------------------------------------------------------------------------------*/

class Square : public Shape
{
 public:
   explicit Square( double _side )
      : m_side( _side )
   {}

   // calls visitor visit() function for Circle
   void accept( ShapeVisitor const& _v ) override { _v.visit(*this); }

   double side() const { return m_side; }

 private:
   double m_side;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                   AREAVISITOR                                               |
+-------------------------------------------------------------------------------------------------------------*/

class AreaVisitor : public ShapeVisitor
{
public:
    explicit AreaVisitor(double _scale = 1.0) : m_scale(_scale) {}

    // compute and print area of a scaled Circle
    void visit(Circle const& _circle) const override
    {
        std::cout << "circle: radius=" << _circle.radius()
            << ", scale = " << m_scale
            << ", area = " << M_PI * pow(_circle.radius() * m_scale , 2) << std::endl;
    }

    // compute and print area of a scaled Square
    void visit(Square const& _square) const override
    {
        std::cout << "square: side=" << _square.side()
            << ", scale = " << m_scale
            << ", area = " << _square.side() * m_scale * _square.side() * m_scale << std::endl;
    }

private:
    double m_scale = 1.0;

};


/*------------------------------------------------------------------------------------------------------------+
|                                                      MAIN                                                   |
+-------------------------------------------------------------------------------------------------------------*/

void areaAllShapes( Shapes const& _shapes )
{
   for( auto const& shape : _shapes )
   {
      shape->accept(AreaVisitor(1.0));
   }
}

int main()
{
   Shapes shapes{};

   shapes.emplace_back( std::make_unique<Circle>( 2.3 ) );
   shapes.emplace_back( std::make_unique<Square>( 1.2 ) );
   shapes.emplace_back( std::make_unique<Circle>( 4.1 ) );

   areaAllShapes( shapes );

   return EXIT_SUCCESS;
}
