#include "stdio.h"
#include "stdint.h"
#include "string.h"

#include "Keccak.h"
#include "Endian.h"
#include "Rotation.h"

//#include <systemc.h>

// Constants of the Keccak algorithm.

const uint64_t RC[] = {
	0x0000000000000001L, 0x0000000000008082L, 0x800000000000808aL,
	0x8000000080008000L, 0x000000000000808bL, 0x0000000080000001L,
	0x8000000080008081L, 0x8000000000008009L, 0x000000000000008aL,
	0x0000000000000088L, 0x0000000080008009L, 0x000000008000000aL,
	0x000000008000808bL, 0x800000000000008bL, 0x8000000000008089L,
	0x8000000000008003L, 0x8000000000008002L, 0x8000000000000080L,
	0x000000000000800aL, 0x800000008000000aL, 0x8000000080008081L,
	0x8000000000008080L, 0x0000000080000001L, 0x8000000080008008L
};

const int R[] = {
	0, 1, 62, 28, 27, 36, 44, 6, 55, 20, 3, 10, 43,
	25, 39, 41, 45, 15, 21, 8, 18, 2, 61, 56, 14
};


inline int index1(int x);
inline int index2(int x, int y);

// Function to create the state structure for keccak application, of size length
//   (where length is the number of bits in the hash divided by 8. 
//   (eg 64 for SHA-3-512)
keccakState *keccakCreate(int length)
{
	keccakState *state = (keccakState*)malloc(sizeof(keccakState));
	memset(state, 0, sizeof(keccakState));

	state->A = calloc(25, sizeof(uint64_t));
	memset(state->A, 0, 25*sizeof(uint64_t));
	state->blockLen = 200 - 2*(length/8);
	state->buffer = calloc(state->blockLen, sizeof(uint8_t));
	memset(state->buffer, 0, state->blockLen*sizeof(uint8_t));
	state->bufferLen = 0;
	state->length = length;
	state->d = length;
	return state;
}

void keccakReset(keccakState *state)
{
	unsigned int i;
	for(i = 0 ; i<25 ; i++)
	{
		state->A[i] = 0L;
	}
	state->bufferLen = 0;
}

// keccakUpdate - Functions to pack input data into a block

//  Process a larger buffer with varying amounts of data in it
void keccakUpdate(const uint8_t *input, int off, unsigned int len, keccakState *state)
{
	uint8_t *buffer = state->buffer;
	while (len > 0) 
	{
		int cpLen = 0;
		if((state->blockLen - state->bufferLen) > len)
		{
			cpLen = len;
		}
		else
		{
			cpLen = state->blockLen - state->bufferLen;
		}
		unsigned int i;
		for(i = 0 ; i!=cpLen ; i++)
		{
			buffer[state->bufferLen+i] = input[off+i];
		}
		state->bufferLen += cpLen;
		off += cpLen;
		len -= cpLen;
		if(state->bufferLen == state->blockLen) 
		{
			keccakProcessBuffer(state);
		}
	}
}


// keccakDigest - called once all data has been few to the keccakUpdate functions
//  Pads the structure (in case the input is not a multiple of the block length)
//  returns the hash result in a char array (not null terminated)
unsigned char *keccakDigest(keccakState *state)
{
	uint64_t *A = state->A;
	keccakAddPadding(state);
	keccakProcessBuffer(state);
	uint64_t *tmp = calloc(state->length, sizeof(uint64_t));
	unsigned int i;
	for(i = 0 ; i < state->length ; i+= 8) 
	{
		switch (sizeof(A[i >> 3])) {
			case sizeof(uint16_t):
				tmp[i >> 3] = NativeToLittle16(A[i >> 3]);
				break;
			case sizeof(uint32_t):
				tmp[i >> 3] = NativeToLittle32(A[i >> 3]);
				break;
			case sizeof(uint64_t):
				tmp[i >> 3] = NativeToLittle64(A[i >> 3]);
				break;
		}
	}
	keccakReset(state);
	return (unsigned char*)tmp;
}

void keccakAddPadding(keccakState *state)
{
	unsigned int bufferLen = state->bufferLen;
	uint8_t *buffer = state->buffer;
	if(bufferLen + 1 == state->blockLen) 
	{
		buffer[bufferLen] = (uint8_t) 0x81;
	} 
	else 
	{
		buffer[bufferLen] = (uint8_t) 0x01;
		unsigned int i;
		for(i = bufferLen + 1 ; i < state->blockLen - 1 ; i++) 
		{
			buffer[i] = 0;
		}
		buffer[state->blockLen - 1] = (uint8_t) 0x80;
	}
}

void keccakProcessBuffer(keccakState *state)
{
	uint64_t *A = state->A;
	unsigned int i;
	for(i = 0 ; i < state->blockLen/8 ; i++) 
	{
		switch (sizeof(((uint64_t*)state->buffer)[i])) {
			case sizeof(uint16_t):
				A[i] ^= LittleToNative16(((uint64_t*)state->buffer)[i]);
				break;
			case sizeof(uint32_t):
				A[i] ^= LittleToNative32(((uint64_t*)state->buffer)[i]);
				break;
			case sizeof(uint64_t):
				A[i] ^= LittleToNative64(((uint64_t*)state->buffer)[i]);
				break;
		}
	}
	keccakf(state);
	state->bufferLen = 0;
}

inline int index1(int x)
{
	return x < 0 ? index1(x + 5) : x % 5;
}

inline int index2(int x, int y)
{
	return index1(x) + 5 * index1(y);
}

typedef struct
{
	uint64_t B[25];
	uint64_t C[5];
	uint64_t D[5];
} keccakfState;


// Hash function proper. 
void keccakf(keccakState *state)
{
	uint64_t *A = state->A;
	keccakfState kState;
	int n;
	for(n = 0 ; n < 24 ; n++) 
	{
        int x;
		for(x = 0 ; x < 5 ; x++) 
		{
			kState.C[x] = A[index2(x, 0)] ^ A[index2(x, 1)] ^ A[index2(x, 2)] ^ A[index2(x, 3)] ^ A[index2(x, 4)];
		}
		int i;
		x = 0;
		int y = 0;
		x = 0; 
		kState.D[x] = kState.C[index1(x - 1)] ^ rotateLeft(kState.C[index1(x + 1)], 1);
		y = 0;
		A[index2(x, y)] ^= kState.D[x];
		y = 1;
		A[index2(x, y)] ^= kState.D[x];
		y = 2;
		A[index2(x, y)] ^= kState.D[x];
		y = 3;
		A[index2(x, y)] ^= kState.D[x];
		y = 4;
		A[index2(x, y)] ^= kState.D[x];
		x = 1; 
		kState.D[x] = kState.C[index1(x - 1)] ^ rotateLeft(kState.C[index1(x + 1)], 1);
		y = 0;
		A[index2(x, y)] ^= kState.D[x];
		y = 1;
		A[index2(x, y)] ^= kState.D[x];
		y = 2;
		A[index2(x, y)] ^= kState.D[x];
		y = 3;
		A[index2(x, y)] ^= kState.D[x];
		y = 4;
		A[index2(x, y)] ^= kState.D[x];
		x = 2; 
		kState.D[x] = kState.C[index1(x - 1)] ^ rotateLeft(kState.C[index1(x + 1)], 1);
		y = 0;
		A[index2(x, y)] ^= kState.D[x];
		y = 1;
		A[index2(x, y)] ^= kState.D[x];
		y = 2;
		A[index2(x, y)] ^= kState.D[x];
		y = 3;
		A[index2(x, y)] ^= kState.D[x];
		y = 4;
		A[index2(x, y)] ^= kState.D[x];
		x = 3; 
		kState.D[x] = kState.C[index1(x - 1)] ^ rotateLeft(kState.C[index1(x + 1)], 1);
		y = 0;
		A[index2(x, y)] ^= kState.D[x];
		y = 1;
		A[index2(x, y)] ^= kState.D[x];
		y = 2;
		A[index2(x, y)] ^= kState.D[x];
		y = 3;
		A[index2(x, y)] ^= kState.D[x];
		y = 4;
		A[index2(x, y)] ^= kState.D[x];
		x = 4; 
		kState.D[x] = kState.C[index1(x - 1)] ^ rotateLeft(kState.C[index1(x + 1)], 1);
		y = 0;
		A[index2(x, y)] ^= kState.D[x];
		y = 1;
		A[index2(x, y)] ^= kState.D[x];
		y = 2;
		A[index2(x, y)] ^= kState.D[x];
		y = 3;
		A[index2(x, y)] ^= kState.D[x];
		y = 4;
		A[index2(x, y)] ^= kState.D[x];


		x = 0;
		y = 0;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 1;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 2;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 3;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 4;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		x = 1;
		y = 0;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 1;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 2;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 3;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 4;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);				
		x = 2;
		y = 0;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 1;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 2;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 3;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 4;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);			
		x = 3;
		y = 0;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 1;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 2;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 3;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 4;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);			
		x = 4;
		y = 0;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 1;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 2;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 3;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);
		y = 4;
		i = index2(x, y);
		kState.B[index2(y, x * 2 + 3 * y)] = rotateLeft(A[i], R[i]);			
				
		x = 0;
		y = 0;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 1;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 2;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 3;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 4;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		x = 1;
		y = 0;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 1;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 2;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 3;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 4;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		x = 2;
		y = 0;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 1;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 2;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 3;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 4;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		x = 3;
		y = 0;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 1;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 2;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 3;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 4;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		x = 4;
		y = 0;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 1;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 2;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 3;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		y = 4;
		i = index2(x, y);
		A[i] = kState.B[i] ^ (~kState.B[index2(x + 1, y)] & kState.B[index2(x + 2, y)]);
		
		A[0] ^= RC[n];
	}
}
