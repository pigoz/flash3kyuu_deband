#include "utils.h"

    static inline int upsample(void* context, unsigned char pixel)
    {
        return pixel << (INTERNAL_BIT_DEPTH - 8);
    }

#if defined(HAS_DOWNSAMPLE)
#undef HAS_DOWNSAMPLE
#else
    static inline int downsample(void* context, int pixel, int row, int column, int pixel_min, int pixel_max)
    {
        pixel = dither(context, pixel, row, column);
        return clamp_pixel(pixel, pixel_min, pixel_max) >> (INTERNAL_BIT_DEPTH - 8);
    }
#endif
    
    static inline int avg_2(void* context, int pixel1, int pixel2)
    {
        return (pixel1 + pixel2 + 1) >> 1;
    }

    static inline int avg_4(void* context, int pixel1, int pixel2, int pixel3, int pixel4)
    {
        // consistent with SSE code
        int avg1 = (pixel1 + pixel2 + 1) >> 1;
        int avg2 = (pixel3 + pixel4 + 1) >> 1;
        return (avg1 + avg2) >> 1;
    }

