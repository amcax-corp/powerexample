#include "CurvesLoftDialog.h"
#include "ui_CurvesLoftDialog.h"
#include <App/Application.h>
#include <App/DocumentObjectTopoShape.h>
#include <App/Properties/PropertyString.h>
#include <App/Properties/PropertyStringList.h>
#include <App/Properties/PropertyTopoShape.h>
#include <Gui/MainWindow.h>
#include <App/Properties/PropertyFloat.h>
#include <Gui/Selection/Selection.h>
#include <Gui/View/MdiView.h>
#include <Widgets/Block/BlockSelectObject.h>
#include <Widgets/ContainerBlock/BlockGroup.h>
#include <Widgets/Block/BlockDouble.h>
#include <Widgets/Block/BlockString.h>
#include <Gui/Selection/Selection.h>
#include <Base/DevSetup.h>
#include <nurbs/NURBSCurveSection.hpp>
#include <nurbs/NURBSAPIGetGeometry.hpp>
#include <nurbs/NURBSAPIConvert.hpp>
#include <geometry/Geom3BSplineSurface.hpp>
#include <nurbs/NURBSAPILoft.hpp>
#include <modeling/MakeFace.hpp>
#include <Gui/MessageWindow.h>
#include <geometry/Geom3Curve.hpp>
#include <Gui/Application.h>
#include <Gui/View/View3DInventor.h>
#include <Gui/View/View3DInventorViewer.h>
#include <Gui/ViewProvider/RenderDataHelper.h>
#include <occtio/OCCTTool.hpp>
#include <modeling/CopyShape.hpp>
#include <Logging/Logging.h>
#ifdef GetObject
#undef GetObject
#endif
namespace Dev
{

	CurvesLoftDialog::CurvesLoftDialog(CurvesLoftObject* obj, QWidget* parent)
		: BlockDialog(parent), ui(new Ui::CurvesLoftDialog), m_object(obj)
	{
		if (m_object == nullptr)
		{
			app::OpenCommand(tr("创建 ").toStdString() + "curves loft");
			m_object = Dev::DevSetup::GetCurDevSetup()->AddCurvesLoft("curves loft");
		}
		else
		{
			app::OpenCommand(tr("编辑 ").toStdString() + std::string(m_object->Label.GetValue()));
		}
		ui->setupUi(this);
		ui->CurvesReverse1->SetButtonIcon(QPixmap(":icon/operation/reverse-direction.png"));
		ui->CurvesReverse2->SetButtonIcon(QPixmap(":icon/operation/reverse-direction.png"));
		m_edge_name1 = m_object->GetPropertyString("CurvesName1");
		m_edge_name2 = m_object->GetPropertyString("CurvesName2");
		m_topo_shape1 = m_object->GetDynamicPropertyByName("TopeShape1")->SafeDownCast<app::PropertyTopoShape>();
		m_topo_shape2 = m_object->GetDynamicPropertyByName("TopeShape2")->SafeDownCast<app::PropertyTopoShape>();

		// 获取对象的ViewProvider，并设置预览box的初始状态，以及预览box状态变化时的回调函数，
		if (auto view_provider = gui::GetGuiApplication()->GetViewProvider(m_object))
		{
			ui->Preview->SetValue(view_provider->SafeDownCast<gui::ViewProviderDocumentObjectTopoShape>()->Visibility.GetValue());
		}
		connect(ui->Preview, &BlockToggle::SignalCheckStateChanged, this, [this](bool value)
			{
				if (auto view_provider = gui::GetGuiApplication()->GetViewProvider(m_object))
				{
					view_provider->SafeDownCast<gui::ViewProviderDocumentObjectTopoShape>()->Visibility.SetValue(value);
					Dev::DevSetup::GetCurDevSetup()->UpdatePartNavigator();
				} });

				// 初始化选择控件UI
				InitSelectUI();

				connect(ui->Preview, &BlockToggle::SignalCheckStateChanged, this, &CurvesLoftDialog::OnPreviewLoft);
				connect(ui->CurvesReverse1, &BlockButton::SignalButtonClicked, this, &CurvesLoftDialog::OnButtonClicked);
				connect(ui->CurvesReverse2, &BlockButton::SignalButtonClicked, this, &CurvesLoftDialog::OnButtonClicked);

				ui->select1->SetFocused(true);
	}

	CurvesLoftDialog::~CurvesLoftDialog()
	{
		delete ui;
		auto render = GetCurrentRender();
		render->pluginManage->RemovePlugin(m_curve1_render_id);
		render->pluginManage->RemovePlugin(m_curve2_render_id);
		RefreshRenderWindow();
	}


	/*
	*初始化edge渲染，核心是方向渲染对象，在析构时候需要删除
	*/
	void CurvesLoftDialog::InitEdgeRender(app::PropertyTopoShape* topoShape, AMCAXRender::EntityId& renderId)
	{
		auto edge = topoShape->GetValue();
		// 如果edge存在，则渲染edge的方向
		if (auto tope_edge = static_cast<AMCAX::TopoEdge&>(edge); !tope_edge.IsNull())
		{
			auto render = GetCurrentRender();
			if (!renderId.empty())
			{
				render->pluginManage->RemovePlugin(renderId);
			}
			renderId = RenderEdgeDirection(tope_edge);
		}
	}

	/**
	*初始化选择器，包括：限定选择范围，设置选择器初始化对象，绑定事件
	*/
	void CurvesLoftDialog::InitSelector(BlockSelectObject* selector, app::PropertyString* edgeName)
	{
		// 安装过滤器, 限定只能选择Edge类型的子对象
		selector->SetCustomHandleForSelection([this](app::Document* doc, app::DocumentObject* obj, const std::string& subType)
			{ return subType.find("Edge") != std::string::npos; });

		// 初始化选择器，如果edgeName不为空，在selector有焦点的情况下，控件会响应gui::Selection().AddSelection处理后的信号，将add的结果添加到selector的控件中
		if (!edgeName->GetValue().empty())
		{
			auto full_name = std::string(edgeName->GetValue());
			std::string doc_name;
			std::string obj_name;
			std::string sub_name;
			SplitFullName(full_name, doc_name, obj_name, sub_name);
			selector->SetFocused(true);
			gui::Selection().AddSelection(doc_name, obj_name, sub_name);
			selector->SetFocused(false);
		}

		connect(selector, &BlockSelectObject::SignalSelectionInBlockChanged, this, &CurvesLoftDialog::OnCurvesSelectionChanged);

	}

	void CurvesLoftDialog::InitSelectUI()
	{
		// 初始化边的渲染
		InitEdgeRender(m_topo_shape1, m_curve1_render_id);
		InitEdgeRender(m_topo_shape2, m_curve2_render_id);

		// 初始化选择器
		InitSelector(ui->select1, m_edge_name1);
		InitSelector(ui->select2, m_edge_name2);
	}


	bool CurvesLoftDialog::OnConfirmed()
	{
		OnPreviewLoft(true);
		app::CommitCommand();
		return true;
	}

	void CurvesLoftDialog::OnCanceled()
	{
		app::AbortCommand();
	}

	std::string GetFullName(const std::string& docname, const std::string& objname, const std::string& subname)
	{
		std::string full_name = docname + "." + objname + "." + subname;
		return full_name;
	}

	void CurvesLoftDialog::OnCurvesSelectionChanged(const QList<gui::SelectionChanges>& changes)
	{
		if (changes.size() > 0)
		{
			// 处理最新的拾取曲线
			auto last_cahnges = changes.last();
			std::string full_name = GetFullName(last_cahnges.document_name, last_cahnges.object_name, last_cahnges.sub_name);
			auto part_obj = app::GetApplication().GetActiveDocument()->GetObject(last_cahnges.object_name)->SafeDownCast<app::DocumentObjectTopoShape>();
			AMCAX::TopoShape edge = part_obj->GetTopoShape(full_name);

			// 使用qt及信号槽机制，判断是哪个信号触发的槽，从而获取到对应的控件
			BlockSelectObject* selector = qobject_cast<BlockSelectObject*>(sender());
			if (!selector)
				return;

			// 根据选择器确定是第一条还是第二条曲线
			int curveIndex = (selector == ui->select1) ? 1 : 2;
			UpdateCurveSelection(curveIndex, full_name, edge);

			OnPreviewLoft(ui->Preview->GetValue());
			RefreshRenderWindow();
		}
	}
	
	void CurvesLoftDialog::OnButtonClicked()
	{ // 处理反向按钮点击的信号
		BlockButton* clickedButton = qobject_cast<BlockButton*>(sender());
		if (!clickedButton)
			return;

		// 根据点击的按钮确定是第一条还是第二条曲线
		int curveIndex = (clickedButton == ui->CurvesReverse1) ? 1 : 2;
		ReverseEdgeOrientation(curveIndex);

		OnPreviewLoft(ui->Preview->GetValue());
		RefreshRenderWindow();
	}

	/**
	*将两条曲线进行放样，返回放样生成的TopoFace
	*/
	AMCAX::TopoFace CurvesLoftDialog::StartLoft(std::vector<AMCAX::TopoEdge>& edges)
	{
		if (edges.size() != 2)
		{
			gui::MessageWindow::Warning(tr("警告"), tr("请现在两条曲线"));
			return AMCAX::TopoFace();
		}
		std::vector<AMCAX::NURBSCurveSection> sections;
		for (auto edge : edges)
		{
			auto geo3Curve = AMCAX::NURBSAPIGetGeometry::GetCurve(edge);
			if (edge.Orientation() == AMCAX::OrientationType::Reversed)
			{//注意几何Curve的方向和拓扑Edge的方向是无关联的，需要根据拓扑的方向来调整几何的方向
				geo3Curve->Reverse();
			}
			sections.push_back(AMCAX::NURBSCurveSection(geo3Curve));
		}

		std::shared_ptr<AMCAX::Geom3BSplineSurface> loft;
		try
		{
			loft = AMCAX::NURBSAPILoft::MakeLoft(sections);
		}
		catch (...)
		{
			gui::MessageWindow::Error(tr("错误"), tr("放样失败！"));
			return AMCAX::TopoFace();
		}
		AMCAX::MakeFace surface(loft, 1e-6);
		AMCAX::TopoFace topoface = surface.Face();
		return topoface;
	}

	/**
	*预览放样的曲面
	*/
	void CurvesLoftDialog::OnPreviewLoft(bool is_preview)
	{
		if (is_preview)
		{
			// 处理 StartLoft 按钮点击
			auto edge1 = m_topo_shape1->GetValue();
			auto edge2 = m_topo_shape2->GetValue();
			if (edge1.IsNull() || edge2.IsNull())
			{
				return;
			}
			std::vector<AMCAX::TopoEdge> edges;
			if (auto tope_edge_1 = static_cast<AMCAX::TopoEdge&>(edge1); !tope_edge_1.IsNull())
			{
				edges.push_back(tope_edge_1);
			}
			if (auto tope_edge_2 = static_cast<AMCAX::TopoEdge&>(edge2); !tope_edge_2.IsNull())
			{
				edges.push_back(tope_edge_2);
			}
			auto face = StartLoft(edges);
			if (auto shape = static_cast<AMCAX::TopoShape&>(face); !shape.IsNull())
			{
				m_object->Shape.SetValue(shape);
			}
		}
		else
		{
			m_object->Shape.SetValue(AMCAX::TopoShape{});
		}
	}

	AMCAXRender::EntityId CurvesLoftDialog::RenderEdgeDirection(AMCAX::TopoEdge& edge)
	{
		std::shared_ptr<AMCAX::Geom3Curve> curve = AMCAX::NURBSAPIGetGeometry::GetCurve(edge);
		if (edge.Orientation() == AMCAX::OrientationType::Reversed)
		{
			curve->Reverse();
		}
		AMCAX::Point3 start_point; // 曲线起点坐标
		AMCAX::Point3 end_point;
		AMCAX::Vector3 vector; // 曲线在起点处的切向量
		curve->D1(curve->FirstParameter(), start_point, vector);
		// 获取当前视图的渲染器
		auto render = GetCurrentRender();
		// 创建箭头插件实体
		auto id = render->pluginManage->AddPluginFromType(AMCAXRender::PluginType::kArrow);
		auto att = render->pluginManage->GetProperty<AMCAXRender::ArrowProp>(id);
		std::vector<double> pos = { start_point.X(), start_point.Y(), start_point.Z() };
		std::vector<double> dir = { vector.X(), vector.Y(), vector.Z() };
		std::vector<double> color = { 255 / 255.0, 0.0, 0.0 };
		// 配置箭头属性
		att->AddArrow(pos, dir, color, 0.35);
		att->SetFixedSize(false);
		render->pluginManage->SetProperty(id, att);
		return id; // 返回箭头实体的ID，用于后续控制
	}
	bool CurvesLoftDialog::SplitFullName(std::string id_name, std::string& document_name, std::string& object_name, std::string& sub_name)
	{
		document_name = "";
		object_name = "";
		sub_name = "";
		std::vector<std::string> name_list;

		std::stringstream ss(id_name);
		std::string name;

		while (std::getline(ss, name, '.'))
		{
			name_list.push_back(name);
		}

		if (name_list.size() == 3)
		{
			document_name = name_list[0];
			object_name = name_list[1];
			sub_name = name_list[2];
			return true;
		}
		return false;
	}
	void CurvesLoftDialog::RefreshRenderWindow()
	{
		gui::GetMainWindow()->ActiveWindow()->OnMessage("Refresh"); // 刷新界面
	}

	std::shared_ptr<AMCAXRender::CBasicRender> CurvesLoftDialog::GetCurrentRender()
	{
		return dynamic_cast<gui::View3DInventor*>(gui::GetMainWindow()->ActiveWindow())->GetViewer()->GetRender();
	}

	void CurvesLoftDialog::UpdateCurveSelection(int curveIndex, const std::string& full_name, const AMCAX::TopoShape& edge)
	{
		// 根据索引获取对应的属性指针和渲染ID
		app::PropertyString* edgeName = (curveIndex == 1) ? m_edge_name1 : m_edge_name2;
		app::PropertyTopoShape* topoShape = (curveIndex == 1) ? m_topo_shape1 : m_topo_shape2;
		AMCAXRender::EntityId& renderId = (curveIndex == 1) ? m_curve1_render_id : m_curve2_render_id;

		// 更新edge名称
		edgeName->SetValue(full_name);

		// 重新更新edge的方向渲染
		if (!edge.IsNull())
		{
			// 保存拾取的 edge
			topoShape->SetValue(edge);

			auto render = GetCurrentRender();
			if (!renderId.empty())
			{
				render->pluginManage->RemovePlugin(renderId);
			}
			renderId = RenderEdgeDirection(static_cast<AMCAX::TopoEdge&>(const_cast<AMCAX::TopoShape&>(edge)));
		}
	}

	void CurvesLoftDialog::ReverseEdgeOrientation(int curveIndex)
	{
		// 根据索引获取对应的属性指针和渲染ID
		app::PropertyString* edgeName = (curveIndex == 1) ? m_edge_name1 : m_edge_name2;
		app::PropertyTopoShape* topoShape = (curveIndex == 1) ? m_topo_shape1 : m_topo_shape2;
		AMCAXRender::EntityId& renderId = (curveIndex == 1) ? m_curve1_render_id : m_curve2_render_id;

		// 检查edge名称是否为空
		if (edgeName->GetValue().empty())
		{
			gui::MessageWindow::Warning(tr("警告"), tr("反向失败"));
			return;
		}

		auto edge = topoShape->GetValue();
		// 对保存的edge进行反向操作，并重新渲染曲线
		if (AMCAX::TopoEdge tope_edge = static_cast<AMCAX::TopoEdge&>(edge); !tope_edge.IsNull())
		{
			// 切换方向
			if (tope_edge.Orientation() != AMCAX::OrientationType::Reversed)
			{
				tope_edge.SetOrientation(AMCAX::OrientationType::Reversed);
			}
			else
			{
				tope_edge.SetOrientation(AMCAX::OrientationType::Forward);
			}
			topoShape->SetValue(tope_edge);
			
			// 重新渲染
			auto render = GetCurrentRender();
			if (!renderId.empty())
			{
				render->pluginManage->RemovePlugin(renderId);
			}
			renderId = RenderEdgeDirection(tope_edge);
			logging::Debug("curve_index={},renderid={}",curveIndex,renderId);
		}
	}

} // namespace Dev