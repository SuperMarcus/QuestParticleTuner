#pragma once

namespace UnityEngine {
    struct Color32;
    struct Color;
}

namespace ParticleTuner {
    void hsv2rgb(float h, float s, float v, UnityEngine::Color32& rgb);
    void rgb2hsv(const UnityEngine::Color32& rgb, float& h, float& s, float& v);

    UnityEngine::Color toColor(const UnityEngine::Color32 &in);
    UnityEngine::Color32 toColor32(UnityEngine::Color in);
}
