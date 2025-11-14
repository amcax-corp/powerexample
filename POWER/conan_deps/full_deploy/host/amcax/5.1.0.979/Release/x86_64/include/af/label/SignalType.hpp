#ifndef DOXYGEN_SKIP
#pragma once

// #include <boost/signals2.hpp>

// namespace bs2 = boost::signals2;
#include <string>
namespace AMCAX
{
// TODO: More types
enum class NotifyType
{
    RebuildRequired,
    AttributeAdd,
    AttributeUpdate,
    AttributeDelete
};

class Label;
class LabelNode;
// Don't export 3rd party dependency boost::signals2 here.
// using LabelSignal = bs2::signal<void(NotifyType /* type */, const Label& /* who */)>;
using NotifyFnType = void(NotifyType /* type */, const std::string&, const Label& /* who */);

} // namespace AMCAX
#endif
