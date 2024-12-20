/*
Game I made for learning OpenGL, more into can be found in DOCUMENTATION
    If anyone stumbles across this code and wants to use parts that I wrote go ahead, just follow AGPL :)
    Parts that have been adapted from other people have been marked as such.

    Copyright (C) 2024  William Steven

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "files.h"

std::filesystem::__cxx11::path findInstallDir() {
    std::filesystem::__cxx11::path cwd, check_dir;
    std::stringstream sstr;
    cwd = std::filesystem::current_path();
    check_dir = cwd.parent_path();
    while (check_dir.filename() != "TrainGame") {
        check_dir = check_dir.parent_path();
    }
    sstr << check_dir;
    return check_dir;
}