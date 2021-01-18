#pragma once

struct Color32;

namespace ParticleTuner {
    void hsv2rgb(float h, float s, float v, Color32& rgb);
    void rgb2hsv(const Color32& rgb, float& h, float& s, float& v);
}
