#pragma once

#include <PFCGlobal.h>
#include <QObject>
#include <QPointer>
#include <boost/signals2/connection.hpp>

class QAction;
namespace gui {
class PFC_GUI_API BasicSelectionFilterDelegate : public QObject
{
    Q_OBJECT
public:
    explicit BasicSelectionFilterDelegate(
        QAction* action_body,
        QAction* action_point,
        QAction* action_edge,
        QAction* action_face,
        QObject* parent = nullptr);
    ~BasicSelectionFilterDelegate() override = default;

    void SetBodySelectable(bool selectable);
    void SetPointSelectable(bool selectable);
    void SetEdgeSelectable(bool selectable);
    void SetFaceSelectable(bool selectable);

    void SetBodyEnabled(bool enabled);
    void SetPointEnabled(bool enabled);
    void SetEdgeEnabled(bool enabled);
    void SetFaceEnabled(bool enabled);

protected Q_SLOTS:
    void OnActionTriggered(bool triggered);
    void OnActionEnabled(bool enabled);

private:
    QPointer<QAction> m_action_body {};
    QPointer<QAction> m_action_point {};
    QPointer<QAction> m_action_edge {};
    QPointer<QAction> m_action_face {};

    boost::signals2::connection connection_pick_filter_changed;
    boost::signals2::connection connection_pick_range_changed;
};
}  // namespace gui