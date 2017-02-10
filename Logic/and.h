#ifndef AND_H
#define AND_H

#include "unitoperation.h"//changed the graphicelement.h to unitoperation.h

class And : public UnitOperation {//change the name of the parent to UnitOperation from GraphicElement
public:
  explicit And( QGraphicsItem *parent = 0 );

  /* GraphicElement interface */
public:
  virtual UOType uoType( ) {//changed ElelmentType to UOType and elementType() to uoType()
    return( UOType::AND );
  }
  virtual UOGroup uoGroup( ) {//changed ElementGroup to UOGroup and elementGroup() to uoGroup()
    return( UOGroup::GATE );
  }
  void updateLogic( );


};

#endif /* AND_H */
