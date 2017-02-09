#include "box.h"
#include "boxnotfoundexception.h"
#include "commands.h"
#include "editor.h"
#include "globalproperties.h"
#include "unitoperation.h"
#include "input.h"
#include "mainwindow.h"
#include "nodes/qneconnection.h"
#include "serializationfunctions.h"

#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <QDrag>
#include <QFileDialog>
#include <QGraphicsItem>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QLabel>
#include <QMenu>
#include <QMessageBox>
#include <QMimeData>
#include <QMimeData>
#include <QSettings>
#include <QtMath>
#include <iostream>

Worksheet::Worksheet( QObject *parent ) : QObject( parent ), scene( nullptr ) {
  mainWindow = qobject_cast< MainWindow* >( parent );
  markingSelectionBox = false;
  _editedConn_id = 0;
  undoStack = new QUndoStack( this );
  scene = new Scene( this );

  scene->setBackgroundBrush( QBrush( QColor( "#ffffe6" ) ) );
  scene->setDots(QPen( Qt::darkGray ));

//  scene->setBackgroundBrush( QBrush( QColor( "#404552" ) ) );
//  scene->setDots(QPen( Qt::black ));

  install( scene );
  draggingElement = false;
  clear( );
  timer.start( );
  mShowConnections = true;
  mShowGates = true;
  connect( this, &Worksheet::circuitHasChanged, simulationController, &SimSettings::reSortElms );
}

Worksheet::~Worksheet( ) {
}

void Worksheet::install( Scene *s ) {
  s->installEventFilter( this );
  connect( scene, &QGraphicsScene::selectionChanged, this, &Worksheet::selectionChanged );
  simulationController = new SimSettings( s );
  simulationController->start( );
  buildSelectionRect( );
  clear( );
}

QNEConnection* Worksheet::getEditedConn( ) {
  return( dynamic_cast< QNEConnection* >( ElementFactory::getItemById( _editedConn_id ) ) );
}

void Worksheet::setEditedConn( QNEConnection *editedConn ) {
  if( editedConn ) {
    _editedConn_id = editedConn->id( );
  }
  else {
    _editedConn_id = 0;
  }
}


void Worksheet::buildSelectionRect( ) {
  selectionRect = new QGraphicsRectItem( );
  selectionRect->setBrush( QBrush( QColor(175, 0, 0, 80)) );
  selectionRect->setFlag( QGraphicsItem::ItemIsSelectable, false );
  selectionRect->setPen( QPen( QColor(175, 0, 0, 255), 1, Qt::SolidLine ) );
  scene->addItem( selectionRect );
}

void Worksheet::clear( ) {
  ElementFactory::instance->clear( );
  undoStack->clear( );
  if( scene ) {
    scene->clear( );
  }
  buildSelectionRect( );
  if( !scene->views( ).isEmpty( ) ) {
    scene->setSceneRect( scene->views( ).front( )->rect( ) );
  }
  emit circuitHasChanged( );
}

void Worksheet::deleteAction( ) {
  const QList< QGraphicsItem* > &items = scene->selectedItems( );
  scene->clearSelection( );
  if( !items.isEmpty( ) ) {
    receiveCommand( new DeleteItemsCommand( items, this ) );
  }
}

void Worksheet::showConnections( bool checked ) {
  mShowConnections = checked;
  for( QGraphicsItem *item : scene->items( ) ) {
    UnitOperation *elm = qgraphicsitem_cast< UnitOperation* >( item );
    if( ( item->type( ) == QNEConnection::Type ) ) {
      item->setVisible( checked );
    }
    else if( ( item->type( ) == UnitOperation::Type ) && elm ) {
      if( elm->uoType( ) == UOType::NODE ) {
        elm->setVisible( checked );
      }
      else {
        for( QNEPort *in : elm->inputs( ) ) {
          in->setVisible( checked );
        }
        for( QNEPort *out : elm->outputs( ) ) {
          out->setVisible( checked );
        }
      }
    }
  }
}
//Need to look closely at the showGates function not needed for dyncm
void Worksheet::showGates( bool checked ) {
  mShowGates = checked;
  for( QGraphicsItem *item : scene->items( ) ) {
    UnitOperation *elm = qgraphicsitem_cast< UnitOperation* >( item );
    if( ( item->type( ) == UnitOperation::Type ) && elm ) {
      switch( elm->uoType( ) ) {
          case UOType::SWITCH:
          case UOType::BUTTON:
          case UOType::LED:
          case UOType::DISPLAY:
          break;
          default:
          item->setVisible( checked );
          break;
      }
    }
  }
}

void Worksheet::rotate( bool rotateRight ) {
  double angle = 90.0;
  if( !rotateRight ) {
    angle = -angle;
  }
  QList< QGraphicsItem* > list = scene->selectedItems( );
  QList< UnitOperation* > elms;
  for( QGraphicsItem *item : list ) {
    UnitOperation *elm = qgraphicsitem_cast< UnitOperation* >( item );
    if( elm && ( elm->type( ) == UnitOperation::Type ) ) {
      elms.append( elm );
    }
  }
  if( ( elms.size( ) > 1 ) || ( ( elms.size( ) == 1 ) && elms.front( )->rotatable( ) ) ) {
    receiveCommand( new RotateCommand( elms, angle ) );
  }
}

void Worksheet::selectionChanged( ) {

}

QList< QGraphicsItem* > Worksheet::itemsAt( QPointF pos ) {
  QRectF rect( pos - QPointF( 4, 4 ), QSize( 9, 9 ) );
  return( scene->items( rect.normalized( ) ) );
}


QGraphicsItem* Worksheet::itemAt( QPointF pos ) {
  QList< QGraphicsItem* > items = scene->items( pos );
  items.append( itemsAt( pos ) );
  for( QGraphicsItem *item : items ) {
    if( item->type( ) == QNEPort::Type ) {
      return( item );
    }
  }
  for( QGraphicsItem *item : items ) {
    if( item->type( ) > QGraphicsItem::UserType ) {
      return( item );
    }
  }
  return( nullptr );
}

ElementEditor* Worksheet::getElementEditor( ) const {
  return( _elementEditor );
}

QPointF Worksheet::getMousePos( ) const {
  return( mousePos );
}

SimSettings* Worksheet::getSimulationController( ) const {
  return( simulationController );
}

void Worksheet::addItem( QGraphicsItem *item ) {
  scene->addItem( item );
}

bool Worksheet::mousePressEvt( QGraphicsSceneMouseEvent *mouseEvt ) {
  QGraphicsItem *item = itemAt( mousePos );
  if( item && ( item->type( ) == QNEPort::Type ) ) {
    /* When the mouse pressed over an connected input port, the line
     * is disconnected and can be connected in an other port. */
    QNEPort *pressedPort = qgraphicsitem_cast< QNEPort* >( item );
    if( pressedPort->isInput( ) && !pressedPort->connections( ).empty( ) ) {
      /* The last connected line is detached */
      QNEConnection *editedConn = pressedPort->connections( ).last( );
      setEditedConn( editedConn );

      editedConn->setFocus( );

      QNEPort *port1 = editedConn->otherPort( pressedPort );
      if( port1 ) {
        QList< QGraphicsItem* > itemList;
        itemList.append( editedConn );
        receiveCommand( new DeleteItemsCommand( itemList, this ) );
        editedConn = ElementFactory::buildConnection( );
        editedConn->setPort1( port1 );
        editedConn->setPort2( nullptr );
        editedConn->updatePosFromPorts( );
        editedConn->setPos2( mousePos );
        editedConn->updatePath( );
        addItem( editedConn );
        setEditedConn( editedConn );
      }
      else {
        setEditedConn( nullptr );
      }
    }
    else {
      QNEConnection *editedConn = ElementFactory::buildConnection( );
      addItem( editedConn );
      setEditedConn( editedConn );
      editedConn->setPort1( pressedPort );
      editedConn->updatePosFromPorts( );
      editedConn->setPos2( mousePos );
      editedConn->updatePath( );
      return( true );
    }
  }
  else if( !item ) {
    if( mouseEvt->button( ) == Qt::LeftButton ) {
      /* Mouse pressed over boar (Selection box). */
      selectionStartPoint = mousePos;
      markingSelectionBox = true;
      selectionRect->setRect( QRectF( selectionStartPoint, selectionStartPoint ) );
      selectionRect->show( );
      selectionRect->update( );
    }
  }
  return( false );
}

void Worksheet::resizeScene( ) {
  QVector< UnitOperation* > elms = scene->getElements( );
  if( !elms.isEmpty( ) ) {
    QRectF rect = scene->sceneRect( );
    for( UnitOperation *elm : elms ) {
      QRectF itemRect = elm->boundingRect( ).translated( elm->pos( ) );
      rect = rect.united( itemRect.adjusted( -10, -10, 10, 10 ) );
    }
    scene->setSceneRect( rect );
  }
  QGraphicsItem *item = itemAt( mousePos );
  if( item && ( timer.elapsed( ) > 100 ) && draggingElement ) {
    if( !scene->views( ).isEmpty( ) ) {
      QGraphicsView *view = scene->views( ).front( );
      view->ensureVisible( QRectF( mousePos - QPointF( 4, 4 ), QSize( 9, 9 ) ).normalized( ) );
    }
    timer.restart( );
  }
}

bool Worksheet::mouseMoveEvt( QGraphicsSceneMouseEvent *mouseEvt ) {
  Q_UNUSED( mouseEvt )
  QNEPort * port = dynamic_cast< QNEPort* >( itemAt( mousePos ) );
  handleHoverPort( port );
  QNEConnection *editedConn = getEditedConn( );
  if( editedConn ) {
    /* If a connection is being created, the ending coordinate follows the mouse position. */
    editedConn->setPos2( mousePos );
    editedConn->updatePath( );
    return( true );
  }
  else if( markingSelectionBox ) {
    /* If is marking the selectionBox, the last coordinate follows the mouse position. */
    QRectF rect = QRectF( selectionStartPoint, mousePos ).normalized( );
    selectionRect->setRect( rect );
    QPainterPath selectionBox;
    selectionBox.addRect( rect );
    scene->setSelectionArea( selectionBox );
  }
  else if( !markingSelectionBox ) {
    /* Else, the selectionRect is hidden. */
    selectionRect->hide( );
  }
  return( false );
}

bool Worksheet::mouseReleaseEvt( QGraphicsSceneMouseEvent *mouseEvt ) {
  /* When mouse is released the selection rect is hidden. */
  selectionRect->hide( );
  markingSelectionBox = false;
  if( QApplication::overrideCursor( ) ) {
    QApplication::setOverrideCursor( Qt::ArrowCursor );
  }
  QNEConnection *editedConn = getEditedConn( );
  if( editedConn && ( mouseEvt->button( ) == Qt::LeftButton ) ) {
    /* A connection is being created, and left button was released. */
    QNEPort *port = dynamic_cast< QNEPort* >( itemAt( mousePos ) );
    if( port && ( port->type( ) == QNEPort::Type ) ) {
      /* The mouse is released over a QNEPort. */
      QNEPort *port1 = editedConn->port1( );
      QNEPort *port2 = dynamic_cast< QNEPort* >( port );
      if( !port2 ) {
        return( true );
      }
      /* Verifying if the connection is valid. */
      if( ( port1->isOutput( ) != port2->isOutput( ) ) &&
          ( port1->graphicElement( ) != port2->graphicElement( ) ) && !port1->isConnected( port2 ) ) {
        /* Making connection. */
        editedConn->setPos2( port2->scenePos( ) );
        editedConn->setPort2( port2 );
        editedConn->updatePath( );
        receiveCommand( new AddItemsCommand( editedConn, this ) );
        setEditedConn( nullptr );
        return( true );
      }
    }
    /* When mouse is released away from a QNEPort, the connection is discarded. */
    scene->removeItem( editedConn );
    if( editedConn->port1( ) ) {
      editedConn->port1( )->disconnect( editedConn );
    }
    setEditedConn( nullptr );
    delete editedConn;

    return( true );
  }
  return( false );
}

bool Worksheet::loadBox( Box *box, QString fname ) {
  try {
    if( box->getParentFile( ).isEmpty( ) ) {
      box->setParentFile( GlobalProperties::currentFile );
    }
    box->loadFile( fname );
  }
  catch( BoxNotFoundException &err ) {
    qDebug( ) << "BoxNotFoundException thrown: " << err.what( );
    int ret = QMessageBox::warning( mainWindow, tr( "Error" ), QString::fromStdString(
                                      err.what( ) ), QMessageBox::Ok, QMessageBox::Cancel );
    if( ret == QMessageBox::Cancel ) {
      return( false );
    }
    else {
      fname = mainWindow->getOpenBoxFile( );
      if( fname.isEmpty( ) ) {
        return( false );
      }
      else {
        return( loadBox( err.getBox( ), fname ) );
      }
    }
  }

  QSettings settings( QSettings::IniFormat, QSettings::UserScope,
                      QApplication::organizationName( ), QApplication::applicationName( ) );
  QStringList files;
  if( settings.contains( "recentBoxes" ) ) {
    files = settings.value( "recentBoxes" ).toStringList( );
    files.removeAll( fname );
  }
  files.prepend( fname );
  settings.setValue( "recentBoxes", files );
  if( mainWindow ) {
    mainWindow->updateRecentBoxes( );
  }
  return( true );
}

void Worksheet::handleHoverPort( QNEPort *port ) {
  QNEConnection *editedConn = getEditedConn( );
  QNEPort *hoverPort = getHoverPort( );
  if( hoverPort && ( port != hoverPort ) ) {
    releaseHoverPort( );
  }
  else if( port && ( port->type( ) == QNEPort::Type ) ) {
    setHoverPort( port );
    if( editedConn && editedConn->port1( ) && ( editedConn->port1( )->isOutput( ) == port->isOutput( ) ) ) {
      QApplication::setOverrideCursor( QCursor( Qt::ForbiddenCursor ) );
    }
  }
}

void Worksheet::releaseHoverPort( ) {
  QNEPort *hoverPort = getHoverPort( );
  if( hoverPort ) {
    setHoverPort( nullptr );
    QApplication::setOverrideCursor( QCursor( ) );
  }
}

void Worksheet::setHoverPort( QNEPort *port ) {
  if( port ) {
    UnitOperation *hoverElm = port->graphicElement( );
    if( hoverElm && ElementFactory::contains( hoverElm->id( ) ) ) {
      _hoverPortElm_id = hoverElm->id( );
      for( int i = 0; i < ( hoverElm->inputSize( ) + hoverElm->outputSize( ) - 1 ); ++i ) {
        if( i < hoverElm->inputSize( ) ) {
          if( port == hoverElm->input( i ) ) {
            _hoverPort_nbr = i;
          }
        }
        else if( port == hoverElm->output( i - hoverElm->inputSize( ) ) ) {
          _hoverPort_nbr = i;
        }
      }
    }
  }
  else {
    _hoverPortElm_id = 0;
    _hoverPort_nbr = 0;
  }
}

QNEPort* Worksheet::getHoverPort( ) {
  UnitOperation *hoverElm = dynamic_cast< UnitOperation* >( ElementFactory::getItemById( _hoverPortElm_id ) );
  QNEPort *hoverPort = nullptr;
  if( hoverElm ) {
    if( _hoverPort_nbr < hoverElm->inputSize( ) ) {
      hoverPort = hoverElm->input( _hoverPort_nbr );
    }
    else if( ( ( _hoverPort_nbr - hoverElm->inputSize( ) ) < hoverElm->outputSize( ) ) ) {
      hoverPort = hoverElm->output( _hoverPort_nbr - hoverElm->inputSize( ) );
    }
  }
  if( !hoverPort ) {
    setHoverPort( nullptr );
  }
  return( hoverPort );
}

bool Worksheet::dropEvt( QGraphicsSceneDragDropEvent *dde ) {
  /* Verify if mimetype is compatible. */
  if( dde->mimeData( )->hasFormat( "application/x-dnditemdata" ) ) {
    /* Extracting mimedata from drop event. */
    QByteArray itemData = dde->mimeData( )->data( "application/x-dnditemdata" );
    QDataStream dataStream( &itemData, QIODevice::ReadOnly );
    QPointF offset;
    QString label_auxData;
    qint32 type;
    dataStream >> offset >> type >> label_auxData;
    QPointF pos = dde->scenePos( ) - offset;
    dde->accept( );

    UnitOperation *elm = ElementFactory::buildElement( ( UOType ) type, this );
    /* If element type is unknown, a default element is created with the pixmap received from mimedata */
    if( !elm ) {
      return( false );
    }
    if( elm->uoType( ) == UOType::BOX ) {
      try {
        Box *box = dynamic_cast< Box* >( elm );
        if( box ) {
          QString fname = label_auxData;
          if( !loadBox( box, fname ) ) {
            return( false );
          }
        }
      }
      catch( std::runtime_error &err ) {
        QMessageBox::warning( mainWindow, tr( "Error" ), QString::fromStdString( err.what( ) ) );
        return( false );
      }
    }
    int wdtOffset = ( 64 - elm->boundingRect( ).width( ) ) / 2;
    if( wdtOffset > 0 ) {
      pos = pos + QPointF( wdtOffset, wdtOffset );
    }
    /*
     * TODO: Rotate all element icons, remake the port position logic, and remove the code below.
     * Rotating element in 90 degrees.
     */
    if( elm->rotatable( ) && ( elm->uoType( ) != UOType::NODE ) ) {
      elm->setRotation( 90 );
    }
    /* Adding the element to the scene. */
    receiveCommand( new AddItemsCommand( elm, this ) );
    /* Cleaning the selection. */
    scene->clearSelection( );
    /* Setting created element as selected. */
    elm->setSelected( true );
    /* Adjusting the position of the element. */
    elm->setPos( pos );

    return( true );
  }
  else if( dde->mimeData( )->hasFormat( "application/ctrlDragData" ) ) {

    QByteArray itemData = dde->mimeData( )->data( "application/ctrlDragData" );
    QDataStream ds( &itemData, QIODevice::ReadOnly );

    QPointF offset;
    ds >> offset;
    offset = dde->scenePos( ) - offset;
    dde->accept( );

    scene->clearSelection( );

    QPointF ctr;
    ds >> ctr;
    double version = GlobalProperties::version;
    QList< QGraphicsItem* > itemList = SerializationFunctions::deserialize( this,
                                                                            ds,
                                                                            version,
                                                                            GlobalProperties::currentFile );
    receiveCommand( new AddItemsCommand( itemList, this ) );
    for( QGraphicsItem *item : itemList ) {
      if( item->type( ) == UnitOperation::Type ) {
        item->setPos( ( item->pos( ) + offset ) );
        item->update( );
        item->setSelected( true );
      }
    }
    resizeScene( );

    return( true );
  }
  return( false );
}

bool Worksheet::dragMoveEvt( QGraphicsSceneDragDropEvent *dde ) {
  /* Accepting drag/drop event of the following mimedata format. */
  if( dde->mimeData( )->hasFormat( "application/x-dnditemdata" ) ) {
    return( true );
  }
  if( dde->mimeData( )->hasFormat( "application/ctrlDragData" ) ) {
    return( true );
  }
  return( false );
}

bool Worksheet::wheelEvt( QWheelEvent *wEvt ) {
  if( wEvt ) {
    int numDegrees = wEvt->delta( ) / 8;
    int numSteps = numDegrees / 15;
    if( wEvt->orientation( ) == Qt::Horizontal ) {
      emit scroll( numSteps, 0 );
    }
    else {
      emit scroll( 0, numSteps );
    }
    wEvt->accept( );
    return( true );
  }
  return( false );
}

void Worksheet::ctrlDrag( QPointF pos ) {
  COMMENT( "Ctrl + Drag action triggered.", 0 );
  QVector< UnitOperation* > selectedElms = scene->selectedElements( );
  if( !selectedElms.isEmpty( ) ) {
    QRectF rect;
    for( UnitOperation *elm : selectedElms ) {
      rect = rect.united( elm->boundingRect( ).translated( elm->pos( ) ) );
    }
    rect = rect.adjusted( -8, -8, 8, 8 );
    QImage image( rect.size( ).toSize( ), QImage::Format_ARGB32 );
    image.fill( Qt::transparent );

    QPainter painter( &image );
    painter.setOpacity( 0.25 );
    scene->render( &painter, image.rect( ), rect );

    QByteArray itemData;
    QDataStream dataStream( &itemData, QIODevice::WriteOnly );

    QPointF offset = pos - rect.topLeft( );
    dataStream << pos;

    copy( scene->selectedItems( ), dataStream );

    QMimeData *mimeData = new QMimeData;
    mimeData->setData( "application/ctrlDragData", itemData );

    QDrag *drag = new QDrag( this );
    drag->setMimeData( mimeData );
    drag->setPixmap( QPixmap::fromImage( image ) );
    drag->setHotSpot( offset.toPoint( ) );
    drag->exec( Qt::CopyAction, Qt::CopyAction );
  }
  scene->clearSelection( );
}

QUndoStack* Worksheet::getUndoStack( ) const {
  return( undoStack );
}

Scene* Worksheet::getScene( ) const {
  return( scene );
}

void Worksheet::cut( const QList< QGraphicsItem* > &items, QDataStream &ds ) {
  copy( items, ds );
  deleteAction( );
}

void Worksheet::copy( const QList< QGraphicsItem* > &items, QDataStream &ds ) {
  QPointF center( 0.0f, 0.0f );
  float elm = 0;
  for( QGraphicsItem *item : items ) {
    if( item->type( ) == UnitOperation::Type ) {
      center += item->pos( );
      elm++;
    }
  }
  ds << center / elm;
  SerializationFunctions::serialize( scene->selectedItems( ), ds );
}

void Worksheet::paste( QDataStream &ds ) {
  scene->clearSelection( );
  QPointF ctr;
  ds >> ctr;
  QPointF offset = mousePos - ctr - QPointF( 32.0f, 32.0f );
  double version = GlobalProperties::version;
  QList< QGraphicsItem* > itemList = SerializationFunctions::deserialize( this,
                                                                          ds,
                                                                          version,
                                                                          GlobalProperties::currentFile );
  receiveCommand( new AddItemsCommand( itemList, this ) );
  for( QGraphicsItem *item : itemList ) {
    if( item->type( ) == UnitOperation::Type ) {
      item->setPos( ( item->pos( ) + offset ) );
      item->update( );
      item->setSelected( true );
    }
  }
  resizeScene( );
}

void Worksheet::selectAll( ) {
  for( QGraphicsItem *item : scene->items( ) ) {
    item->setSelected( true );
  }
}

void Worksheet::save( QDataStream &ds ) {
  ds << QApplication::applicationName( ) + " " + QApplication::applicationVersion( ).split("-").first();
  ds << scene->sceneRect( );
  SerializationFunctions::serialize( scene->items( ), ds );
}

void Worksheet::load( QDataStream &ds ) {
  clear( );
  SerializationFunctions::load( this, ds, GlobalProperties::currentFile, scene );
  scene->clearSelection( );
  emit circuitHasChanged( );
}

void Worksheet::setElementEditor( ElementEditor *value ) {
  _elementEditor = value;
  _elementEditor->setScene( scene );
  _elementEditor->setEditor( this );
  connect( _elementEditor, &ElementEditor::sendCommand, this, &Worksheet::receiveCommand );
}

QPointF roundTo( QPointF point, int multiple ) {
  int x = static_cast< int >( point.x( ) );
  int y = static_cast< int >( point.y( ) );
  int nx = multiple * qFloor( x / multiple );
  int ny = multiple * qFloor( y / multiple );
  return( QPointF( nx, ny ) );
}

void Worksheet::contextMenu( QPoint screenPos ) {
  QGraphicsItem *item = itemAt( mousePos );
  if( item ) {
    if( scene->selectedItems( ).contains( item ) ) {
      _elementEditor->contextMenu( screenPos );
    }
    else if( ( item->type( ) == UnitOperation::Type ) ) {
      scene->clearSelection( );
      item->setSelected( true );
      _elementEditor->contextMenu( screenPos );
    }
  }
  else {
    QMenu menu;
    QAction *pasteAction = menu.addAction( QIcon( QPixmap( ":/toolbar/paste.png" ) ), tr( "Paste" ) );
    const QClipboard *clipboard = QApplication::clipboard( );
    const QMimeData *mimeData = clipboard->mimeData( );
    if( mimeData->hasFormat( "wpanda/copydata" ) ) {
      connect( pasteAction, &QAction::triggered, this, &Worksheet::pasteAction );
    }
    else {
      pasteAction->setEnabled( false );
    }
    menu.exec( screenPos );
  }
}

void Worksheet::updateVisibility( ) {
  showGates( mShowGates );
  showConnections( mShowConnections );
}

void Worksheet::receiveCommand( QUndoCommand *cmd ) {
  undoStack->push( cmd );
}

void Worksheet::copyAction( ) {
  QVector< UnitOperation* > elms = scene->selectedElements( );
  if( elms.empty( ) ) {
    QClipboard *clipboard = QApplication::clipboard( );
    clipboard->clear( );
  }
  else {
    QClipboard *clipboard = QApplication::clipboard( );
    QMimeData *mimeData = new QMimeData;
    QByteArray itemData;
    QDataStream dataStream( &itemData, QIODevice::WriteOnly );
    copy( scene->selectedItems( ), dataStream );
    mimeData->setData( "wpanda/copydata", itemData );
    clipboard->setMimeData( mimeData );
  }
}

void Worksheet::cutAction( ) {
  QClipboard *clipboard = QApplication::clipboard( );
  QMimeData *mimeData = new QMimeData( );
  QByteArray itemData;
  QDataStream dataStream( &itemData, QIODevice::WriteOnly );
  cut( scene->selectedItems( ), dataStream );
  mimeData->setData( "wpanda/copydata", itemData );
  clipboard->setMimeData( mimeData );
}

void Worksheet::pasteAction( ) {
  const QClipboard *clipboard = QApplication::clipboard( );
  const QMimeData *mimeData = clipboard->mimeData( );
  if( mimeData->hasFormat( "wpanda/copydata" ) ) {
    QByteArray itemData = mimeData->data( "wpanda/copydata" );
    QDataStream dataStream( &itemData, QIODevice::ReadOnly );
    paste( dataStream );
  }
}

bool Worksheet::eventFilter( QObject *obj, QEvent *evt ) {
  if( obj == scene ) {
    QGraphicsSceneDragDropEvent *dde = dynamic_cast< QGraphicsSceneDragDropEvent* >( evt );
    QGraphicsSceneMouseEvent *mouseEvt = dynamic_cast< QGraphicsSceneMouseEvent* >( evt );
    QWheelEvent *wEvt = dynamic_cast< QWheelEvent* >( evt );
    QKeyEvent *keyEvt = dynamic_cast< QKeyEvent* >( evt );
    if( mouseEvt ) {
      mousePos = mouseEvt->scenePos( );
      resizeScene( );
      if( mouseEvt->modifiers( ) & Qt::ShiftModifier ) {
        mouseEvt->setModifiers( Qt::ControlModifier );
        return( QObject::eventFilter( obj, evt ) );
      }
    }
    bool ret = false;
    if( ( evt->type( ) == QEvent::GraphicsSceneMousePress )
        || ( evt->type( ) == QEvent::GraphicsSceneMouseDoubleClick ) ) {
      QGraphicsItem *item = itemAt( mousePos );
      if( item && ( mouseEvt->button( ) == Qt::LeftButton ) ) {
        if( ( mouseEvt->modifiers( ) & Qt::ControlModifier ) && ( item->type( ) == UnitOperation::Type ) ) {
          item->setSelected( true );
          ctrlDrag( mouseEvt->scenePos( ) );
          return( true );
        }
        draggingElement = true;
        /* STARTING MOVING ELEMENT */
/*        qDebug() << "IN"; */
        QList< QGraphicsItem* > list = scene->selectedItems( );
        list.append( itemsAt( mousePos ) );
        movedElements.clear( );
        oldPositions.clear( );
        for( QGraphicsItem *it : list ) {
          UnitOperation *elm = qgraphicsitem_cast< UnitOperation* >( it );
          if( elm ) {
            movedElements.append( elm );
            oldPositions.append( elm->pos( ) );
          }
        }
      }
      else if( mouseEvt->button( ) == Qt::RightButton ) {
        contextMenu( mouseEvt->screenPos( ) );
      }
    }
    if( evt->type( ) == QEvent::GraphicsSceneMouseRelease ) {
      if( draggingElement && ( mouseEvt->button( ) == Qt::LeftButton ) ) {
        if( !movedElements.empty( ) ) {
/*
 *          if( movedElements.size( ) != oldPositions.size( ) ) {
 *            throw std::runtime_error( tr( "Invalid coordinates." ).toStdString( ) );
 *          }
 *          qDebug() << "OUT";
 */
          bool valid = false;
          for( int elm = 0; elm < movedElements.size( ); ++elm ) {
            if( movedElements[ elm ]->pos( ) != oldPositions[ elm ] ) {
              valid = true;
              break;
            }
          }
          if( valid ) {
            receiveCommand( new MoveCommand( movedElements, oldPositions ) );
          }
        }
        draggingElement = false;
        movedElements.clear( );
      }
    }
    switch( ( int ) evt->type( ) ) {
        case QEvent::GraphicsSceneMousePress: {
        ret = mousePressEvt( mouseEvt );
        break;
      }
        case QEvent::GraphicsSceneMouseMove: {
        ret = mouseMoveEvt( mouseEvt );
        break;
      }
        case QEvent::GraphicsSceneMouseRelease: {
        ret = mouseReleaseEvt( mouseEvt );
        break;
      }
        case QEvent::GraphicsSceneDrop: {
        ret = dropEvt( dde );
        break;
      }
        case QEvent::GraphicsSceneDragMove:
        case QEvent::GraphicsSceneDragEnter: {
        ret = dragMoveEvt( dde );
        break;
      }
        case QEvent::GraphicsSceneWheel: {
        ret = wheelEvt( wEvt );
        break;
      }
        case QEvent::GraphicsSceneMouseDoubleClick: {
        QNEConnection *connection = dynamic_cast< QNEConnection* >( itemAt( mousePos ) );
        if( connection && ( connection->type( ) == QNEConnection::Type ) ) {
          /* Mouse pressed over a connection. */
          if( connection ) {
            if( connection->port1( ) && connection->port2( ) ) {
              receiveCommand( new SplitCommand( connection, mousePos, this ) );
            }
          }
          evt->accept( );
          return( true );
        }
        break;
      }
        case QEvent::KeyPress: {
        if( keyEvt && !( keyEvt->modifiers( ) & Qt::ControlModifier ) ) {
          for( UnitOperation *elm : scene->getElements( ) ) {
            if( elm->hasTrigger( ) && !elm->getTrigger( ).isEmpty( ) ) {
              Input *in = dynamic_cast< Input* >( elm );
              if( in && elm->getTrigger( ).matches( keyEvt->key( ) ) ) {
                if( elm->uoType( ) == UOType::SWITCH ) {
                  in->setOn( !in->getOn( ) );
                }
                else {
                  in->setOn( true );
                }
              }
            }
          }
        }
        break;
      }
        case QEvent::KeyRelease: {
        if( keyEvt && !( keyEvt->modifiers( ) & Qt::ControlModifier ) ) {
          for( UnitOperation *elm : scene->getElements( ) ) {
            if( elm->hasTrigger( ) && !elm->getTrigger( ).isEmpty( ) ) {
              Input *in = dynamic_cast< Input* >( elm );
              if( in && ( elm->getTrigger( ).matches( keyEvt->key( ) ) == QKeySequence::ExactMatch ) ) {
                if( elm->uoType( ) != UOType::SWITCH ) {
                  in->setOn( false );
                }
              }
            }
          }
        }
        break;
      }
    }
    if( ret ) {
      return( ret );
    }
  }
  return( QObject::eventFilter( obj, evt ) );
}
