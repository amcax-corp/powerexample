#ifndef SELECTIONBLOCKER_H
#define SELECTIONBLOCKER_H

#include "PFCGlobal.h"
#include <functional>
#include <memory>

namespace gui {
/// 阻塞器
/// 当析构时，自动执行恢复函数
class PFC_GUI_API SelectionBlocker
{
public:
    SelectionBlocker(const SelectionBlocker&) = delete;
    SelectionBlocker& operator=(const SelectionBlocker&) = delete;
    SelectionBlocker(SelectionBlocker&&) noexcept;
    SelectionBlocker& operator=(SelectionBlocker&&) noexcept;
    ~SelectionBlocker();
private:
    friend class SelectionSingleton;
    explicit SelectionBlocker(std::function<void()>&& restore);

    std::function<void()> m_restore_function{};
};

/// 选择操作接力器
enum class SelectionResult;
class PFC_GUI_API SelectionRelay
{
public:
    SelectionRelay(const SelectionRelay&) = delete;
    SelectionRelay& operator=(const SelectionRelay&) = delete;
    SelectionRelay(SelectionRelay&&) = default;
    SelectionRelay& operator=(SelectionRelay&&) = default;
    ~SelectionRelay();

private:
    friend class SelectionSingleton;
    SelectionRelay();
};
}


#endif //SELECTIONBLOCKER_H
