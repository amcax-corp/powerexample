#ifndef POWERFC_BASE_TOGGLERGUARD_H_
#define POWERFC_BASE_TOGGLERGUARD_H_
#pragma once

namespace base {
// A RAII guard to toggle a boolean variable

struct TogglerGuard
{
    bool& togger;
    bool toggled;

    TogglerGuard(bool& togger)
      : togger(togger)
      , toggled(true)
    {
        togger = !togger;
    }

    TogglerGuard(bool& togger, bool check)
      : togger(togger)
      , toggled(check == togger)
    {
        if (toggled)
        {
            togger = !togger;
        }
    }

    ~TogglerGuard()
    {
        if (toggled)
        {
            //恢复原始值
            togger = !togger;
        }
    }
};
}  // namespace base

#endif