/*********************************************************************************************************************
 *
 * class_design.cpp
 *
 * visitor_modern
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
+-------------------------------------------------------------------------------------------------------------*/

// only for data storage, avoid virtual functions as much as possible
class ShapeData
{
public:
    ShapeData()
        :center_()
    {}

    virtual ~ShapeData() = default;

    // no need for accept() function anymore
    // this class could be removed if there were no data to store (here center_ as an example)

    Point  center() const { return center_; }

protected:
    Point center_;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      CIRCLE                                                 |
+-------------------------------------------------------------------------------------------------------------*/

class Circle : public ShapeData
{
 public:
   explicit Circle( double radius )
      : radius_( radius )
   {}

   double radius() const { return radius_; }

 private:
   double radius_;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                      SQUARE                                                 |
+-------------------------------------------------------------------------------------------------------------*/

class Square : public ShapeData
{
 public:
   explicit Square( double side )
      : side_( side )
   {}

   double side() const { return side_; }

 private:
   double side_;
};


/*------------------------------------------------------------------------------------------------------------+
|                                                   AREAVISITOR                                               |
+-------------------------------------------------------------------------------------------------------------*/

class AreaVisitor
{
 public:
   explicit AreaVisitor(double _scale) : m_scale(_scale) {}

   ~AreaVisitor() = default;

   // compute and print area of a scaled Circle
   void operator()(Circle const& circle) const
   {
       std::cout << "circle: radius=" << circle.radius()
           << ", scale = " << m_scale
           << ", area = " << std::numbers::pi * pow(circle.radius() * m_scale , 2) << std::endl;
   }

   // compute and print area of a scaled Square
   void operator()(Square const& square) const
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

// a Shape is either a Circle or a Square
using Shape = std::variant<Circle, Square>;
using Shapes = std::vector< Shape >;

void areaAllShapes( Shapes const& shapes )
{
    for (auto const& shape : shapes)
    {
        // std::visit calls a callable (AreaVisitor) onto a variant (shape)
        // https://en.cppreference.com/w/cpp/utility/variant/visit
        std::visit(AreaVisitor(1.0), shape);
    }
}


int main()
{
   Shapes shapes{};

   shapes.emplace_back( Circle( 2.3 ) );
   shapes.emplace_back( Square( 1.2 ) );
   shapes.emplace_back( Circle( 4.1 ) );

   areaAllShapes( shapes );

   return EXIT_SUCCESS;
}
