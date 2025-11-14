#ifndef POWERFC_GUI_LISTINGWINDOW_H
#define POWERFC_GUI_LISTINGWINDOW_H
#pragma once

#include <QWidget>
#include <PFCGlobal.h>

namespace gui {
class PFC_GUI_API ListingWindow
{
  public:
    ListingWindow(QWidget* parent=nullptr);
    ~ListingWindow();

    void WriteLine(QString const& line);
    void WriteLines(QStringList const& list);
    void WriteTable(QStringList const& keys, QStringList const& values);
    
};

}  // namespace gui

#endif