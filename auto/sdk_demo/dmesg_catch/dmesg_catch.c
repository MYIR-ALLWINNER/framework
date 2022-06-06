#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/klog.h>
#include <string.h>

#define DISPLAY_KLOG
#define FALLBACK_KLOG_BUF_SHIFT 17  /* CONFIG_LOG_BUF_SHIFT from our kernel */
#define FALLBACK_KLOG_BUF_LEN   (1 << FALLBACK_KLOG_BUF_SHIFT)

#define KLOG_CLOSE         0
#define KLOG_OPEN          1
#define KLOG_READ          2
#define KLOG_READ_ALL      3
#define KLOG_READ_CLEAR    4
#define KLOG_CLEAR         5
#define KLOG_CONSOLE_OFF   6
#define KLOG_CONSOLE_ON    7
#define KLOG_CONSOLE_LEVEL 8
#define KLOG_SIZE_UNREAD   9
#define KLOG_SIZE_BUFFER   10


typedef struct TestParm_
{
    char outputFile[256];
    int  clean;
    int  no_printf;
    int  testWay;
    int  testTimes;
} TestParm;

typedef enum
{
    INPUT,
    HELP,
    OUTPUT,
    CLEAN,
    NO_PRINTF,
    TEST_WAY,
    TEST_TIMES,
    INVALID
} ArguType;

typedef struct
{
    char option[8];
    char type[128];
    ArguType argument;
    char description[512];
} Argument;

static const Argument ArguTypeMapping[] =
{
    {
        "-h",  "--help",    HELP,
        "Print this help"
    },
    {
        "-o",  "--output",  OUTPUT,
        "set output file path"
    },
    {
        "-c",  "--clean",   CLEAN,
        " nonzero: will clear ring buffer "
    },
    {
        "-d",  "--no-printf",  NO_PRINTF,
        " nonzero: will disable printk to console.."
    },
    {
        "-w",  "--test way",  TEST_WAY,
        "(no use)"
    },
    {
        "-t",  "--test times",  TEST_TIMES,
        " no use."
    },
};

TestParm    testParam;

static ArguType GetArguType(char* name)
{
    int i = 0;
    int num = sizeof(ArguTypeMapping) / sizeof(Argument);
    while (i < num)
    {
        if ((0 == strcmp(ArguTypeMapping[i].type, name)) ||
                ((0 == strcmp(ArguTypeMapping[i].option, name)) &&
                 (0 != strcmp(ArguTypeMapping[i].option, "--"))))
        {
            return ArguTypeMapping[i].argument;
        }
        i++;
    }
    return INVALID;
}

static void PrintDemoUsage(void)
{
    int i = 0;
    int num = sizeof(ArguTypeMapping) / sizeof(Argument);
    printf("Usage:");
    while (i < num)
    {
        printf("%s %-32s %s", ArguTypeMapping[i].option, ArguTypeMapping[i].type,
               ArguTypeMapping[i].description);
        printf("\n");
        i++;
    }
}

static void ParseArguType(TestParm* testParam, char* argument, char* value)
{
    ArguType arg;

    arg = GetArguType(argument);

    switch (arg)
    {
    case HELP:
        PrintDemoUsage();
        exit(-1);
    case OUTPUT:
        memset(testParam->outputFile, 0, sizeof(testParam->outputFile));
        sscanf(value, "%255s", testParam->outputFile);
        printf(" get output file: %s \n", testParam->outputFile);
        break;
    case CLEAN:
        sscanf(value, "%32u", &testParam->clean);
        printf(" clean: %d \n", testParam->clean);
        break;
    case NO_PRINTF:
        sscanf(value, "%32u", &testParam->no_printf);
        printf(" no_printf: %d \n", testParam->no_printf);
        break;
    case TEST_WAY:
        sscanf(value, "%32d", &testParam->testWay);
        printf(" test %d way. \n", testParam->testWay);
        break;

    case TEST_TIMES:
        sscanf(value, "%32d", &testParam->testTimes);
        printf(" test %d times \n",  testParam->testTimes);

        break;
    case INVALID:
    default:
        printf("unknowed argument :  %s\n", argument);
        break;
    }

}

static void printfArgs()
{
    printf("\t\t ================================\n");
    printf("\t\t ========= demesg catch =========\n");
    printf("\t\t ====  outputFile:%s \n", testParam.outputFile );
    printf("\t\t ====  clean:%d               ====\n",  testParam.clean);
    printf("\t\t ====  dis_printf:%d          ====\n", testParam.no_printf);
    printf("\t\t ================================\n");
}


int main(int argc, char** argv)
{

    char* buffer;
    char* p;
    ssize_t ret;
    int n, op, klog_buf_len;
    FILE* fp = NULL;

    memset(&testParam, 0, sizeof(testParam));
    int i;
    if (argc >= 2)
    {
        for (i = 1; i < (int)argc; i += 2)
        {
            ParseArguType(&testParam, argv[i], argv[i + 1]);
        }
    }
    printfArgs();


    if (strlen(testParam.outputFile) > 0)
    {
        fp = fopen(testParam.outputFile, "wa");
        if (fp == NULL)
        {
            printf("Open File Failed:%s!\n",testParam.outputFile);
        }
    }

    klogctl(KLOG_CONSOLE_LEVEL, NULL, 1);
    klog_buf_len = klogctl(KLOG_SIZE_BUFFER, 0, 0);

    if (klog_buf_len <= 0)
    {
        klog_buf_len = FALLBACK_KLOG_BUF_LEN;
    }

    buffer = (char*)malloc(klog_buf_len + 1);

    if (!buffer)
    {
        perror("malloc");
        return EXIT_FAILURE;
    }


    if (0 != testParam.clean)
    {
        op = KLOG_READ_CLEAR;
    }
    else
    {
        op = KLOG_READ;
    }

    int unread_length;
    while (1)
    {
        p = buffer;
        unread_length = klogctl(KLOG_SIZE_UNREAD, NULL, 0);
        n = klogctl(op, buffer, unread_length);
        if (n < 0)
        {
            perror("klogctl");
            return EXIT_FAILURE;
        }
        buffer[n] = '\0';

        if ((strlen(testParam.outputFile) > 0) && (fp))
        {
            fwrite(p, n, 1, fp);
        }

        if (testParam.no_printf == 0)
        {
            while ((ret = write(STDOUT_FILENO, p, n)))
            {
                if (ret == -1)
                {
                    if (errno == EINTR)
                        continue;
                    perror("write");
                    return EXIT_FAILURE;
                }
                p += ret;
                n -= ret;
            }
        }

        fflush(fp);
        memset(buffer, 0, klog_buf_len + 1);
    }
    free(buffer);
    fclose(fp);
    return 0;
}

