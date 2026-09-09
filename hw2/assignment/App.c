#include "App.h"
#include "stopwatch.h"
#include <stdio.h>
#include <stdlib.h>

#define DATA_SIZE (12000 * 8000)
#define STAGES (4)

unsigned char * Data[STAGES + 1];

void Exit_with_error(void)
{
  perror(NULL);
  exit(EXIT_FAILURE);
}

void Load_data(void)
{
  FILE * File = fopen("Input.bin", "rb");
  if (File == NULL)
    Exit_with_error();

  if (fread(Data[0], 1, DATA_SIZE, File) != DATA_SIZE)
    Exit_with_error();

  if (fclose(File) != 0)
    Exit_with_error();
}

void Store_data(const char * Filename, int Stage, unsigned int Size)
{
  FILE * File = fopen(Filename, "wb");
  if (File == NULL)
    Exit_with_error();

  if (fwrite(Data[Stage], 1, Size, File) != Size)
    Exit_with_error();

  if (fclose(File) != 0)
    Exit_with_error();
}

stopwatch total_time;
stopwatch scale;
stopwatch differentiate;
stopwatch compress;

int main()
{
  total_time.start();
  for (int i = 0; i <= STAGES; i++)
  {
    // We could strictly allocate less memory for some of these buffers, but
    // that is irrelevant here.
    Data[i] = (unsigned char*)malloc(DATA_SIZE);
    if (Data[i] == NULL)
      Exit_with_error();
  }
  Load_data();

  scale.start();
  Scale(Data[0], Data[1]);
  scale.stop();

  double filter_horizontal_time;
  double filter_vertical_time;

  
  Filter(Data[1], Data[2], &filter_horizontal_time, &filter_vertical_time);

  differentiate.start();
  Differentiate(Data[2], Data[3]);
  differentiate.stop();

  compress.start();
  int Size = Compress(Data[3], Data[4]);
  compress.stop();

  Store_data("Output.bin", 4, Size);

  for (int i = 0; i <= STAGES; i++)
    free(Data[i]);
  
  total_time.stop();

  puts("Application completed successfully.");

  printf("\n----------------- Profiling Results -----------------\n");

  printf("Average latency of Scale:             %.2f ns\n",
        scale.avg_latency());

  printf("Average latency of Filter_horizontal: %.2f ns\n",
        filter_horizontal_time);

  printf("Average latency of Filter_vertical:   %.2f ns\n",
        filter_vertical_time);

  printf("Average latency of Differentiate:     %.2f ns\n",
        differentiate.avg_latency());

  printf("Average latency of Compress:          %.2f ns\n",
        compress.avg_latency());

  printf("Total application latency:            %.2f ns\n",
        total_time.latency());

  printf("-----------------------------------------------------\n");

  
  return EXIT_SUCCESS;
}


