#include "unitoperation.h"
#include "scene.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <iostream>
#include <nodes/qneconnection.h>
#include <stdexcept>

QMap< QString, QPixmap > loadedPixmaps;


UnitOperation::UnitOperation( int minInputSz, int maxInputSz, int minOutputSz, int maxOutputSz,
                                QGraphicsItem *parent ) : QGraphicsObject( parent ), label( new QGraphicsTextItem(
                                                                                              this ) )
{
  pixmap = NULL;
  COMMENT( "Setting flags of elements. ", 4 );
  setFlag( QGraphicsItem::ItemIsMovable );
  setFlag( QGraphicsItem::ItemIsSelectable );
/*  setFlag(QGraphicsItem::ItemSendsScenePositionChanges); */
  setFlag( QGraphicsItem::ItemSendsGeometryChanges );

  COMMENT( "Setting attributes. ", 4 );
  label->hide( );
  QFont font( "SansSerif" );
  font.setBold( true );
  label->setFont( font );
  label->setPos( 64, 30 );
  label->setParentItem( this );
  label->setDefaultTextColor(Qt::black);
  m_bottomPosition = 64;
  m_topPosition = 0;
  m_minInputSz = minInputSz;
  m_minOutputSz = minOutputSz;
  m_maxInputSz = maxInputSz;
  m_maxOutputSz = maxOutputSz;
/*
 *  m_visited = false;
 *  m_beingVisited = false;
 */
  m_rotatable = true;
  m_hasColors = false;
  m_hasTrigger = false;
  m_hasFrequency = false;
  m_hasLabel = false;
  m_disabled = false;
  m_outputsOnTop = true;

  COMMENT( "Including input and output ports.", 4 );
  for( int i = 0; i < minInputSz; i++ ) {
    addInputPort( );
  }
  for( int i = 0; i < minOutputSz; i++ ) {
    addOutputPort( );
  }
}

UnitOperation::~UnitOperation( ) {

}

QPixmap UnitOperation::getPixmap( ) const {
  if( pixmap ) {
    return( *pixmap );
  }
  else {
    return( QPixmap( ) );
  }
}


void UnitOperation::disable( ) {
  m_disabled = true;
}

void UnitOperation::enable( ) {
  m_disabled = false;
}

void UnitOperation::setPixmap( const QString &pixmapPath, QRect size ) {
  if( pixmapPath != currentPixmapPath ) {
    if( !loadedPixmaps.contains( pixmapPath ) ) {
      loadedPixmaps[ pixmapPath ] = QPixmap::fromImage( QImage( pixmapPath ) ).copy( size );
    }
    pixmap = &loadedPixmaps[ pixmapPath ];
    setTransformOriginPoint( pixmap->rect( ).center( ) );
    update( boundingRect( ) );
  }
}

QVector< QNEPort* > UnitOperation::outputs( ) const {
  return( m_outputs );
}

QNEPort* UnitOperation::input( int pos ) const {
  return( m_inputs.at( pos ) );
}

QNEPort* UnitOperation::output( int pos ) const {
  return( m_outputs.at( pos ) );
}

void UnitOperation::setOutputs( const QVector< QNEPort* > &outputs ) {
  m_outputs = outputs;
}

void UnitOperation::save( QDataStream &ds ) {
  COMMENT( "Saving element. Type: " << objectName( ).toStdString( ), 4 );
  ds << pos( );
  ds << rotation( );

  /* <Version1.2> */
  ds << getLabel( );
  /* <\Version1.2> */

  /* <Version1.3> */
  ds << m_minInputSz;
  ds << m_maxInputSz;
  ds << m_minOutputSz;
  ds << m_maxOutputSz;
  /* <\Version1.3> */
  /* <Version1.9> */
  ds << m_trigger;
  /* <\Version1.9> */
  ds << ( quint64 ) m_inputs.size( );
  foreach( QNEPort * port, m_inputs ) {
    ds << ( quint64 ) port;
    ds << port->portName( );
    ds << port->portFlags( );
  }
  ds << ( quint64 ) m_outputs.size( );
  foreach( QNEPort * port, m_outputs ) {
    ds << ( quint64 ) port;
    ds << port->portName( );
    ds << port->portFlags( );
  }
  COMMENT( "Finished saving element.", 4 );
}

void UnitOperation::load( QDataStream &ds, QMap< quint64, QNEPort* > &portMap, double version ) {
  COMMENT( "Loading element. Type: " << objectName( ).toStdString( ), 4 );
  QPointF p;
  QString label_text;
  ds >> p;
  qreal angle;
  ds >> angle;
  setPos( p );
  setRotation( angle );
  /* <Version1.2> */
  if( version >= 1.2 ) {
    ds >> label_text;
    setLabel( label_text );
  }
  /* <\Version1.2> */
  /* <Version1.3> */
  if( version >= 1.3 ) {
    quint64 min_isz, max_isz, min_osz, max_osz;
    ds >> min_isz;
    ds >> max_isz;
    ds >> min_osz;
    ds >> max_osz;
    /* FIXME: Was it a bad decision to store Min and Max input/ouput sizes? */
    /* Version 2.2 ?? fix ?? */
    if( !( ( m_minInputSz == m_maxInputSz ) && ( m_minInputSz > max_isz ) ) ) {
      m_minInputSz = min_isz;
      m_maxInputSz = max_isz;
    }
    if( !( ( m_minOutputSz == m_maxOutputSz ) && ( m_minOutputSz > max_osz ) ) ) {
      m_minOutputSz = min_osz;
      m_maxOutputSz = max_osz;
    }
  }
  /* <\Version1.3> */
  /* <Version1.9> */
  if( version >= 1.9 ) {
    ds >> m_trigger;
    setLabel( label_text );
  }
  /* <\Version1.9> */

  quint64 inputSz, outputSz;

  COMMENT( "Setting input ports.", 4 );
  ds >> inputSz;
  if( inputSz > MAXIMUMVALIDINPUTSIZE ) {
    throw std::runtime_error( "Corrupted file!" );
  }
  for( size_t port = 0; port < inputSz; ++port ) {
    QString name;
    int flags;
    quint64 ptr;
    ds >> ptr;
    ds >> name;
    ds >> flags;
    if( port < ( size_t ) m_inputs.size( ) ) {
      portMap[ ptr ] = m_inputs[ port ];
      if( uoType( ) == UOType::BOX ) {
        m_inputs[ port ]->setName( name );
      }
      m_inputs[ port ]->setPortFlags( flags );
      m_inputs[ port ]->setPtr( ptr );
    }
    else {
      portMap[ ptr ] = addPort( name, false, flags, ptr );
    }
  }
  while( inputSize( ) > ( int ) inputSz && inputSz >= m_minInputSz ) {
    delete m_inputs.back( );
    m_inputs.pop_back( );
  }
  COMMENT( "Setting output ports.", 4 );
  ds >> outputSz;
  if( outputSz > MAXIMUMVALIDINPUTSIZE ) {
    throw std::runtime_error( "Corrupted file!" );
  }
  for( size_t port = 0; port < outputSz; ++port ) {
    QString name;
    int flags;
    quint64 ptr;
    ds >> ptr;
    ds >> name;
    ds >> flags;
    if( port < ( size_t ) m_outputs.size( ) ) {
      portMap[ ptr ] = m_outputs[ port ];
      if( uoType( ) == UOType::BOX ) {
        m_outputs[ port ]->setName( name );
      }
      m_outputs[ port ]->setPortFlags( flags );
      m_outputs[ port ]->setPtr( ptr );
    }
    else {
      portMap[ ptr ] = addPort( name, true, flags, ptr );
    }
  }
  COMMENT( "Updating port positions.", 4 );
  updatePorts( );

  COMMENT( "Finished loading element.", 4 );
}

QVector< QNEPort* > UnitOperation::inputs( ) const {
  return( m_inputs );
}

void UnitOperation::setInputs( const QVector< QNEPort* > &inputs ) {
  m_inputs = inputs;
}


QRectF UnitOperation::boundingRect( ) const {
  return( pixmap->rect( ) );
}

void UnitOperation::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) {
  Q_UNUSED( widget )
  painter->setClipRect( option->exposedRect );
  if( isSelected( ) ) {
    painter->setBrush(  QColor(175, 0, 0, 80) );
    painter->setPen( QPen( QColor(175, 0, 0, 255), 0.5, Qt::SolidLine ) );
    painter->drawRoundedRect( boundingRect( ), 5, 5 );
  }
  painter->drawPixmap( QPoint( 0, 0 ), getPixmap( ) );
}

QNEPort* UnitOperation::addPort( const QString &name, bool isOutput, int flags, int ptr ) {
  COMMENT( "Adding new port.", 4 );
  if( isOutput && ( ( quint64 ) m_outputs.size( ) >= m_maxOutputSz ) ) {
    return( NULL );
  }
  else if( !isOutput && ( ( quint64 ) m_inputs.size( ) >= m_maxInputSz ) ) {
    return( NULL );
  }
  QNEPort *port = new QNEPort( this );
  port->setName( name );
  port->setIsOutput( isOutput );
  port->setGraphicElement( this );
  port->setPortFlags( flags );
  port->setPtr( ptr );
  if( isOutput ) {
    m_outputs.push_back( port );
  }
  else {
    m_inputs.push_back( port );
  }
  COMMENT( "Updating new port.", 4 );
  this->updatePorts( );
  port->show( );
  return( port );
}

void UnitOperation::addInputPort( const QString &name ) {
  addPort( name, false );
}

void UnitOperation::addOutputPort( const QString &name ) {
  addPort( name, true );
}

void UnitOperation::setPortName( QString name ) {
  setObjectName( name );
  setToolTip( name );
}

void UnitOperation::updatePorts( ) {
/*  qDebug() << "UpdatePorts"; */
  COMMENT( "Updating port positions that belong to the box.", 4 );
  int inputPos = m_topPosition;
  int outputPos = m_bottomPosition;
  if( m_outputsOnTop ) {
    inputPos = m_bottomPosition;
    outputPos = m_topPosition;
  }
  if( !m_outputs.isEmpty( ) ) {
    int step = qMax( 32 / m_outputs.size( ), 6 );
    int x = 32 - m_outputs.size( ) * step + step;
    foreach( QNEPort * port, m_outputs ) {
      port->setPos( x, outputPos );
      port->update( );
      x += step * 2;
    }
  }
  if( !m_inputs.isEmpty( ) ) {
    int step = qMax( 32 / m_inputs.size( ), 6 );
    int x = 32 - m_inputs.size( ) * step + step;
    foreach( QNEPort * port, m_inputs ) {
      port->setPos( x, inputPos );
      port->update( );
      x += step * 2;
    }
  }
}

/*
 * void UnitOperation::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * e) {
 *  if(e->button() == Qt::LeftButton) {
 *    addOutputPort();
 *  } else {
 *    addInputPort();
 *  }
 * }
 */

QVariant UnitOperation::itemChange( QGraphicsItem::GraphicsItemChange change, const QVariant &value ) {
  COMMENT( "Align to grid.", 4 );
  if( ( change == ItemPositionChange ) && scene( ) ) {
    QPointF newPos = value.toPointF( );
    Scene *customScene = dynamic_cast< Scene* >( scene( ) );
    if( customScene ) {
      int gridSize = customScene->gridSize( );
      qreal xV = qRound( newPos.x( ) / gridSize ) * gridSize;
      qreal yV = qRound( newPos.y( ) / gridSize ) * gridSize;
      return( QPointF( xV, yV ) );
    }
    else {
      return( newPos );
    }
  }
  COMMENT( "Moves wires.", 4 );
  if( ( change == ItemScenePositionHasChanged ) || ( change == ItemRotationHasChanged ) ||
      ( change == ItemTransformHasChanged ) ) {
    foreach( QNEPort * port, m_outputs ) {
      port->updateConnections( );
    }
    foreach( QNEPort * port, m_inputs ) {
      port->updateConnections( );
    }
  }
  update( );
  return( QGraphicsItem::itemChange( change, value ) );
}

QKeySequence UnitOperation::getTrigger( ) const {
  return( m_trigger );
}

void UnitOperation::setTrigger( const QKeySequence &trigger ) {
  m_trigger = trigger;
}

QString UnitOperation::genericProperties( ) {
  return( QString( ) );
}

void UnitOperation::setLabel( QString label ) {
  m_labelText = label;
  if( !hasTrigger( ) || getTrigger( ).toString( ).isEmpty( ) ) {
    this->label->setPlainText( label );
  }
  else {
    if( !label.isEmpty( ) ) {
      label += " ";
    }
    this->label->setPlainText( label + QString( "(%1)" ).arg( getTrigger( ).toString( ) ) );
  }
}

QString UnitOperation::getLabel( ) {
  return( m_labelText );
}

bool UnitOperation::isValid( ) {
  COMMENT( "Checking if the element has the required signals to comput its value.", 4 );
  bool valid = true;
  for( QNEPort *input  : m_inputs ) {
    /* Required inputs must have exactly one connection. */
    if( !input->isValid( ) ) {
      valid = false;
      break;
    }
  }
  if( valid == false ) {
    foreach( QNEPort * output, outputs( ) ) {
      foreach( QNEConnection * conn, output->connections( ) ) {
        conn->setStatus( QNEConnection::Invalid );
        QNEPort *port = conn->otherPort( output );
        if( port ) {
          port->setValue( -1 );
        }
      }
    }
  }
  return( valid );
}

bool UnitOperation::hasColors( ) const {
  return( m_hasColors );
}

bool UnitOperation::hasTrigger( ) const {
  return( m_hasTrigger );
}

void UnitOperation::setColor( QString ) {

}

QString UnitOperation::getColor( ) {
  return( QString( ) );
}

void UnitOperation::setHasColors( bool hasColors ) {
  m_hasColors = hasColors;
}

void UnitOperation::setHasTrigger( bool hasTrigger ) {
  m_hasTrigger = hasTrigger;
}

bool UnitOperation::hasFrequency( ) const {
  return( m_hasFrequency );
}

void UnitOperation::setHasFrequency( bool hasFrequency ) {
  m_hasFrequency = hasFrequency;
}

bool UnitOperation::hasLabel( ) const {
  return( m_hasLabel );
}

void UnitOperation::setHasLabel( bool hasLabel ) {
  m_hasLabel = hasLabel;
  label->setVisible( hasLabel );
}

bool UnitOperation::rotatable( ) const {
  return( m_rotatable );
}

void UnitOperation::setRotatable( bool rotatable ) {
  m_rotatable = rotatable;
}

int UnitOperation::minOutputSz( ) const {
  return( m_minOutputSz );
}

int UnitOperation::inputSize( ) {
  return( m_inputs.size( ) );
}

void UnitOperation::setInputSize( int size ) {
  if( ( size >= minInputSz( ) ) && ( size <= maxInputSz( ) ) ) {
    if( inputSize( ) < size ) {
      while( inputSize( ) < size ) {
        addInputPort( );
      }
    }
    else {
      while( inputSize( ) > size ) {
        delete m_inputs.back( );
        m_inputs.pop_back( );
      }
      updatePorts( );
    }
  }
}

int UnitOperation::outputSize( ) {
  return( m_outputs.size( ) );
}

void UnitOperation::setOutputSize( int size ) {
  if( ( size >= minOutputSz( ) ) && ( size <= maxOutputSz( ) ) ) {
    if( outputSize( ) < size ) {
      for( int port = outputSize( ); port < size; ++port ) {
        addOutputPort( );
      }
    }
    else {
      while( outputSize( ) > size ) {
        m_outputs.pop_back( );
      }
    }
  }
}

float UnitOperation::getFrequency( ) {
  return( 0.0 );
}

void UnitOperation::setFrequency( float ) {

}

void UnitOperation::setMinOutputSz( int minOutputSz ) {
  m_minOutputSz = minOutputSz;
}

int UnitOperation::minInputSz( ) const {
  return( m_minInputSz );
}

void UnitOperation::setMinInputSz( int minInputSz ) {
  m_minInputSz = minInputSz;
}


int UnitOperation::maxOutputSz( ) const {
  return( m_maxOutputSz );
}

void UnitOperation::setMaxOutputSz( int maxOutputSz ) {
  m_maxOutputSz = maxOutputSz;
}

int UnitOperation::maxInputSz( ) const {
  return( m_maxInputSz );
}

void UnitOperation::setMaxInputSz( int maxInputSz ) {
  m_maxInputSz = maxInputSz;
}

int UnitOperation::bottomPosition( ) const {
  return( m_bottomPosition );
}

void UnitOperation::setBottomPosition( int bottomPosition ) {
  m_bottomPosition = bottomPosition;
  updatePorts( );
}

int UnitOperation::topPosition( ) const {
  return( m_topPosition );
}

void UnitOperation::setTopPosition( int topPosition ) {
  m_topPosition = topPosition;
  updatePorts( );
}

bool UnitOperation::outputsOnTop( ) const {
  return( m_outputsOnTop );
}

void UnitOperation::setOutputsOnTop( bool outputsOnTop ) {
  m_outputsOnTop = outputsOnTop;
  updatePorts( );
}

bool UnitOperation::disabled( ) {
  return( m_disabled );
}
