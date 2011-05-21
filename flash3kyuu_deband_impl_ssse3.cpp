#include "stdafx.h"

#include <tmmintrin.h>

static __m128i __inline _mm_blendv_epi8( 
   __m128i a,
   __m128i b,
   __m128i mask 
)
{
	// mask is always returned from cmp functions, so it can be used directly
	__m128i b_mask = _mm_and_si128(mask, b);
	__m128i a_mask = _mm_andnot_si128(mask, a);

	return _mm_or_si128(a_mask, b_mask);
}

static __m128i _mm_mullo_epi32(__m128i a, __m128i b)
{
	// input can always be fit in 16bit

	a = _mm_packs_epi32(a, a);

	b = _mm_packs_epi32(b, b);
	
	__m128i lo_part = _mm_mullo_epi16(a, b);

	__m128i hi_part = _mm_mulhi_epi16(a, b);

	return _mm_unpacklo_epi16(lo_part, hi_part);
}
#include "flash3kyuu_deband_sse_base.h"

DEFINE_SSE_IMPL(ssse3);