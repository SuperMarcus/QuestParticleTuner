#include <algorithm>

#include "color.h"
#include "particletune_private.hpp"

// Modified from Jan Winkler <winkler@cs.uni-bremen.de>'s color conversion code:
// https://gist.github.com/fairlight1337/4935ae72bcbcc1ba5c72

using namespace std;

void ParticleTuner::hsv2rgb(float fH, float fS, float fV, Color32 &rgb) {
    float fC = fV * fS; // Chroma
    float fHPrime = fmod(fH * 6.0f, 6.0f);
    float fX = fC * (1.0f - fabs(fmod(fHPrime, 2.0f) - 1.0f));
    float fM = fV - fC;
    float fR, fG, fB;

    if(0 <= fHPrime && fHPrime < 1) {
        fR = fC;
        fG = fX;
        fB = 0.0f;
    } else if(1 <= fHPrime && fHPrime < 2) {
        fR = fX;
        fG = fC;
        fB = 0.0f;
    } else if(2 <= fHPrime && fHPrime < 3) {
        fR = 0.0f;
        fG = fC;
        fB = fX;
    } else if(3 <= fHPrime && fHPrime < 4) {
        fR = 0.0f;
        fG = fX;
        fB = fC;
    } else if(4 <= fHPrime && fHPrime < 5) {
        fR = fX;
        fG = 0.0f;
        fB = fC;
    } else if(5 <= fHPrime && fHPrime < 6) {
        fR = fC;
        fG = 0.0f;
        fB = fX;
    } else {
        fR = 0.0f;
        fG = 0.0f;
        fB = 0.0f;
    }

    fR += fM;
    fG += fM;
    fB += fM;

    rgb.r = static_cast<uint8_t>(fR * 255.0f);
    rgb.g = static_cast<uint8_t>(fG * 255.0f);
    rgb.b = static_cast<uint8_t>(fB * 255.0f);
}

void ParticleTuner::rgb2hsv(const Color32 &rgb, float &fH, float &fS, float &fV) {
    auto fR = clamp(static_cast<float>(rgb.r) / 255.0f, 0.0f, 1.0f);
    auto fG = clamp(static_cast<float>(rgb.g) / 255.0f, 0.0f, 1.0f);
    auto fB = clamp(static_cast<float>(rgb.b) / 255.0f, 0.0f, 1.0f);
    auto fCMax = max({ fR, fG, fB });
    auto fCMin = min({ fR, fG, fB });
    auto fDelta = fCMax - fCMin;

    if(fDelta > 0) {
        if(fCMax == fR) {
            fH = (fmod(((fG - fB) / fDelta), 6.0f)) / 6.0f;
        } else if(fCMax == fG) {
            fH = (((fB - fR) / fDelta) + 2.0f) / 6.0f;
        } else if(fCMax == fB) {
            fH = (((fR - fG) / fDelta) + 4.0f) / 6.0f;
        }

        if(fCMax > 0) {
            fS = fDelta / fCMax;
        } else {
            fS = 0.0f;
        }

        fV = fCMax;
    } else {
        fH = 0.0f;
        fS = 0.0f;
        fV = fCMax;
    }

    if(fH < 0) {
        fH = 1.0f + fH;
    }
}
