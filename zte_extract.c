/*
* Copyright (c) 2014 Toni Spets <toni.spets@iki.fi>
*
* Permission to use, copy, modify, and distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*
 * compile: gcc -std=c99 -Wall -o zte_extract zte_extract.c
 * usage: ./zte_extract <l/x> <firmware.exe> [files...]
*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define CHUNK 16384

struct installer_info
{
    uint32_t offset;
    int32_t files;
};

struct installer_file
{
    int8_t name[512];
    int8_t unk1[6];
    int8_t md5[33];
    int8_t unk2[21];
    uint32_t length;
};

enum
{
    MODE_UNK,
    MODE_LIST,
    MODE_EXTRACT
};

int main(int argc, char **argv)
{
    int ret = 1;
    FILE *installer_fh = NULL, *file_fh = NULL;
    struct installer_info info;
    int mode = MODE_UNK;

    fprintf(stderr, "ZTE Extract / Copyright (c) 2014 Toni Spets <toni.spets@iki.fi>\n");

    if (argc < 3 || strlen(argv[1]) > 1)
        goto usage;

    switch (argv[1][0])
    {
        case 'l': mode = MODE_LIST; break;
        case 'x': mode = MODE_EXTRACT; break;
        default: mode = MODE_UNK;
    }

    if (mode == MODE_UNK)
        goto usage;

    installer_fh = fopen(argv[2], "r");
    if (installer_fh == NULL)
    {
        perror(argv[2]);
        goto cleanup;
    }

    if (fseek(installer_fh, -(sizeof info), SEEK_END) != 0)
    {
        perror("fseek");
        goto cleanup;
    }

    if (fread(&info, sizeof info, 1, installer_fh) != 1)
    {
        perror("fread");
        goto cleanup;
    }

    if (fseek(installer_fh, info.offset, SEEK_SET) != 0)
    {
        fprintf(stderr, "Not a ZTE firmware installer, invalid offset 0x%X\n", info.offset);
        goto cleanup;
    }

    if (info.files > 256 || info.files < 1)
    {
        fprintf(stderr, "Not a ZTE firmware installer, invalid number of files (%d)\n", info.files);
        goto cleanup;
    }

    if (mode == MODE_LIST)
    {
        printf("Length     MD5                              Name\n");
        printf("----------------------------------------------------------------------\n");

        unsigned long total = 0;
        for (int i = 0; i < info.files + 1; i++)
        {
            struct installer_file file;

            if (fread(&file, sizeof file, 1, installer_fh) != 1)
            {
                fprintf(stderr, "Invalid installer, reading file info failed\n");
                goto cleanup;
            }

            printf("%10d %s %s\n", file.length, file.md5, file.name);
            fseek(installer_fh, file.length, SEEK_CUR);

            total += file.length;
        }

        printf("----------------------------------------------------------------------\n");
        printf("%10lu                                  %d files\n", total, info.files + 1);
    }

    else if (mode == MODE_EXTRACT)
    {
        for (int i = 0; i < info.files + 1; i++)
        {
            struct installer_file file;
            int do_extract = (argc == 3);

            if (fread(&file, sizeof file, 1, installer_fh) != 1)
            {
                fprintf(stderr, "Invalid installer, reading file info failed\n");
                goto cleanup;
            }

            if (argc > 3)
            {
                for (int j = 3; j < argc; j++)
                {
                    if (strcmp(argv[j], (const char *)file.name) == 0)
                    {
                        do_extract = 1;
                        break;
                    }
                }
            }

            if (do_extract)
            {
                fprintf(stderr, "Extracting %s...\n", file.name);

                file_fh = fopen((const char *)file.name, "w");
                if (!file_fh)
                {
                    perror((const char *)file.name);
                    goto cleanup;
                }

                unsigned long p = 0;
                int8_t buf[CHUNK];
                do {
                    unsigned long next = (p + CHUNK < file.length) ? CHUNK : file.length - p;

                    if (fread(buf, next, 1, installer_fh) != 1)
                    {
                        perror("fread");
                        goto cleanup;
                    }

                    if (fwrite(buf, next, 1, file_fh) != 1)
                    {
                        perror("fwrite");
                        goto cleanup;
                    }

                    p += next;
                } while (p < file.length);

                fclose(file_fh);
                file_fh = NULL;
            }
            else
            {
                fseek(installer_fh, file.length, SEEK_CUR);
            }
        }
    }

    ret = 0;
    goto cleanup;

usage:
    fprintf(stderr, "usage: %s <l/x> <firmware.exe> [files...]\n", argv[0]);

cleanup:
    if (installer_fh) fclose(installer_fh);
    if (file_fh) fclose(file_fh);

    return ret;
}
