%{Cpp:LicenseTemplate}\
#include "%{JS: Util.relativeFilePath('%{Path}/%{HdrFileName}', '%{Path}' + '/' + Util.path('%{SrcFileName}'))}"
@if %{JS: QtSupport.uiAsPointer() }
#include "%{UiHdrFileName}"
@endif
%{JS: Cpp.openNamespaces('%{Class}')}\

%{CN}::%{CN}(QWidget *parent)
    : %{BaseClass}(parent)
@if %{JS: QtSupport.uiAsPointer() }
    , ui(new Ui::%{CN})
@endif
{
@if %{JS: QtSupport.uiAsPointer() }
    ui->setupUi(this);
@elsif %{JS: QtSupport.uiAsMember() }
    ui.setupUi(this);
@else
    setupUi(this);
@endif
}

%{CN}::~%{CN}()
{
@if %{JS: QtSupport.uiAsPointer() }
    delete ui;
@endif
}

%{JS: Cpp.closeNamespaces('%{Class}')}\
