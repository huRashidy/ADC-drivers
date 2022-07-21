///*
// * adc.h
// *
// *  Created on: ??þ/??þ/????
// *      Author: hosen
// */
//
#ifndef INCLUDE_ADC_H_
#define INCLUDE_ADC_H_

#define USE_POLLING 1
//
//enum Resolution{
//	twelve_bits , ten_bits , eight_bits , six_bits };
//enum ConversionMode{
//	single , cont };

typedef struct {
	enum Resolution {twelve_bits , ten_bits , eight_bits , six_bits } res;
	enum ConversionMode {single , cont }conv;
	float VRef;
}ADCConfigType;

void ADC_Init(ADCConfigType* ConfigParamPtr);
void ADC_StartConv(unsigned char ChannelNum);
void ADC_GetConversionState(unsigned char* ConversionStatePtr);
unsigned char ADC_ReadData(unsigned short int* DataPtr);

#endif /* INCLUDE_ADC_H_ */
