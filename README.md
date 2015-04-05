# interaction
This is a sample use template and tuple to make a vtable manually.

Since C++11 doesn't prvide a method to get an element from tuple by type,
I make that get-by-type function so that this source can compile with C++11.

This vtable perform like a virtual template function witch doesn't support by language.

You can define the default action as a template function in the base class
and overload it in the derived class.
The correct method will be called by the correct type of objects.

As the source in interaction.cpp:
```C++
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
    
    void action(B* b)
    {
        cout << "call A for B" << endl;
    }
    void action(C* c)
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
    void action(A* a)
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
    void action(A* a)
    {
        cout << "call C for A" << endl;
    }
    void action(B* a)
    {
        cout << "call C for B" << endl;
    }
};
```
We defined three type with the interaction from A to B, C; from B to A and from C to A, B.
```C++
        InteractionBase* a = new A(), *b = new B(), *c = new C();
    a->onAction(a);
    b->onAction(a);
    c->onAction(a);
    a->onAction(b);
    b->onAction(b);
    c->onAction(b);
    a->onAction(c);
    b->onAction(c);
    c->onAction(c);
```
Run these code will get output like this even we don't know the type of all the objects:
```
call base for 1A
call A for B
call A for C
call B for A
call base for 1B
call base for 1C
call C for A
call C for B
call base for 1C
```
#Compile
```
g++ interaction.cpp --std=c++11
