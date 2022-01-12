/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-26     ChenYong     First version
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <webnet.h>
#include <wn_module.h>

static void asp_var_version(struct webnet_session* session)
{
    RT_ASSERT(session != RT_NULL);

    static const char *version = "<html><body><font size=\"+2\">RT-Thread %d.%d.%d</font><br><br>"
                                "<a href=\"javascript:history.go(-1);\">Go back to root</a></html></body>";

    webnet_session_printf(session, version, RT_VERSION, RT_SUBVERSION, RT_REVISION);
}

static void cgi_calc_handler(struct webnet_session* session)
{
    int a, b;
    const char* mimetype;
    struct webnet_request* request;
    static const char* header = "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; "
                                "charset=gb2312\" /><title> calc </title></head>";

    static const char* body = "<body><form method=\"post\" action=\"/cgi-bin/calc\"><input type=\"text\" name=\"a\" value=\"%d\"> "
                              "+ <input type=\"text\" name=\"b\" value=\"%d\"> = %d<br><input type=\"submit\" value=\"\xBC\xC6\xCB\xE3\"></form>"
                              "<br><a href=\"/index.html\">Go back to root</a></body></html>\r\n";

    RT_ASSERT(session != RT_NULL);
    request = session->request;
    RT_ASSERT(request != RT_NULL);

    /* get mimetype */
    mimetype = mime_get_type(".html");

    a = 1;
    b = 1;
    /* set http header */
    session->request->result_code = 200;
    webnet_session_set_header(session, mimetype, 200, "Ok", -1);

    webnet_session_write(session, (const rt_uint8_t*)header, rt_strlen(header));
    if (request->query_counter)
    {
        const char *a_value, *b_value;
        a_value = webnet_request_get_query(request, "a");
        b_value = webnet_request_get_query(request, "b");

        a = atoi(a_value);
        b = atoi(b_value);
    }

    webnet_session_printf(session, body, a, b, a + b);
}

static void cgi_hello_handler(struct webnet_session* session)
{
    const char* mimetype;
    static const char* status = "<html><head><title> hello </title>"
                                "</head><body><font size=\"+2\">hello world</font><br><br>"
                                "<a href=\"javascript:history.go(-1);\">Go back to root</a></body></html>\r\n";
    RT_ASSERT(session != RT_NULL);

    /* get mimetype */
    mimetype = mime_get_type(".html");

    /* set http header */
    session->request->result_code = 200;
    webnet_session_set_header(session, mimetype, 200, "Ok", strlen(status));

    webnet_session_write(session, (const rt_uint8_t*)status, rt_strlen(status));
}

void webnet_test(void)
{
#ifdef WEBNET_USING_CGI
    webnet_cgi_register("hello", cgi_hello_handler);
    webnet_cgi_register("calc", cgi_calc_handler);
#endif

#ifdef WEBNET_USING_ASP
    webnet_asp_add_var("version", asp_var_version);
#endif

#ifdef WEBNET_USING_ALIAS
    webnet_alias_set("/test", "/admin");
#endif

#ifdef WEBNET_USING_AUTH
    webnet_auth_set("/admin", "admin:admin");
#endif

#ifdef WEBNET_USING_UPLOAD
    extern const struct webnet_module_upload_entry upload_entry_upload;

    webnet_upload_add(&upload_entry_upload);
#endif

    webnet_init();
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(webnet_test, wenbet test);
#endif
