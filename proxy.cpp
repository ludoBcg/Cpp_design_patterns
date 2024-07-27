/*********************************************************************************************************************
 *
 * proxy.cpp
 *
 * Cpp_design_patterns
 * Ludovic Blache
 *
 *********************************************************************************************************************/

 // https://refactoring.guru/design-patterns/proxy
 // https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Proxy

#include <iostream>
# define _USE_MATH_DEFINES
#include <math.h>


/*------------------------------------------------------------------------------------------------------------+
|                                                 ABSTRACTWIDGET                                              |
+------------------------------------------------------------------------------------------------------------*/

// Parent clas for both real widget and the proxy. 
#ifndef _ABSTRACTWIDGET_H_
#define _ABSTRACTWIDGET_H_

class AbstractWidget
{
public:

    virtual ~AbstractWidget() = default;

    virtual void print() const = 0;

    virtual double size() const = 0;
    virtual std::string title() const = 0;

    virtual void setSize(double _size) = 0;
    virtual void setTitle(std::string _title) = 0;

};

#endif


/*------------------------------------------------------------------------------------------------------------+
|                                                      WIDGET                                                 |
+------------------------------------------------------------------------------------------------------------*/

#ifndef _WIDGET_H_
#define _WIDGET_H_

// Actual Widget
class Widget : public AbstractWidget
{
public:

    Widget()
        : m_size(0.0)
        , m_title("default widget")
    {}

    Widget(double _size, std::string _title)
        : m_size(_size)
        , m_title(_title)
    {
        std::cout << "Widget(" << _size << ", " << _title << ")" << std::endl;
    }


    virtual ~Widget() = default;

    void print() const override
    {
        std::cout << "    Title = " << m_title << "\n"
            << "    Size = " << m_size << "  "
            << std::endl;
    }

    double size() const override { return m_size; }
    std::string title() const override { return m_title; }

    void setSize(double _size) override { 
        std::cout << "setSize(" << _size << ")" << std::endl;
        m_size = _size; 
    }
    void setTitle(std::string _title) override { 
        std::cout << "setTitle(" << _title << ")" << std::endl;
        m_title = _title; 
    }

protected:

    double m_size;
    std::string m_title;
};

#endif


/*------------------------------------------------------------------------------------------------------------+
|                                                    PROXYWIDGET                                              |
+------------------------------------------------------------------------------------------------------------*/

#ifndef _PROXYWIDGET_H_
#define _PROXYWIDGET_H_

class ProxyWidget : public AbstractWidget
{
public:

    ProxyWidget()
        : m_widget{ std::make_unique<Widget>() }
    {}

    ProxyWidget(double _size, std::string _title)
        : m_widget{ std::make_unique<Widget>(_size,  _title) }
    {}

    ~ProxyWidget() { }

    void print() const override
    {
        // transfer instruction to real widget, only if some conditions are met
        if (this->checkAccess())
        {
            this->m_widget->print();
        }
    }

    double size() const override { return m_widget->size(); }
    std::string title() const override { return m_widget->title(); }

    void setSize(double _size) override { m_widget->setSize(_size); }
    void setTitle(std::string _title) override { m_widget->setTitle(_title); }
    

protected:

    std::unique_ptr<Widget> m_widget = nullptr;

    bool checkAccess() const
    {
        // only print widget if its size is not null
        if (m_widget->size() != 0.0)
            return true;

        std::cout << "Do not print widgets of size zero." << std::endl;
        return false;
    }
};

#endif



/*------------------------------------------------------------------------------------------------------------+
|                                                      MAIN                                                   |
+------------------------------------------------------------------------------------------------------------*/

int main()
{
    // print default widget
    std::cout << "Using Widget:" << std::endl;
    Widget widget;
    widget.print();
    // print widget of size 1
    Widget widget2(1.0, "Widget of size 1");
    widget2.print();


    // create and print default widget using proxy
    std::cout << "\nUsing ProxyWidget:" << std::endl;
    std::unique_ptr<ProxyWidget> proxy = std::make_unique<ProxyWidget>();
    proxy->print();

    // change widget title using proxy and print
    proxy->setTitle("new title");
    proxy->print();

    // change widget size using proxy and print
    proxy->setSize(3.14);
    proxy->print();

    // change widget size to 0 using proxy and print
    proxy->setSize(0);
    proxy->print();

    // create and print widget of size 2 using proxy
    std::unique_ptr<ProxyWidget> proxy2 = std::make_unique<ProxyWidget>(2.0, "widget of size 2");
    proxy2->print();

    return EXIT_SUCCESS;
}
