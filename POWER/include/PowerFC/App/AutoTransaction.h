#ifndef POWERFC_APP_AUTOTRANSACTION_H_
#define POWERFC_APP_AUTOTRANSACTION_H_
#pragma once
#include <PFCGlobal.h>
#include <cstddef>
#include <string_view>

namespace app {
class Application;

class PFC_APP_API AutoTransaction
{
  public:
    void* operator new(std::size_t) = delete;

  public:
    /** @brief 构造函数
    * @param name: 构造时可选的新事务名称（默认nullptr）
    * @param is_temporary: 若为true且新建事务，则给定的名称被视为临时名称，
    *                 后续构造本类或调用Application::SetActiveTransaction()时
    *                 可覆盖该事务名称
    * 
    * 本构造函数会递增内部计数器(Application::s_active_transaction_guard)。
    * 该计数器的作用：
    * 1. 阻止新建任何活动事务
    * 2. 当计数器未归零时，阻止当前活动事务的提交（即commit操作）
    * 注意：对事务中止(abort)操作无影响
    */
    AutoTransaction(std::string_view name = {}, bool is_temporary = false);

    /** @brief 析构函数
    * 本析构函数会递减内部计数器(Application::_activeTransactionGuard)，
    * 当计数器归零时，将提交(commit)当前所有活动事务
    */
    ~AutoTransaction();

    /** @brief 关闭或中止事务
    * 本函数用于显式关闭（即提交）事务，前提是当前事务ID与构造函数内创建的事务ID匹配。
    * 若设置is_abort_else_commit参数为true，则将中止当前任意活动中的事务。
    * 
    * @param is_abort_else_commit 是否执行中止操作（默认为false，即执行提交）
    *              
    * 注意：当is_abort_else_commit=true时，不受事务ID匹配限制，可强制中止任何活动事务
    */
    void Close(bool is_abort_else_commit = false);

    /**
    * 启用/禁用当前调用栈中的所有AutoTransaction实例
    * 
    * 一旦禁用：
    * 1. 将立即关闭所有空的临时命名事务
    * 2. 对于非空或非临时命名的活动事务，则不会自动关闭
    * 
    * 典型应用场景：
    * 例如在Gui::Document::SetEdit()中调用，
    * 允许事务跨越任何命令作用域而持续存活
    * 
    * @param enable 是否启用自动事务处理（true=启用，false=禁用）
    */
    static void SetEnable(bool enable);

  private:
    int m_transaction_id{0};  //事务ID
};
}  // namespace app

namespace app {

/**
    * 事务锁定辅助类（防止事务被意外关闭或中止）
    * 
    * 本辅助类用于保护关键事务免遭提前关闭，
    * 典型应用场景包括但不限于：
    * - 对象删除操作期间的事务保护
    * - 关键数据修改过程的事务保持
    * 
    * 实现原理：
    * 通过内部计数器维护锁定状态，
    * 在实例存活期间强制保持事务活跃
    */
class PFC_APP_API TransactionLocker
{
  public:
    /** Constructor
    * @param lock: whether to activate the lock
    */
    TransactionLocker(bool lock = true);

    /** Destructor
    * Unlock the transaction is this locker is active
    */
    ~TransactionLocker();

    /**
    * 激活/禁用当前事务锁
    * 
    * @param enable 是否激活锁（true=激活，false=禁用）
    * 
    * 内部采用计数器机制支持递归加锁：
    * 1. 激活期间，当前活动事务将禁止关闭或中止
    * 2. 所有关闭请求（通过Application::closeActiveTransaction调用）
    *    会被暂存，待内部锁计数器归零后执行
    * 
    * 典型应用场景：
    * - 递归函数调用中的事务保护
    * - 多步骤操作的事务一致性保证
    */
    void Activate(bool enable);

    /// Check if the locker is active
    bool IsActive() const
    {
        return m_is_active;
    }

    /// Check if transaction is being locked
    static bool IsLocked();

    friend class Application;

  private:
    bool m_is_active{false};  //是否激活锁定状态

  public:
    void* operator new(std::size_t) = delete;
};

}  // namespace app

#endif