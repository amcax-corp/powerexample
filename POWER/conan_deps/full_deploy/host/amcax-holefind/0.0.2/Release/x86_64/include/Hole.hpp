#pragma once
#include <vector>
#include <memory>
#include <common/AxisT.hpp>
#include <topology/TopoShape.hpp>
#include <math/GeometryMacros.hpp>

using namespace AMCAX;


class __declspec(dllexport) SewThread
{
public:
    SewThread() = default;
    SewThread(AMCAX::Axis3 _position, double _radius, double _deepth) :
        m_axis(_position), m_radius(_radius), m_deepth(_deepth){};
    SewThread(AMCAX::Axis3 _position, double _radius, double _deepth,double _screwpitch) :
        m_axis(_position), m_radius(_radius), m_deepth(_deepth),m_screwpitch(_screwpitch){};

    AMCAX::Axis3 m_axis{};
    AMCAX::Point3 location_next{}; //另一个圆的位置
    double m_radius = 0;
    double m_deepth = 0;
    double m_screwpitch = 0;
    std::vector<TopoShape> m_cirlces;

};


struct __declspec(dllexport) face_node
{
    AMCAX::TopoShape face;
    int id = 0;
    SurfaceType type = AMCAX::SurfaceType::Plane;
    AMCAX::Point3 uppoint;
    AMCAX::Point3 downpoint;
    double upradius = 0;
    double downradius = 0;
    double angle = 0;
    AMCAX::Axis3 ver;
    double radius = 0;
    double deepth = 0;
    AMCAX::Point3 location{};
    std::vector<AMCAX::TopoShape> nextnodes;
    bool hasthread = false;
    SewThread thread{};
};


enum class HoleType
{
    EasyHole,     //简单孔
    TaperedHole, //锥形孔
    Counterbore,  //沉头孔
    other       //通用孔

};

//螺纹信息
struct Thread
{
    Thread() = default;
    Thread(bool _hasthread, double _radius, double _length, double _srewpith) :
        hasthread(_hasthread), radius(_radius), length(_length), screwpitch(_srewpith) {};
    Thread(const SewThread& t) :
        hasthread(true), radius(t.m_radius), length(t.m_deepth),screwpitch(t.m_screwpitch){};
    bool operator==(const Thread& other) const;

    bool hasthread = false;
    double radius = 0;
    double length = 0;
    double screwpitch = 0;
};

struct hash_Thread {
    size_t operator()(const Thread& t)const {
        return std::hash<std::string>()(std::to_string(t.radius)) ^
               std::hash<std::string>()(std::to_string(t.screwpitch));
    }
};


//底部类型
enum class bottom
{
    Cusp,
    Through,
    Flatten,
    IndirectThrough
};

class __declspec(dllexport) BottomBasic {
public:
    virtual bottom GetType() const = 0;
    virtual bool IsEqual(const std::shared_ptr<BottomBasic>&) const = 0;//已有数据完全一致
    face_node part;
};

class __declspec(dllexport) CuspBasic : public BottomBasic {
public:
    CuspBasic() = default;
    CuspBasic(double _angle):angle(_angle){}
    bottom GetType()const override;
    bool IsEqual(const std::shared_ptr<BottomBasic>&) const override;
    

    double angle = 0;
};

class __declspec(dllexport) ThroughBasic :public BottomBasic
{
public:
    ThroughBasic() = default;
    ThroughBasic(double _chamfer,double _offset):
        chamfer_deepth(_chamfer),offset_d(_offset){}
    bottom GetType()const override;

    bool IsEqual(const std::shared_ptr<BottomBasic>&) const override;

    double chamfer_deepth = 0;
    double offset_d = 0;
};

class __declspec(dllexport) FlattenBasic :public BottomBasic
{
public:
    FlattenBasic() = default;
    bottom GetType()const override;
    bool IsEqual(const std::shared_ptr<BottomBasic>&) const override;

};

class __declspec(dllexport) IndirectThroughBasic :public BottomBasic
{
public:
    IndirectThroughBasic() = default;
    bottom GetType()const override;
    bool IsEqual(const std::shared_ptr<BottomBasic>&) const override;

};

//边缘类型
enum class VergeType
{
    Sharp,
    Chamfer,
    Fillet
};
class __declspec(dllexport) VergeBasic
{
public:
    virtual VergeType GetType() const = 0;
    virtual bool IsEqual(const std::shared_ptr<VergeBasic>&) const = 0;
    virtual double Length() const = 0;
    virtual void Reverse() = 0;
};

class __declspec(dllexport) Verge_sharp : public VergeBasic
{
public:
    Verge_sharp() = default;
    VergeType GetType() const override;
    bool IsEqual(const std::shared_ptr<VergeBasic>&)const override;
    double Length()const override;
    void Reverse() override;
};

class __declspec(dllexport) Verge_chamfer : public VergeBasic
{
public:
    Verge_chamfer() = default;
    Verge_chamfer(double _deepth):chamfer_deepth(_deepth){}

    VergeType GetType() const override;
    bool IsEqual(const std::shared_ptr<VergeBasic>&)const override;
    double Length() const override;
    void Reverse() override;

    face_node part;
    double chamfer_deepth = 0;
};

class __declspec(dllexport) Verge_fillet : public VergeBasic
{
public:
    Verge_fillet() = default;
    Verge_fillet(double _radius) :fillet_radius(_radius) {};
    VergeType GetType() const override;
    bool IsEqual(const std::shared_ptr<VergeBasic>&) const override;
    double Length() const override;
    void Reverse()override;

    face_node part;
    double fillet_radius = 0;
};

//沉头附加类型
enum class CountersunkType
{
    Counterbore,   //沉头孔
    Countersink,   //沉头 埋孔
    Drilled,     //钻孔，有顶锥角
    Torus,       //圆环面，有顶部和底部直径参数
    TaperedCounter    //锥形沉头
};

class __declspec(dllexport) CounterBasic
{
public:
    virtual CountersunkType GetType() const = 0;
    virtual bool IsEqual(const std::shared_ptr<CounterBasic>&) const = 0;
};

class __declspec(dllexport) Counter_Tapered :public CounterBasic
{
public:
    Counter_Tapered() = default;
    Counter_Tapered(double _angle) :angle(_angle){}
    CountersunkType GetType() const override;
    bool IsEqual(const std::shared_ptr<CounterBasic>&) const override;
    double angle = 0;
};


class __declspec(dllexport) Counter_bore :public CounterBasic
{
public:
    CountersunkType GetType() const override;
    bool IsEqual(const std::shared_ptr<CounterBasic>&) const override;
    Thread screw_message;
};

class __declspec(dllexport) Counter_drilled :public CounterBasic
{
public:
    Counter_drilled() = default;
    Counter_drilled(double _angle):angle(_angle){}
    CountersunkType GetType() const override;
    bool IsEqual(const std::shared_ptr<CounterBasic>&) const override;

    double angle = 0;
    Thread screw_message;
};
class __declspec(dllexport) Counter_torus :public CounterBasic
{
public:
    CountersunkType GetType() const override;

    bool IsEqual(const std::shared_ptr<CounterBasic>&) const override;

    double top_radius = 0;
    double bottom_radius = 0;
    double radius = 0;
    Thread screw_message;
    bool isinner = false;
};
class __declspec(dllexport) Counter_sink :public CounterBasic
{
public:
    Counter_sink() = default;
    Counter_sink(double _angle):degree(_angle){}
    CountersunkType GetType() const override;
    bool IsEqual(const std::shared_ptr<CounterBasic>&) const override;
    
    double degree = 0;

};

//沉头信息
class __declspec(dllexport) CountersunkProperty
{
public:
    std::shared_ptr<VergeBasic> verge;
    std::shared_ptr<CounterBasic> basic;
    bool IsEqual(const CountersunkProperty&) const; //已有数据完全一致
    bool IsSame(const CountersunkProperty&) const; //除了深度完全一致
    double GetAllLength()const;
    void Reverse();
    double Radius{};
    double Deepth{};
    bool hasthread = false;
    std::vector<face_node> parts{};

};

//槽信息
class __declspec(dllexport) SinkProperty
{
public:
    SinkProperty() = default;
    SinkProperty(double _offset,double _deepth,double _radius):
        offset(_offset),deepth(_deepth),radius(_radius){}
    bool IsEqual(const SinkProperty&) const;
    bool IsSame(const SinkProperty&) const; //只有半径相同
    double offset = 0;
    double deepth = 0;
    double radius = 0;
};

//孔信息
class __declspec(dllexport) Hole
{
public:
    Hole() = default;
    Hole(double _radius,double _deepth):
        Radius(_radius),Deepth(_deepth){}
    std::shared_ptr<VergeBasic> perVertype;
    std::shared_ptr<VergeBasic> backVertype;
    void Reverse();
    double GetAllLength()const;
    bool IsEqual(const Hole&) const; //完全一样
    bool IsSame(const Hole&) const; //只需要前半段相同即可
    double Radius = 0;
    double Deepth = 0;
    double angle = 0;
    Thread screw_message;
    face_node part;
};

class Organization
{
public:
    bool hasOrganization = false;
    
    std::vector<AMCAX::Point3> positions{};
};


class __declspec(dllexport) CommonHole
{
public:
    CommonHole() = default;
    void Reverse();
    double GetAllLength()const;
    AMCAX::Axis3 axis;
    HoleType Type=HoleType::EasyHole;
    std::shared_ptr<BottomBasic> Bottom;
    int SinkNum = 0;
    int CountersunkHeadNum = 0;
    int AntiCountersunlHeadNum = 0;

    std::vector<CountersunkProperty> CounterMessage{};
    std::vector<SinkProperty> SinkMessage{};
    std::vector<CountersunkProperty> AntiCounterMessage{};
    Hole HoleMessage;
    //Organization pos;
    std::vector<AMCAX::TopoShape> compose;
    std::vector<face_node> faces;

};

//定义每个孔的特征参数（槽、沉头、反沉头、底面类型）
__declspec(dllexport)
CommonHole DefineHole(const std::vector<face_node>& hole,const std::vector<TopoShape>& parts);

//根据已有的螺纹信息，分配到识别的孔上
__declspec(dllexport)
void AddThread(std::vector<CommonHole>& holes, std::vector<SewThread> threads);

//按照Hypermill方式分组，不存在重复出现的孔
__declspec(dllexport)
std::vector<std::vector<CommonHole>> GroupHoleHypermill(const std::vector<CommonHole>& wholeholes);

//按照UG的方式分组，穿孔存在正反两面的加工组中
__declspec(dllexport)
std::vector<std::vector<CommonHole>> GroupHoleNx(const std::vector<CommonHole>& wholeholes,Point3 pmin,Point3 pmax);

//按照Hypermill设置加工组，只有完全相同的会分成一组,输入首先需要是同一个面的
__declspec(dllexport)
std::vector<std::vector<CommonHole>> ProcessHypermill(const std::vector<CommonHole>& wholeholes);

//按照UG的方式设置加工组，除最内侧孔之外不同其余都相同，输入首先需要是同一个面的
__declspec(dllexport)
std::vector<std::vector<CommonHole>> ProcessNx(const std::vector<CommonHole>& wholeholes);

//打印孔的特征信息
__declspec(dllexport)
std::string PrintHoleMessage(const CommonHole& hole);



void GetBounds(const AMCAX::TopoShape& shape,
  double& umin, double& umax, double& vmin, double& vmax);
Point3 GetPlanePoint(const TopoShape& plane);



