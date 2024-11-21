/*********************************************************************************************************************
 *
 * flyweight.cpp
 *
 * Cpp_design_patterns
 * Ludovic Blache
 *
 *********************************************************************************************************************/

 // See https://gameprogrammingpatterns.com/flyweight.html
 //     https://refactoring.guru/design-patterns/flyweight/cpp/example

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
|                                                     WIDGET                                                  |
+-------------------------------------------------------------------------------------------------------------*/

#ifndef _WIDGET_H_
#define _WIDGET_H_

class Widget
{
    public:

        Widget() {}

        explicit Widget(double _size, Point _position, std::string _title, std::string _texture, std::string _content)
            : m_size(_size)
            , m_position{ _position }
            , m_title(_title)
            , m_texture(_texture)
            , m_content(_content)
        {}

        // Copy constructor
        Widget(Widget const& _other )
            : m_size( _other.m_size )
            , m_position{ _other.m_position }
            , m_title(_other.m_title)
            , m_texture(_other.m_texture)
            , m_content(_other.m_content)
        {}

        // Copy assignment operator
        Widget& operator=(Widget const& _other)
        {
            m_size = _other.m_size;
            m_position = _other.m_position;
            m_title = _other.m_title;
            m_texture = _other.m_texture;
            m_content = _other.m_content;

            return *this; 
        }

        virtual ~Widget()
        {}

        void print() const
        {
            std::cout << "Title: " << m_title 
                      << "\nPosition: (" << m_position.x << " " << m_position.y << ")"
                      << "\nSize: " << m_size
                      << "\nTexture: " << m_texture
                      << "\nContent: " << m_content
                      << "\n" << std::endl;
        }

    protected:
   
        Point m_position = { 0.0, 0.0 };
        double m_size = 0.0;
        std::string m_title = "default widget";

        // some data
        std::string m_texture = "##########";
        std::string m_content = "abcdefghij";
};

#endif


/*------------------------------------------------------------------------------------------------------------+
|                                                   WIDGETOWNER                                               |
+-------------------------------------------------------------------------------------------------------------*/

#ifndef _WIDGETOWNER_H_
#define _WIDGETOWNER_H_

class WidgetOwner
{
    public:

        WidgetOwner()
            : m_widgetA()
            , m_widgetB(10, { 10.0, 10.0 }, "widgetB", "@@@@@@@@@@", "0123456789")
            , m_widgetC(20, { 20.0, 20.0 }, "widgetC", "&&&&&&&&&&", "ipsum lorem")
        {}

        virtual ~WidgetOwner() = default;

        WidgetOwner(WidgetOwner const& _other)
            : m_widgets(_other.m_widgets)
            , m_widgetA(_other.m_widgetA)
            , m_widgetB(_other.m_widgetB)
            , m_widgetC(_other.m_widgetC)
        {}

        WidgetOwner& operator=(WidgetOwner const& _other)
        {
            m_widgets = _other.m_widgets;
            m_widgetA = _other.m_widgetA;
            m_widgetB = _other.m_widgetB;
            m_widgetC = _other.m_widgetC;
            return *this;
        }

        void generateWidgets()
        {
            m_widgets = { &m_widgetA, &m_widgetA, &m_widgetB, &m_widgetC, &m_widgetB };
        }

        int size() { return m_widgets.size(); }

        const Widget& getWidget(int _id) const
        {
            if (_id >= m_widgets.size())
            {
                std::cerr << "out of range" << std::endl;
                _id %= m_widgets.size();
            }
            return *m_widgets.at(_id);
        }


    private:

        // store only one instance of each type of widget
        Widget m_widgetA;
        Widget m_widgetB;
        Widget m_widgetC;

        std::vector<Widget*> m_widgets;
};

#endif


/*------------------------------------------------------------------------------------------------------------+
|                                                      MAIN                                                   |
+-------------------------------------------------------------------------------------------------------------*/

int main()
{
    WidgetOwner widgetOwner;
    widgetOwner.generateWidgets();
    
    for(int i=0; i<widgetOwner.size(); i++)
        widgetOwner.getWidget(i).print();

     widgetOwner.getWidget(widgetOwner.size()).print();

    return EXIT_SUCCESS;
}
