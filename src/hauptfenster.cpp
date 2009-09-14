/***************************************************************************
 *   Copyright (C) 2009 by Christian Doerffel                              *
 *   schdorm@googlemail.com                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/



// #define _RELEASE_
// #define _NO_CONTROL_LABEL_

#include "hauptfenster.h"

#include "shipdata.h"

#include <math.h>

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsItem>

#include <QtGui/QImage>
#include <QtGui/QBrush>

#include <QtCore/QTimer>

#include <QtGui/QKeyEvent>

#ifndef _RELEASE_
#include <QtGui/QVBoxLayout>
#include <QtCore/QtDebug>
#endif

#include <QtGui/QScrollBar>
#include <QtGui/QPushButton>
// #include <QtGui/QPlainTextEdit>
// #include <QtGui/QLineEdit>
// #include <QtCore/QFile>

#include "konsole.h"
#include "dataclass.h"

hauptfenster::hauptfenster(/*DataClass *param_GAMEDATA, Settings *paramsettings*/)
{
// 	GAMEDATA = param_GAMEDATA;
// 	currentSettings = paramsettings;

// 	qWarning() << "Schiffstyp" << GAMEDATA->activeShip()->type;

// 	GAMEDATA->anbord = true;
	pause = false;
	
// 	GAMEDATA->gametime.init();
// 	GAMEDATA->wind().init();

// 	szene = new QGraphicsScene();

// 	kartegeladen=true;
// 	setScene(szene);
// 	setSceneRect(20,20,mapprops.breite-40, mapprops.hoehe-40);


	setFocus();
// 	centerOn(testschiff->x(),testschiff->y());
// 	centerOn(testschiff);
// 	GAMEDATA->activeShip()->schiffbreite = testschiff->boundingRect().width();
// 	GAMEDATA->activeShip()->schifflange = testschiff->boundingRect().height();
//   	GAMEDATA->activeShip()->setName(tr("Seeadler"));

#ifndef _NO_CONTROL_LABEL_

	QWidget *status = new QWidget();

	knoten = new QLabel();
// 	sollknoten = new QLabel();
	segel = new QLabel();
	sollsegel = new QLabel();
	solldir = new QLabel();
	dir = new QLabel();
	steuerdir = new QLabel();
	sollsteuerdir = new QLabel();
	winddir = new QLabel();
 	windv = new QLabel();
	segeldir = new QLabel();
	acclabel = new QLabel();

	fokussieren = new QCheckBox();

	fokussieren->setChecked(true);

	QLabel *fok = new QLabel("Auf Schiff fokussieren");

	knoten -> setText (QString("V:%1").arg(GAMEDATA->activeShip()->v()));
// 	sollknoten -> setText(QString("SollV: %1").arg(GAMEDATA->activeShip()->attribute.sollgeschwindigkeit));

	segel->setText(QString("SegelFlaeche: %1").arg(GAMEDATA->activeShip()->settedSails()));
	sollsegel->setText(QString("SollSegelFl: %1").arg(GAMEDATA->activeShip()->toSettedSails()));
	segeldir -> setText(QString("SegelDir: %1").arg(GAMEDATA->activeShip()->sailDir()));

	solldir -> setText(QString("SollDir %1").arg(GAMEDATA->activeShip()->toDir()));
	dir -> setText(QString("Dir %1").arg(GAMEDATA->activeShip()->dir()));
	steuerdir -> setText(QString("SteuerDir: %1").arg(GAMEDATA->activeShip()->rudderDir()));
	sollsteuerdir -> setText(QString("SollSteuerDir: %1").arg(GAMEDATA->activeShip()->toRudderDir()));

//  	winddir -> setText(QString("WindDir: %1").arg(windrichtung));
// 	windv -> setText(QString("WindV: %1").arg(windgeschwindigkeit));
	acclabel->setText(QString("Beschleunigung:"));



	steuerdir->setFixedWidth(200);
	sollsteuerdir->setFixedWidth(200);
	QVBoxLayout layout;
	layout.addWidget(knoten);
// 	layout.addWidget(sollknoten);

	layout.addWidget(sollsegel);
	layout.addWidget(segel);
	layout.addWidget(segeldir);

	layout.addWidget(solldir);
	layout.addWidget(dir);
	layout.addWidget(steuerdir);
	layout.addWidget(sollsteuerdir);

	layout.addWidget(winddir);
	layout.addWidget(windv);
	layout.addWidget(acclabel);


	layout.addWidget(fokussieren);
	layout.addWidget(fok);

	status->setLayout(&layout);
	status->setParent(this,Qt::Tool);
	status->move(1100,400);
	status->show();
	connect(this, SIGNAL(destroyed(QObject)), status, SIGNAL(deleteLater()));
#endif
connect(&refreshGraphicsTimer, SIGNAL(timeout()), this, SLOT(aktualisieren()));

}


hauptfenster::~hauptfenster()
{
QList<QGraphicsItem*> dellist = scene()->items();
foreach(graphicsitem_it, dellist)
{
delete graphicsitem_it;
}
scene()->clear();
delete scene();
}


void hauptfenster::starttimer(int param_delay)
{
konsolenwidget->debug(QString("void hauptfenster::starttimer()"));
graphics_refresh_delay = param_delay;
refreshGraphicsTimer.start(param_delay);
}

void hauptfenster::mousePressEvent(QMouseEvent *event) /// MAUS-Steuerungssachen
{
konsolenwidget->debug(QString("void hauptfenster::mousePressEvent(QMouseEvent *event) "));

const float scale = transform().m11();
QPointF clickpoint = QPointF((event->x() + horizontalScrollBar()->value())/scale,
(event->y() + verticalScrollBar()->value())/scale);
if(!pause)
{
/*	if(GAMEDATA->landingState().status == Landing::WaitingForDestination)
	{
	QGraphicsItem *it;
	QList <QGraphicsItem *> qgilistAP = scene()->items(clickpoint);
	foreach(it, qgilistAP)
	{
		if(it->data(0).toInt() >= 100 && it->data(0).toInt() < 500 )
		{
		GAMEDATA->landingProcess()->landing_line = QLineF(QPointF(GAMEDATA->landingState().landingShip_gi->x() + GAMEDATA->landingState().landingShip_gi->boundingRect().width()/2, GAMEDATA->landingState().landingShip_gi->y() + GAMEDATA->landingState().landingShip_gi->boundingRect().height()/2), clickpoint);
		GAMEDATA->landingProcess()->status = Landing::ActiveLanding;
		GAMEDATA->landingProcess()->vx = GAMEDATA->landingState().landing_line.dx() / GAMEDATA->landingState().landing_line.length();
		GAMEDATA->landingProcess()->vy = GAMEDATA->landingState().landing_line.dy() / GAMEDATA->landingState().landing_line.length();
		GAMEDATA->landingstruct()->l_orientation = (GAMEDATA->landingstruct()->landing_line.angle() - 90) ;
		if (GAMEDATA->landingstruct()->l_orientation < 0)
		{
		GAMEDATA->landingstruct()->l_orientation += 360;
		}
		GAMEDATA->landingstruct()->l_orientation = GAMEDATA->landingstruct()->l_orientation *  M_PI / 180;
		konsolenwidget->debug(QString("landing_line_orientation: %1 ").arg(GAMEDATA->landingstruct()->l_orientation));
		konsolenwidget->debug(QString("landing_line_angle: %1 ").arg(GAMEDATA->landingstruct()->landing_line.angle()));
		konsolenwidget->debug(QString("landing orientation: %1 ").arg(GAMEDATA->landingstruct()->orientation));
		qWarning() << GAMEDATA->landingstruct()->vx << GAMEDATA->landingstruct()->landing_line.dx() << GAMEDATA->landingstruct()->vy << GAMEDATA->landingstruct()->landing_line.dy() << GAMEDATA->landingstruct()->landing_line.length();
		GAMEDATA->landingstruct()->correctOrientation = false;
		return;
		}
		else if(it->data(0).toString() == QString("ship")){
				// Iterator, that find
// 		foreach(GAMEDATA->activeShip(), GAMEDATA->currentMap()->ships)
		
		}
	}
	
	
	}*/
	if(!GAMEDATA->anbord() && GAMEDATA->landingState().status() == Landing::AtLand)
	{
//	if(QLine(clickpoint, active_person->ortblah).lenght < 100)
		QGraphicsItem *ort = scene()->itemAt(clickpoint);
		if(ort==0)
		{
#ifndef _RELEASE_
			qWarning() << "(Leerer Platz)";
#endif
		}

		else
		{
// 			if(ort->toolTip() == "Name")
// 			{
// #ifndef _RELEASE_
// 			qWarning() << "Item Name getroffen";
// #endif
// 			}
// 			if(ort == GAMEDATA->landingstruct()->landingShip_gi)
// 			{
// 			GAMEDATA->landingstruct()->landingstate = LandingProcess::WaitingForDestination;
// 			}
			switch (ort->data(0).toInt())
			{
				case ObjectType::Market:
				{
#ifndef _RELEASE_
					qWarning() << "Man begibt sich auf den Markt ...";
#endif
					emit handel();
					break;
				}
				case ObjectType::Townhall:
				{
					break;
				}
				
				case ObjectType::Church:
				{
					break;
				}
				case ObjectType::Port:
				{
					break;
				}
				case ObjectType::Kontor:
				{
					break;
				}
				case ObjectType::Bank:
				{
					break;
				}
				case ObjectType::Tavern:
				{
					emit enterBuilding(ObjectType::Tavern);
					break;
				}
			}
/*			if(ort->toolTip() == "Uhr" || ort->toolTip() == "grosser Zeiger" || ort->toolTip() == "kleiner Zeiger")
			{
#ifndef _RELEASE_
			qWarning() << "Zeit" << tag << stunde << minute;
#endif
			emit zeitsig();
			slotpause();
// 
// 			QWidget zeitw(this);
// 			QLabel anzeige(tr("Zeit: %1:%2").arg(stunde, minute),&zeitw);
// 			QPushButton ok("Ok",&zeitw);
// 			ok. move(50,50);
// 			zeitw.setGeometry(50,50,200,100);
// 			zeitw.show();
// 			zeitw.raise();
// 			connect(&ok, SIGNAL(clicked()),this,SLOT(slotpause()));
// 			connect(&ok, SIGNAL(clicked()),&zeitw,SLOT(close()));
			}*/

// #ifndef _RELEASE_
// 			 qWarning() << testschiff->pos() << event->posF() << (testschiff->x() - event->x()) << " \t" << testschiff->y() - event->y() << "\nVBar-Value:" <<verticalScrollBar()->value();
// #endif
		}
	}
	else if(GAMEDATA->anbord())
	{
// 	GAMEDATA->activeShip()->mouse_control = true;
	int x = (event->x() + horizontalScrollBar()->value())/scale;
	int y = (event->y() + verticalScrollBar()->value())/scale;

	PositioningStruct ship_pos = GAMEDATA->activeShip()->currentPosition();
	
	int mposx = ship_pos.m_position.x();
	int mposy = ship_pos.m_position.y();

#ifndef _RELEASE_
	qWarning() << "Maussteuerung" << x << y << mposx << mposy;
	QGraphicsLineItem *blah = new QGraphicsLineItem(QLineF(mposx, mposy, x, y));
	scene()->addItem(blah);
#endif

	if(x > mposx &&  y < mposy)			// Klick im "I. Quadrant" (Schiff -> KO [O(0|0)] )
							//(Koordinatensystem: gespiegelte Y-Achse ...)
	{
		int diffx = (x - mposx);
// 		int diffy = int(testschiff->y() - (event->y() + verticalScrollBar()->value()));
		int diffy = (mposy - y);
		float klickabstand = sqrt( diffx*diffx + diffy*diffy);
		float winkel = asin(diffy/klickabstand);

		GAMEDATA->activeShip()->set_ToDir(3*M_PI/2 + winkel);

#ifndef _RELEASE_
		qWarning() << "I" << winkel << "Ausrichtung" << GAMEDATA->activeShip()->toDir() <<"Abstand:" <<klickabstand;
#endif
	}

	else if(x < mposx && y < mposy)			// Klick im II. Quadrant
	{
		int diffx = (mposx - x);
		int diffy = (mposy - y);
		float klickabstand = sqrt( diffx*diffx + diffy*diffy);
		float winkel = asin(diffx/klickabstand);
// #ifndef _RELEASE_
// 		qWarning() << "II" << winkel << klickabstand;
// #endif
		GAMEDATA->activeShip()->set_ToDir(winkel);

#ifndef _RELEASE_
		qWarning() << "II" << winkel << "Ausrichtung" << GAMEDATA->activeShip()->toDir() <<"Abstand:" <<klickabstand;
#endif
	}

	else if(x < mposx && y > mposy)			// Klick im III. Quadrant
	{
		int diffx = (mposx - x);
		int diffy = (y - mposy);
		float klickabstand = sqrt( diffx*diffx + diffy*diffy);
		float winkel = asin(diffy/klickabstand);
// #ifndef _RELEASE_
// 		qWarning() << "III" << winkel << klickabstand;
// #endif
		GAMEDATA->activeShip()->set_ToDir(M_PI/2 + winkel);

#ifndef _RELEASE_
		qWarning() << "III" << winkel << "Ausrichtung" << GAMEDATA->activeShip()->toDir() <<"Abstand:" <<klickabstand;
#endif
	}

	else if(x > mposx && y > mposy)			// Klick im IV. Quadrant
	{
		int diffx = (x - mposx);
		int diffy = (y - mposy);
		float klickabstand = sqrt( diffx*diffx + diffy*diffy);
		float winkel = asin(diffx/klickabstand);
// #ifndef _RELEASE_
// 		qWarning() << "IV" << winkel << klickabstand;
// #endif
		GAMEDATA->activeShip()->set_ToDir(M_PI + winkel);
#ifndef _RELEASE_
		qWarning() << "IV" << winkel << "Ausrichtung" << GAMEDATA->activeShip()->toDir() <<"Abstand:" <<klickabstand;
#endif
	}
// 	tastatur=false;
	GAMEDATA->activeShip()->setMouseControl(true);
	}
}
}

void hauptfenster::keyEventWeiterleitung(QKeyEvent *event)
{
keyPressEvent(event);
}


void hauptfenster::keyPressEvent(QKeyEvent *event)
{
konsolenwidget->debug(QString("void hauptfenster::keyPressEvent(QKeyEvent *event) ").append(event->text()));
switch (event->key())
{
	case Qt::Key_W:
	{
		if(GAMEDATA->anbord())
		{
// 		if(GAMEDATA->activeShip()->attribute.sollprozentgesetzteSegel < 1)
// 		{
// 			GAMEDATA->activeShip()->attribute.sollprozentgesetzteSegel = GAMEDATA->activeShip()->attribute.sollprozentgesetzteSegel + 0.2;
			GAMEDATA->activeShip()->set_ToSettedSails(GAMEDATA->activeShip()->toSettedSails() + 0.2);
// 			GAMEDATA->activeShip()->mouse_control = false;
#ifndef _RELEASE_
			qWarning() << "Segel gesetzt:" << GAMEDATA->activeShip()->toSettedSails();
#endif

// 		}
		}
		break;
	}
	case Qt::Key_S: 
	{
		switch (event->modifiers())
		{
			case Qt::NoModifier:
			{
				if(GAMEDATA->anbord())
				{
					GAMEDATA->activeShip()->set_ToSettedSails(GAMEDATA->activeShip()->toSettedSails() - 0.2);
// 					GAMEDATA->activeShip()->mouse_control = false;
				}
				else
				{
				}
				break;
			}
			case Qt::ControlModifier:
			{
				emit savesig();
				break;
			}
			case Qt::ShiftModifier:
			{
				
				
				break;
			}
		
		}
		break;
	}
	
	case Qt::Key_A:
	{
		switch (event->modifiers())
		{
			case Qt::NoModifier:
			{
				if(GAMEDATA->anbord())
				{
					GAMEDATA->activeShip()->set_ToRudderDir(GAMEDATA->activeShip()->toRudderDir() + 0.0002);
// 					tastatur = true;
// 					GAMEDATA->activeShip()->mouse_control = false;
					
				}
				else
				{
					
				}
				break;
			}
			case Qt::ShiftModifier:
			{
				if(GAMEDATA->anbord())
				{
				GAMEDATA->activeShip()->set_SailDir(GAMEDATA->activeShip()->sailDir() + 0.02);

				}
				else
				{
					
				}
				break;
			}
		}
		break;
	}
	
	case Qt::Key_D:
	{
		switch (event->modifiers())
		{
			case Qt::NoModifier:
			{
				if(GAMEDATA->anbord())
				{
					GAMEDATA->activeShip()->set_ToRudderDir(GAMEDATA->activeShip()->toRudderDir() - 0.0002);
// 					GAMEDATA->activeShip()->mouse_control = false;
				}
				else
				{
					
				}
				break;
			}
			case Qt::ShiftModifier:
			{
				if(GAMEDATA->anbord())
				{
					
				}
				else
				{
					
				}
				break;
			}
		}
		break;
	}
	
	case Qt::Key_P:
	{
#ifndef _RELEASE_
		qWarning() << "Pause" << pause;
#endif
		slotpause();
		break;
	}
// 		static int zoomlvl;
	case Qt::Key_Minus:		/*&& zoomlvl <2)*/
	{
		scale(0.8,0.8);
		zoomlvl++;
		break;
	}
	case Qt::Key_Plus:		/*&& zoomlvl >0)*/
	{
		scale(1.25,1.25);
		zoomlvl--;
		break;
	}
	
	case Qt::Key_AsciiCircum:
	{
		qWarning() << "Open Console!";

		konsolenwidget->show();
		break;
	}
	case Qt::Key_Escape:
	{
		emit menusig();
		qWarning() << "Menusig";
		break;
	}
	
	case Qt::Key_M:
	{
		switch (event->modifiers())
		{
			case Qt::NoModifier:
			{
				if(GAMEDATA->anbord())
				{
				}
				else
				{
					
				}
				break;
			}
			case Qt::ShiftModifier:
			{
				if(GAMEDATA->anbord())
				{
					
				}
				else
				{
					
				}
				break;
			}
			case Qt::ControlModifier:
			{
#ifndef _RELEASE_
				Warenstruct tempware = GAMEDATA->activeShip()->cargo();
				tempware.taler += 1000;
				GAMEDATA->activeShip()->setCargo(tempware);
#endif
				break;
			}
		}

		break;
	}
#ifndef _RELEASE_
	case Qt::Key_C:
	{
// 		centerOn(GAMEDATA->activeShip()->graphicsitem);
		break;
	}
	case Qt::Key_L:
	{
		GAMEDATA->wind().setV(GAMEDATA->wind().v() + 1);
		break;
	}
	case Qt::Key_K:
	{
		GAMEDATA->wind().setV(GAMEDATA->wind().v() - 1);
		break;
	}
	case Qt::Key_Left:
	{
// 		if(anbord)
// 		{
// 		GAMEDATA->activeShip()->attribute.ausrichtung += 0.2;
// 		if(GAMEDATA->activeShip()->attribute.ausrichtung > 2 * M_PI)
// 		{
// 			GAMEDATA->activeShip()->attribute.ausrichtung = 0.1;
// 		}
// 		}
		break;
	}
	case Qt::Key_Right:
	{
// 		if(anbord)
// 		{
// 		GAMEDATA->activeShip()->attribute.ausrichtung -= 0.2;
// 		if(GAMEDATA->activeShip()->attribute.ausrichtung < 0 )
// 		{
// 			GAMEDATA->activeShip()->attribute.ausrichtung = 2 * M_PI - 0.1;
// 		}
// 		}
		break;
	}
	case Qt::Key_Up:
	{
		if(GAMEDATA->anbord())
// 		GAMEDATA->activeShip()->attribute.geschwindigkeit ++;
		break;
	}

	case Qt::Key_Down:
	{
		if(GAMEDATA->anbord())
// 		GAMEDATA->activeShip()->attribute.geschwindigkeit--;
		break;
	}

#endif
}

if(event->text() =="Q" || (event->key() == Qt::Key_Q && event->modifiers() == Qt::ControlModifier))
{
	close();
	deleteLater();
}

}



void hauptfenster::slotpause()
{
konsolenwidget->debug(QString("void hauptfenster::slotpause()"));

		if(!pause)
		{
			refreshGraphicsTimer.stop();
			GAMEDATA->pause();
		}
		if(pause)
		{
			refreshGraphicsTimer.start(graphics_refresh_delay);
			GAMEDATA->startTimer();
		}

		if(refreshGraphicsTimer.isActive())
		{
			pause=false;
		}
		if(!refreshGraphicsTimer.isActive())
		{
			pause=true;
		}
}

void hauptfenster::endePause()
{
konsolenwidget->debug(QString("void hauptfenster::endePause()"));
		if(!refreshGraphicsTimer.isActive())
		{
			GAMEDATA->startTimer();
			refreshGraphicsTimer.start(graphics_refresh_delay);
			pause=false;
		}
}

void hauptfenster::startPause()
{
konsolenwidget->debug(QString("void hauptfenster::startPause()"));
		if(refreshGraphicsTimer.isActive())
		{
			GAMEDATA->pause();
			refreshGraphicsTimer.stop();
			pause=true;
		}
}


void hauptfenster::segelsetzen(int i)
{
konsolenwidget->debug(QString("void hauptfenster::segelsetzen(int i) ").append(i));
// float n = i;
// GAMEDATA->activeShip()->attribute.sollprozentgesetzteSegel = n/5;
GAMEDATA->activeShip()->set_ToSettedSails(i/5);
#ifndef _RELEASE_
qWarning() << "sollgesetzteSegel:" << GAMEDATA->activeShip()->toSettedSails();
#endif
}


// #define _DEBUG_REFRESH_

void hauptfenster::aktualisieren()
{
durchlauf++;
#ifdef _DEBUG_REFRESH_
qWarning() << "graphics Aktualisieren";
#endif

// static int durchlauf;	//Zaehlvariable fuer Ruder bzw. Geschwindigkeit -> Schiff ist traege und wird nur langsam schneller / lenkt langsam ----> jetzt Klassenvariable

// if(GAMEDATA->gametime.refreshTime())			//returns true, when a new day starts ...


/////////////WIND + WOLKEN/////////////////////////////

// qWarning() << "Vor Wolkenzeugs";

// qWarning()<< "KGL: WL: Eintraege" << wolkenliste.size();

if(GAMEDATA->wind().v() > 0)
{
	double windrichtung = GAMEDATA->wind().dir();
	int windgeschwindigkeit = GAMEDATA->wind().v();

#ifndef _NO_CONTROL_LABEL_
	winddir -> setText(QString("WindDir: %1").arg(windrichtung));
	windv -> setText(QString("WindV: %1").arg(windgeschwindigkeit));
#endif
	if(durchlauf%10 == 0)					//Bewegung mit Verschiebung
	{
		foreach(QGraphicsItem *wolkenit, wolkenliste)
		{
			int rx = (rand() % 3)-1;
			float xverschiebung = rx / 10;

			int ry = (rand() % 3)-1;
			float yverschiebung = ry / 10;

			wolkenit->moveBy(-(windgeschwindigkeit * sin(windrichtung))/10 + xverschiebung, -(windgeschwindigkeit * cos(windrichtung))/10 + yverschiebung);

			if(wolkenit->x() <10 )
			{
// wolke->setPos(3800 - (windgeschwindigkeit * sin(windrichtung))/10, wolke->y() - (windgeschwindigkeit * cos(windrichtung))/10);
				wolkenit->setPos(GAMEDATA->currentMap()->size().width() - 10, (rand()%(GAMEDATA->currentMap()->size().height() - 200)) + 50);
			}
			else if(wolkenit->x() > GAMEDATA->currentMap()->size().width() - 10 )
			{
// wolke->setPos(205 - (windgeschwindigkeit * sin(windrichtung))/10, wolke->y() - (windgeschwindigkeit * cos(windrichtung))/10);
				wolkenit->setPos(10, (rand()%(GAMEDATA->currentMap()->size().height() - 200)) + 50);
			}
			else if(wolkenit->y() <10 )
			{
				wolkenit->setPos((rand() % (GAMEDATA->currentMap()->size().width() - 200)) + 50, GAMEDATA->currentMap()->size().height() - 10);
// wolke->setPos( wolke->x() - (windgeschwindigkeit * sin(windrichtung))/10, 2800 - (windgeschwindigkeit * cos(windrichtung))/10);
			}
			else if(wolkenit->y() > GAMEDATA->currentMap()->size().height() - 10 )
			{
				wolkenit->setPos((rand() % (GAMEDATA->currentMap()->size().width() - 200)) + 50, 10);
// wolke->setPos( wolke->x() - (windgeschwindigkeit * sin(windrichtung))/10, 205 - (windgeschwindigkeit * cos(windrichtung))/10);
			}
		}
	}
	else						//Wolkenbewegung ohne Verschiebung
	{
		foreach(QGraphicsItem *wolkenit, wolkenliste)
		{
			wolkenit->moveBy(-(windgeschwindigkeit * sin(windrichtung))/10, -(windgeschwindigkeit * cos(windrichtung))/10);

			if(wolkenit->x() <10 )
			{
// wolke->setPos(3800 - (windgeschwindigkeit * sin(windrichtung))/10, wolke->y() - (windgeschwindigkeit * cos(windrichtung))/10);
				wolkenit->setPos(GAMEDATA->currentMap()->size().width() - 10, (rand()%(GAMEDATA->currentMap()->size().height() - 200)) + 50);
			}
			else if(wolkenit->x() > GAMEDATA->currentMap()->size().width() - 10 )
			{
// wolke->setPos(205 - (windgeschwindigkeit * sin(windrichtung))/10, wolke->y() - (windgeschwindigkeit * cos(windrichtung))/10);
				wolkenit->setPos(10, (rand()%(GAMEDATA->currentMap()->size().height() - 200)) + 50);
			}
			else if(wolkenit->y() <10 )
			{
				wolkenit->setPos((rand() % (GAMEDATA->currentMap()->size().width() - 200)) + 50, GAMEDATA->currentMap()->size().height() - 10);
// wolke->setPos( wolke->x() - (windgeschwindigkeit * sin(windrichtung))/10, 2800 - (windgeschwindigkeit * cos(windrichtung))/10);
			}
			else if(wolkenit->y() > GAMEDATA->currentMap()->size().height() - 10 )
			{
				wolkenit->setPos((rand() % (GAMEDATA->currentMap()->size().width() - 200)) + 50, 10);
// wolke->setPos( wolke->x() - (windgeschwindigkeit * sin(windrichtung))/10, 205 - (windgeschwindigkeit * cos(windrichtung))/10);
			}
		}
	}

}

//  qWarning() << "Ende Wolkenzeugs";

// #define _DEBUG_REFRESH_
///////SCHIFF////////////////////////////////////////
//falls v>0 / geplant: v>0
// qWarning() << "IfAnbord";
/*if(GAMEDATA->landingstruct()->landingstate == LandingProcess::ActiveLanding)
{
#ifdef _DEBUG_REFRESH_
qWarning() << "Landing";
#endif
activeLanding();
}*/


else if(GAMEDATA->anbord())
{

// qWarning() << "Beginn Schiffszeug";
// if(GAMEDATA->activeShip()->attribute.geschwindigkeit > 0 || GAMEDATA->activeShip()->attribute.sollprozentgesetzteSegel > 0 || GAMEDATA->activeShip()->attribute.prozentgesetzteSegel > 0 || windgeschwindigkeit > 0)
{
#ifdef _DEBUG_REFRESH_
  	qWarning() << "Calc Movement";
#endif

///	GAMEDATA->activeShip()->calcMovement(GAMEDATA->wind().retV(), GAMEDATA->wind().retDir());

#ifdef _DEBUG_REFRESH_
	qWarning() << "End: Calc Movement (disabled), move Graphics";
#endif
// 	GAMEDATA->activeShip()->moveGraphics();

//////////////////////Landkollossion
/////////////////Schiffbar?
// qWarning() << "Schiffbar?";

// if(0==1)
if(activeship_model->setShipPos())
 {
#ifdef _DEBUG_REFRESH_
	qWarning() << "End moveGraphics()";
#endif
	float bremsfaktor = 0;

// QList <QGraphicsItem*> collliste = testschiff->collidingItems();	//Kollisionsliste

// if(/*!collliste.isEmpty() &&*/ durchlauf % 5 ==0)
// {
// bool found = false;
// qWarning() << "Not Empty" << collliste.size() << landobjektliste.size();
	QGraphicsPixmapItem *landgi;
	int iz = 0;
	for(QList <QGraphicsPixmapItem*>::iterator it = landobjektliste.begin(); it < landobjektliste.end(); ++it)
	{
		iz ++;
		landgi = *it;
		if(schiffskollision(landgi))
		{
			static int ibrprufg[3];			//Ueberpruefungszahl: Neubelegung der Bilder erforderlich?
// int eolx = (testschiff->x() +  (cos(GAMEDATA->activeShip()->attribute.ausrichtung) * schifflange)/2 + (sin(GAMEDATA->activeShip()->attribute.ausrichtung) * schiffhohe)/2 - landgi->x()),
// eoly = testschiff->y() + (cos(GAMEDATA->activeShip()->attribute.ausrichtung) * schiffhohe)/2 + (sin(GAMEDATA->activeShip()->attribute.ausrichtung) * schifflange)/2 - landgi->y();
			int eolx = GAMEDATA->activeShip()->mPosX() - landgi->x(),
			eoly = GAMEDATA->activeShip()->mPosY() - landgi->y();

			int arrakt;				// Ueberpruefung: aktives Arrayfeld
			if(ibrprufg[0] != iz)
			{
				if(ibrprufg[1] != iz)
				{
					if(ibrprufg[2] != iz)
					{
						static int arrind;
// 						qWarning() << "Neubelegung" << iz << ibrprufg;
						collimg[arrind] = landgi->pixmap().toImage();
						ibrprufg[arrind] = iz;
						arrakt = arrind;
						arrind++;
						if(arrind > 2)
						{
							arrind = 0;
						}
					}
					else
						arrakt = 2;
				}
				else
					arrakt = 1;
			}
			else
				arrakt = 0;
			if(eolx > 0 && eolx < collimg[arrakt].width() && eoly >= 0 && eoly < collimg[arrakt].height())
			{
			float tempfloat = qAlpha(collimg[arrakt].pixel(eolx, eoly));
			if(tempfloat > bremsfaktor)
			{
				bremsfaktor = tempfloat;
				qWarning() << bremsfaktor;
			}
			}

		}
	}
	if(bremsfaktor > 3)
	{
	bremsfaktor = bremsfaktor/255;
	qWarning() << bremsfaktor;
// 	bremsfaktor = bremsfaktor /** bremsfaktor * bremsfaktor*/ / 10;
// 	bremsfaktor = sqrt(sqrt(sqrt(bremsfaktor)));
//  	qWarning() << bremsfaktor;
// 	GAMEDATA->activeShip()->attribute.geschwindigkeit = GAMEDATA->activeShip()->attribute.geschwindigkeit * (1 - bremsfaktor);
	GAMEDATA->activeShip()->brake(bremsfaktor);
	}
// }
	/////Kartenrand - Mapwechsel
	int ship_xpos = GAMEDATA->activeShip()->mPosX();
	int ship_ypos = GAMEDATA->activeShip()->mPosY();
	if(ship_xpos > GAMEDATA->currentMap()->size().width() - 120 )
		{
 		qWarning()<< "Mapwechsel zu Ost" << GAMEDATA->currentMap()->mapeast();
 		if(! GAMEDATA->currentMap()->mapeast().isEmpty())
 		{
// 			float ty = ypos;
// 			delete testschiff;
// 			karteladen(mapprops.mapeast);
// 			GAMEDATA->activeShip()->attribute.map = mapprops.mapname;
// //  			qWarning() << "Karte geladen (mapeast)";
// //  			activeship->graphicsitem->setPos(125, ypos);
// // 			qWarning() << "Pos gesetzt";
// 			centerOn(testschiff);
			return;
 		}
 		else	{
// 			  testschiff->setPos(mapprops.breite - 120,testschiff->y());
			}
		}
	else if(ship_xpos < 120 )
		{
		qWarning() << "Mapwechsel zu West" << GAMEDATA->currentMap()->mapwest();
		if(!GAMEDATA->currentMap()->mapwest().isEmpty())
		{
// 			float ty = testschiff->y();
//  			qWarning() << ty;
// 			delete testschiff;
// 			scene()-> clear();
// 			scene()-> deleteLater();
// 			karteladen(mapprops.mapwest);
// 			GAMEDATA->activeShip()->attribute.map = mapprops.mapname;
// // 			delete testschiff;
// //  			qWarning() << "Karte geladen (mapwest)";
// // 			testschiff = szene->addPixmap(QPixmap(GAMEDATA->activeShip()->attribute.filename));
// // 			testschiff = szene->add#
// // 			qWarning() << "Schiff geladen";
// 			testschiff->setPos(mapprops.breite-125,ty);
// // 			qWarning() << "Pos gesetzt";
// 			centerOn(testschiff);
// // 			setScene(szene);
// // 			qWarning() << "Szene gesetzt";
			return;
		}
		else{}
// 			testschiff->setPos(120,testschiff->y());
		}

	if(ship_ypos < 120)
		{
 		qWarning()<< "Mapwechsel zu Nord:" << GAMEDATA->currentMap()->mapnorth();
		if(! GAMEDATA->currentMap()->mapnorth().isEmpty())
		{
// 			float tx = testschiff->x();
// 			delete testschiff;

// 			karteladen(mapprops.mapnorth);
// 			GAMEDATA->activeShip()->attribute.map = mapprops.mapname;
// //  			qWarning() << "Karte geladen (mapnorth)";
// 			testschiff->setPos(tx,mapprops.hoehe-125);
// // 			qWarning() << "Pos gesetzt";
// 			centerOn(testschiff);
// 			return;
		}
		else{}
// 			testschiff->setPos(testschiff->x(), 120);
		}

	else if(ship_ypos > GAMEDATA->currentMap()->size().height() - 100)
		{
		qWarning()<< "Mapwechsel zu Sued" << GAMEDATA->currentMap()->mapsouth();
		if(!GAMEDATA->currentMap()->mapsouth().isEmpty())
		{
		/*
			float tx = testschiff->x();
			delete testschiff;
			karteladen(mapprops.mapsouth);
			GAMEDATA->activeShip()->attribute.map = mapprops.mapname;
// 			qWarning() << "Karte geladen (mapsouth)";
			testschiff->setPos(tx, 125);
// 			qWarning() << "Pos gesetzt";
			centerOn(testschiff);
			return;*/
		}
		else{}
// 			testschiff->setPos(testschiff->x(), mapprops.hoehe - 100);
		}
// }
}
if(durchlauf%50==0
#ifndef _NO_CONTROL_LABEL_
 && fokussieren->isChecked()
#endif
)
{
// centerOn(testschiff->x(),testschiff->y());
}
}
// }

#ifndef _NO_CONTROL_LABEL_

if(durchlauf%10==0)
{
	knoten -> setText (QString("V:%1").arg(GAMEDATA->activeShip()->v()));
// 	sollknoten -> setText(QString("SollV: %1").arg(GAMEDATA->activeShip()->attribute.sollgeschwindigkeit));
	solldir -> setText(QString("SollDir %1").arg(GAMEDATA->activeShip()->toDir()));
	dir -> setText(QString("Dir %1").arg(GAMEDATA->activeShip()->dir()));
	steuerdir -> setText(QString("SteuerDir: %1").arg(GAMEDATA->activeShip()->rudderDir()));
	sollsteuerdir -> setText(QString("SollSteuerDir: %1").arg(GAMEDATA->activeShip()->toRudderDir()));
// 	segeldir -> setText(QString("SegelDir: %1").arg(GAMEDATA->activeShip()->attribute.segelausrichtung));
	segel->setText(QString("SegelFlaeche: %1").arg(GAMEDATA->activeShip()->settedSails()));
	sollsegel->setText(QString("SollSegelFl: %1").arg(GAMEDATA->activeShip()->toSettedSails()));
	segeldir -> setText(QString("SegelDir: %1").arg(GAMEDATA->activeShip()->sailDir()));
}
#endif

}}
///				ENDE Aktualisierung




bool hauptfenster::schiffskollision(QGraphicsItem *land)
{
// int x = testschiff->x();
	if(GAMEDATA->activeShip()->mPosX() > land->x() && GAMEDATA->activeShip()->mPosY() > land->y() && GAMEDATA->activeShip()->mPosX() < land->x() + land->boundingRect().width() && GAMEDATA->activeShip()->mPosY() < land->y() + land->boundingRect().height() )
	{
		qWarning() << "Kollision";
	      return true;
	}
	else return false;
}

bool hauptfenster::kollision(QGraphicsItem *param_item, QGraphicsItem *param_ground)
{
	int param_item_posx = param_item->x() + param_item->boundingRect().width();
	int param_item_posy = param_item->y() + param_item->boundingRect().height();
	if(param_item_posx  > param_ground->x() && param_item_posy > param_ground->y() && param_item_posx < param_ground->x() + param_ground->boundingRect().width() && param_item_posy < param_ground->y() + param_ground->boundingRect().height() )
	{
		qWarning() << "Kollision";
	      return true;
	}
	else return false;

}

bool hauptfenster::isLand(QGraphicsItem *checkqgi) const
{
	if(checkqgi->data(0).toInt() >= 100 && checkqgi->data(0).toInt() < 1000)
	{
		qWarning() << "isLand = true";
	      return true;
	}
	else return false;
}

void hauptfenster::rotateItem(QGraphicsItem *item, double angle)
{
	const int w = item->boundingRect().width()/2;
	const int h = item->boundingRect().height()/2;

	item->resetTransform();
	QTransform t;

	t.translate( w, h );
	t.rotateRadians(- angle);
	t.translate( -w, -h );
	item->setTransform( t );
}



void hauptfenster::schuss()
{
konsolenwidget->debug(QString("void hauptfenster::schuss()"));

}
