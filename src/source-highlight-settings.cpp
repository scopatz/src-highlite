/*
 * Copyright (C) 2007-2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

/*
 * This program is part of GNU source-highlight
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cstdlib>
#include <iostream>

#include "srchilite/settings.h"
#include "srchilite/versions.h"

#ifdef HAVE_CONFIG_H
// this is glib related so don't use it when compiling with qmake
#include "progname.h"

#else

#define set_program_name(x) ;

#endif


using namespace std;
using namespace srchilite;

Settings settings;

bool checkForTestFile() {
    bool checkForTestFile = settings.checkForTestFile();

    if (!checkForTestFile)
        cout << "*** ERROR: ";

    cout << "it seems that the datadir " << (checkForTestFile ? "contains"
            : "does not contain") << " files for source-highlight" << endl;

    return checkForTestFile;
}

bool save() {
    SettingError error = settings.save();

    if (error != NO_SETTING_ERROR) {
        cout << "cannot create configuration file: " << settings.getConfDir()
                + settings.getConfFileName() << endl;
        return false;
    }

    return true;
}

int main(int argc, char * argv[]) {
    set_program_name(argv[0]);
    string answer;

    cout << "source-highlight-settings" << endl;
    cout << "part of " << Versions::getCompleteVersion() << endl;

    string configurationFile = settings.getConfDir()
            + settings.getConfFileName();

    cout << "configuration file: " << configurationFile << endl;

    if (!settings.checkForConfFile()) {
        cout << "The configuration file does not exist..." << endl;
        cout << "Creating a default one, with the value for datadir: "
                << Settings::retrieveDataDir() << endl;
        save();
    }

    while (true) {
        if (!settings.readDataDir()) {
            cout << "the datadir is not specified in the configuration file"
                    << endl;
        } else {
            cout << "the current datadir is: " << settings.getDataDir() << endl;

            checkForTestFile();
        }

        cout
                << "Do you want to change the datadir and save the configuration file? [y/n] ";
        cin >> answer;
        if (answer != "y" && answer != "Y") {
            cout << "No configuration file modified" << endl;
            break;
        }

        cout << "Please enter the new path for datadir: ";
        cin >> answer;

        settings.setDataDir(answer);
        cout << "Checking " << settings.getDataDir() << endl;
        if (!checkForTestFile()) {
            continue;
        }

        if (!save()) {
            continue;
        }

        cout << "New configuration file saved: " << configurationFile << endl;

        break;
    }

    cout << "Thanks for using source-highlight! :-)" << endl;

    return EXIT_SUCCESS;
}

