/** @file storagesimpletext.cpp
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

#include <fstream>
#include <iostream>
#include <algorithm>

#include "storagesimpletext.h"

/** @brief Constructor
 *
 * The default filename is the original one from qtimetracker.
 */
StorageSimpleText::StorageSimpleText() {
    /* add an option for the filename */
    StoreOption_t opt_filename;
    opt_filename.name = "Filename";
    opt_filename.value = "qtimetracker.txt";
    opt_filename.conf_text = "Filename for the storage file.";
    opt_filename.help_text = "This is the filename for the text file that will \
            contain all the tasks in textual form. If you want to use a \
            central file set an absolute path to the file.";
    AddOption(opt_filename);
}

/** @brief Set the filename for storage file
 *  @param filename The new filename or an empty string for querying the current one
 *  @return The current filename
 *  @todo (Frank Bergmann, 20.3.14) This should be a function for an additional
 * interface class that define functions for backends that use files.
 */
std::string StorageSimpleText::SetFileName(std::string filename/* = ""*/) {

    if (!filename.empty())
        SetOptionValue("Filename", filename);
    return GetOptionValue("Filename");
}

/** @brief Save a vector of tasks.
 *  @param v the vector containing the tasks to save
 *  @return an empty string for success or a failure message
 */
std::string StorageSimpleText::Save(const std::vector<task_t> &v) {

    std::ofstream ofs;
    ofs.open(GetOptionValue("Filename").c_str(), std::ofstream::out | std::ofstream::trunc);

    if (!ofs.is_open())
        return std::string("could not open file for writing");

    /* Lambda function for writing each entry to the file */
    auto func = [&] (task_t t) -> void {
        ofs << m_IdNameMap.find(t.id)->second << std::endl;
        ofs << t.time << std::endl;
        if (t.complete)
            ofs << "complete";
        else
            ofs << "incomplete";
        ofs << std::endl;
    };
    /* call the lambda function for each element in the vector */
    for_each(v.begin(), v.end(), func);

    ofs.close();

    return std::string();
}

/** @brief Load a vector of tasks.
 *  @param v the vector for saving the loaded tasks
 *  @return an empty string for success or a failure message
 */
std::string StorageSimpleText::Load(std::vector<task_t> &v) {

    std::ifstream ifs;
    ifs.open(GetOptionValue("Filename").c_str(), std::ifstream::in);

    if (!ifs.is_open())
        return std::string("could not open file for reading");

    std::string line;
    uint32_t id = 1;
    while (ifs.good()) {

        task_t t;
        getline(ifs, line);
        if (!ifs.good()) {
            /* single empty line does not matter */
            if (line.empty())
                return std::string();
            else
                return std::string("file looks broken");
        }
        t.id = id;
        m_IdNameMap.insert(std::pair<uint32_t, std::string>(id, line));
        ++id;
        t.parent = 0;
        getline(ifs, line);
        if (!ifs.good())
            return std::string("file looks broken");
        t.time = line;
        getline(ifs, line);
        if ("complete" == line)
            t.complete = true;
        else
            t.complete = false;
        v.push_back(t);
    }

    ifs.close();
    return std::string();
}

/** @brief Add a time period to a task
 *  @param id ID of the task
 *  @param start Start time (in unix seconds) of the period
 *  @param end End time (in unix seconds) of the period
 *  @return An failure message because this feature isn't supported
 *
 * Simple text storage does not support saving time periods.
 * The function exists only for the interface of the (interface) base class.
 */
std::string StorageSimpleText::AddTaskPeriod(uint32_t id, uint32_t start, uint32_t end) {

    return std::string("not supported");
}

/** @brief Ask for the name of a task
 *  @param id The ID of the task
 *  @return The name of the task
 */
std::string StorageSimpleText::GetTaskName(uint32_t id) {
    /* find the id in the internal list/map */
    std::map<uint32_t, std::string>::iterator it =  m_IdNameMap.find(id);
    if (m_IdNameMap.end() == it)
        return std::string();
    return (*it).second;
}

/** @brief Add a new task to the storage.
 *  @param name Name of the new task
 *  @param parent Parent ID for the new task
 *  @return The new ID of the task or 0 for error
 *
 * This function adds a new task to the storage.
 * The name will be given and comes from the users input.
 * A parent ID is not supported by this type of storage and will raise an
 * error.
 */
uint32_t StorageSimpleText::AddTask(const std::string &name, uint32_t parent/* = 0*/) {
    /* Parents are not supported by simple text storage backend */
    if (parent) return 0;

    /* Get a new ID, insert it with the name into the map and return the new ID */
    uint32_t id = 0;
    while (0 == id) {
        id = GetNewId();
        if (m_IdNameMap.end() != m_IdNameMap.find(id))
            id = 0;
    }

    m_IdNameMap.insert(std::pair<uint32_t, std::string>(id, name));
    return id;
}

/** @brief Delete a task from the storage.
 *  @param id The ID of the task to be deleted
 *  @return True if the task was successfully deleted
 */
bool StorageSimpleText::DelTask(uint32_t id) {

    if (m_IdNameMap.end() != m_IdNameMap.find(id)) {
        m_IdNameMap.erase(m_IdNameMap.find(id));
        return true;
    }
    return false;
}
