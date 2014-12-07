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
const std::string STR_SETTING_VIEW_FRAME_WINDOW = "VIEW_FRAME_WINDOW";
const std::string STR_SETTING_VIEW_STATISTIC_WINDOW = "VIEW_STATISTIC_WINDOW";
const std::string STR_SETTING_VIEW_CALCULATED_PERSPECTIVE = "VIEW_CALCULATED_PERSPECTIVE";
const std::string STR_SETTING_VIEW_BALL_POSITION = "VIEW_BALL_POSITION";
const std::string STR_SETTING_VIEW_NULL_POSITION = "VIEW_NULL_POSITION";
const std::string STR_SETTING_VIEW_CROSSHAIR = "VIEW_CROSSHAIR";
const std::string STR_SETTING_VIEW_TIME_SINCE_ROUND_START = "VIEW_TIME_SINCE_ROUND_START";
const std::string STR_SETTING_VIEW_BALL_VELOCITY = "VIEW_BALL_VELOCITY";
const std::string STR_SETTING_VIEW_PLATE_VELOCITY = "VIEW_PLATE_VELOCITY";
const std::string STR_SETTING_VIEW_PERSPECTIVE_CALCULATION = "VIEW_PERSPECTIVE_CALCULATION";
const std::string STR_SETTING_VIEW_NULL_POS_CALCULATION = "VIEW_NULL_POS_CALCULATION";
const std::string STR_SETTING_VIEW_BALL_POS_CALCULATION = "VIEW_BALL_POS_CALCULATION";


const std::string STR_NOT_ENOUGH_SPACE = "Nicht genug Speicher";
const std::string STR_ERR_READING_SETTINGS = "Fehler beim Lesen der Gui-Settings-Datei.";
#define STR_CANNOT_OPEN_FILE(SETTINGS_FILE) std::string("Kann die Datei \"") + SETTINGS_FILE + "\" nicht öffnen"

#endif /* STRINGS_H_ */
