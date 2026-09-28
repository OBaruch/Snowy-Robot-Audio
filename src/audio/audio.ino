
#include "SoundData.h"
#include "XT_DAC_Audio.h"

                            
XT_DAC_Audio_Class DacAudio(25,0);          

XT_Wav_Class bellsD(bells_wav);       //b
XT_Wav_Class navidadD(navidad_wav);   //n
XT_Wav_Class faltanD(faltan_wav);     //f
XT_Wav_Class paraD(para_wav);         //p
XT_Wav_Class semanasD(semanas_wav);   //s
XT_Wav_Class unaD(una_wav);           //1
XT_Wav_Class dosD(dos_wav);           //2
XT_Wav_Class tresD(tres_wav);         //3
XT_Wav_Class cuatroD(cuatro_wav);     //4
XT_Wav_Class cincoD(cinco_wav);       //5   

 
XT_Sequence_Class Sequence;              


void setup() {
    Serial.begin(115200);
}




void loop() {
  DacAudio.FillBuffer();    
  if(Serial.available()) 
    PlayNumber(Serial.readString().c_str());      

}












void PlayNumber(char const *Number)
{  
  int NumChars=strlen(Number);              
  Sequence.RemoveAllPlayItems();            
  for(int i=0;i<NumChars;i++)
    AddNumberToSequence(Number[i]);         
  DacAudio.Play(&Sequence);        
  Serial.println(Number);         
}

void AddNumberToSequence(char TheNumber)
{
  switch(TheNumber)
  {
    case 'b' : Sequence.AddPlayItem(&bellsD);break;
    case 'n' : Sequence.AddPlayItem(&navidadD);break;
    case 'f' : Sequence.AddPlayItem(&faltanD);break;
    case 'p' : Sequence.AddPlayItem(&paraD);break;
    case 's' : Sequence.AddPlayItem(&semanasD);break;
    case '1' : Sequence.AddPlayItem(&unaD);break;
    case '2' : Sequence.AddPlayItem(&dosD);break;
    case '3' : Sequence.AddPlayItem(&tresD);break;
    case '4' : Sequence.AddPlayItem(&cuatroD);break;
    case '5' : Sequence.AddPlayItem(&cincoD);break;
  }
}
