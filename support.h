/*
 * Copyright 2013 by Frank Bergmann
 *
 * This file is part of qtimetracker.
 *
 * qtimetracker is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * qtimetracker is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with qtimetracker.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SUPPORT_H
#define SUPPORT_H

#include <QString>

int timestringtoseconds(QString timestring);
QString secondstotimestring(int seconds);

#endif // SUPPORT_H
