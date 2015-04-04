#ifndef __INTERACTION_H__
#define __INTERACTION_H__
#include <typeinfo>
#include <string>
#include "tuple_type.h"

template <class T, class U>
void call_action(void* this_, const U& u)
{
    T& t = *static_cast<T*>(this_);
    t.action(u);
}

template <class T>
using act_ptr = void (*)(void*, const T&);

template <class ...Args>
class Interaction
{
protected:
    const std::tuple<act_ptr<Args>...>* vtable;
public:
    template <class T>
    struct vtable_init {
        const static std::tuple<act_ptr<Args>...> vtable;
    };
    template <class T>
    Interaction(T*)
    {
        vtable = &vtable_init<T>::vtable;
    }
    template <class T>
    void callAction(const T& t)
    {
       get_by_type<act_ptr<T>>(*vtable)(this, t);
    }
    template <class T>
    void action(const T&)
    {
        std::cout << "call base for " << typeid(T).name() << std::endl;
    }

    virtual void onAction(Interaction<Args...>& b) = 0;
};
template <class ...Args>
template <class T>
const std::tuple<act_ptr<Args>...> Interaction<Args...>::vtable_init<T>::vtable = std::tuple<act_ptr<Args>...>{(&call_action<T, Args>)...};
#endif
