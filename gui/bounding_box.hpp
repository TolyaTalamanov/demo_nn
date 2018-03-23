#ifndef GUI_BOUNDING_BOX_HPP_
#define GUI_BOUNDING_BOX_HPP_

#include <QtWidgets>

class QBoundingBox {
 public:
  QBoundingBox(const QRect&, const QColor&, const QString&);
  void draw(QImage&);
 private:
  QRect _rect;
  QColor _color;
  QString _label;
};
#endif  // GUI_BOUNDING_BOX_HPP_
