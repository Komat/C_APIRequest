/**
 * @fileName APIManager.h.
 * @author komatsu
 * @version 0.0
 * @date 8/1/16.
 * @description
 */

#ifndef APIMANAGER_APIMANAGER_H
#define APIMANAGER_APIMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

#define BUF_LEN 256

/**
 *
 */
typedef struct URL {
    char host[BUF_LEN];
    char path[BUF_LEN];
    char query[BUF_LEN];
    char fragment[BUF_LEN];
    unsigned short port;
} REQUEST_URL;


void parseURL(const char *urlStr, struct URL *url, char **error);


int requestURL(REQUEST_URL *url, void (*callback)(char *response));

#endif //APIMANAGER_APIMANAGER_H
