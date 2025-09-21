#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <ctime>
#include <sstream>
#include <algorithm>


using namespace std;


void helper() {
    cout << "\n----- Filesystem Command Reference -----\n\n";
    cout << " - Core File Operations \n";
    cout << "    -File Management \n";
    cout << "      CREATE <filename>           : Create a new file with given name\n";
    cout << "      DELETE <filename>           : Delete an existing file\n";
    cout << "      RENAME <old> <new>          : Rename an existing file\n";
    cout << "      OPEN <filename>             : Open a file to work on\n";
    cout << "      CLOSE                       : Close the currently opened file\n";
    cout << "      LS                          : List all files in the filesystem\n\n";
    cout << "    -Content Operations \n";
    cout << "      READ <filename>             : Read content of the active version\n";
    cout << "      INSERT <filename> <text>    : Insert text into the active version\n";
    cout << "      UPDATE <filename> <text>    : Replace content of the active version\n\n";
    cout << "    -Version Control \n";
    cout << "      SNAPSHOT <filename> <msg>   : Take a snapshot of the active version\n";
    cout << "      ROLLBACK <filename> [id]    : Rollback to parent or specific version id\n";
    cout << "      HISTORY <filename>          : Show snapshot history (id, time, message)\n";
    cout << "      PRINT <filename>            : Print the full version tree of the file\n\n";
    cout << " - System Wide Analytics \n";
    cout << "      RECENT_FILES                : Show files by last modification time\n";
    cout << "      BIGGEST_TREES               : Show files by total versions\n\n";
    cout << "  HELP                           : Show this list of valid commands\n";
    cout << "  EXIT                           : Exit the terminal\n\n";
    cout << "Note: Commands are not case-sensitive.\n";
    cout << "Filenames and content are case-sensitive.\n\n";
    cout << "------------------------------------------\n\n";
}

string Time(time_t t) {
    char buf[80];
    tm *ltm = localtime(&t); 
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ltm); //to convert epochs to standard date-time format
    return string(buf);
}
