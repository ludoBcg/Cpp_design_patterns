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

class Shape
{
 public:
    Shape()
        :center_()
    {}

   virtual ~Shape() = default;

   // accept visitor
   virtual void accept( ShapeVisitor const& v ) = 0;

   Point  center() const { return center_; }

protected:
    Point center_;
};

using Shapes = std::vector< std::unique_ptr<Shape> >;


/*------------------------------------------------------------------------------------------------------------+
|                                                      CIRCLE                                                 |
+-------------------------------------------------------------------------------------------------------------*/

class Circle : public Shape
{
 public:
   explicit Circle( double radius )
      : radius_( radius )
   {}

   // calls visitor visit() function for Circle
   void accept( ShapeVisitor const& v ) override { v.visit(*this); }

   double radius() const { return radius_; }

 private:
   double radius_;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      SQUARE                                                 |
+-------------------------------------------------------------------------------------------------------------*/

class Square : public Shape
{
 public:
   explicit Square( double side )
      : side_( side )
   {}

   // calls visitor visit() function for Circle
   void accept( ShapeVisitor const& v ) override { v.visit(*this); }

   double side() const { return side_; }

 private:
   double side_;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                   AREAVISITOR                                               |
+-------------------------------------------------------------------------------------------------------------*/

class AreaVisitor : public ShapeVisitor
{
public:
    explicit AreaVisitor(double _scale = 1.0) : m_scale(_scale) {}

    // compute and print area of a scaled Circle
    void visit(Circle const& circle) const override
    {
        std::cout << "circle: radius=" << circle.radius()
            << ", scale = " << m_scale
            << ", area = " << M_PI * pow(circle.radius() * m_scale , 2) << std::endl;
    }

    // compute and print area of a scaled Square
    void visit(Square const& square) const override
    {
        std::cout << "square: side=" << square.side()
            << ", scale = " << m_scale
            << ", area = " << square.side() * m_scale * square.side() * m_scale << std::endl;
    }

private:
    double m_scale = 1.0;

};


/*------------------------------------------------------------------------------------------------------------+
|                                                      MAIN                                                   |
+-------------------------------------------------------------------------------------------------------------*/

void areaAllShapes( Shapes const& shapes )
{
   for( auto const& shape : shapes )
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
