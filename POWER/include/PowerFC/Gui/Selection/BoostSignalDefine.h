#ifndef BOOSTSIGNALDEFINE_H
#define BOOSTSIGNALDEFINE_H

#include <boost/signals2.hpp>
template<typename CallSignature>
using BoostSignal = typename boost::signals2::signal_type<CallSignature,
boost::signals2::keywords::mutex_type<boost::signals2::dummy_mutex>>::type;

#endif //BOOSTSIGNALDEFINE_H
