#include "simsettings.h"

#include <QDebug>
#include <limits>

#include <element/clock.h>

#include <nodes/qneconnection.h>

#include <QStack>

SimSettings::SimSettings( Scene *scn ) : QObject( dynamic_cast< QObject* >( scn ) ), timer( this ) {
  scene = scn;
  timer.setInterval( GLOBALCLK );
  connect( &timer, &QTimer::timeout, this, &SimSettings::update );
}

SimSettings::~SimSettings( ) {

}

int SimSettings::calculatePriority( UnitOperation *elm,
                                             QMap< UnitOperation*, bool > &beingvisited,
                                             QMap< UnitOperation*, int > &priority ) {
  if( !elm ) {
    return( 0 );
  }
  if( beingvisited.contains( elm ) && ( beingvisited[ elm ] == true ) ) {

    return( 0 );
  }
  if( priority.contains( elm ) ) {
    return( priority[ elm ] );
  }
  beingvisited[ elm ] = true;
  int max = 0;
  for( QNEPort *port : elm->outputs( ) ) {
    for( QNEConnection *conn : port->connections( ) ) {
      QNEPort *sucessor = conn->otherPort( port );
      if( sucessor ) {
        max = qMax( calculatePriority( sucessor->unitOperation( ), beingvisited, priority ), max );
      }
    }
  }
  int p = max + 1;
  priority[ elm ] = p;
  beingvisited[ elm ] = false;
  return( p );
}

QVector< UnitOperation* > SimSettings::sortElements( QVector< UnitOperation* > elms ) {
  QMap< UnitOperation*, bool > beingvisited;
  QMap< UnitOperation*, int > priority;
  for( UnitOperation *elm : elms ) {
    calculatePriority( elm, beingvisited, priority );
  }
  std::sort( elms.begin( ), elms.end( ), [ priority ]( UnitOperation *e1, UnitOperation *e2 ) {
    return( priority[ e2 ] < priority[ e1 ] );
  } );

  return( elms );
}

void SimSettings::update( ) {
  QVector< UnitOperation* > elements = scene->getElements( );
  if( Clock::reset ) {
    for( UnitOperation *elm : elements ) {
      if( elm->elementType( ) == ElementType::CLOCK ) {
        Clock *clk = dynamic_cast< Clock* >( elm );
        if( clk ) {
          clk->resetClock( );
        }
      }
    }
    Clock::reset = false;
  }
  if( elements.isEmpty( ) ) {
    return;
  }
  for( UnitOperation *elm : sortedElements ) {
    elm->updateLogic( );
  }
}

void SimSettings::stop( ) {
  timer.stop( );
}

void SimSettings::start( ) {
  timer.start( );
  Clock::reset = true;
  reSortElms();
}

void SimSettings::reSortElms( ) {
  COMMENT( "Re-sorting elements", 0 );
  QVector< UnitOperation* > elements = scene->getElements( );
  sortedElements = sortElements( elements );
}
