#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int hour;
    int min;
} Time;
void OpenFile(FILE **, char *, char *);
int ReadLine(FILE *, char *);
int Get4Turn(FILE *, Time *, Time *);
void GetTime(Time *, Time *, Time*);
int main(void)
{
    FILE *fp = NULL;
    Time start;
    Time end;
    Time sum;
    int ch;
    sum.hour = sum.min = 0;
    OpenFile(&fp, "studytime.txt", "r");
    while (1)
    {
        if ((Get4Turn(fp, &start, &end)) == EOF)
            break;
        GetTime(&sum, &start, &end);
    }
    printf(__DATE__"\n총 공부시간 : %d시간 %d분\n", sum.hour, sum.min);
    fclose(fp);
    printf("\nEnter to quit\n");
    while ((ch = getchar()) != '\n');

    return 0;
}
void OpenFile(FILE **fp, char *file_name, char *file_type)
{
    if ((*fp = fopen(file_name, file_type)) == NULL)
    {
        fprintf(stderr, "%s 파일을 열 수 없습니다.\n", file_name);
        exit(1);
    }
}
int ReadLine(FILE *fp, char *line)
{
    return fscanf(fp, "%[^\n]\n", line);
}
int Get4Turn(FILE *fp, Time *start, Time *end)
{
    char line[50], trash[50];
    if (ReadLine(fp, line) == EOF)
        return EOF;
    sscanf(line, "%s %s %s %s %d:%d", trash, trash, trash, trash, &start->hour, &start->min);
    if (!strcmp(trash, "오후") && start->hour != 12)
    {
        start->hour += 12;
    }
    ReadLine(fp, line);
    ReadLine(fp, line);
    sscanf(line, "%s %s %s %s %d:%d", trash, trash, trash, trash, &end->hour, &end->min);
    if (!strcmp(trash, "오후") && end->hour != 12)
    {
        end->hour += 12;
    }

    ReadLine(fp, line);
    return 0;
}
void GetTime(Time *sum, Time *start, Time *end)
{
    sum->hour += (end->hour - start->hour);
    sum->min += (end->min - start->min);
    if (sum->min < 0)
    {
        (sum->hour)--;
        sum->min += 60;
    }
    if (sum->min >= 60)
    {
        (sum->hour)++;
        sum->min -= 60;
    }
}