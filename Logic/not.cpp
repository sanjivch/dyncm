#include "not.h"

Not::Not(QGraphicsItem *parent) : UnitOperation(1,1,1,1,parent) {
  setOutputsOnTop(true);
  setPixmap( ":/basic/not.png" );
  updatePorts();
  setPortName("NOT");
}

Not::~Not() {

}

void Not::updateLogic() {
  char res = ! inputs().first()->value();
  if(!isValid()) {
    res = -1;
  }
  outputs().first()->setValue(res);
}
