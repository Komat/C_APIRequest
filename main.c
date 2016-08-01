/**
 * @fileName APIManagerExample.c.
 * @author komatsu
 * @version 0.0
 * @date 8/1/16.
 * @description
 */

#include "classes/APIManager/APIManager.h"

void callback(char *response);

int main(int argc, char *argv[]) {

    REQUEST_URL url = {
            .host = "weather.livedoor.com",
            .path = "/forecast/webservice/json/v1",
            .query = "?city=200010",
            .port = 80,
    };

    // URLが指定されていたら
    if (argc > 1) {
        char *error = NULL;
        parseURL(argv[1], &url, &error);

        if (error) {
            printf("%s\n", error);
            return 1;
        }
    }

    printf("\n\n\n[REQUEST] http://%s%s%s\n\n\n\n", url.host, url.path, url.query);

    requestURL(&url, &callback);

}


/**
 * API のレスポンスのコールバック
 * @param response
 */
void callback(char *response) {
    printf("\n\n\n%s\n\n\n", response);
}

