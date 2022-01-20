#include "../include/function.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

/**
 * @brief
 * 传入指向已有的用户验证文件和用户登录日志文件描述符，逐一扫描用户验证文件中已定义的用户名和密码，首先与用户输入用户名进行比较，在用户名正确的前提下将文件中扫描到的密码与用户输入密码进行比较，若两者皆相同则退出函数并返回OK。用户拥有三次验证机会。日志文件描述符用以将验证行为写入日志文件
 *
 * @param users_fp  已定义用户名和密码的文件的描述符
 * @param log_fp    写入验证行为的日志文件的描述符
 * @param username  二级指针，指向通过验证的用户名
 * @param flag      验证用户为普通用户或拥有管理员权限用户
 * @return VERIFY_ERROR or OK
 */
int login(FILE *users_fp, FILE *log_fp, char **username, char **flag) {
  static char user[1000], user_ver[1000];
  static char passwd[100], passwd_ver[1000];
  static int rcount, user_cmp, passwd_cmp, count, user_flag;

  for (count = 1; count <= VERIFY_COUNT; count++) {
    rewind(users_fp);

    fprintf(stdout, "用户名: ");
    fscanf(stdin, "%s", user);
    fprintf(stdout, "密码: ");
    fscanf(stdin, "%s", passwd);

    while (EOF != (rcount = fscanf(users_fp, "%s %s %d", user_ver, passwd_ver,
                                   &user_flag))) {
      user_cmp = strcmp(user, user_ver);
      if (user_cmp == 0) {
        passwd_cmp = strcmp(passwd, passwd_ver);
        if (passwd_cmp == 0) {
          *username = user;
          fprintf(stdout, "登录成功\n");
          if (user_flag == 1) {
            *flag = ROOT;
            fprintf(
                log_fp,
                "[INFO %s] VERIFY: Root user %s login in system successfully\n",
                local_time(), user);
          } else {
            *flag = NORMAL;
            fprintf(log_fp,
                    "[INFO %s] VERIFY: user %s login in system successfully\n",
                    local_time(), user);
          }
          return OK;
        } else {
          fprintf(stdout, "密码错误， 你还有%d次验证机会\n",
                  VERIFY_COUNT - count);
          fprintf(
              log_fp,
              "[ERROR %s] VERIFY: user %s failure in log in system. password "
              "error.\n",
              local_time(), user);
        }

        break;
      }

      bzero(user_ver, sizeof(user_ver));
      bzero(passwd_ver, sizeof(passwd_ver));
    }

    if (user_cmp < 0) {
      fprintf(stdout, "用户名错误。你还有%d次验证机会\n", VERIFY_COUNT - count);
      fprintf(log_fp,
              "[ERROR %s] VERIFY: user %s failure in log in system. user not "
              "exists.\n",
              local_time(), user);
    }
    fflush(log_fp);

    bzero(user, sizeof(user));
    bzero(passwd, sizeof(passwd));
  }

  return VERIFY_ERROR;
}

char *local_time() {
  time_t mytime = time(NULL);
  char *time_str = ctime(&mytime);
  time_str[strlen(time_str) - 1] = '\0';

  return time_str;
}