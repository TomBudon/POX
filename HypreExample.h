#pragma once

#include <stdio.h>
#include <vector>
#include "alien_files/MpiMock.h"
#include "alien_files/AlienMock.h"



class HypreExample {
public:
    std::vector<int> run();
};
