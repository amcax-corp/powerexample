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

private:
    Ui::%{CN} *ui;

};
%{JS: Cpp.closeNamespaces('%{Class}')}\
#endif // %{GUARD}
