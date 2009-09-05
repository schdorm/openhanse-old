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

gesamtbild::gesamtbild()
{
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
	errorstream << dt.toString(QString("ddd MMM dd. yyyy hh:mm:ss ")) << "\n";
	dbf.close();
}
	qWarning() << dir.path();
	if(dir.cd("maps/"))
	{
		if(dir.count() > 0)
		{
// 		dir = QDir().home();
// 		QFile cfg();
/// 		if(!currentSettings.readConfigs(dir.absolutePath().append("/.OpenHanse/cfg.ohc")))
// 		{
// 		resize(800,600);
/// 		}
// 		if(!cfg.exists())
// 		{
// 			cfg.open(QIODevice::WriteOnly);
// 			QTextStream cfgstream(&cfg);
// 			cfgstream << "1\n";
// 			cfg.close();
// 			resize(1024,768);
// 		}
// 		else
// 		{
// 			cfg.open(QIODevice::ReadOnly);
// 			QTextStream cfgstream(&cfg);
// 			QString res;
// 			res = cfgstream.readLine();
// 			if(res == "1")
// 			{
// 				resize(1024,768);
// 			}
// 			if(res == "2")
// 			{
// 				resize(1280,1024);
// 			}
// 			cfg.close();
// 		}

// #ifndef _RELEASE_
		srand(time(NULL));



// #endif
// 		setFixedSize(1024,768);
// 		setFixedSize(1280,1024);

		move(0,0);
		setWindowTitle("OpenHanse");
		setBackgroundRole(
// 	 	QPalette::Shadow
 		QPalette::Dark
 		);
		setWindowIcon(QIcon(":/img/icons/holzfass_icon.png"));


		spielbool=false;
//	 	aktiv=true;
		aktiv=false;
		hauptmenu();

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
delete rahmen;
delete hf;
delete hwin;
delete okbutton;
delete schwierigkeitsauswahl;
delete menupanel;
delete konsolenwidget;
delete gamedata;
}


void gesamtbild::hauptmenu()
{
	rahmen = new QFrame(this);
// 	QVBoxLayout layout(rahmen);
	rahmen->setGeometry(200,300,600,400);
	rahmen->setFrameShape(QFrame::Panel);
	rahmen->setFrameShadow(QFrame::Sunken);
	QPushButton *spielbt = new QPushButton(tr("Einzelspiel"), rahmen);
// 	spielbt->move(450,340);
	spielbt->move(50,50);
	QPushButton *laden = new QPushButton(tr("Laden"), rahmen);
	laden->move(50,160);
	QPushButton *ende = new QPushButton(tr("Beenden"), rahmen);
	ende->move(50,220);
	QLabel *lbl = new QLabel(tr("Hauptmenue"),rahmen);
	lbl->move(50,0);
// 	ende->move(450,380);
// 	spielbt->move();
	connect(spielbt,SIGNAL(clicked()),rahmen, SLOT(deleteLater()));
	connect(spielbt,SIGNAL(clicked()),this, SLOT(startNewGame()));
// 	connect(spielbt,SIGNAL(clicked()),this, SLOT(handel()));
	connect(ende,SIGNAL(clicked()),this,SLOT(close()));

	connect(laden,SIGNAL(clicked()),rahmen, SLOT(deleteLater()));
	connect(laden,SIGNAL(clicked()),this,SLOT(lademenu()));

// 	QPushButton *toggler = new QPushButton (tr("Toggle"),rahmen);	//Testsache
// 	connect(toggler,SIGNAL(clicked()),laden,SLOT(toggle()));

	schwierigkeitsauswahl = new QComboBox(rahmen);
	schwierigkeitsauswahl -> addItem(tr("Einfach"));
	schwierigkeitsauswahl -> addItem(tr("Schwierig"));
	schwierigkeitsauswahl -> move(50,90);
	rahmen->show();
}

void gesamtbild::keyPressEvent(QKeyEvent *event)
{
// if(event->key() !=
//  Qt::Key_Escape && spielbool)
//  {
// hf->keyEventWeiterleitung(event);
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

		hf->keyEventWeiterleitung(event);
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
