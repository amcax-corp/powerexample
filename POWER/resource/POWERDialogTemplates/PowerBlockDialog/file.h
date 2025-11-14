%{JS: Cpp.licenseTemplate()}\
#ifndef %{GUARD}
#define %{GUARD}

// 如果包含头文件异常，请检查是否在Make(CMake/QMake)中添加了依赖库
#include <Widgets/ContainerBlock/%{BaseClass}.h>

namespace Ui { class %{CN}; }

class %{CN} : public %{BaseClass}
{

Q_OBJECT

public:
    %{CN}(QWidget *parent = nullptr);
    ~%{CN}();

public slots:
    // 点击确定时触发
    bool OnConfirmed() override;
    // 点击应用时触发
    bool OnApplied() override;
    // 点击重置时触发
    void OnResetted() override;
    // 点击取消时触发
    void OnCanceled() override;

private:
    Ui::%{CN} *ui;

};
%{JS: Cpp.closeNamespaces('%{Class}')}\
#endif // %{GUARD}
