#ifndef STORAGEOPTIONS_H
#define STORAGEOPTIONS_H

#include <string>
#include <list>

/** @brief Structure that holds an option */
typedef struct {
    /** @brief Name of the option */
    std::string name;
    /** @brief Value of the option
     *  @todo (Frank Bergmann, 3.4.14) Find a satisfying solution for
     * non-string values */
    std::string value;
    /** @brief Text beside the configure input */
    std::string conf_text;
    /** @brief Popup help text for the configure input */
    std::string help_text;
} StoreOption_t;

/** @brief The list that contains all options */
typedef std::list<StoreOption_t> StoreOptionList_t;

/** @class IStorageOptions A base class for storing options used in the
 * storage classes */
class IStorageOptions {

public:
    IStorageOptions();
    virtual ~IStorageOptions() {}

    StoreOptionList_t GetOptions() const;

    bool AddOption(StoreOption_t);
    std::string GetOptionValue(const std::string &) const;
    std::string SetOptionValue(const std::string &, std::string);

private:
    StoreOptionList_t m_OptList;
};

#endif // STORAGEOPTIONS_H
