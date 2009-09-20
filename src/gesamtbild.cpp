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
#include "gesamtbild.h"

// #include <QAbstractSlider>
#include <QtGui/QPushButton>
// #include <QtGui/QFrame>
#include <QtGui/QLabel>
#include <QtGui/QErrorMessage>
// #include <QtGui/QVBoxLayout>
// #include <QtGui/QProgressBar>
// #include <QtGui/QVBoxLayout>

// #include <math.h>

#include <QtCore/QtDebug>
// #include <QtCore/QFile>
#include <QtCore/QDir>

//  #include "udbutton.h"

#include <QtCore/QDateTime>
#include "konsole.h"
#include "tabpanel.h"

gesamtbild::gesamtbild()
{
tradingwindow = 0;
gameview = 0;
menupanel = 0;
schwierigkeitsauswahl = 0;
connect(TERMINAL, SIGNAL(destroyed(QObject*)), this, SLOT(deleteLater()));

	QDir dir = QDir().current();
// 	qWarning() << dir.absolutePath();
{
	QDateTime dt = QDateTime().currentDateTime();
	QFile("debug.log").rename("debug.log~");
	QFile dbf("debug.log");
	dbf.open(QIODevice::WriteOnly);
	QTextStream errorstream(&dbf);
	errorstream << dir.path();
	errorstream << "\nStarting Log on ";
	errorstream << dt.toString(QString("ddd. MMM dd. yyyy hh:mm:ss ")) << "\n";
	dbf.close();
}
	qWarning() << dir.path();
	if(dir.cd("maps/"))
	{
		if(dir.count() > 0)
		{

		srand(time(NULL));




		move(0,0);
		setWindowTitle("OpenHanse");
		setBackgroundRole(
// 	 	QPalette::Shadow
 		QPalette::Dark
 		);
		setWindowIcon(QIcon(":/img/icons/holzfass_icon.png"));


		spielbool=false;
		aktiv=false;
		mainmenu();

		return;
		}
	}


	QErrorMessage *Error = new QErrorMessage();
	Error->setModal(true);
	Error->showMessage(tr("Installation files corrupted. Please reinstall and/or contact any developer."));
	connect(Error,SIGNAL(accepted()),this, SLOT(close()));
	connect(Error,SIGNAL(rejected()),this, SLOT(close()));
}

gesamtbild::~gesamtbild()
{
#ifdef _DEBUG_DESTRUCTORS
qWarning() << "Destructing MainFrame(Gesamtbild)";
#endif
delete tradingwindow;
delete schwierigkeitsauswahl;
delete menupanel;
#ifdef _DEBUG_DESTRUCTORS
qWarning() << "End of Destructing MainFrame(Gesamtbild)";
#endif
}


void gesamtbild::mainmenu()
{
	QFrame *mmframe = new QFrame(this);			// Main Menu Frame
// 	QVBoxLayout layout(mmframe);
	mmframe->setGeometry(200,300,600,400);
	mmframe->setFrameShape(QFrame::Panel);
	mmframe->setFrameShadow(QFrame::Sunken);
	QPushButton *spielbt = new QPushButton(tr("Single-Player-Game"), mmframe);
// 	spielbt->move(450,340);
	spielbt->move(50,50);
	QPushButton *laden = new QPushButton(tr("Load"), mmframe);
	laden->move(50,160);
	QPushButton *ende = new QPushButton(tr("Quit"), mmframe);
	ende->move(50,220);
	QLabel *lbl = new QLabel(tr("Mainmenu"), mmframe);
	lbl->move(50,0);
// 	ende->move(450,380);
// 	spielbt->move();
	connect(spielbt, SIGNAL(clicked()), mmframe, SLOT(deleteLater()));
	connect(spielbt, SIGNAL(clicked()), this, SLOT(startNewGame()));
// 	connect(spielbt,SIGNAL(clicked()),this, SLOT(handel()));
	connect(ende, SIGNAL(clicked()), this, SLOT(close()));

	connect(laden, SIGNAL(clicked()), mmframe, SLOT(deleteLater()));
	connect(laden, SIGNAL(clicked()), this, SLOT(lademenu()));

// 	QPushButton *toggler = new QPushButton (tr("Toggle"),mmframe);	//Testsache
// 	connect(toggler,SIGNAL(clicked()),laden,SLOT(toggle()));

	schwierigkeitsauswahl = new QComboBox(mmframe);
	schwierigkeitsauswahl -> addItem(tr("Easy"));
	schwierigkeitsauswahl -> addItem(tr("Hard"));
	schwierigkeitsauswahl -> move(50,90);
	mmframe->show();
}

void gesamtbild::keyPressEvent(QKeyEvent *event)
{

switch(event->key())
{
	case Qt::Key_Q:
	{
		switch(event->modifiers())
		{
			case Qt::ControlModifier:
			{
			close();
			break;
			}
			default:
			break;
		
		}
		break;
	}
	default:
		break;

}
// if(event->key() !=
//  Qt::Key_Escape && spielbool)
//  {
// gameview->keyEventWeiterleitung(event);
//  }
			//Menue-Zeugs
	if(aktiv)
	{
		if(event->key() == Qt::Key_Escape )
		{
			spielmenu();
			return;
		}

		else if(event->key() == Qt::Key_Q && (event->modifiers() == Qt::ControlModifier || event->text() == "Q"))
		{
			close();
			return;
		}

		gameview->keyEventWeiterleitung(event);
	}
}

/*
void gesamtbild::lademenu()
{
qWarning() << "Lademenu";
	QWidget *lademenu = new QWidget(this);
	lademenu->resize(1024,768);

	QListWidget *liste = new QListWidget(lademenu);
	liste->setSelectionMode(QAbstractItemView::SingleSelection);

	QDir dir = QDir().current();
	if(!dir.cd("save"))
	{
		qWarning() << "kein gespeichertes Spiel!";
	}
	else
	{
	liste->addItems(dir.entryList());
	}

}*/

// void gesamtbild::mmenuslot()
// {
// gesamtbild();
// show();
// 
// qWarning() << "mmenuslot()";
// 
// }
