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

#include <QRegExp>

#include "support.h"

/** \brief Convert a time string into a value of seconds
 *  \param timestring
 *  \return Seconds
 *
 * The timestring that is saved or is used inside this program will be divided
 * into the hour, minute ans second values. From this values the seconds will
 * be calculated.
 * If the time string does not match the expected format this function returns
 * zero.
 * \remarks In a further version the time string is converted into a QTime
 * value. But QTime can only work with value up to "23:59:59". If a project
 * takes longer ...
 * \todo unit test !
 */
int timestringtoseconds(QString timestring) {
    QRegExp saved_time_re("^(\\d\\d+):(\\d\\d):(\\d\\d)$");
    if (saved_time_re.exactMatch(timestring)) {
        return saved_time_re.cap(1).toInt() * 3600 + saved_time_re.cap(2).toInt() * 60 + saved_time_re.cap(3).toInt();
    }
    return 0;
}

/** \brief Convert a value of seconds into a time string
 *  \param seconds Seconds to convert into time string
 *  \return The time string as QString
 *
 * Extracts the hours from the value of seconds and substracts
 * the hours immediately because QTime seems to have problems
 * if the minute value is greater than 60.
 */
QString secondstotimestring(int seconds) {
    char time_string[32];
    int hours = (int)(seconds / 3600);  /* hours */
    seconds -= hours * 3600;
    int minutes= (int)(seconds / 60);   /* minutes */
    seconds -= minutes * 60;
    snprintf(time_string, 32, "%02d:%02d:%02d", hours, minutes, seconds);
    return QString(time_string);
}
