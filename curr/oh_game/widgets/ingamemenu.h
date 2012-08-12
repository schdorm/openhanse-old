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

#ifndef _IngameMenu_H
#define _IngameMenu_H

#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QGroupBox>

class IngameMenu : public QWidget
{
  Q_OBJECT
  public:
    IngameMenu(QWidget *parent = 0);
    
  public slots:
    
  signals:
    void load();
    void save();
    void exit();
    void options();
    void resume();
    void buttonClicked();
    
  protected:
    QGroupBox GroupBox;
    QPushButton ResumeButton;
    QPushButton QuitButton;
    QPushButton SaveButton;
    QPushButton LoadButton;
    QPushButton OptionsButton;
    QVBoxLayout MenuLayout;
};

#endif
