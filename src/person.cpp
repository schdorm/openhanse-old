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
 
 #include "person.h"
 
 void Person::setPixmapItem(QGraphicsPixmapItem *param_gpi)
 {
 graphicsitem = param_gpi;
 
 }
 
 void Person::fillSidePixmapList(QImage *param_img_ptr, const QRect param_rect, const int param_count, const bool param_left_side)
 {
	QImage section_image;
// 	QPixmap *add_pixmap_left = new QPixmap();
// 	QPixmap *add_pixmap_right = new QPixmap();
	QRect workrect = param_rect;
	for(int i = 0; i < param_count; i++)
	{
		workrect.moveRight( i * param_rect.width());
		section_image = param_img_ptr->copy(workrect);
		if(param_left_side)
		{
// 		add_pixmap_left->fromImage(section_image);
// 		LeftPixmapList << *add_pixmap_left;
		LeftPixmapList << QPixmap().fromImage(section_image);
		
// 		add_pixmap_right->fromImage(section_image.mirrored(false, true));
// 		RightPixmapList << *add_pixmap_right;
		RightPixmapList << QPixmap().fromImage(section_image.mirrored(false, true));
		}
		else
		{
// 		add_pixmap_left->fromImage(section_image.mirrored(false, true));
// 		LeftPixmapList << *add_pixmap_left;
		RightPixmapList << QPixmap().fromImage(section_image);
		LeftPixmapList << QPixmap().fromImage(section_image.mirrored(false, true));

// 		add_pixmap_right->fromImage(section_image);
// 		RightPixmapList << *add_pixmap_right;
		}
	}
 }
 
  void Person::fillUpPixmapList(QImage *param_img_ptr, const QRect param_rect, const int param_count)
 {
	QImage section_image;
	QRect workrect = param_rect;
	for(int i = 0; i < param_count; i++)
	{
		workrect.moveRight( i * param_rect.width());
		section_image = param_img_ptr->copy(workrect);
		
		UpPixmapList << QPixmap().fromImage(section_image);

	}
 }
 
void Person::fillDownPixmapList(QImage *param_img_ptr, const QRect param_rect, const int param_count)
 {
	QImage section_image;
	QRect workrect = param_rect;
	for(int i = 0; i < param_count; i++)
	{
		workrect.moveRight( i * param_rect.width());
		section_image = param_img_ptr->copy(workrect);
		
		DownPixmapList << QPixmap().fromImage(section_image);

	}
 }
 
void Person::move(int param_dir)
{
 switch (param_dir)
 {
	case Direction::Up:
	{
		if(currentDirection == param_dir) //Move
		{
			if(step == UpPixmapList.size())
			{
			step = 0;
			}
			else
			{
				step ++;
			}
			graphicsitem->setPixmap(UpPixmapList.value(step));
		}
		else	// Rotate
		{
			graphicsitem->setPixmap(UpPixmapList.first());
			step = 0;
			currentDirection = param_dir;
		}
		break;
	}
	case Direction::Down:
	{
		if(currentDirection == param_dir) //Move
		{
			if(step == DownPixmapList.size())
			{
			step = 0;
			}
			else
			{
				step ++;
			}
			graphicsitem->setPixmap(DownPixmapList.value(step));
		}
		else	// Rotate
		{
			graphicsitem->setPixmap(DownPixmapList.first());
			step = 0;
			currentDirection = param_dir;
		}
		break;
	}
	case Direction::Left:
	{
		if(currentDirection == param_dir) //Move
		{
			if(step == LeftPixmapList.size())
			{
			step = 0;
			}
			else
			{
				step ++;
			}
			graphicsitem->setPixmap(LeftPixmapList.value(step));
		}
		else	// Rotate
		{
			graphicsitem->setPixmap(LeftPixmapList.first());
			step = 0;
			currentDirection = param_dir;
		}
		break;
	}
	case Direction::Right:
	{
		if(currentDirection == param_dir) //Move
		{
			if(step == RightPixmapList.size())
			{
			step = 0;
			}
			else
			{
				step ++;
			}
			graphicsitem->setPixmap(RightPixmapList.value(step));
		}
		else	// Rotate
		{
			graphicsitem->setPixmap(RightPixmapList.first());
			step = 0;
			currentDirection = param_dir;
		}
		 break;
	}
 
 }
 
}
 