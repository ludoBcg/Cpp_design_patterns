/*********************************************************************************************************************
 *
 * decorator.cpp
 *
 * Cpp_design_patterns
 * Ludovic Blache
 *
 *********************************************************************************************************************/

 // https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Decorator

#include <iostream>
# define _USE_MATH_DEFINES
#include <math.h>


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

// abstract Widget
class Widget
{
public:

    Widget()
        : m_size(0.0)
        , m_center{ 0.0, 0.0 }
        , m_title("abstract widget")
    {}

    virtual ~Widget() = default;

    virtual void print() const
    {
        std::cout << std::endl 
                  << "Title = " << m_title << "  "
                  << "Center = ( " << m_center.x << " , " << m_center.y << " )  "
                  << "Size = " << m_size << "  "
                  << std::endl;
    }

    // to be implemented in decorators
    virtual void render() = 0;

protected:

    Point m_center;
    double m_size;
    std::string m_title;
};

#endif


/*------------------------------------------------------------------------------------------------------------+
|                                                  WIDGETMODEL1                                               |
+-------------------------------------------------------------------------------------------------------------*/

#ifndef _WIDGETMODEL1_H_
#define _WIDGETMODEL1_H_

// Concrete Widget (could be others)
class WidgetModel1 : public Widget
{
public:

    WidgetModel1()
    {
        this->m_title = "widget model 1";
    }

    WidgetModel1(Point _center, double _size, std::string _title)
    {
        m_size = _size;
        m_center = _center;
        m_title = _title;
    }

    virtual ~WidgetModel1() = default;

    void render()
    {
        std::cout << "  draw widget" << std::endl;;
    }

};

#endif


/*------------------------------------------------------------------------------------------------------------+
|                                                 WIDGETDECORATOR                                             |
+-------------------------------------------------------------------------------------------------------------*/

#ifndef _WIDGETDECORATOR_H_
#define _WIDGETDECORATOR_H_

// Abstract Widget Decorator
class WidgetDecorator : public Widget
{
public:

    WidgetDecorator(std::shared_ptr<Widget> _widget)
    {
        m_widget = _widget;
    }

    virtual ~WidgetDecorator() = default;

    virtual void print() const = 0;

protected:
    std::shared_ptr<Widget> m_widget = nullptr;

};

#endif


/*------------------------------------------------------------------------------------------------------------+
|                                                  COLORDECORATOR                                             |
+-------------------------------------------------------------------------------------------------------------*/

#ifndef _COLORDECORATOR_H_
#define _COLORDECORATOR_H_

// Decorator to add color in rendering of a Widget
class ColorDecorator : public WidgetDecorator
{
public:

    ColorDecorator(std::shared_ptr<Widget> _widget)
        : WidgetDecorator(_widget)
    {}
    virtual ~ColorDecorator() = default;

    virtual void print() const
    {
        m_widget->print();
        std::cout << "Option = color " << std::endl;
    }

    void render()
    {
        std::cout << "  activate color" << std::endl;
        m_widget->render();
        std::cout << "  deactivate color" << std::endl;
    }

};

#endif


/*------------------------------------------------------------------------------------------------------------+
|                                                  ALPHADECORATOR                                             |
+-------------------------------------------------------------------------------------------------------------*/

#ifndef _ALPHADECORATOR_H_
#define _ALPHADECORATOR_H_

// Decorator to add alpha blending in rendering of a Widget
class AlphaDecorator : public WidgetDecorator
{
public:

    AlphaDecorator(std::shared_ptr<Widget> _widget)
        : WidgetDecorator(_widget)
    {}
    virtual ~AlphaDecorator() = default;

    virtual void print() const
    {
        m_widget->print();
        std::cout << "Option = alpha blending " << std::endl;
    }

    void render()
    {
        std::cout << "  activate alpha blending" << std::endl;
        m_widget->render();
        std::cout << "  deactivate alpha blending" << std::endl;
    }

};

#endif


/*------------------------------------------------------------------------------------------------------------+
|                                                  SHADOWDECORATOR                                            |
+-------------------------------------------------------------------------------------------------------------*/

#ifndef _SHADOWDECORATOR_H_
#define _SHADOWDECORATOR_H_

// Decorator to add shadow effect in rendering of a Widget
class ShadowDecorator : public WidgetDecorator
{
public:

    ShadowDecorator(std::shared_ptr<Widget> _widget)
        : WidgetDecorator(_widget)
    {}
    virtual ~ShadowDecorator() = default;

    virtual void print() const
    {
        m_widget->print();
        std::cout << "Option = shadow " << std::endl;
    }

    void render()
    {
        std::cout << "  activate shadow" << std::endl;
        m_widget->render();
        std::cout << "  deactivate shadow" << std::endl;
    }

};

#endif


/*------------------------------------------------------------------------------------------------------------+
|                                                      MAIN                                                   |
+-------------------------------------------------------------------------------------------------------------*/

int main()
{
    // Create a default Widget
    std::shared_ptr<Widget> widget1 = std::make_shared<WidgetModel1>();
    widget1->print();
    std::cout << "Rendering pipeline: " << std::endl;
    widget1->render();
    // add color feature
    widget1 = std::make_shared <ColorDecorator>(widget1);
    widget1->print();
    std::cout << "Rendering pipeline: " << std::endl;
    widget1->render();
    // add alpha blending feature
    widget1 = std::make_shared<AlphaDecorator>(widget1);
    widget1->print();
    std::cout << "Rendering pipeline: " << std::endl;
    widget1->render();

    // Create another Widget
    Point p = { 1, 2 };
    WidgetModel1 w(p, 10.0, "custom widget");
    std::shared_ptr<Widget> widget2 = std::make_shared<WidgetModel1>(w);
    // add alpha blending feature
    widget2 = std::make_shared<ShadowDecorator>(widget2);
    widget2->print();
    std::cout << "Rendering pipeline: " << std::endl;
    widget2->render();


    return EXIT_SUCCESS;
}
