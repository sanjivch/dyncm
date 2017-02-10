#ifndef NOT_H
#define NOT_H

#include "unitoperation.h"//changed the name of the parent to UnitOperation from GraphicElement

class Not : public UnitOperation {
public:
  explicit Not( QGraphicsItem *parent );
  virtual ~Not( );

  /* GraphicElement interface */
public:
  virtual UOType uoType( ) {//replaced element with UO or uo
    return( UOType::NOT );
  }
  virtual UOGroup uoGroup( ) {
    return( UOGroup::GATE );
  }
  void updateLogic( );
};

#endif /* NOT_H */
