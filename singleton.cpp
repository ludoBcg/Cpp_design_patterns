/*********************************************************************************************************************
 *
 * singleton.cpp
 *
 * Cpp_design_patterns
 * Ludovic Blache
 *
 *********************************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <algorithm>


/*------------------------------------------------------------------------------------------------------------+
|                                                   SINGLETON                                                 |
+-------------------------------------------------------------------------------------------------------------*/

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

class Singleton
{
protected:

    // Hide constructors in protected field to prevent the class being instanciated from outside 
    Singleton()
        : m_val(0)
    { }

    virtual ~Singleton()
    { }

    int m_val = 0;

    // store instance as attribute
    //static Singleton* m_instance; // Pointer version


public:

    // Prevent copy/assignation
    Singleton(Singleton const& _other) = delete;
    Singleton(Singleton&& _other) = delete;
    Singleton& operator=(Singleton const& _other) = delete;
    Singleton& operator=(Singleton&& _other) = delete;

    void setVal(const int _val) { m_val = _val; }
    int getVal() const { return m_val; }

    // Static function to create/access instance
    static Singleton& instance() // Reference version
    {
        // static variable is not destroyed at the end of the function
        // will still exist at next call
        static Singleton theInstance;
        return theInstance;
    }

    //static Singleton* instance() // Pointer version
    //{
    //    if (m_instance == nullptr)
    //    {
    //        m_instance = new Singleton;
    //    }
    //    return m_instance;
    //}

};

//Singleton* Singleton::m_instance = nullptr; // Pointer version

#endif



/*------------------------------------------------------------------------------------------------------------+
|                                                      MAIN                                                   |
+-------------------------------------------------------------------------------------------------------------*/


int main()
{
   {
       std::cout << " Singleton " << &Singleton::instance() << " init value: " << Singleton::instance().getVal() << std::endl;
       Singleton::instance().setVal(1);
       std::cout << " Singleton " << &Singleton::instance() << " new value: " << Singleton::instance().getVal() << std::endl;
   }

   //{
   //     std::cout << " Singleton " << Singleton::instance() << " init value: " << Singleton::instance()->getVal() << std::endl;
   //     Singleton::instance()->setVal(1);
   //     std::cout << " Singleton " << Singleton::instance() << " new value: " << Singleton::instance()->getVal() << std::endl;
   //}

    return EXIT_SUCCESS;
}
