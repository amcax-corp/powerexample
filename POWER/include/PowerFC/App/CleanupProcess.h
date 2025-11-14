#ifndef POWER_FC_APP_CLEANUPPROCESS_H
#define POWER_FC_APP_CLEANUPPROCESS_H

#include <functional>
#include <PFCGlobal.h>

namespace app
{

/*!
 * \brief The CleanupProcess class
 */
class PFC_APP_API CleanupProcess
{
public:
    /*!
     * \brief registerCleanup
     * \param func
     * This adds a callback function that will be called when the application
     * is about to be shut down.
     * @note A callback function is only about to free resources. Accessing
     * stuff of the application like parameter groups should be avoided.
     */
    static void RegisterCleanup(const std::function<void()>& func);
    /*!
     * \brief callCleanup
     * Calls the functions that are registered with \a registerCleanup.
     */
    static void CallCleanup();
};

}

#endif  // APP_CLEANUPPROCESS_H