/*********************************************************************************************************************
 *
 * observer.cpp
 *
 * Cpp_design_patterns
 * Ludovic Blache
 *
 *********************************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <list>



/*------------------------------------------------------------------------------------------------------------+
|                                                    OBSERVER                                                 |
+------------------------------------------------------------------------------------------------------------*/

#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Observer
{
    public:
        virtual ~Observer() {}

        // receive an update from subject (triggered by the Subject's Notify() method)
        virtual void Update(const std::string& _message) = 0;
};

#endif


/*------------------------------------------------------------------------------------------------------------+
|                                                    SUBJECT                                                  |
+------------------------------------------------------------------------------------------------------------*/

#ifndef _SUBJECT_H_
#define _SUBJECT_H_

class Subject
{
    public:
        virtual void Attach(Observer* _observer) = 0;
        virtual void Detach(Observer* _observer) = 0;

        // send an update to observers (by calling their Update() method)
        virtual void Notify() = 0;

    protected:
        std::list<Observer*> m_listObservers;
};

#endif


/*------------------------------------------------------------------------------------------------------------+
|                                                   MYOBSERVER                                                |
+------------------------------------------------------------------------------------------------------------*/


#ifndef _MYOBSERVER_H_
#define _MYOBSERVER_H_

class MyObserver : public Observer
{
    public:
        MyObserver(Subject& _subject, std::string _name) 
            : m_subject(_subject)
            , m_name(_name)
        {
            // join the subject's list of observers
            this->m_subject.Attach(this);
        }

        virtual ~MyObserver() 
        {}

        void Update(const std::string& _msgFromSubject) override 
        {
            m_msgFromSubject = _msgFromSubject;
            std::cout << this->m_name << " has received a new message: " << this->m_msgFromSubject << "\n";
        }

        void RemoveMeFromTheList() 
        {
            // Leave the subject's list of observers
            m_subject.Detach(this);
        }


    private:
        
        Subject& m_subject;
        std::string m_name;
        std::string m_msgFromSubject;
};

#endif


/*------------------------------------------------------------------------------------------------------------+
|                                                   MYSUBJECT                                                 |
+------------------------------------------------------------------------------------------------------------*/


#ifndef _MYSUBJECT_H_
#define _MYSUBJECT_H_

class MySubject : public Subject 
{
    public:

        virtual ~MySubject()
        {
            m_listObservers.clear();
        }

        // Add an Observer to the list
        void Attach(Observer* _observer) override 
        {
            m_listObservers.push_back(_observer);
        }

        // Remove an Observer from the list
        void Detach(Observer* _observer) override 
        {
            m_listObservers.remove(_observer);
        }

        // Send an message to all Observers in the list
        void Notify() override 
        {
            std::list<Observer*>::iterator iterator = m_listObservers.begin();

            while (iterator != m_listObservers.end()) 
            {
                (*iterator)->Update(m_message);
                ++iterator;
            }
        }

        void publishMessage(std::string message = "Empty") 
        {
            this->m_message = message;
            Notify();
        }


    private:
  
        std::string m_message;
};

#endif


/*------------------------------------------------------------------------------------------------------------+
|                                                      MAIN                                                   |
+-------------------------------------------------------------------------------------------------------------*/

int main()
{
    // instanciate 2 Subjects (publishers)
    MySubject publisher1;
    MySubject publisher2;

    // instanciate 2 Observers (subscribers)
    MyObserver subscriber1(publisher1, "Subscriber 1");
    MyObserver subscriber2(publisher2, "Subscriber 2");

    // publish messages
    publisher1.publishMessage("News A from Publisher One");
    publisher2.publishMessage("News A from Publisher Two");

    // add another Observer
    MyObserver subscriber3(publisher2, "Subscriber 3");

    // publish messages
    publisher1.publishMessage("News B from Publisher One");
    publisher2.publishMessage("News B from Publisher Two");

    // remove Observers
    subscriber1.RemoveMeFromTheList();
    subscriber3.RemoveMeFromTheList();

    // publish messages
    publisher1.publishMessage("News C from Publisher One");
    publisher2.publishMessage("News C from Publisher Two");


    return EXIT_SUCCESS;
}
