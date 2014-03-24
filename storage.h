/** @file storage.h
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

#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>

#include <stdint.h>
#include <time.h>

/** @brief Type for the entries in the task list interface */
typedef struct {
    /** @brief The ID of task */
    uint32_t id;
    /** @brief The ID of the parent of the task (hierarchically tasks) */
    uint32_t parent;
    /** @brief The whole time period for the task.
     *  @todo (Frank Bergmann, 20.3.14) Use the number instead of a string */
    std::string time;
    /** @brief Flag showing whether the task is completed */
    bool complete;
} task_t;

/** @class IStorage Interface for accessing the storage
 *
 * This class works as an interface for storing tasks and time and or time
 * periods spending work on the tasks.
 */
class IStorage {
public:
    virtual ~IStorage() {}
    /** @brief Saving the tasks and times to the storage backend */
    virtual std::string Save(const std::vector<task_t> &) = 0;
    /** @brief Loading the tasks and times from the backend */
    virtual std::string Load(std::vector<task_t> &) = 0;
    /** @brief Add (or finish) a time period an a task */
    virtual std::string AddTaskPeriod(uint32_t, uint32_t, uint32_t) = 0;
    /** @brief Get the name for a task (id) */
    virtual std::string GetTaskName(uint32_t) = 0;
    /** @brief Add a new task */
    virtual uint32_t AddTask(const std::string &, uint32_t = 0) = 0;
    /** @brief Delete a task */
    virtual bool DelTask(uint32_t) = 0;

protected:
    uint32_t GetNewId(void);
};

/** @brief Create and deliver a new random unique task ID.
 *  @return The new task ID
 *
 * Generate a new random number that has to be not 0.
 * It' the first and one and only function and therefor inline.
 */
inline uint32_t IStorage::GetNewId(void) {
    /* initialize the random number generator with the current time */
    srand(time(NULL));
    uint32_t id = 0;
    /* get an id not equal to zero */
    do {
        id = (uint32_t)rand();
    }
    while (0 == id);
    return id;
}

#endif // STORAGE_H
