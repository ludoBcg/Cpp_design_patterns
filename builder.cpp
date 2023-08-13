/*********************************************************************************************************************
 *
 * builder.cpp
 *
 * Cpp_design_patterns
 * Ludovic Blache
 *
 *********************************************************************************************************************/

// https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Builder

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

class Widget
{
public:

    Widget()
        : m_size(0.0)
        , m_center{ 0.0, 0.0 } 
        , m_title("default widget") 
    {}

    virtual ~Widget() = default;

    Point center() const { return m_center; }
    double size() const { return m_size; }
    std::string title() const { return m_title; }

    void setCenter(Point _center) {  m_center = _center; }
    void setSize(double _size) {  m_size = _size; }
    void setTitle(std::string _title) {  m_title = _title; }

    void print() const
    {
        std::cout << "Title = " << m_title << "  "
                  << "Center = ( " << m_center.x << " , " << m_center.y << " )  "
                  << "Size = " << m_size << "  "
                  << std::endl;
    }

protected:

    Point m_center;
    double m_size;
    std::string m_title;
};

#endif


/*------------------------------------------------------------------------------------------------------------+
|                                                   WIDGETBUILDER                                             |
+-------------------------------------------------------------------------------------------------------------*/

#ifndef _WIDGETBUILDER_H_
#define _WIDGETBUILDER_H_

// abstract builder
class WidgetBuilder
{

public:
    WidgetBuilder()
        : m_widget(nullptr)
    {}

    virtual ~WidgetBuilder() = default;

    std::shared_ptr<Widget> getWidget()
    {
        return m_widget;
    }
    void createNewWidget()
    {
        m_widget = std::make_shared<Widget>();
    }
    virtual void buildCenter() = 0;
    virtual void buildSize() = 0;
    virtual void buildTitle() = 0;

protected:
    std::shared_ptr<Widget> m_widget = nullptr;

};

#endif


/*------------------------------------------------------------------------------------------------------------+
|                                                SMALLWIDGETBUILDER                                           |
+-------------------------------------------------------------------------------------------------------------*/

#ifndef _SMALLWIDGETBUILDER_H_
#define _SMALLWIDGETBUILDER_H_

// builder for a small widget at position (0,0)
class SmallWidgetBuilder : public WidgetBuilder
{
public:
    SmallWidgetBuilder()
    {}

    virtual ~SmallWidgetBuilder() = default;

    virtual void buildCenter()
    {
        m_widget->setCenter({0, 0});
    }
    virtual void buildSize()
    {
        m_widget->setSize(1.0);
    }
    virtual void buildTitle()
    {
        m_widget->setTitle("Small widget");
    }
};

#endif


/*------------------------------------------------------------------------------------------------------------+
|                                                 BIGWIDGETBUILDER                                            |
+-------------------------------------------------------------------------------------------------------------*/

#ifndef _BIGWIDGETBUILDER_H_
#define _BIGWIDGETBUILDER_H_

// builder for a big widget at position (2,3)
class BigWidgetBuilder : public WidgetBuilder
{
public:
    BigWidgetBuilder()
    {}

    virtual ~BigWidgetBuilder() = default;

    virtual void buildCenter()
    {
        m_widget->setCenter({2, 3});
    }
    virtual void buildSize()
    {
        m_widget->setSize(10.0);
    }
    virtual void buildTitle()
    {
        m_widget->setTitle("Big widget");
    }
};

#endif


/*------------------------------------------------------------------------------------------------------------+
|                                               WIDGETBUILDEROWNER                                            |
+-------------------------------------------------------------------------------------------------------------*/

#ifndef _WIDGETBUILDEROWNER_H_
#define _WIDGETBUILDEROWNER_H_

// owns a widget builder
class WidgetBuilderOwner
{
public:

    WidgetBuilderOwner()
        : m_widgetBuilder(nullptr)
    {}

    virtual ~WidgetBuilderOwner() = default;

    void printWidget()
    {
        m_widgetBuilder->getWidget()->print();
    }
    void makeWidget(std::shared_ptr<WidgetBuilder> _widgetBuilder)
    {
        // use widget builder provided
        m_widgetBuilder = _widgetBuilder;
        // use it to create new widget
        m_widgetBuilder->createNewWidget();
        // use build functions
        m_widgetBuilder->buildCenter();
        m_widgetBuilder->buildSize();
        m_widgetBuilder->buildTitle();
    }

private:

    std::shared_ptr<WidgetBuilder> m_widgetBuilder = nullptr; 
};

#endif

/*------------------------------------------------------------------------------------------------------------+
|                                                      MAIN                                                   |
+-------------------------------------------------------------------------------------------------------------*/

int main()
{
    // instanciate different widget builders
    auto widgetBuilder1 = std::make_shared<SmallWidgetBuilder>();
    auto widgetBuilder2 = std::make_shared<BigWidgetBuilder>();

    // instanciate a single widget builder owner
    WidgetBuilderOwner widgetBuilderOwner;
    // provides widget builders to build and use a widget
    widgetBuilderOwner.makeWidget(widgetBuilder1);
    widgetBuilderOwner.printWidget();
    widgetBuilderOwner.makeWidget(widgetBuilder2);
    widgetBuilderOwner.printWidget();

    return EXIT_SUCCESS;
}
