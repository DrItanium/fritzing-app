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

#ifndef DRC_H
#define DRC_H

#include <QList>
#include <QObject>
#include <QImage>
#include <QDomDocument>
#include <QGraphicsPixmapItem>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QRadioButton>
#include <QListWidgetItem>
#include <QPointer>

#include "../svg/svgfilesplitter.h"
#include "../viewlayer.h"

struct CollidingThing {
	QPointer<class NonConnectorItem> nonConnectorItem;
	QList<QPointF> atPixels;
};

struct Markers {
	QString inSvgID;
	QString inSvgAndID;
	QString inTerminalID;
	QString inNoID;
	QString outID;
};

class PCBSketchWidget;
class ItemBase;
class ConnectorItem;
class DRC : public QObject
{
	Q_OBJECT

public:
	DRC(PCBSketchWidget *, ItemBase * board);
	virtual ~DRC();

	QStringList start(bool showOkMessage, double keepoutMils);

public:
	static void splitNetPrep(QDomDocument * masterDoc, QList<ConnectorItem *> & equi, const Markers &, QList<QDomElement> & net, QList<QDomElement> & alsoNet, QList<QDomElement> & notNet, bool checkIntersection);
	static void extendBorder(double keepoutImagePixels, QImage * image);

public slots:
	void cancel();

signals:
	void hideProgress();
	void setMaximumProgress(int);
	void setProgressValue(int);
	void wantTopVisible();
	void wantBottomVisible();
	void wantBothVisible();
	void setProgressMessage(const QString &);

public:
	static const QString NotNet;
	static const QString AlsoNet;
	static const QString Net;
	static const uchar BitTable[];
	static const QString KeepoutSettingName;
	static const double KeepoutDefaultMils;

protected:
	bool makeBoard(QImage *, QRectF & sourceRes);
	void splitNet(QDomDocument *, QList<ConnectorItem *> &, QImage * minusImage, QImage * plusImage, QRectF & sourceRes, ViewLayer::ViewLayerPlacement viewLayerPlacement, int index, double keepoutMils);
	void updateDisplay();
	bool startAux(QString & message, QStringList & messages, QList<CollidingThing *> &, double keepoutMils);
	CollidingThing * findItemsAt(QList<QPointF> &, ItemBase * board, const LayerList & viewLayerIDs, double keepout, double dpi, bool skipHoles, ConnectorItem * already);
	void checkHoles(QStringList & messages, QList<CollidingThing *> & collidingThings, double dpi);
	void checkCopperBoth(QStringList & messages, QList<CollidingThing *> & collidingThings, double dpi);
	QList<ConnectorItem *> missingCopper(const QString & layerName, ViewLayer::ViewLayerID, ItemBase *, const QDomElement & svgRoot);

protected:
	static void markSubs(QDomElement & root, const QString & mark);
	static void splitSubs(QDomDocument *, QDomElement & root, const QString & partID, const Markers &, const QStringList & svgIDs,  const QStringList & terminalIDs, const QList<ItemBase *> &, QHash<QString, QString> & both, bool checkIntersection);

protected:
	PCBSketchWidget * m_sketchWidget = nullptr;
	ItemBase * m_board = nullptr;
	double m_keepout = 0.0;
	QImage * m_plusImage = nullptr;
	QImage * m_minusImage = nullptr;
	QImage * m_displayImage = nullptr;
	QGraphicsPixmapItem * m_displayItem = nullptr;
	QHash<ViewLayer::ViewLayerPlacement, QDomDocument *> m_masterDocs;
	bool m_cancelled = false;
	int m_maxProgress = 0;
};

class DRCResultsDialog : public QDialog
{
	Q_OBJECT

public:
	DRCResultsDialog(const QString & message, const QStringList & messages, const QList<CollidingThing *> &, QGraphicsPixmapItem * displayItem,  QImage * displayImage, class PCBSketchWidget * sketchWidget, QWidget *parent = nullptr);
	~DRCResultsDialog();

protected slots:
	void pressedSlot(QListWidgetItem *);
	void releasedSlot(QListWidgetItem *);

protected:
	QStringList m_messages;
	QList<CollidingThing *> m_collidingThings;
	QPointer <class PCBSketchWidget> m_sketchWidget;
	QGraphicsPixmapItem * m_displayItem = nullptr;
	QImage * m_displayImage = nullptr;
};

#endif
