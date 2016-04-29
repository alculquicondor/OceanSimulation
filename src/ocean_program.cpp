#include "ocean_program.h"


OceanProgram::OceanProgram() : MvpProgram("shaders/ocean_vertex.glsl", "shaders/texture_fragment.glsl") {
    set_uniform("time", 0);
}

const std::vector<glm::vec4> OceanProgram::waves = {
        {0.504,	-1.571,	0.225, 0.1},
        {0.484,	-1.190,	0.202, 0.2},
        {0.471,	-1.249,	0.237, 0.3},
        {0.430,	-1.571,	0.188, 0.1},
        {0.405,	-1.107,	0.252, 0.2},
        {0.399,	-1.571,	0.263, 0.3},
        {0.398,	-1.429,	0.265, 0.4},
        {0.385,	-1.893,	0.237, 0.5},
        {0.381,	-1.951,	0.202, 0.4},
        {0.372,	-1.713,	0.265, 0.1},
        {0.365,	-0.927,	0.18, 0.2},
        {0.332,	-0.983,	0.270, 0.3},
        {0.327,	-0.785,	0.212, 0.3},
        {0.326,	-1.166,	0.286, 0.2},
        {0.313,	-2.034,	0.252, 0.1},
        {0.294,	-0.785,	0.265, 0.4},
        {0.278,	-1.976,	0.286, 0},
        {0.277,	-1.107,	0.168, 0.1},
        {0.276,	-0.644,	0.187, 0.5},
        {0.268,	-2.214,	0.188, 0.2},
};


void OceanProgram::set_time(float time) {
    set_uniform("time", time);
}

void OceanProgram::set_waves() {
    set_uniform("waves", waves);
}