# 插件开发示例

## 项目简介

当前项目是基于 **九韶聚力 POWER 平台** 的示例项目，包含基本的工作台插件开发代码及其依赖框架。本项目展示了如何开发一个完整的 POWER 平台工作台插件，包括命令注册、对象管理、导航栏、视图提供者、GUI 对话框等功能模块。

### 编译运行

在安装完毕VS,Qt等工具之后，当前项目编译后会生成 `DevWorkbench.dll` 文件，输出到 `${POWER_HOME}/bin/<CONFIG>/Workbench/` 目录下。当 Power 主程序PowerFCMain.exe启动时，会自动加载该插件。加载成功后，点击 **"主页->新建"** 再点击 **"工作台->Dev"** 按钮即可查看当前Dev插件包含的所有功能的工具栏了。

---

## 目录结构

```
DevWorkbench/
├── Base/                          # 基础框架层
│   ├── Navigator/                 # 导航栏组件
│   ├── Object/                    # 数据对象定义
│   ├── ViewProvider/              # 视图提供者
│   ├── PartCollection.cpp/h       # 部件集合管理
│   ├── DevSetup.cpp/h             # Dev插件管理器
│   └── Utils.hpp                  # 工具函数
├── Command/                       # 命令层
├── Gui/                          # 图形界面层
├── Resources/                     # 资源文件夹
│   ├── feature/                   # 特征相关图标
│   ├── icon/                      # 各类图标资源
│   ├── lang/                      # 多语言翻译文件
│   ├── theme/                     # 界面主题样式
│   ├── py/                        # Python 脚本支持
├── __Loader.cpp                   # 插件加载入口
├── DevWorkbench.cpp/h             # 工作台主类
├── DevGlobal.h                    # 全局定义
└── CMakeLists.txt                 # CMake 构建配置
```

---

## 目录详解

### 1.  **根目录文件** 

-  **`__Loader.cpp`**   
  插件的动态库加载入口文件，导出 `CreateInstance()` 函数供主程序调用，用于创建工作台实例。

-  **`DevWorkbench.cpp/h`**   
  工作台主类实现，继承自 `gui::Workbench`。定义了插件的基本信息（名称、版本、图标）、菜单栏、工具栏列表等核心接口。

-  **`CMakeLists.txt`**   
  CMake 构建配置文件，定义了POWER_HOME路径、powerfc_toolchain.cmake文件路径(用于定义详细的组件依赖如AMCAX,Qt等)。

---

### 2.  **Base/ 文件夹 - 基础框架层** 

该文件夹包含插件的核心业务逻辑和数据模型，是插件功能的基础支撑层。

####  **Base/Object/ - 数据对象定义** 
-  **抽象层次** ：数据模型层（Model Layer）
-  **作用** ：定义插件中的各类业务对象，继承自 POWER 平台的 `DocumentObject`，实现对象的序列化、属性管理等功能。
-  **文件说明** ：
  - `DevObject.cpp/h`：基础对象-作为基类
  - `BoxObject.cpp/h`：Box对象
  - `CurvesLoftObject.cpp/h`：曲线放样对象
  - `RenderDistanceObject.cpp/h`：渲染距离对象

####  **Base/ViewProvider/ - 视图提供者** 
-  **抽象层次** ：视图层（View Layer）
-  **作用** ：为数据对象提供可视化表现，负责对象在 3D 视图中的渲染、被选择、被双击、被修改、高亮等场景下的显示逻辑。
-  **文件说明** ：
  - `ViewProviderBox.cpp/h`：Box对象视图提供者
  - `ViewProviderCurvesLoft.cpp/h`：曲线放样对象视图提供者
  - `ViewProviderRenderDistance.cpp/h`：渲染距离对象视图提供者

####  **Base/Navigator/ - 导航栏组件** 
-  **抽象层次** ：界面控制层（Controller Layer）
-  **作用** ：实现插件的导航面板（通常在主窗口左侧或右侧），用于显示对象树、属性面板等结构化数据。
-  **文件说明** ：
  - `PartNavigator.cpp/h`：部件导航栏，管理部件对象的树形展示
  - `ShapeTree.cpp/h`：形状树控件，用于显示当前Document页中所有部件的树形结构，支持右键菜单操作对象

####  **其他文件** 
-  **`PartCollection.cpp/h`** ：部件集合管理类，用于管理和操作部件对象。
-  **`DevSetup.cpp/h`** ：Dev插件管理器
-  **`Utils.hpp`** ：工具函数库，包含常用的Utils函数和宏定义。

---

### 3.  **Command/ 文件夹 - 命令层** 

-  **抽象层次** ：控制器层（Controller Layer）
-  **作用** ：定义插件的所有命令（Command），每个命令对应工具栏或菜单中的一个操作按钮。命令负责响应用户操作，协调数据模型和视图的交互。
-  **文件说明** ：
  - `CommandDev.cpp/h`：注册和实现插件的所有命令，如创建对象、导入导出等操作。

---

### 4.  **Gui/ 文件夹 - 图形界面层** 

-  **抽象层次** ：界面层（UI Layer）
-  **作用** ：实现插件的对话框界面，用于用户输入参数和交互。使用 Qt Designer 设计界面（`.ui` 文件），并通过 C++ 代码实现业务逻辑。
-  **文件说明** ：
  - `BoxDialog.cpp/h/ui`：创建Box对象的设置对话框
  - `CurvesLoftDialog.cpp/h/ui`：创建曲线放样对象的设置对话框
  - `RenderDistanceDialog.cpp/h/ui`：渲染距离对象的设置对话框

---

### 5.  **Resources/ 文件夹 - 资源文件** 

该文件夹包含插件的所有非代码资源，如图标、样式、多语言翻译、脚本等。

####  **Resources/icon/ - 图标资源** 
- 包含插件所需的所有图标文件（PNG/SVG 格式），按功能分类存放：
  - `base/`：基础 UI 图标（关闭、最大化、树节点等）
  - `toolbar/`：工具栏按钮图标
  - `navigator/`：导航栏图标
  - `cuttertool/`：刀具图标

####  **Resources/lang/ - 多语言支持** 
-  **作用** ：提供国际化支持，包含中英文翻译文件。
-  **文件说明** ：
  - `lang_zh_CN.ts/qm`：简体中文翻译（TS 源文件，QM 编译后文件）
  - `lang_en.ts/qm`：英文翻译
  - `powercam.qph`：翻译短语库

####  **Resources/theme/ - 界面主题** 
-  **作用** ：Qt 样式表（QSS）文件，定义插件界面的外观风格。
-  **文件说明** ：
  - `application-theme1.qss`：应用程序整体主题
  - `ribbonbar-theme1.qss`：Ribbon 工具栏主题
  - `tree-theme.qss`：树形控件主题

####  **Resources/py/ - Python 脚本** 
-  **作用** ：提供 Python 扩展功能，包括特征管理、后处理等脚本。
-  **目录说明** ：
  - `Fbm/`：特征管理器脚本
  - `PostProcessor/`：后处理脚本
  - `Python/`：Python 运行时库（PYD、DLL 等）

####  **Resources/tip/ - 提示信息** 
-  **作用** ：存储界面提示信息的 JSON 配置文件，支持多语言。
-  **目录** ：`en_us/`、`zh_cn/`

####  **Resources/view_cube/ - 视图立方体** 
-  **作用** ：软件右上角 3D 视图导航立方体的纹理和模型文件（PNG、STL）。

####  **其他资源** 
- `feature/`：特征相关的图标和素材
- `images/`：背景图片等通用图片资源
- `icon.qrc`：Qt 资源配置文件，将所有图标打包到 DLL 中
- `Resource.qrc`：其他资源的配置文件

---

## 使用说明

1.  **启动主程序**   
   运行 POWER 平台主程序（`PowerFCMain.exe`），插件会自动加载。

2.  **切换到Dev工作台**   
   新建文件之后，在主界面点击工作台切换区域的 **"Dev"** 按钮。

3.  **使用插件功能**   
   工具栏中会显示以下功能按钮：
   - 导入/导出功能
   - 创建立方体
   - 曲线放样
   - 距离渲染

---

## 二次开发注意事项

### 开发流程概述

本节以 **新增创建球体功能** 为例，详细说明 POWER 平台插件的完整开发流程。完整的功能开发需要以下 7 个步骤。

---

### 1. 新增数据对象类（Object）

 **目的：**  创建业务数据模型，管理对象的属性和数据

每一个独立的可以编辑修改的实体都需要创建一个 Object 类，本质上是管理一组数据抽象层。

 **文件位置：**  `Base/Object/BallObject.h` 和 `BallObject.cpp`

 **头文件示例（BallObject.h）：** 

```cpp
#pragma once
#include <Base/Object/DevObject.h>

namespace Dev {

class BallObject : public Dev::DevObject
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

  public:
    BallObject();
    ~BallObject() override;

    // 关键：返回对应的 ViewProvider 类名
    std::string_view GetViewProviderClassName() const override
    {
        return "Dev::ViewProviderBall";
    }
};

}  // namespace Dev
```

 **实现文件示例（BallObject.cpp）：** 

```cpp
#include "BallObject.h"
#include <App/Properties/PropertyFloat.h>
#include <App/Properties/PropertyVector.h>

PFC_PROPERTY_IMPL(Dev::BallObject, Dev::DevObject)

namespace Dev
{
    BallObject::BallObject()
        : DevObject()
    {
        TypeName.SetValue("Ball");
        // 添加球心位置属性
        AddPropertyVector("Center", base::Vector3d(0, 0, 0));
        // 添加半径属性
        AddPropertyFloat("Radius", 5.0);
    }

    BallObject::~BallObject()
    {
    }
}
```

 **关键要点：** 
- 继承自 `Dev::DevObject`
- 使用 `AddPropertyVector`、`AddPropertyFloat` 等方法动态添加属性
- 通过 `GetViewProviderClassName()` 关联对应的 ViewProvider

---

### 2. 新增视图提供者（ViewProvider）

 **目的：**  负责对象在 3D 视图中的可视化渲染

ViewProvider 与 Object 通过 `GetViewProviderClassName()` 函数返回的类名字符串关联，由 Power 平台的反射系统自动完成映射。

 **文件位置：**  `Base/ViewProvider/ViewProviderBall.h` 和 `ViewProviderBall.cpp`

 **头文件示例：** 

```cpp
#pragma once
#include <Gui/ViewProvider/ViewProviderDocumentObjectTopoShape.h>

namespace Dev {

class ViewProviderBall : public gui::ViewProviderDocumentObjectTopoShape
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    ViewProviderBall();
    ~ViewProviderBall() override;

    // 返回被双击之后的视图（对话框）
    QWidget* GetTaskView() const override;

  protected:
    // 实现 3D 渲染逻辑
};

}  // namespace Dev
```

 **关键要点：** 
- 继承自 `gui::ViewProviderDocumentObjectTopoShape`
- 实现 `GetTaskView()` 返回编辑对话框
- 类名必须与 Object 的 `GetViewProviderClassName()` 返回值一致

---

### 3. 新增 GUI 编辑对话框

 **目的：**  为用户提供参数输入和编辑界面

 **文件位置：**  `Gui/BallDialog.h`、`BallDialog.cpp` 和 `BallDialog.ui`

 **头文件示例：** 

```cpp
namespace Dev {

class BallDialog : public BlockDialog
{
    Q_OBJECT

public:
    BallDialog(Dev::BallObject *obj, QWidget *parent = nullptr);
    ~BallDialog();

public slots:
    bool OnConfirmed() override;  // 点击确定
    bool OnApplied() override;     // 点击应用
    void OnResetted() override;    // 点击重置
    void OnCanceled() override;    // 点击取消

private:
    Ui::BallDialog *ui;
    Dev::BallObject *m_object;
};

}
```

 **关键要点：** 
- 继承自 `BlockDialog`
- 使用 Qt Designer 创建 `.ui` 文件设计界面
- 通过信号槽机制响应用户操作

---

### 4. 新增 Command 命令

 **目的：**  定义命令的元信息和执行逻辑

 **文件位置：**  `Command/CommandDev.cpp` 和 `CommandDev.h`

 **代码示例：** 

```cpp

DEF_STD_CMD_A(CreateBall)

CreateBall::CreateBall()
    : Command("CreateBall")  // 命令名称
{
    m_group = QT_TR_NOOP("Dev");
    m_menuText = QT_TR_NOOP("创建球");
    m_toolTipText = QT_TR_NOOP("创建球");
    m_whatsThis = "创建球";
    m_statusTip = QT_TR_NOOP("创建球");
    m_pixmap = ":icon/toolbar/bounding-sphere.png";  // 图标路径
    m_type = 0;
}

void CreateBall::Activated(int iMsg)
{
    Q_UNUSED(iMsg);
    // 弹出对话框
    auto dialog = new BallDialog(nullptr, gui::GetMainWindow());
    dialog->show();
}

bool CreateBall::IsActive()
{
    return true;  // 命令始终可用
}
```

 **关键要点：** 
- 使用 `DEF_STD_CMD_A` 宏定义命令类
- 在构造函数中设置命令的各项属性（名称、图标、提示等）
- `Activated()` 方法中实现命令的执行逻辑
- `IsActive()` 方法控制命令的可用状态

---

### 5. 注册命令

 **目的：**  将命令注册到 CommandManager，使其可被调用

 **文件位置：**  `Command/CommandDev.cpp`

 **代码示例：** 

```cpp
void CreateDevWorkbenchCommands()
{
    gui::CommandManager &commandMgr = gui::CommandManager::GetInstance();
    
    commandMgr.AddCommand(new CreateBox());
    commandMgr.AddCommand(new CreateBall());           // 注册球体命令
}
```

 **关键要点：** 
- 在 `CreateDevWorkbenchCommands()` 函数中统一注册所有命令
- 该函数在工作台初始化时被调用（`DevWorkbench::RegistCommand()`）

---

### 6. 添加对象创建方法

 **目的：**  在 DevSetup 中提供创建对象并添加到 Document 的接口

 **文件位置：**  `Base/DevSetup.h` 和 `DevSetup.cpp`

 **头文件声明：** 

```cpp
// DevSetup.h
BallObject* AddBallObject(std::string_view name);
```

 **实现代码：** 

```cpp
// DevSetup.cpp
BallObject* DevSetup::AddBallObject(std::string_view name)
{
    auto obj = new BallObject();
    // 获取唯一名称（避免重名）
    auto unique_name = part_collection->GetUniqueName(name);
    obj->Label.SetValue(unique_name);
    // 添加到 Document
    GetDocument()->AddObject(std::unique_ptr<BallObject>(obj));
    return obj;
}
```

 **关键要点：** 
- 创建对象实例
- 使用 `PartCollection` 生成唯一名称
- 通过 `GetDocument()->AddObject()` 添加到文档
- 使用智能指针管理对象生命周期

---

### 7. 在工作台中添加按钮

 **目的：**  在工具栏中显示命令按钮

 **文件位置：**  `DevWorkbench.cpp`

 **代码示例：** 

```cpp
gui::ToolBarItem* DevWorkbench::SetupToolBars() const
{
    gui::ToolBarItem *root = new gui::ToolBarItem;
    {
        gui::ToolBarItem *wave = new gui::ToolBarItem(root, "Dev");
        gui::ToolBarItem *base = new gui::ToolBarItem(wave, "基本");
        
        // 使用 << 操作符添加命令（通过命令名称字符串）
        *base << "Dev_Import" 
              << "Dev_Export" 
              << "Dev_CreateBox" 
              << "CreateBall"                    // 添加球体按钮
              << "Dev_CreateCurvesLoft" 
              << "Dev_CreateRenderDistance";
    }
    return root;
}
```

 **关键要点：** 
- 使用 `<<` 操作符添加命令字符串
- 命令字符串必须与 Command 构造函数中的命令名称一致
- 工具栏支持多级菜单结构

---


### 完整开发流程示意图

```
1. 创建 BallObject (数据模型)

2. 创建 ViewProviderBall (视图渲染)

3. 创建 BallDialog (用户界面)

4. 创建 CreateBall Command (命令逻辑)

5. 注册命令到 CommandManager

6. 在 DevSetup 添加 AddBallObject 方法

7. 在 SetupToolBars 中添加按钮

      编译运行，功能完成
```
