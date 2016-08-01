/**
 * @fileName APIManagerExample.c.
 * @author komatsu
 * @version 0.0
 * @date 8/1/16.
 * @description
 */

#include "classes/APIManager/APIManager.h"

/**
 *
 */
void error_message(void);

/**
 *
 * @param response
 * @param result
 */
void callback(char *response, RESPONSE_CODE result);


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
 *
 */
void success_message(void) {
    printf("SUCCESS...");
}


/**
 *
 */
void error_message(void) {
    printf("ERROR...");
}


/**
 * API のレスポンスのコールバック
 * @param response
 * @param result
 */
void callback(char *response, RESPONSE_CODE result) {
    switch(result) {
        case REQUEST_SUCCESS:
            success_message();
            break;

        case REQUEST_FAIL:
            error_message();
            break;

        default:
            error_message();
            break;

    }


    printf("\n\n\n(%d): %s\n\n\n", result, response);


}
