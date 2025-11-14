#pragma once

#include <QLabel>
#include <QPixmap>

class PowerDrawingArea : public QLabel
{
    Q_OBJECT
public:
    explicit PowerDrawingArea(QWidget *parent = nullptr);
    ~PowerDrawingArea();

   int GetHeight() const;

   void SetHeight(int height);

   void SetWidth(int width);

   int GetWidth() const;

   void SetImage(const QPixmap &image);

   QPixmap GetImage() const;

protected:
    void resizeEvent(QResizeEvent *event);

//    QSize CalculateScaledSize(const QPixmap &image) const;

private:
    QPixmap m_image;
    int m_height;
    int m_width;
};
