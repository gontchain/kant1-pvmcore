#ifndef KECCAK_H
#define KECCAK_H

// State structure
typedef struct {
	uint64_t *A;
	unsigned int blockLen;
	uint8_t *buffer;
	unsigned int bufferLen;
	int length;
	unsigned int d;
} keccakState;

void keccakProcessBuffer(keccakState *state);
void keccakUpdate(const uint8_t *input, int off, unsigned int len, keccakState *state);
unsigned char *keccakDigest(keccakState *state);
unsigned char *sha3Digest(keccakState *state);
unsigned char *shakeDigest(keccakState *state);
void keccakAddPadding(keccakState *state);
void keccakf(keccakState *state);
void sha3AddPadding(keccakState *state);
void shakeAddPadding(keccakState *state);
keccakState *keccakCreate(int length);
keccakState *shakeCreate(int length, unsigned int d_);

#endif // KECCAK_H
