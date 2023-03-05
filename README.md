# WeenieViewer

* ACE Database source: https://github.com/ACEmulator/ACE-World-16PY-Patches
* Converted ACE database into SQLite format using https://github.com/dumblob/mysql2sqlite

## What is it?

WeenieViewer is a very basic tool to view different weenies (items, generators, monsters, etc) in the ACE database, an emulator for the defunct MMO Asheron's Call.

**It is currently very much incomplete and further progress is unlikely due to feedback from community.**

## How to use?

Program will attempt to open the sqlite database on load (if using the source, a copy of this database can be found in the Releases as part of the binary package). Enter a search term into the box and it will automatically search and filter as you type. Double click an result to open it and view more details (which does not actually display any details).
