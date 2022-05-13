#include <stdio.h>

#define MAXVALUE 20000
#define SIZE 26

int size(char *);
int ccount(char *, char);
void inverse(char *s);
void lower(char *s);

void freq(char *s, int *);
void rel_freq(int *, FILE *);

void read_string(char *s, FILE *);

int main(int argc, char *argv[]) {

  if (argc !=3)
  {
    printf("Incorrect number of arguments..."
      "\nFormat:cfreq num fname out\n"
      "num - number of files to be read\n" //argv[1]
      "fname - The base file name without extension. Assumes all files are ordered in the following format"
      "\ndata0.txt, data1.txt, data2.txt, ...\n"); //argv[2]

    return 1;
  }

  int nfile; // number of data files to be read
  sscanf(argv[1], "%d", &nfile);

  for(int i=0; i<nfile; i++)
    {
      char fname[MAXVALUE];
      char out_name[MAXVALUE];


      sprintf(fname, "%s%d.txt", argv[2], i);    // Concatenates the integer i with the string from the
      sprintf(out_name, "%s%d.dat", argv[2], i); // command line to prepare for reading the file.
                                              
      FILE *in;
      FILE *out;
      in = fopen(fname, "r");      
      out = fopen(out_name, "w");


      char text[MAXVALUE];
      read_string(text, in);
      
      int freq_arr[SIZE] = {0};
      
      freq(text, freq_arr);
      rel_freq(freq_arr, out);

      fclose(in);
      fclose(out);
    }

  return 0;
}

int ccount(char *s, char c)

/*
  Returns the number of occurances of a character in the given string.
*/

{
  int counter, i;
  counter = i = 0;

  while(s[i] != '\0')
  {
    if(s[i] == c)
      counter++;
    i++;
  }

  return counter;
}

void lower(char *s)

/*
  Lowers all capital ASCII letters given a char pointer.
*/

{
  int i;
  i = 0;

  while(s[i] != '\0')
    {
      if( s[i] >= 'A' && s[i] <= 'Z')
        s[i] += 32;
      i++;
    }
}

/*
  Writes the frequency of English alphabets into a given int array.
  All capital letters are lowered beforehand.   
*/

void freq(char *s, int *freq)
{
  lower(s);
  
  for(char i = 'a'; i <= 'z'; i++)
    freq[i - 'a'] = (ccount(s, i));

}

void rel_freq(int *freq_arr, FILE *out)
/*
  Writes the frequency, relative frequency of each alphabets into files seperated by a line break.
  Receives: integer array of frequencies for each alphabet and its size,
            string for the name of the output file. 
*/

{ 
  
  int total = 0;

  for(int j=0; j<SIZE; j++)
      total += freq_arr[j];
  
  for(int j=0; j<SIZE; j++)
    fprintf(out, "%c: %d %f \n", 'a'+j, freq_arr[j],   (float)freq_arr[j]/(float)total*100);
  
  //Histogram implementation
  int histo[SIZE] = {0};
  for(int j=0; j<SIZE; j++)
  {
    histo[j] = (int)((float)freq_arr[j]/(float)total*100);
  }

  fprintf(out, "\n\nRelative Frequency Histogram\n");
  for (int i=0; i<SIZE; ++i) 
  {
    fprintf(out, "%2c |", i+'a');
    for (int j=0; j<histo[i]; ++j)
      fprintf(out, "|");
    fprintf(out, "  %.3f", (float)freq_arr[i]/(float)total*100);
    fprintf(out, "\n");
  }
    
}  


void read_string(char *s, FILE *fp)
/*
  Reads all characters from the file to a given string.
  Breaks in either the char array's MAXVALUE or EOF has been reached.
*/

{
  char c;
  int i = 0;
  while( (c = fgetc(fp)) != EOF ) 
  {
    s[i] = c;
    if (i < MAXVALUE)
      i++;
    else
      break; 
  }
}