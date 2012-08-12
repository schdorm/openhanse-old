/***************************************************************************
 *   Copyright (C) 2009 by Christian Doerffel                              *
 *   oh.devs@googlemail.com                                                *
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

#include "widgets/mainwindow.h"


#ifdef enable_sound
#include <Phonon/AudioOutput>
#include <Phonon/MediaObject>
#endif

#include <QKeyEvent>

#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QErrorMessage>

#include <QApplication>
#include <QtCore/QtDebug>
#include <QtCore/QDir>

#include "serverprocess.h"

#include "widgets/mainmenu.h"
#include "widgets/terminal.h"

#include "widgets/servermenu.h"

#include "widgets/mainview.h"
#include "widgets/playerlist.h"
// #include "widgets/shipcontrolbar.h"
// #include "widgets/tradingwindow.h"

#include "datamanager.h"
#include "clientgamedata.h"

#include "debugqueue.h"
#include "settings.h"

#include "widgets/gamesettingsmenu.h"
#include "widgets/ingamemenu.h"
#include "widgets/optionwindow.h"



MainWindow::MainWindow(QWidget *parent) : QWidget(parent), m_Terminal (new Terminal(this)), m_Playerlist(new Playerlist(this)), m_GameView (0), m_TradingWindow (0), m_ShipControlBar (0), m_MainMenu(0), m_GameSettingsMenu (0), m_activeWidget(0), m_layout(new QGridLayout(this))
{
  connect(m_Terminal, SIGNAL(sig_command(QString)), this, SLOT(execCommand(QString)));
  
  
  #ifdef enable_sound
  m_musicMedia = new Phonon::MediaObject(this);
  m_musicOutput = new Phonon::AudioOutput(Phonon::GameCategory, this);
  Phonon::createPath(m_musicMedia, m_musicOutput);
  
  m_miscMedia = new Phonon::MediaObject(this);
  m_miscOutput = new Phonon::AudioOutput(Phonon::GameCategory, this);
  Phonon::createPath(m_miscMedia, m_miscOutput);
  #endif 
  
  m_Playerlist->hide();
  
//   QDir dir = QDir().current();
  // 	qWarning() << dir.absolutePath();
  
//   qWarning() << dir.path();
//   if(dir.cd("maps/"))
//   {
//     if(dir.count() > 0)
//     {
      
      move(0,0);
      setWindowTitle("OpenHanse");
      setBackgroundRole(
      // 	 	QPalette::Shadow
      QPalette::Dark
      );
      setWindowIcon(QIcon(":/img/holzfass_icon.png"));
      
      
      spielbool=false;
      aktiv=false;
      showMainMenu();
      
      return;
//     }
//   }
  
  
  QErrorMessage *Error = new QErrorMessage();
  Error->setModal(true);
  Error->showMessage(tr("No maps available."));
  connect(Error,SIGNAL(finished(int)),this, SLOT(close()));
}

MainWindow::~MainWindow()
{
  DAMAPOR->serverProcess()->close();
//   sleep(1);
//    m_serverprocess->deleteLater();
  #ifdef _DEBUG_DESTRUCTORS
  qWarning() << "Destructing MainFrame(Gesamtbild)";
  #endif
//   delete m_tradingwindow;
//   delete menupanel;
  #ifdef _DEBUG_DESTRUCTORS
  qWarning() << "End of Destructing MainFrame(Gesamtbild)";
  #endif
  emit destroyed();
}


void MainWindow::showMainMenu()
{
  #ifdef enable_sound
  m_musicMedia->enqueue(Phonon::MediaSource(":/audio/music/theme.mp3"));
  m_musicMedia->setTransitionTime (1000);
  m_musicMedia->play();
  connect(m_musicMedia, SIGNAL(aboutToFinish()), this, SLOT(addMainMenuMusic()));
  #endif
  if(m_GameView != 0)
    m_GameView->deleteLater();
  
  m_MainMenu = new MainMenu(this);
  m_layout->addWidget(m_MainMenu,1,1);
//   m_MainMenu->move(width()/2 - width()/5, height()/2 - height()/5);
//   m_MainMenu->show();
  
  
//   connect(m_MainMenu, SIGNAL(buttonClicked()), m_MainMenu, SLOT(close()));
//   connect(m_MainMenu, SIGNAL(buttonClicked()), m_MainMenu, SLOT(deleteLater()));
  
  connect(m_MainMenu, SIGNAL(spGame()), this, SLOT(singleplayerGame()));
  connect(m_MainMenu, SIGNAL(mpGame()), this, SLOT(serverMenu()));
  
  connect(m_MainMenu, SIGNAL(Options()), this, SLOT(options()));
//   connect(m_MainMenu, SIGNAL(Quit()), this, SIGNAL(appQuit())); //solved: qApp->quit() connected with MainMenu-Button

}


void MainWindow::addMainMenuMusic()
{
  
   m_musicMedia->enqueue(Phonon::MediaSource(":/audio/music/theme.mp3"));
//    m_musicMedia->enqueue(Phonon::MediaSource("dong.ogg"));
}

void MainWindow::gameSettingsMenu()
{
  m_GameSettingsMenu = new GameSettingsMenu(this);
  m_layout->addWidget(m_GameSettingsMenu,0,0);
//   m_GameSettingsMenu->show();
  m_activeWidget = m_GameSettingsMenu;
  
  connect(m_GameSettingsMenu, SIGNAL(abort()), m_GameSettingsMenu, SLOT(deleteLater()));
  connect(m_GameSettingsMenu, SIGNAL(abort()), this, SLOT(showMainMenu()));
// 
  if(GAMEDATA->localGame())
  {
    connect(m_GameSettingsMenu, SIGNAL(ready()), this, SLOT(startSingleplayerGame()));
    connect(m_GameSettingsMenu, SIGNAL(start()), m_GameSettingsMenu, SLOT(deleteLater()));
  }
//   if(!m_localGame)
//   {
//     
//   }
}

void MainWindow::singleplayerGame()
{
  GAMEDATA->setLocalGame(true);
  gameSettingsMenu();
  qWarning() << "void MainWindow::singleplayerGame()";
  connect(DAMAPOR->serverProcess(), SIGNAL(serverReady()), GAMEDATA, SLOT(connectToServer()));
//   connect(GAMEDATA, SIGNAL(connected()), GAMEDATA, SLOT(playerReady()));
  DAMAPOR->serverProcess()->startServer();
//   qWarning() << "Server started!";
//   createGameView();
}

void MainWindow::multiplayerGame()
{
  GAMEDATA->setLocalGame(false);
  serverMenu();
}


void MainWindow::serverMenu()
{
  ServerMenu *f_ServerMenu = new ServerMenu(this);
  m_layout->addWidget(f_ServerMenu,0,0);
  f_ServerMenu->show();
  
  connect(f_ServerMenu, SIGNAL(mainMenu()), this, SLOT(showMainMenu()));
  connect(f_ServerMenu, SIGNAL(mpConnected()), this, SLOT(gameSettingsMenu()));
}


void MainWindow::options()
{
  OptionWindow *OptionWin = new OptionWindow(this);
  m_layout->addWidget(OptionWin,0,0);
//   OptionWin -> setGeometry (width() * 0.05, height() * 0.05, width() * 0.9, height() * 0.9);
//   OptionWin -> show();
  connect(OptionWin, SIGNAL(aborted()), OptionWin, SLOT(deleteLater()));
  connect(OptionWin, SIGNAL(aborted()), this, SLOT(showMainMenu()));
  
  connect(OptionWin, SIGNAL(modAssumed()), this, SLOT(applySettings()));
  connect(OptionWin, SIGNAL(modAssumed()), OptionWin, SLOT(deleteLater()));
  connect(OptionWin, SIGNAL(modAssumed()), this, SLOT(showMainMenu()));
}

void MainWindow::applySettings()
{
  if(SETTINGS->fullscreen())
  {
    setWindowState(windowState() | Qt::WindowFullScreen);
    // set to Fullscreen State
  }
  else if ((windowState() | Qt::WindowFullScreen) == windowState() )		// if Fullscreen state = current state
  {
    setWindowState(windowState() ^ Qt::WindowFullScreen);			//toggle to normal win state
//     qWarning() << "Resizing ...";
  }
  else
    resize(SETTINGS->resolution());
  
  m_Terminal->setGeometry(0,0, width(), height()/2);
  
  m_Terminal->setWindowFlags(Qt::Popup);
  m_Terminal->hide();
  
  
  #ifdef enable_sound
    qWarning() << "Set Volumes:\nMusic Volume: " << SETTINGS->musicVolume() << "\tMisc Volume: " << SETTINGS->miscVolume();
//     qreal uvol = ;
//     qreal ivol = SETTINGS->miscVolume();
    m_musicOutput->setVolume(((qreal) SETTINGS->musicVolume())/100);
    m_miscOutput->setVolume(((qreal)SETTINGS->miscVolume())/100);
  #endif
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
  qWarning() << "void MainWindow::keyPressEvent(QKeyEvent *event)" << event->key() << Qt::Key_AsciiCircum << Qt::Key_Tab << event->text() << "12214";
  switch(event->key())
  {
    case Qt::Key_Q:
    {
      switch(event->modifiers())
      {
	case Qt::ControlModifier:	// CRTL + Q = Quit
	{
	  // 			close();
	  qApp->quit();
	  return;
	}
	default:
	  break;
	  
      }
      break;
    }
	case Qt::Key_AsciiCircum:		// ^ = Terminal
	case Qt::Key_Tab:
	case Qt::Key_Escape:
	{
	  qWarning() << "Toogle WIdget!!!";
	  toggleWidget(event->key());
	  return;
	}
	#ifdef OH_DEVELOPERS_TEST
	#ifdef linux
	case Qt::Key_N:
	{
	  // 	  DMP->setRestartEnabled();
	  #ifdef enable_sound
	  QApplication::exit(3);
	  break;
	  #else
	  emit appQuit();
	  system("./OpenHanse &");
	  break;
	  // 	system("sh restart.sh");
	  #endif
	}
	case Qt::Key_T:
	{
	  emit appQuit();
	  system("./OpenHanse &");
	  break;
	}
	#endif
	#endif
	default:
	  break;
	  
  }
  // if(event->key() !=
  //  Qt::Key_Escape && spielbool)
  //  {
    // gameview->keyEventWeiterleitung(event);
    //  }
    //Menue-Zeugs
    
    QWidget::keyPressEvent(event);
}

void MainWindow::toggleWidget(int key)
{
  qWarning() << "void MainWindow::toggleWidget(int key)" << key;
  if(m_activeWidget != 0)
  {
    if(m_activeWidget->isVisible())
      m_activeWidget->hide();
    else
      m_activeWidget->show();
  }
  switch(key)
  {
    case Qt::Key_Tab:
    {
      OHDEBUG("Show Playerlist ...");
      GAMEDATA->requestPlayerlist();
      m_Playerlist->setVisible(!m_Playerlist->isVisible());
      m_Playerlist->refreshData();
      break;
    }
    case Qt::Key_AsciiCircum:
    {
      OHDEBUG("Show Terminal ...");
      m_Terminal->setVisible(!m_Terminal->isVisible());
      break;
    }
    case Qt::Key_Escape:
    {
      emit closeCurrentWidget();
      m_Terminal->setVisible(false);
      m_Playerlist->setVisible(false);
      showIngameMenu();
      break;
    }
    default:
      break;
  }
}

/*void MainWindow::serverMenu()
{
  QPushButton *button = new QPushButton (this);
  connect(button, SIGNAL(clicked()), GAMEDATA, SLOT(playerReady()));
  connect(button, SIGNAL(clicked()), this, SLOT(createGameView()));
  connect(button, SIGNAL(clicked()), button, SLOT(deleteLater()));
  button->show();
}*/

void MainWindow::createGameView()
{
  qWarning() << "void MainWindow::createGameView()";
  
  m_GameView = new MainView(this);
//   m_GameView->move(0,0);
  m_GameView->setFocus();
  m_activeWidget = m_GameView;
  connect(GAMEDATA, SIGNAL(worldmapReceived()), m_GameView, SLOT(setWorldmap()));
//   m_GameView->setWorldmap(GAMEDATA->getWorldmapData());
//   m_layout = new QGridLayout(this);
  m_layout->addWidget(m_GameView,0,0,1,1);
  connect(m_GameView, SIGNAL(destroyed(QObject *)), m_layout, SLOT(deleteLater()));
  #ifdef OH_EVOLUTION_DEVELOPED
  
//   m_layout.addWidget(gameview,0,0,1,1);
  
  
  qWarning() << "SFA1";
  menupanel = new ShipControlBar(this);
  qWarning() << "created";
  m_layout.addWidget(menupanel,0,1,1,1);
  
  qWarning()<< "gameview->setFocus(); (gb->spiel)";
  
  
  // 	menupanel->setGameData(GAMEDATA);
  // 	menupanel->show();
  
  m_layout.setColumnStretch(0,7);
  m_layout.setColumnStretch(1,2);
  #endif
  
  m_GameView->resize(800,600);
  m_GameView->show();
///   connect(m_GameView, SIGNAL(inputReceived(QString)), GAMEDATA, SLOT(loadData(QString)));
  
// 	connect(gameview, SIGNAL(appQuit()), this, SIGNAL(appQuit()));

// 	connect(gameview, SIGNAL(sig_trade()), this, SLOT(handel()));

// 	connect(gameview, SIGNAL(sig_anlegbar(bool)), menupanel, SLOT(setDockable(bool)));

// 	connect(gameview, SIGNAL(SIGgeschwindigkeit(int)), menupanel->geschwindigkeitsanzeige,SLOT(setValue(int)));

// 	connect(gameview, SIGNAL(sig_time()),this,SLOT(zeitanzeige()));

// 	connect(gameview, SIGNAL(sig_save()),this,SLOT(speicherndialog()));

	connect(m_GameView, SIGNAL(gameMenuRequested()), this, SLOT(showGameMenu()));

// 	connect(menupanel, SIGNAL(dock()), this, SLOT(landmenu()));
// 	connect(menupanel, SIGNAL(dock()), gameview, SLOT(landgang()));

// 	connect(menupanel, SIGNAL(shoot()), gameview, SLOT(schuss()));
// 	connect(anlegen, SIGNAL(clicked()), anlegen, SLOT(hide()));
// 	connect(menupanel->anlegen, SIGNAL(clicked()), menupanel->ablegen, SLOT(show()));

// 	connect(menupanel->ablegen, SIGNAL(clicked()), this, SLOT(seemenu()));
// 	connect(menupanel->ablegen, SIGNAL(clicked()), gameview, SLOT(ablegen()));
// 	connect(ablegen, SIGNAL(clicked()), anlegen, SLOT(show()));
// 	connect(ablegen, SIGNAL(clicked()), ablegen, SLOT(hide()));

// 	connect(menupanel->geschwindigkeitsregler,SIGNAL(valueChanged(int)), m_gameview, SLOT(segelsetzen(int)));

// 	connect(gameview, SIGNAL(sig_konsole()), m_terminal, SLOT(show()));
// 	connect(TERMINAL, SIGNAL(sig_loadMap(QString)), gameview, SLOT(karteladen(QString)));
}
/*
void MainWindow::lademenu()
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

// void MainWindow::()
// {
// gesamtbild();
// show();
// 
// qWarning() << "mmenuslot()";
// 
// }

void MainWindow::showIngameMenu()
{
  IngameMenu *igm = new IngameMenu(this);
  igm->show();
  
  connect(this, SIGNAL(closeCurrentWidget()), igm, SLOT(deleteLater()));
  connect(igm, SIGNAL(buttonClicked()), igm, SLOT(deleteLater()));
  connect(igm, SIGNAL(exit()), this, SLOT(mainMenu()));
}