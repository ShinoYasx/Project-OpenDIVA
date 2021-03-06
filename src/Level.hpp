//
// Created by hugo on 4/25/20.
//

#ifndef OPENDIVA_LEVEL_HPP
#define OPENDIVA_LEVEL_HPP

#include "Beatmap.hpp"
#include <string>
#include <vector>

class Level {
  private:
    std::string_view version, songName;
    std::string audioFilename;
    float beatsPerMinute;
    struct Params {
        std::string beatmapFilename, difficultyLabel;
        Beatmap::Difficulty difficulty;
    };
    std::vector<Params> difficultyBeatmapParamsSet;

  public:
    explicit Level(const std::string& levelFile);
    void Test();
};

#endif // OPENDIVA_LEVEL_HPP
