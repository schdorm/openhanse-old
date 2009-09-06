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

#ifndef _konsole_h
#define _konsole_h

#include <QtGui/QWidget>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QLineEdit>
#include <QStringList>

#include "zeit.h"

class konsole : public QWidget
{
Q_OBJECT
public:
// zeit *hfgametime;
konsole();
void debug(QString);

public slots:
void execCommand();

signals:
void sig_command(QString);

private:
QPlainTextEdit *output;
QLineEdit *input;

QStringList lastcommands;
// QStringListIterator lc_iterator(QStringList);
int row;

protected:
void keyPressEvent(QKeyEvent *);
};

#endif
