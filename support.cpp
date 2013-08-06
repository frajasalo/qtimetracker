/*
 * Copyright 2010-2013 by Thorsten Staerk
 * http://www.staerk.de/thorsten
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

#include <QTime>

#include "support.h"

/** \brief Converts a value of seconds into a time string of "HH:MM:SS"
 *  \param seconds Value of seconds
 *  \return time string
 *  \bug (Frank Bergmann, 6. Aug 2013) This functions fails when the value reaches 24 hours and above.
 */
QString timestring(int seconds) {

	return QTime((int)(seconds/3600),(int)(seconds/60)%60,seconds%60).toString();
}
