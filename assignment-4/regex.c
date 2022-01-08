#include <regex.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    char str[200];
    int len, check_bef, check_af;
    regex_t regex;

    scanf("%[^\n]s", str);
    printf("%s\n", str);
    len = strlen(str);
    printf("%d\n", len);

    check_bef = regcomp(&regex, "([:number]{1,2}[\\:][:number][:number])", REG_EXTENDED);
    printf("%d\n", check_bef);

    check_af = regexec(&regex, str, 0, NULL, 0);
    printf("%d\n", check_af);

    return 0;
}
