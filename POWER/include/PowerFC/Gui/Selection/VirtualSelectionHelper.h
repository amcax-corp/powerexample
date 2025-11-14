#ifndef VIRTUALSELECTIONHELPER_H
#define VIRTUALSELECTIONHELPER_H

#include "PFCGlobal.h"
#include "SelectionGateManager.h"
#include "VirtualSelectionHelper.h"
#include "BoostSignalDefine.h"

#include <Interface/Constants.h>
#include <common/AxisT.hpp>
#include <common/PointT.hpp>
#include <topology/TopoShape.hpp>

#include <boost/uuid/random_generator.hpp>

#include <optional>
#include <vector>

namespace AMCAX {
class TopoEdge;
}

class QColor;
namespace gui {
class VirtualFunctionInterface;
class VirtualResult;

class PFC_GUI_API VirtualSelectionHelper {
public:
    VirtualSelectionHelper();
    ~VirtualSelectionHelper();

    void RegisterVirtualFunction(VirtualFunctionInterface* function);
    void UnregisterVirtualFunction(std::string_view name);

    void Activate();
    void Deactivate();
    void SetDirectionArrowVisible(bool visible);

    bool AppendXYZPoint(double x, double y, double z);
    bool AppendXYZPoint(const AMCAX::Point3& point);
    bool AppendLine(const AMCAX::Point3& start, const AMCAX::Point3& end);
    bool AppendShape(const AMCAX::TopoShape& shape);
    bool AppendDirection(const AMCAX::Point3& point, const AMCAX::Direction3& direction, int scale = 1);

    BoostSignal<void()> SignalResultChanged;
    const auto& GetResults() const { return m_results; }

    void Clear();

    static std::shared_ptr<VirtualSelectionHelper> CreateDefaultVirtualSelectionHelper();

private:
    friend class BlockSelectObject;
    void SetSelectMode(bool single);
    void SetSelectionLimit(int limit);
    void SetClearOuterSelectionsFunction(std::function<void()>&& clear_outer_function);

    bool IsReachMaxLimit() const;
    bool CheckAndRemoveIfExists(const std::string& id);
    void CheckPreselectAndMakeResult(const std::string& id);
    bool CheckHoverPreselect(const std::string& id);
    bool CheckLeavePreselect(const std::string& id);

    void NotifyInitFinished();

private:
    bool m_initial_mode { true };

    bool m_focused { false };
    boost::signals2::scoped_connection m_connection_pick_filter_changed;
    BasicPickFilter m_current_pick_filter{ BasicPickFilter::AllGeom };

    bool m_single_mode { true };
    int m_selection_limit { 1 };
    std::function<void()> m_clear_outer_selections_function;

    std::optional<AMCAXRender::EventId>
    m_hover_entity_event_id{},
    m_hover_plugin_event_id{},
    m_leave_plugin_event_id{},
    m_click_plugin_event_id{},
    m_click_entity_event_id{},
    m_leave_entity_event_id{};

    std::vector<VirtualFunctionInterface*> m_virtual_functions{};

    bool m_dirty { false };
    std::vector<std::shared_ptr<VirtualResult>> m_results;
    std::shared_ptr<VirtualResult> m_preselect;
};

class PFC_GUI_API VirtualResult
{
public:
    enum class Type
    {
        Point,
        Line,
        Shape,
        Direction,
    };
    explicit VirtualResult(Type type);
    virtual ~VirtualResult();

    enum class Status
    {
        Initial,
        Preselecting,
        Selecting,
        NoFocus
    };

    bool IsValid() const { return !m_plugin_id.empty(); }
    const std::string& GetPluginId() const { return m_plugin_id; }
    virtual void SetStatus(Status status);

    virtual AMCAX::Point3 GetPoint() const { return {}; }
    [[nodiscard]] virtual AMCAX::TopoShape GetShape() const { return {}; }

    virtual bool IsEqual(const VirtualResult& result) const { return m_type == result.m_type;}

    const Type m_type;
protected:
    friend class VirtualFunctionInterface;
    friend class VirtualSelectionHelper;
    virtual void Create() = 0;

    std::string m_plugin_id;
private:
    virtual void SetColor(const QColor& color);

protected:
    Status m_status { Status::Initial };

    static boost::uuids::random_generator generator;
};

class PFC_GUI_API VirtualResult_Point : public VirtualResult
{
public:
    explicit VirtualResult_Point(const AMCAX::Point3& pos);
    ~VirtualResult_Point() override;
    AMCAX::Point3 GetPoint() const override { return m_pos; }
    [[nodiscard]] AMCAX::TopoShape GetShape() const override;
    bool IsEqual(const VirtualResult& result) const override;
    void SetStatus(Status status) override;
private:
    void Create() override;
    void SetColor(const QColor& color) override;
    AMCAX::Point3 m_pos;
    AMCAX::TopoShape m_vertex;
};

class PFC_GUI_API VirtualResult_Line : public VirtualResult
{
public:
    explicit VirtualResult_Line(const AMCAX::Point3& start, const AMCAX::Point3& end);

    const AMCAX::Point3& GetStart() const { return m_start; }
    const AMCAX::Point3& GetEnd() const { return m_end; }
    bool IsEqual(const VirtualResult& result) const override;
    [[nodiscard]] AMCAX::TopoShape GetShape() const override;
private:
    void Create() override;
    AMCAX::Point3 m_start, m_end;
};

class PFC_GUI_API VirtualResult_Shape : public VirtualResult
{
public:
    explicit VirtualResult_Shape(const AMCAX::TopoShape& shape);

    bool IsEqual(const VirtualResult& result) const override;
    [[nodiscard]] AMCAX::TopoShape GetShape() const override;
private:
    void Create() override;
    AMCAX::TopoShape m_shape;
};

class PFC_GUI_API VirtualResult_Direction : public VirtualResult
{
public:
    explicit VirtualResult_Direction(const AMCAX::Point3& pos, const AMCAX::Direction3& direction, int scale = 1);
    AMCAX::Point3 GetPoint() const override { return m_pos; }
    bool IsEqual(const VirtualResult& result) const override;
    [[nodiscard]] AMCAX::TopoShape GetShape() const override;
private:
    void Create() override;
    void SetColor(const QColor& color) override;
    AMCAX::Point3 m_pos;
    AMCAX::Direction3 m_direction;
    int m_scale;
};

using namespace std::string_literals;
class PFC_GUI_API VirtualFunctionInterface
{
public:
    virtual ~VirtualFunctionInterface() = default;

    virtual std::string GetName() const = 0;
    virtual bool CallWhenHoveringEntity(const AMCAXRender::EntityId&, const AMCAXRender::EntityId&, AMCAXRender::PickType, int, int*) = 0;
    virtual bool CallWhenHoveringPlugin(const AMCAXRender::EntityId&, AMCAXRender::PickType, int, double*) = 0;
    virtual BasicPickFilter GetEnableBasicPickType() const = 0;

    void Generate();

    const std::shared_ptr<VirtualResult>& GetResult() const { return m_preselect_result; }
    void SwapResult(std::shared_ptr<VirtualResult>& result);
protected:
    std::shared_ptr<VirtualResult> m_preselect_result{};
};

class PFC_GUI_API VirtualFunction_CircularCenter : public VirtualFunctionInterface
{
public:
    ~VirtualFunction_CircularCenter() override = default;

    std::string GetName() const override { return "CircularCenter"s; }
    bool CallWhenHoveringEntity(const AMCAXRender::EntityId&, const AMCAXRender::EntityId&, AMCAXRender::PickType, int, int*) override;
    bool CallWhenHoveringPlugin(const AMCAXRender::EntityId&, AMCAXRender::PickType, int, double*) override;
    BasicPickFilter GetEnableBasicPickType() const override;

    static std::optional<AMCAX::Point3> GetCircularCenter(const AMCAX::TopoEdge& edge);
};

class PFC_GUI_API VirtualFunction_CoordinateSystemOrigin : public VirtualFunctionInterface
{
public:
    ~VirtualFunction_CoordinateSystemOrigin() override = default;

    std::string GetName() const override { return "CoordinateSystemOrigin"s; }
    bool CallWhenHoveringEntity(const AMCAXRender::EntityId&, const AMCAXRender::EntityId&, AMCAXRender::PickType, int, int*) override;
    bool CallWhenHoveringPlugin(const AMCAXRender::EntityId&, AMCAXRender::PickType, int, double*) override;
    BasicPickFilter GetEnableBasicPickType() const override;
};
}


#endif //VIRTUALSELECTIONHELPER_H
