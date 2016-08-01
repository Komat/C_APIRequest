/**
 * @fileName APIManager.c.
 * @author komatsu
 * @version 0.0
 * @date 8/1/16.
 * @description
 */

#include "APIManager.h"


/**
 *
 * @param urlStr
 * @param url
 * @param error
 */
void parseURL(const char *urlStr, struct URL *url, char **error) {
    char host_path[BUF_LEN];

    if (strlen(urlStr) > BUF_LEN - 1) {
        *error = "URLが長過ぎます。\n";
        return;
    }

    // http://から始まる文字列で
    // sscanfが成功して
    // http://の後に何か文字列が存在するなら
    if (strstr(urlStr, "http://")              &&
        sscanf(urlStr, "http://%s", host_path) &&
        strcmp(urlStr, "http://")) {

        char *p = NULL;

        p = strchr(host_path, '#');
        if (p != NULL) {
            strcpy(url->fragment, p);
            *p = '\0';
        }

        p = strchr(host_path, '?');
        if (p != NULL) {
            strcpy(url->query, p);
            *p = '\0';
        }

        p = strchr(host_path, '/');
        if (p != NULL) {
            strcpy(url->path, p);
            *p = '\0';
        }

        strcpy(url->host, host_path);

        // ホスト名の部分に":"が含まれていたら
        p = strchr(url->host, ':');
        if (p != NULL) {
            // ポート番号を取得
            url->port = (unsigned short) atoi(p + 1);

            // 数字ではない（atoiが失敗）か、0だったら
            // ポート番号は80に決め打ち
            if (url->port <= 0) {
                url->port = 80;
            }

            // 終端文字で空にする
            *p = '\0';
        }
        else {
            url->port = 80;
        }
    }
    else {
        *error = "URLはhttp://host/pathの形式で指定してください。\n";
        return;
    }
}


/**
 *
 * @param url
 * @param callback
 * @return
 */
int requestURL(REQUEST_URL *url, void (*callback)(char *response, RESPONSE_CODE result)) {

    // ソケットのためのファイルディスクリプタ
    int _socket;

    RESPONSE_CODE result = REQUEST_FAIL;

    // IPアドレスの解決
    struct addrinfo hints, *res;
    int err;

    // サーバに送るHTTPプロトコル用バッファ
    char send_buf[BUF_LEN];

    // 0クリア
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;

    char *serviceType = "http";

    if ((err = getaddrinfo(url->host, serviceType, &hints, &res)) != 0) {
        printf("error %d\n", err);
        return 1;
    }

    // ソケット生成
    if ((_socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
        fprintf(stderr, "SOCKET GENERATE ERROR\n");
        callback("SOCKET GENERATE ERROR", result);
        return 1;
    }

    // サーバに接続
    if (connect(_socket, res->ai_addr, res->ai_addrlen) != 0) {
        fprintf(stderr, "CONNECT FAILED\n");
        callback("CONNECT FAILED", result);
        return 1;
    }

    result = REQUEST_SUCCESS;

    // HTTPプロトコルの開始 ＆サーバに送信
    sprintf(send_buf, "GET %s%s HTTP/1.0\r\n", url->path, url->query);
    write(_socket, send_buf, strlen(send_buf));

    sprintf(send_buf, "Host: %s:%d\r\n", url->host, url->port);
    write(_socket, send_buf, strlen(send_buf));

    sprintf(send_buf, "\r\n");
    write(_socket, send_buf, strlen(send_buf));

    // 受信が終わるまでループ
    while (1) {
        char buf[BUF_LEN];
        int read_size;
        read_size = (int) read(_socket, buf, BUF_LEN);

        if (read_size > 0) {
            write(1, buf, (size_t) read_size);
        }
        else {
            break;
        }
    }

    // ソケットを閉じる
    close(_socket);

    callback("CONNECT REQUEST SUCCESS", result);

    return 0;

}
