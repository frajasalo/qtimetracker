/** @file storageoptions.cpp
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

#include "storageoptions.h"

/** @brief Constructor for the class. */
IStorageOptions::IStorageOptions() {
    /* clear the (default) options list */
    m_OptList.clear();
}

/** @brief Add a new option to the list
 *  @param opt the new option (struct)
 *  @return true for successfully insertion of the option.
 *
 * The function ENSHURES that the name of the option is unique.
 */
bool IStorageOptions::AddOption(StoreOption_t opt) {

    for (StoreOptionList_t::iterator it = m_OptList.begin(); it != m_OptList.end(); ++it)
        if (opt.name == (*it).name)
            return false;
    m_OptList.push_back(opt);
    return true;
}

/** @brief Get the whole list of options.
 *  @return The current option list.
 */
StoreOptionList_t IStorageOptions::GetOptions() const {
    return m_OptList;
}

/** @brief Get an option value by name.
 *  @param opt_name The name of the option to get the value from.
 *  @return The value of the option as a std::string or an empty string
 */
std::string IStorageOptions::GetOptionValue(const std::string &opt_name) const {
    /* serach for the option ... */
    for (StoreOptionList_t::const_iterator it = m_OptList.begin(); it != m_OptList.end(); ++it)
        if (opt_name == (*it).name)
            /* ... and return its value */
            return (*it).value;
    return std::string();
}

/** @brief Set an option value by name
 *  @param opt_name The name of the option to set the value for.
 *  @param opt_value The new value for the option.
 *  @return The new value if the operation was successfull or an empty string.
 */
std::string IStorageOptions::SetOptionValue(const std::string &opt_name, std::string opt_value) {
    /* search for the option ... */
    for (StoreOptionList_t::iterator it = m_OptList.begin(); it != m_OptList.end(); ++it)
        if (opt_name == (*it).name) {
            /* ... and set its value */
            (*it).value = opt_value;
            return opt_value;
        }
    return std::string();
}
