/*
 * strings.h
 *
 *  Created on: Dec 6, 2014
 *      Author: sven
 */

#ifndef STRINGS_H_
#define STRINGS_H_

#include <string>

const std::string STR_SETTING_SLOWMO = "SLOWMO";
const std::string STR_SETTING_QUALI = "QUALI";
const std::string STR_SETTING_SERVER = "SERVER";


const std::string STR_NOT_ENOUGH_SPACE = "Nicht genug Speicher";
const std::string STR_ERR_READING_SETTINGS = "Fehler beim Lesen der Gui-Settings-Datei.";
#define STR_CANNOT_OPEN_FILE(SETTINGS_FILE) std::string("Kann die Datei \"") + SETTINGS_FILE + "\" nicht öffnen"

#endif /* STRINGS_H_ */
