#ifndef ENDIAN_H_
#define ENDIAN_H_

typedef enum { false, true } bool;
#define true 1
#define false 0

#include "stdint.h"

// Endianness conversion inlines - These will be optimised out on platforms where
//  it's not necessary, and will collapse to only the swapping code on 
//  other big endian platforms.

inline bool littleEndian()
{
	uint16_t tn;
	uint8_t test;

	tn = 0xff00;
	test = (uint8_t)tn;
	if (!test)
		return true;
	else
		return false;
}


inline uint16_t swapEndian16(uint16_t in)
{
	uint8_t b[2];
	uint16_t out[2];

	b[0] = (uint8_t)(in >> 8);
	b[1] = (uint8_t)in;

	out[0] = ((b[1]) & 0x00FF);
	out[1] = ((b[0]) & 0x00FF);
	out[0] <<= 8;

	return (out[0] | out[1]);
}

inline uint32_t swapEndian32(uint32_t in)
{
	uint16_t b[2];
	uint32_t out[2];

	b[0] = (uint16_t)(in >> 16);
	b[1] = (uint16_t)in;
	b[0] = swapEndian16(b[0]);
	b[1] = swapEndian16(b[1]);

	out[0] = ((b[1]) & 0x0000FFFF);
	out[1] = ((b[0]) & 0x0000FFFF);
	out[0] <<= 16;

	return (out[0] | out[1]);
}

inline uint64_t swapEndian64(uint64_t in)
{
	uint32_t b[2];
	uint64_t out[2];

	b[0] = (uint32_t)(in >> 32);
	b[1] = (uint32_t)in;
	b[0] = swapEndian32(b[0]);
	b[1] = swapEndian32(b[1]);

	out[0] = ((b[1]) & 0x00000000FFFFFFFF);
	out[1] = ((b[0]) & 0x00000000FFFFFFFF);
	out[0] <<= 32;

	return (out[0] | out[1]);
}



inline uint16_t NativeToLittle16(uint16_t in)
{
	if (littleEndian())
	{
		return in;
	}
	else
	{
		return swapEndian16(in);
	}
}

inline uint32_t NativeToLittle32(uint32_t in)
{
	if (littleEndian())
		return in;
	else
	{
		return swapEndian32(in);
	}
}

inline uint64_t NativeToLittle64(uint64_t in)
{
	if (littleEndian())
		return in;
	else
	{
		return swapEndian64(in);
	}
}

inline uint16_t LittleToNative16(uint16_t in)
{
	if (littleEndian())
		return in;
	else
	{
		return swapEndian16(in);
	}
}

inline uint32_t LittleToNative32(uint32_t in)
{
	if (littleEndian())
		return in;
	else
	{
		return swapEndian32(in);
	}
}

inline uint64_t LittleToNative64(uint64_t in)
{
	if (littleEndian())
		return in;
	else
	{
		return swapEndian64(in);
	}
}


inline uint16_t NativeToBig16(uint16_t in)
{
	if (littleEndian())
	{
		return swapEndian16(in);
	}
	else
	{
		return in;
	}
}

inline uint32_t NativeToBig32(uint32_t in)
{
	if (littleEndian())
	{
		return swapEndian32(in);
	}
	else
	{
		return in;
	}
}

inline uint64_t NativeToBig64(uint64_t in)
{
	if (littleEndian())
	{
		return swapEndian64(in);
	}
	else
	{
		return in;
	}
}


inline uint16_t BigToNative16(uint16_t in)
{
	if (littleEndian())
	{
		return swapEndian16(in);
	}
	else
	{
		return in;
	}
}


inline uint32_t BigToNative32(uint32_t in)
{
	if (littleEndian())
	{
		return swapEndian32(in);
	}
	else
	{
		return in;
	}
}

inline uint64_t BigToNative64(uint64_t in)
{
	if (littleEndian())
	{
		return swapEndian64(in);
	}
	else
	{
		return in;
	}
}

#endif //ENDIAN_H_
