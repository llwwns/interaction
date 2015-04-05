#ifndef __INTERACTION_H__
#define __INTERACTION_H__
#include "tuple_type.h"

template <class T, class U>
void call_action(void* this_, U* u)
{
    static_cast<T*>(this_)->action(u);
}

template<class T, class U>
void call_action_base(void* this_, U* t)
{
    static_cast<U*>(this_)->callAction(static_cast<T*>(t));
}

template <class T>
using act_ptr = void (*)(void*, T*);

template <class ...Args>
class Interaction
{
protected:
    const std::tuple<act_ptr<Interaction<Args...>>, act_ptr<Args>...>* vtable;
public:
    template <class T>
    struct vtable_init {
        const static std::tuple<act_ptr<Interaction<Args...>>, act_ptr<Args>...> vtable;
    };
    template <class T>
    Interaction(T*)
    {
        vtable = &vtable_init<T>::vtable;
    }
    template <class T>
    void callAction(T* t)
    {
       get_by_type<act_ptr<T>>(*vtable)(this, t);
    }
    void action(Interaction<Args...>)
    {
        std::cout << "call default function" << std::endl;
    }

    void onAction(Interaction<Args...>* b) {
       get_by_type<act_ptr<Interaction<Args...>>>(*vtable)(b, this);
    }
};
template <class ...Args>
template <class T>
const std::tuple<act_ptr<Interaction<Args...>>, act_ptr<Args>...>
    Interaction<Args...>::vtable_init<T>::vtable = std::tuple_cat
    (
        std::make_tuple(&call_action_base<T, Interaction<Args...>>),
        std::make_tuple((&call_action<T, Args>)...)
    );
#endif
