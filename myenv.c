/*
 *  myenv.c : env コマンドのクローン
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __linux__
#include "myputenv.h"
#endif

extern char **environ; /* 現在の環境変数一覧 */

int main(int argc, char *argv[]) {
  int i;

  /* putenv() がエラーになるまで、引数を環境変数の設定として扱う */
  for (i = 1; i < argc; i++) {
    if (putenv(argv[i]) != 0) {
      /* "=" を含まない → command の開始とみなしてループを抜ける */
      break;
    }
  }

  if (i == argc) {
    /* command が省略された場合：変更後の環境変数一覧を表示 */
    char **env;
    for (env = environ; *env != NULL; env++) {
      printf("%s\n", *env);
    }
  } else {
    /* command が指定された場合：それを実行する */
    execvp(argv[i], &argv[i]);
    /* execvp が戻ってきたら実行失敗 */
    perror(argv[i]);
    exit(1);
  }

  return 0;
}

/* 実行例

nakamurayuusuke@London kadai09-i23nakamura % make
cc -D_GNU_SOURCE -Wall -std=c99 -o myenv myenv.c myputenv.c

nakamurayuusuke@London kadai09-i23nakamura % ./myenv
TMPDIR=/var/folders/g4/jq7xr1415sq9gv2kg1qfkp0h0000gn/T/
__CFBundleIdentifier=com.apple.Terminal
XPC_FLAGS=0x0
LaunchInstanceID=C367AD1A-E737-40E7-8514-2B83E7025822
TERM=xterm-256color
SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.bVJN1V7484/Listeners
SECURITYSESSIONID=186b6
XPC_SERVICE_NAME=0
TERM_PROGRAM=Apple_Terminal
COLORTERM=truecolor
OSLogRateLimit=64
TERM_PROGRAM_VERSION=466
TERM_SESSION_ID=BD8EB034-12EF-46D5-8F4B-6DB4F4F05F07
SHELL=/bin/zsh
HOME=/Users/nakamurayuusuke
LOGNAME=nakamurayuusuke
USER=nakamurayuusuke
PATH=/opt/homebrew/opt/openjdk/bin:/opt/homebrew/opt/openjdk/bin:/opt/homebrew/opt/git/bin:/opt/homebrew/bin:/opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin:/opt/pmk/env/global/bin
SHLVL=1
PWD=/Users/nakamurayuusuke/Syspro/kadai09-i23nakamura
OLDPWD=/Users/nakamurayuusuke/Syspro
HOMEBREW_PREFIX=/opt/homebrew
HOMEBREW_CELLAR=/opt/homebrew/Cellar
HOMEBREW_REPOSITORY=/opt/homebrew
FPATH=/opt/homebrew/share/zsh/site-functions:/usr/local/share/zsh/site-functions:/usr/share/zsh/site-functions:/usr/share/zsh/5.9/functions
INFOPATH=/opt/homebrew/share/info:
CPPFLAGS=-I/opt/homebrew/opt/openjdk/include
LANG=ja_JP.UTF-8
_=/Users/nakamurayuusuke/Syspro/kadai09-i23nakamura/./myenv

nakamurayuusuke@London kadai09-i23nakamura % ./myenv LC_TIME=ja_JP.UTF-8 TZ=Cuba
ls -l total 384 -rw-r--r--  1 nakamurayuusuke  staff     132  6月 29 21:50
Makefile -rwxr-xr-x  1 nakamurayuusuke  staff   33784  7月  1 22:21 myenv
-rw-r--r--  1 nakamurayuusuke  staff    1274  7月  1 22:25 myenv.c
-rwxr-xr-x  1 nakamurayuusuke  staff     216  6月 29 21:50 myputenv.c
-rw-r--r--  1 nakamurayuusuke  staff      93  6月 29 21:50 myputenv.h
-rw-r--r--  1 nakamurayuusuke  staff    1268  6月 29 21:50 README.md
-rw-r--r--  1 nakamurayuusuke  staff  139098  6月 29 21:50 README.pdf

nakamurayuusuke@London kadai09-i23nakamura % ./myenv NAME=NAKAMURA
TMPDIR=/var/folders/g4/jq7xr1415sq9gv2kg1qfkp0h0000gn/T/
__CFBundleIdentifier=com.apple.Terminal
...(中略)...
LANG=ja_JP.UTF-8
_=/Users/nakamurayuusuke/Syspro/kadai09-i23nakamura/./myenv
NAME=NAKAMURA

nakamurayuusuke@London kadai09-i23nakamura % ./myenv OOOOO
OOOOO: No such file or directory
*/