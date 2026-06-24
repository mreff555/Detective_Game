#ifndef OPUS_AUDIO_H
#define OPUS_AUDIO_H

#include <raylib.h>

namespace highline_ridge
{

bool decodeOpusBytesToWave(const unsigned char* data, int dataSize, Wave& outWave);
void unloadDecodedWave(Wave& wave);

}

#endif /* OPUS_AUDIO_H */