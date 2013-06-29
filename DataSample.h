#ifndef DATASAMPLE_H
#define	DATASAMPLE_H

void vSample40MHz (unsigned char *Port, unsigned char *Buffer, unsigned int n);
void vSample20MHz (unsigned char *Port, unsigned char *Buffer, unsigned int n);
void vSample10MHz (unsigned char *Port, unsigned char *Buffer, unsigned int n);
void vSample4MHz (unsigned char *Port, unsigned char *Buffer, unsigned int n);
void vSample400KHz (unsigned char *Port, unsigned char *Buffer, unsigned int n);
void vSample2KHz (unsigned char *Port, unsigned char *Buffer, unsigned int n);
void vSample10Hz (unsigned char *Port, unsigned char *Buffer, unsigned int n);

void vSample40MHzTriggerSimple (unsigned char *Port, unsigned char *Buffer, unsigned int n);
void vSample20MHzTriggerSimple (unsigned char *Port, unsigned char *Buffer, unsigned int n);
void vSample10MHzTriggerSimple (unsigned char *Port, unsigned char *Buffer, unsigned int n);
void vSample4MHzTriggerSimple (unsigned char *Port, unsigned char *Buffer, unsigned int n);
void vSample400KHzTriggerSimple (unsigned char *Port, unsigned char *Buffer, unsigned int n);

#endif

