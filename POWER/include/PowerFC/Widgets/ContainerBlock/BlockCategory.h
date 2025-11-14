#pragma once
#include <SARibbonCategory.h>
#include <Widgets/PowerWidgetsConfig.h>

class PW_API BlockCategory : public SARibbonCategory
{
    Q_OBJECT
public:
    BlockCategory(QWidget *parent = nullptr);
    ~BlockCategory();
};