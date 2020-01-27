/*******************************************************************

Part of the Fritzing project - http://fritzing.org
Copyright (c) 2007-2019 Fritzing

Fritzing is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Fritzing is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Fritzing.  If not, see <http://www.gnu.org/licenses/>.

********************************************************************/

#ifndef RESIZEHANDLE_H
#define RESIZEHANDLE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

// currently used by Note.cpp

class ResizeHandle : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:
	ResizeHandle(const QPixmap & pixmap, const QCursor &, bool ignoresTransforms, QGraphicsItem * parent = nullptr);
	~ResizeHandle() = default;

	constexpr QPointF resizeOffset() const noexcept { return m_resizeOffset; }
	void setResizeOffset(QPointF);
	double currentScale();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

public slots:
	void zoomChangedSlot(double scale);

protected:
	void mousePressEvent ( QGraphicsSceneMouseEvent * event );
	void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
	void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	bool scaling();

signals:
	void mousePressSignal(QGraphicsSceneMouseEvent * event, ResizeHandle *);
	void mouseMoveSignal(QGraphicsSceneMouseEvent * event, ResizeHandle *);
	void mouseReleaseSignal(QGraphicsSceneMouseEvent * event, ResizeHandle *);
	void zoomChangedSignal(double scale);

protected:
	QPointF m_resizeOffset;

};

#endif
