#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define DEFT_SCALE (500)
#define BIN_MODE   1
#define CHAR_MODE 2
void Generate(FILE *fout, int gen_scale, int out_mode, char *out_file);
void ErrOrHelp(void);

int main(int argc, char *argv[])
{
    int   option;
    FILE *fout;
    int   scale, outputmode;
    char *outputfile = "RandomInput";
    int   modeflag, errflag;

    scale = DEFT_SCALE;
    outputmode = BIN_MODE;
    modeflag = errflag = 0;

    if (argc > 1)
        {
            while (errflag==0 && (option = getopt(argc, argv, "bcS:N:"))!=-1)
                {
                    switch (option)
                        {
                        case 'b':
                            if (modeflag == 0)
                                {
                                    modeflag   = 1;
                                    outputmode = BIN_MODE;
                                }
                            else
                                {
                                    errflag = 1;
                                    ErrOrHelp();
                                }
                            break;

                        case 'c':
                            if (modeflag == 0)
                                {
                                    modeflag   = 1;
                                    outputmode = CHAR_MODE;
                                }
                            else
                                {
                                    errflag = 1;
                                    ErrOrHelp();
                                }
                            break;

                        case 'N':
                            outputfile = optarg;
                            break;

                        case 'S':
                            if ((scale = atoi(optarg)) == 0)
                                {
                                    errflag = 1;
                                    ErrOrHelp();
                                }
                            break;

                        default:
                            errflag = 1;
                            ErrOrHelp();
                            break;
                        }
                }
            if (errflag == 0)
                Generate(fout, scale, outputmode, outputfile);
        }    
    else
        Generate(fout, scale, outputmode, outputfile);

    return 0;
}

void Generate(FILE *fout, int gen_scale, int out_mode, char *out_file)
{
    int i = 0, num;

    srand((unsigned)time(NULL));
    if ((fout = fopen(out_file, "w")) == NULL)
        {
            fprintf(stderr,"Can't open or create file.Check your permission.");
            exit(1);
        }

    if (out_mode == BIN_MODE)
        {
            fprintf(stdout, "Generating %d random numbers using fwrite()...\n", gen_scale);
            fprintf(stdout, "You should read it by using fread()\n");
            while (i++ < gen_scale)
                {
                    num = rand() % gen_scale;
                    fwrite(&num, sizeof(int), 1, fout);
                }
        }
    else if (out_mode == CHAR_MODE)
        {
            fprintf(stdout, "Generating %d random numbers using fprintf()...\n", gen_scale);
            fprintf(stdout, "You should read it by using fscanf()\n");
            
            while (i++ < gen_scale)
                {
                    num = rand() % gen_scale;
                    fprintf(fout, "%d ", num);
                }
        }
    else
        ;
}

void ErrOrHelp(void)
{
    fprintf(stdout, "You must specify one of the `-bcSN' options.Usage:\n");
    fprintf(stdout, "-c    write the output file using fprint() \n");
    fprintf(stdout, "-b    write the output file using fwrite() \n");
    fprintf(stdout, "-S    Set the size of output you want.(default 500) \n");
    fprintf(stdout, "-N    Set the name of the output file.(default RandomInput) \n");
}
        
            
    
    
