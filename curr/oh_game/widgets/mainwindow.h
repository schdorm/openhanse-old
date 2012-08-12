/***************************************************************************
 *   Copyright (C) 2009 - 2010 by Christian Doerffel                       *
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

#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QtCore/QList>
#include <QtCore/QObject>

#include <QtGui/QWidget>
// #include <QtGui/QGridLayout>

#include "sound_pre.h"


#define _NO_SAVE__

class ShipControlBar;
class ShipData;

class MainView;
class TradingWindow;

class MainMenu;
class GameSettingsMenu;

class Terminal;
class Playerlist;
class ServerProcess;
class QGridLayout;

class MainWindow : public QWidget
{
  Q_OBJECT
  public:
    MainWindow(QWidget * = 0);
    ~MainWindow();
    
    
  public slots:
    void options();
    void applySettings();

//     void aktivieren();
    
//     void startNewGame();
    
//     void handel();
//     void tradingFinished();
    
//     void landmenu();
//     void seemenu();
    
//     void zeitanzeige();
    
  private slots:
    void showMainMenu();
    void showIngameMenu();
    
    void singleplayerGame();
    void multiplayerGame();
    void serverMenu();
    void gameSettingsMenu();
    
    void addMainMenuMusic();
    
    void createGameView();
    void toggleWidget(int);
    
//     void startSingleplayerGame();
    void execCommand(const QString&);
    
  private:
    bool spielbool;
    bool aktiv;
    
    
    int schwierigkeitsgrad;
    
    Terminal *m_Terminal;
    Playerlist *m_Playerlist;
    MainView *m_GameView;
    TradingWindow *m_TradingWindow;
    ShipControlBar *m_ShipControlBar;
    MainMenu *m_MainMenu;
    GameSettingsMenu *m_GameSettingsMenu;
    
    QWidget *m_activeWidget;
    
    QString filename;			// fuer Savegame 
//     ServerProcess *m_serverProcess;
    
    
    #ifdef enable_sound
    Phonon::MediaObject *m_musicMedia;
    Phonon::AudioOutput *m_musicOutput;
    
    Phonon::MediaObject *m_miscMedia;
    Phonon::AudioOutput *m_miscOutput;
    #endif
    
    QGridLayout *m_layout;
    
  signals:
    void appQuit();
    void closeCurrentWidget();
    
  protected:
    void keyPressEvent(QKeyEvent *event);
    
};

#endif
