#pragma once
#include "Hole.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <common/IndexSet.hpp>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

class aag_Edge;


enum class ConcavityType
{
    convex, 
    crossover,
    concave,   
};


class __declspec(dllexport) Node
{
public:
    Node() = default;
    std::shared_ptr<AMCAX::TopoShape> m_face;
    int m_Adjacent = 0;;  //相邻面的数量
    bool visit = false;
    std::shared_ptr<aag_Edge> m_firstedge{};
    std::shared_ptr<Node> m_next{};

};


class __declspec(dllexport) aag_Edge
{
public:
    aag_Edge() = default;
    int nextindex = 0;  //下一条边的索引
    ConcavityType m_concavity=ConcavityType::crossover;
    std::shared_ptr<AMCAX::TopoShape> m_edge;
    std::shared_ptr<Node> next{};

};



class __declspec(dllexport) Graph
{
public:
    int nodenum = 0;
    int edgenum = 0;
    std::vector<Node> m_nodes{};
    //face,<next face,edge>
    std::unordered_map<AMCAX::TopoShape,
        std::vector<std::pair<AMCAX::TopoShape,AMCAX::TopoShape>>> MAP;
};



//当前问题：无法区分凸台圆柱圆锥和圆柱圆锥孔
class __declspec(dllexport) AAG
{
public:
    AAG() = default;
    void BuildAAG(AMCAX::TopoShape graph,std::vector<TopoShape> _circles);
    //void BuildAAG(std::string& filename);
    void ExtractHole();
    std::vector<json> ToJson(const std::vector<double>& direct, bool outputjson = false);//false 不输出json
    std::string ToJsonString(const std::vector<double>& direct, bool outputjson = false);
    std::string ReverseHole(const std::vector<TopoShape>& hole, std::vector<double>direct,bool& success, bool mustreverse=false,bool outputjson = false);

    //单孔识别，输入单一孔面的id
    std::vector<face_node> FindSingle(int index);
    json FindSingleJson(int index);
    
    //单面识别，输入单一的面,给这个面连接下的所有孔面
    std::vector<std::vector<face_node>> FindSingleFace(int index);
    std::vector<json> AAG::FindSingleFaceJson(int index);


    Graph m_aag{};
    std::vector<TopoShape> circles{}; //储存螺纹信息
    AMCAX::TopoShape solid{};
    AMCAX::IndexSet<TopoShape> shapeAndID;  //所有toposhape对应的id
    std::vector<std::vector<face_node>> entireholes{};  //所有的孔
    std::vector<std::vector<TopoShape>> topoholes{};   //所有的孔对应的剩余的面
    std::vector<std::vector<int>> m_rest_index{};//剩余面对应的id
    std::vector<std::vector<face_node>> complicts{};   //复杂的孔
    std::vector<std::vector<face_node>> errorholes{};   //可能识别错误，或者构造错误的孔
    Point3 m_pmin;
    Point3 m_pmax;
};

AMCAX::Axis3 GetAxisSurface(const AMCAX::TopoShape& shape);
AMCAX::Axis3 GetAxisCircle(const AMCAX::TopoShape& shape);
double GetRadiusCircle(const AMCAX::TopoShape& shape);
AMCAX::SurfaceType GetType(const AMCAX::TopoShape& shape);
bool IsCoaxial(AMCAX::Axis3 p1, AMCAX::Axis3 p2,double err=1e-4,double err2=1e-2);



