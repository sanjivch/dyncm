#ifndef SIMSETTINGS_H
#define SIMSETTINGS_H

#include "unitoperation.h"
#include "scene.h"

#include <QGraphicsScene>
#include <QMap>
#include <QObject>
#include <QTimer>

class SimSettings : public QObject {
  Q_OBJECT
public:
  explicit SimSettings( Scene *scn );
  ~SimSettings( );
  static QVector< UnitOperation* > sortElements( QVector< UnitOperation* > elms );
signals:

public slots:
  void update( );
  void stop( );
  void start( );
  void reSortElms();

private:
  Scene *scene;
  QTimer timer;
  QVector< UnitOperation* > sortedElements;
  static int calculatePriority( UnitOperation *elm,
                                QMap< UnitOperation*, bool > &beingvisited,
                                QMap< UnitOperation*, int > &priority );
};

#endif /* SIMSETTINGS_H */
