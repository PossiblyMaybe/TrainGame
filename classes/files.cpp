//
// Created by will on 09/12/24.
//

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