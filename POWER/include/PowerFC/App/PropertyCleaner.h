#ifndef _POWERFC_APP_PROPERTYCLEANER_H_
#define _POWERFC_APP_PROPERTYCLEANER_H_
#pragma once
#include <memory>
#include <vector>

namespace app {
class Property;
}

namespace app {
/**
* @brief 定义了一个名为 PropertyCleaner 的结构体，其目的是通过延迟销毁动态属性（Property 对象）来使其删除操作更安全。
动态属性可能会在任何时候被删除，甚至在触发其 onChanged() 信号的过程中。为了避免在信号处理过程中删除属性而导致未定义行为，
PropertyCleaner 通过将删除的属性放入一个队列中，并在适当的时候进行销毁。有些类似于Qt的deletelater()机制。
比如当前在操作属性对象A，那么在操作A的过程中，如果需要删除属性对象B，则调用B->DeleteLater(),将其加入到removed_properties队列中，
当操作A完成时，会调用PropertyCleaner的析构函数，此时会检查removed_properties队列，如果队列中A之后有属性对象，则执行删除B的动作。
* 
*/
struct PropertyCleaner
{
    PropertyCleaner(Property* property);

    ~PropertyCleaner();

    static void Add(std::unique_ptr<Property>&& property_to_remove);

    private:
    friend Property;
    private:

    Property* property;
    static std::vector<std::unique_ptr<Property>> removed_properties;  //使用unique_ptr来管理已移除的属性对象，确保cleaner拥有唯一的删除权
    static int cleaner_count;
};

}  // namespace app

#endif