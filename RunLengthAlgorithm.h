#ifndef RUNLENGTHALGORITHM_H
#define RUNLENGTHALGORITHM_H

void RLEncode (char *source, char *target, unsigned int bufferLenght);
signed int RLEncodeSaveToSameBuffer (char *buffer, unsigned int bufferLenght);
void RLEncodeSendBuffer (char *buffer, unsigned int bufferLenght);

#endif
