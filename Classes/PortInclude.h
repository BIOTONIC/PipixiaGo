#include <stdio.h>
#include <stdlib.h>
#include "../include/portaudio.h"

// change 'SAMPLE_RATE', 'NUM_CHANNELS' and 'PA_SAMPLE_TYPE' according to your own microphones' parameters
#define SAMPLE_RATE  (44100)
#define FRAMES_PER_BUFFER (1024)
#define RECORD_TIME     (0.01)
#define NUM_CHANNELS    (2)

// select sample format
#if 1
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
typedef char SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif

PaStreamParameters inputParameters;
PaStream *stream;
PaError err;
SAMPLE *recordedSamples;
int numSamples;
SAMPLE max, val;