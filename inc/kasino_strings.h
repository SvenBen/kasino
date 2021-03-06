/*
 * strings.h
 *
 *  Created on: Dec 6, 2014
 *      Author: sven
 */

#ifndef KASINO_STRINGS_H_
#define KASINO_STRINGS_H_

#include <string>

const std::string STR_SETTING_SLOWMO = "SLOWMO";
const std::string STR_SETTING_QUALI = "QUALI";
const std::string STR_SETTING_SERVER = "SERVER";
const std::string STR_SETTING_VIEW_FRAME_WINDOW = "VIEW_FRAME_WINDOW";
const std::string STR_SETTING_VIEW_STATISTIC_WINDOW = "VIEW_STATISTIC_WINDOW";
const std::string STR_SETTING_VIEW_CALCULATED_PERSPECTIVE = "VIEW_CALCULATED_PERSPECTIVE";
const std::string STR_SETTING_VIEW_ROUND_NR = "VIEW_ROUND_NR";
const std::string STR_SETTING_VIEW_BALL_POSITION = "VIEW_BALL_POSITION";
const std::string STR_SETTING_VIEW_NULL_POSITION = "VIEW_NULL_POSITION";
const std::string STR_SETTING_VIEW_CROSSHAIR = "VIEW_CROSSHAIR";
const std::string STR_SETTING_VIEW_TIME_SINCE_ROUND_START = "VIEW_TIME_SINCE_ROUND_START";
const std::string STR_SETTING_VIEW_BALL_VELOCITY = "VIEW_BALL_VELOCITY";
const std::string STR_SETTING_VIEW_PLATE_VELOCITY = "VIEW_PLATE_VELOCITY";
const std::string STR_SETTING_VIEW_PERSPECTIVE_CALCULATION = "VIEW_PERSPECTIVE_CALCULATION";
const std::string STR_SETTING_VIEW_NULL_POS_CALCULATION = "VIEW_NULL_POS_CALCULATION";
const std::string STR_SETTING_VIEW_BALL_POS_CALCULATION = "VIEW_BALL_POS_CALCULATION";
const std::string STR_SETTING_VIDEO_RECORD_PATH = "VIDEO_RECORD_PATH";
const std::string STR_SETTING_IMAGE_RECORD_PATH = "IMAGE_RECORD_PATH";
const std::string STR_SETTING_ANALYZE = "ANALYZE";
const std::string STR_SETTING_PATH_ROUND_LOG_FILE = "PATH_ROUND_LOG_FILE";

const std::string STR_COULD_NOT_OPEN = "Kann Datei nicht oeffnen: ";
const std::string STR_NOT_ENOUGH_SPACE = "Nicht genug Speicher";
const std::string STR_ERR_READING_SETTINGS = "Fehler beim Lesen der Gui-Settings-Datei.";
#define STR_CANNOT_OPEN_FILE(FILENAME) std::string("Kann die Datei \"") + (FILENAME) + "\" nicht öffnen"

#endif /* KASINO_STRINGS_H_ */
