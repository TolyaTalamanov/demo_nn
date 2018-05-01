#include "bounding_box.hpp"

QBoundingBox::QBoundingBox(const QRect& rect,
                           const QColor& color,
                           const QString& label) {
  _color = color;
  _rect  = rect;
  _label = label;
}

void QBoundingBox::draw(QImage& image) {
  QPen pen(_color, 5);
  QFont* fontText = new QFont("Serif", 20, QFont::Normal);

  QPainter qPainter(&image);
  qPainter.setRenderHint(QPainter::TextAntialiasing, true);
  qPainter.setFont(*fontText);
  qPainter.setPen(pen);

  QRect label_rect(_rect.topLeft().x(), _rect.topLeft().y() - 40,
                   _label.size() * 17, 40);

  qPainter.drawRect(_rect);
  qPainter.drawRect(label_rect);
  qPainter.fillRect(label_rect, _color);

  QPen text_pen(Qt::black);
  qPainter.setPen(text_pen);
  qPainter.drawText(QPoint(_rect.topLeft().x(), _rect.topLeft().y() - 5),
                                                                      _label);
}
