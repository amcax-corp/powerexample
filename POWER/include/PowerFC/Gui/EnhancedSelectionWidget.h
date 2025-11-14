#ifndef ENHANCEDSELECTIONWIDGET_H
#define ENHANCEDSELECTIONWIDGET_H

#include <QComboBox>
#include <QWidget>
#include <boost/signals2/connection.hpp>

namespace gui {
class EnhancedSelectionManager;
}
class EnhancedSelectionWidget : public QWidget
{
    Q_OBJECT
  public:
    explicit EnhancedSelectionWidget(QWidget* parent = Q_NULLPTR);
    ~EnhancedSelectionWidget() override = default;

    void SetManager(const std::shared_ptr<gui::EnhancedSelectionManager>& manager);

    void SetEnabled(bool visible);

    enum class ModeType
    {
        Face,
        Edge,
        Body
    };
    Q_ENUM(ModeType);
    /// @brief 设置不可用
    void SetEnabled(bool enabled, ModeType mode);
    /// @brief 设置不可见
    /// @note 该函数等价于临时不可用，当控件重新生成时将恢复原状态
    void SetVisible(bool visible, ModeType mode);

private Q_SLOTS:
    void SlotComboBoxIndexChanged(int index);
    void SlotActionCheckedChanged();

  private:
    void InitWidget();
    void Refresh();
    void UpdateGeometry();

    bool eventFilter(QObject* watched, QEvent* event) override;

  private:
    boost::signals2::scoped_connection m_connection_manager_changed;
    boost::signals2::scoped_connection m_connection_mode_enabled_changed;
    boost::signals2::scoped_connection m_connection_enabled_changed;

    QComboBox* m_cb_body{};
    QComboBox* m_cb_face{};
    QComboBox* m_cb_edge{};
    QToolButton* m_btn_settings{};
    QAction* m_action_face{};
    QAction* m_action_edge{};
    QAction* m_action_body{};
    std::shared_ptr<gui::EnhancedSelectionManager> m_manager;
};


#endif //ENHANCEDSELECTIONWIDGET_H
