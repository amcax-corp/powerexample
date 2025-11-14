#include <string>
#include <vector>
#include <sstream>

namespace Dev{
class Utils
{
    public:
    static std::string GetSubNameByFullName(const std::string &fullName)
    {
        std::string sub_name = "";
        std::vector<std::string> name_list;

        std::stringstream ss(fullName);
        std::string name;

        while (std::getline(ss, name, '.'))
        {
            name_list.push_back(name);
        }

        if (name_list.size() == 3)
        {
            sub_name = name_list[2];
            return sub_name;
        }
        return "";
    }
};
}
