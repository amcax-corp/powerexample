#ifndef POWERFC_GUI_WAITCURSOR_H_
#define POWERFC_GUI_WAITCURSOR_H_
#pragma once
#include <PFCGlobal.h>
#include <QObject>
namespace gui{

    /**
 * This class sets a waitcursor automatically while a slow operation is running.
 * Therefore you just have to create an instance of WaitCursor before the time
 * consuming operation starts.
 *
 * \code:
 * WaitCursor ac;
 * ...
 * ...                   // slow operation
 * ...
 * \endcode
 *
 * Sometimes you have two slow operations with some user interactions in between them.
 * Avoiding to show the waiting cursor then you have to call the methods @ref restoreCursor()
 * and setWaitCursor manually, like:
 *
 * \code:
 * WaitCursor ac;
 * ...
 * ...                   // 1st slow operation
 * ac.restoreCursor();
 * ...
 * ...                  // some dialog stuff
 * ac.setWaitCursor();
 * ...
 * ...                  // 2nd slow operation
 * \endcode
 *
 * @author Werner Mayer
 */

 class PFC_GUI_API WaitCursor
 {
    public:
    enum FilterEventsFlag{
        NoEvents = 0x00,
        KeyEvents = 0x01,
        MouseEvents = 0x02,
        AllEvents = KeyEvents | MouseEvents
    };

    Q_DECLARE_FLAGS(FilterEventsFlags, FilterEventsFlag)

    WaitCursor();
    ~WaitCursor();

    void SetWaitCursor();
    void RestoreCursor();

    FilterEventsFlags GetIgnoreEvents() const;

    void SetIgnoreEvents(FilterEventsFlags events);

    private:
    FilterEventsFlags m_filter;
    static int s_numbers_of_instances;
 };
    
}


#endif