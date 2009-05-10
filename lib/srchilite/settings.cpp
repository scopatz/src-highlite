/*
 * settings.cpp
 *
 *  Created on: Apr 18, 2009
 *      Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2008
 *  Copyright: See COPYING file that comes with this distribution
 */

#include "settings.h"

#include <config.h>
#include <dirent.h>
#include <sys/stat.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <boost/regex.hpp>

#include "fileutil.h"
#include "verbosity.h"

using namespace std;

namespace srchilite {

/// the regular expression for the conf file syntax
boost::regex
        datadir_exp(
                "[[:blank:]]*(datadir)[[:blank:]]*=[[:blank:]]*\"([^[:blank:]\\r]+)\"[[:blank:]\\r]*|([[:space:]]+)|([[:space:]]*#.*)");

#define DEFAULT_CONF_DIR ".source-highlight"
#define DEFAULT_CONF_FILE "source-highlight.conf"

Settings::Settings() :
    confFileName(DEFAULT_CONF_FILE),
    testFileName("lang.map"), dataDir(ABSOLUTEDATADIR) {
    const char *home = getenv("HOME");
    if (home) {
        homeDir = home;
    }

    confDir = (homeDir != "" ? homeDir + "/" + DEFAULT_CONF_DIR + "/" : string(
            DEFAULT_CONF_DIR) + "/");
}

Settings::~Settings() {

}

bool Settings::checkForTestFile() {
    string file = dataDir + "/" + testFileName;
    ifstream i(file.c_str());

    return (i != 0);
}

bool Settings::checkForConfFile() {
    string file = confDir + confFileName;
    ifstream i(file.c_str());

    return (i != 0);
}

bool Settings::readDataDir() {
    string file = confDir + confFileName;
    ifstream i(file.c_str());

    string line;
    if (i != 0) {
        while (read_line(&i, line)) {
            if (line.size()) {
                boost::cmatch what;
                if (boost::regex_match(line.c_str(), what, datadir_exp)
                        && what[2].matched) {// not all spaces, nor comments
                    dataDir = what[2];
                    return true;
                }
            }
        }
    }

    return false;
}

SettingError Settings::save() {
    // the directory does not exist?
    if (opendir(confDir.c_str()) == 0) {
        // then create it
        if (mkdir(confDir.c_str(), S_IRWXU) != 0) {
            return CANT_CREATE_DIR;
        }
    }

    string file = confDir + confFileName;
    ofstream o;
    o.open(file.c_str());

    if (o) {
        o << "# settings for source-highlight" << endl;
        o << endl;
        o << "datadir = \"" << dataDir << "\"" << endl;
        o.close();
        return NO_SETTING_ERROR;
    }

    return CANT_CREATE_FILE;
}

const string Settings::retrieveDataDir(bool reload) {
    static string dataDir;

    if (dataDir != "" && !reload)
        return dataDir; // cached value

    VERBOSELN("retrieving default datadir value...");

    const char *_dataDir = getenv("SOURCE_HIGHLIGHT_DATADIR");
    if (_dataDir) {
        VERBOSELN("using SOURCE_HIGHLIGHT_DATADIR env value " + string(_dataDir));
        dataDir = _dataDir;
        return _dataDir;
    }

    static Settings settings;

    if (!settings.readDataDir()) {
        VERBOSELN("using hardcoded datadir value " ABSOLUTEDATADIR);
        dataDir = ABSOLUTEDATADIR;
        return ABSOLUTEDATADIR;
    }

    dataDir = settings.getDataDir();

    VERBOSELN("using datadir value from conf file " + dataDir);

    return dataDir;
}

}
