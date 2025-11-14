#ifndef POWERFC_CONFIRMSAVE_H
#define POWERFC_CONFIRMSAVE_H
#pragma once
#include <QObject>
#include <string_view>

namespace gui {
class ConfirmSave : QObject
{
    Q_OBJECT
  public:
    ConfirmSave(std::string_view doc_label, QWidget* widget = nullptr, bool add_checkbox = false);
    ~ConfirmSave() override;

    enum class Result
    {
        Cancel = 0,
        Save,
        SaveAll,
        Discard,
        DiscardAll
    };

    Result operator()() const;

  private:
    struct Private;
    std::unique_ptr<Private> d_ptr;
};
}  // namespace gui
#endif