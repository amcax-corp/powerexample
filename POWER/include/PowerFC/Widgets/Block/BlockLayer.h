#pragma once
#include <Widgets/Block/BlockBase.h>
class PowerInteger;
class PowerEnumeration;
class PW_API BlockLayer : public BlockBase
{
    Q_OBJECT
    Q_PROPERTY(bool LabelVisibility READ IsLabelVisibility WRITE SetLabelVisibility FINAL DESIGNABLE false)
    Q_PROPERTY(int LayerValue READ GetLayerValue WRITE SetLayerValue)
    Q_PROPERTY(bool MaintainLayerOptionVisibility READ IsMaintainLayerOptionVisibility WRITE SetMaintainLayerOptionVisibility)
    Q_PROPERTY(bool OriginalLayerOptionVisibility READ IsOriginalLayerOptionVisibility WRITE SetOriginalLayerOptionVisibility)
    Q_PROPERTY(bool UserDefinedLayerOptionVisibility READ IsUserDefinedLayerOptionVisibility WRITE SetUserDefinedLayerOptionVisibility)
    Q_PROPERTY(bool WorkLayerOptionVisibility READ IsWorkLayerOptionVisibility WRITE SetWorkLayerOptionVisibility)

public:
    /// @brief 构造函数，创建一个BlockLayer对象
    /// @param parent 父QWidget指针，默认为nullptr
    explicit BlockLayer(QWidget *parent = nullptr);
    /// @brief 析构函数，销毁BlockLayer对象
    ~BlockLayer();
    /// @brief 获取图层值
    /// @return 图层值
    int GetLayerValue() const;

    /// @brief 设置图层值
    /// @param value 图层值
    void SetLayerValue(int value);

    /// @brief 获取是否显示维护图层选项
    /// @return 是否显示维护图层选项
    bool IsMaintainLayerOptionVisibility() const;

    /// @brief 设置是否显示维护图层选项
    /// @param value 是否显示维护图层选项
    void SetMaintainLayerOptionVisibility(bool value);

    /// @brief 获取是否显示原始图层选项
    /// @return 是否显示原始图层选项
    bool IsOriginalLayerOptionVisibility() const;
    
    /// @brief 设置是否显示原始图层选项
    /// @param value 是否显示原始图层选项
    void SetOriginalLayerOptionVisibility(bool value);

    /// @brief 获取是否显示用户定义图层选项
    /// @return 是否显示用户定义图层选项
    bool IsUserDefinedLayerOptionVisibility() const;

    /// @brief 设置是否显示用户定义图层选项
    /// @param value 是否显示用户定义图层选项
    void SetUserDefinedLayerOptionVisibility(bool value);

    /// @brief 获取是否显示工作图层选项
    /// @return 是否显示工作图层选项
    bool IsWorkLayerOptionVisibility() const;
    
    /// @brief 设置是否显示工作图层选项
    /// @param value 是否显示工作图层选项
    void SetWorkLayerOptionVisibility(bool value);

private:
    /// @brief 初始化用户界面
    void InitUI();
    /// @brief 初始化数据
    void InitData();
    /// @brief 更新图层选项
    void UpdataLayerOptions();

private:
    /// @brief 图层值
    int m_layer_value;
    /// @brief 是否显示维护图层选项
    bool m_show_maintain_layer_option;
    /// @brief 是否显示原始图层选项
    bool m_show_original_layer_option;
    /// @brief 是否显示用户定义图层选项
    bool m_show_user_defined_layer_option;
    /// @brief 是否显示工作图层选项
    bool m_show_work_layer_option;
    /// @brief 图层选项列表
    QStringList m_layer_options_list;

    /// @brief 图层QWidget指针
    QWidget *m_widget_layer;
    /// @brief 图层选项PowerEnumeration指针
    PowerEnumeration *m_widget_options;
    /// @brief 图层值PowerInteger指针
    PowerInteger *m_widget_value;
};
