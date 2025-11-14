#pragma once
#include <Widgets/Block/BlockBase.h>

class PW_API BlockLabel : public BlockBase
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数，用于创建一个 BlockLabel 对象。
     * 
     * @param parent 指向父窗口部件的指针，默认为 nullptr。
     */
    explicit BlockLabel(QWidget *parent = nullptr);

    /**
     * @brief 析构函数，用于销毁一个 BlockLabel 对象。
     */
    ~BlockLabel();
};
