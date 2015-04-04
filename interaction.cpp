#include <iostream>
#include "interaction.h"
using namespace std;
class A;
class B;
class C;
using InteractionBase = Interaction<A, B, C>;

class A : public InteractionBase
{
public:
    using InteractionBase::action;
    A() : InteractionBase(this) {
    }
    void onAction(InteractionBase& b) override
    {
        b.callAction(*this);
    }
    
    void action(const B& b)
    {
        cout << "call A for B" << endl;
    }
    void action(const C& c)
    {
        cout << "call A for C" << endl;
    }
};
class B : public InteractionBase
{
public:
    using InteractionBase::action;
    B() : InteractionBase(this) {
    }
    void onAction(InteractionBase& b) override
    {
        b.callAction(*this);
    }
    void action(const A& a)
    {
        cout << "call B for A" << endl;
    }
};
class C : public InteractionBase
{
public:
    using InteractionBase::action;
    C() : InteractionBase(this) {
    }
    void onAction(InteractionBase& b) override
    {
        b.callAction(*this);
    }
    void action(const A& a)
    {
        cout << "call C for A" << endl;
    }
    void action(const B& a)
    {
        cout << "call C for B" << endl;
    }
};

int main()
{
    InteractionBase* a = new A(), *b = new B(), *c = new C();
    a->onAction(*a);
    b->onAction(*a);
    c->onAction(*a);
    a->onAction(*b);
    b->onAction(*b);
    c->onAction(*b);
    a->onAction(*c);
    b->onAction(*c);
    c->onAction(*c);
}
