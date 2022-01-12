/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-08-02     Bernard      the first version
 * 2021-02-18     lizhirui     fixed default mimetype,add json minetype
 */

#include <string.h>
#include <rtthread.h>

#include <wn_utils.h>

struct webnet_mime_entry
{
    const char* name;
    const char* type;
};

static const struct webnet_mime_entry mime_tables[] =
{
    { "any",    "application/binary" }, /* default. */
    { "html",   "text/html" },
    { "htm",    "text/html" },
    { "css",    "text/css" },
    { "txt",    "text/plain" },
    { "pdf",    "application/pdf" },
    { "gif",    "image/gif" },
    { "png",    "image/png" },
    { "jpeg",   "image/jpeg" },
    { "jpg",    "image/jpeg" },
    { "svg",    "image/svg+xml" },
    { "avi",    "video/x-msvideo" },
    { "mp3",    "audio/mpeg" },
    { "ogg",    "audio/x-oggvorbis" },
    { "wav",    "audio/x-wav" },
    { "class",  "application/octet-stream" },
    { "js",     "application/x-javascript" },
    { "tar",    "application/x-tar" },
    { "zip",    "application/zip" },
    { "xml",    "text/xml" },
    { "json",   "application/json" },
    { RT_NULL,  RT_NULL }
};

/**
 * get mime type according to URL
 */
const char* mime_get_type(const char* url)
{
    rt_uint32_t index;

    index = 0;
    if (url == RT_NULL)
    {
        return mime_tables[0].type;
    }

    while (mime_tables[index].name != RT_NULL)
    {
        if (str_end_with(url, mime_tables[index].name))
        {
            return mime_tables[index].type;
        }

        index++;
    }

    /* return text/html as default */
    return mime_tables[1].type;
}
