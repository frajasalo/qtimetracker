/** @file storagesimpletext.h
 *  @author Frank Bergmann
 *  @date 2014
 *  @copyright GNU Public License.
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

#ifndef STORAGESIMPLETEXT_H
#define STORAGESIMPLETEXT_H

#include <string>
#include <vector>
#include <map>
#include <stdint.h>

#include "storage.h"

/** @brief Simple text storage backend (original qtimetracker)
 *
 * The class inherits from IStorage and therefore provides the basic storage
 * interface.
 * This class implements the original .qtimetracker file backend.
 * Every task uses 3 lines in a text file:
 *   1. name of the task
 *   2. string with the whole time
 *      Format: HH:MM:SS
 *   3. string 'complete' or 'incomplete'
 * This backend does not support the storage of individual time periods.
 */
class StorageSimpleText : public IStorage {
public:
    StorageSimpleText();

    std::string SetFileName(std::string = "");
    std::string Save(const std::vector<task_t> &);
    std::string Load(std::vector<task_t> &);
    std::string AddTaskPeriod(uint32_t, uint32_t, uint32_t);
    std::string GetTaskName(uint32_t);
    uint32_t AddTask(const std::string &, uint32_t = 0);
    bool DelTask(uint32_t);

private:
    std::map<uint32_t, std::string> m_IdNameMap;
};

#endif // STORAGESIMPLETEXT_H
