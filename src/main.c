#include "../include/custom_err_msg.h"
#include "../include/function.h"
#include "../include/graph.h"
#include "../include/list.h"
#include "../include/queue.h"
#include "../include/short_path.h"
#include "../include/stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

int main(int argc, char *argv[]) {
  static FILE *map_fp, *verify_fp, *log_fp;
  static char *username, *flag;
  static int log, init_cout;

  verify_fp = fopen("users.txt", "r");
  log_fp = fopen("login.log", "a");

  if (verify_fp < 0) {
    fprintf(stderr, "读取用户验证文件失败\n");
    exit(-1);
  }
  if (log_fp < 0) {
    fprintf(stderr, "读写用户登录日志文件失败\n");
    exit(-1);
  }

  log = login(verify_fp, log_fp, &username, &flag);
  if (log < 0) {
    fprintf(stderr, "用户验证失败\n");
    exit(-1);
  } else {
    fprintf(stdout, "用户验证成功。");
    if (strcmp(flag, ROOT) == 0)
      fprintf(stdout, "该用户为管理员用户。\n");
    else
      fprintf(stdout, "该用户为普通用户。\n");
  }

  fclose(verify_fp);

  int ver_num;
  graph_t *graph;
  vqueue_t *queue;
  vstack_t *stack;
  spath_t *spath;

  queue = init_queue();
  stack = init_stack();

  int choose, stat_code;
  long dist;
  ver_code ver1, ver2;
  char name[1000], desc[1000];

  for (;;) {
    printf("\n\t\t\t校园导览图\n");
    printf("\n\t\t========================================\n");
    printf("\n\t\t=        1.  初始化景点                   =\n");
    printf("\n\t\t=        2.  初始化景点路线               =\n");
    printf("\n\t\t=        3.  移除景点路线                 =\n");
    printf("\n\t\t=        4.  景点信息                    =\n");
    printf("\n\t\t=        5.  更新景点距离                 =\n");
    printf("\n\t\t=        6.  移除景点                    =\n");
    printf("\n\t\t=        7.  暂闭景点                    =\n");
    printf("\n\t\t=        8.  恢复景点                    =\n");
    printf("\n\t\t=        9.  所有景点                    =\n");
    printf("\n\t\t=        10. 路线推荐                    =\n");
    printf("\n\t\t=        11. 最小路线                    =\n");
    printf("\n\t\t=        12. 添加景点                    =\n");
    printf("\n\t\t=        13. 添加景点路线                 =\n");
    printf("\n\t\t=        14. 系统可初始化景点个数          =\n");
    printf("\n\t\t=        0.  退出                       =\n");
    printf("\n\t\t========================================\n");

    fprintf(stdout, "请选择: ");
    fscanf(stdin, "%d", &choose);

    switch (choose) {
    case 0:
      fprintf(log_fp, "[INFO %s] user %s log out system.\n", local_time(),
              username);
      fclose(log_fp);
      exit(0);
    case 1:
      fprintf(stdout, "输入待添加到图中顶点个数(顶点上限为100): ");
      fscanf(stdin, "%d", &ver_num);

      graph = init_graph(ver_num);
      map_fp = fopen("maps.txt", "r");
      if (map_fp < 0) {
        fprintf(stderr, "读写地图数据文件失败\n");
        exit(-1);
      }
      while (EOF != fscanf(map_fp, "%s %d %s", name, &ver1, desc)) {
        init_vertex(graph, ver1, name, desc);
        bzero(name, sizeof(name));
        bzero(desc, sizeof(desc));
      }
      fclose(map_fp);
      break;
    case 2:
      map_fp = fopen("path.txt", "r");
      assert(map_fp);
      while (EOF != fscanf(map_fp, "%d %d %ld", &ver1, &ver2, &dist)) {
        stat_code = add_edge(graph, ver1, ver2, dist);
        fprintf(stdout, "status: %d\n", stat_code);
      }
      fclose(map_fp);
      break;
    case 3:
      fprintf(stdout, "景点代码: ");
      fscanf(stdin, "%d", &ver1);
      fprintf(stdout, "景点代码: ");
      fscanf(stdin, "%d", &ver2);
      stat_code = remove_edge(graph, ver1, ver2);
      fprintf(stdout, "status: %d", stat_code);
      break;
    case 4:
      fprintf(stdout, "景点代码: ");
      fscanf(stdin, "%d", &ver1);
      stat_code = vertex_info(graph, ver1);
      fprintf(stdout, "status: %d", stat_code);
      break;
    case 5:
      fprintf(stdout, "景点代码: ");
      fscanf(stdin, "%d", &ver1);
      fprintf(stdout, "景点代码: ");
      fscanf(stdin, "%d", &ver2);
      fprintf(stdout, "更新后两顶点间距离");
      fscanf(stdin, "%ld", &dist);
      stat_code = update_edge(graph, ver1, ver2, dist);
      fprintf(stdout, "status: %d", stat_code);
      break;
    case 6:
      fprintf(stdout, "景点代码: ");
      fscanf(stdin, "%d", &ver1);
      stat_code = remove_vertex(graph, ver1);
      fprintf(stdout, "status: %d", stat_code);
      break;
    case 7:
      fprintf(stdout, "景点代码: ");
      fscanf(stdin, "%d", &ver1);
      stat_code = lazzy_remove_vertex(graph, ver1);
      fprintf(stdout, "status: %d\n", stat_code);
      break;
    case 8:
      fprintf(stdout, "景点代码: ");
      fscanf(stdin, "%d", &ver1);
      stat_code = restore_vertex(graph, ver1);
      fprintf(stdout, "status: %d\n", stat_code);
      break;
    case 9:
      stat_code = traverse_graph(graph);
      fprintf(stdout, "status: %d\n", stat_code);
      break;
    case 10:
      fprintf(stdout, "景点代码: ");
      fscanf(stdin, "%d", &ver1);
      if (is_empty(queue) == ELEM_NOT_NULL)
        clean_queue(queue);
      fprintf(stdout, "路线一\n");
      stat_code = BFS(graph, queue, ver1);
      fprintf(stdout, "status: %d\n", stat_code);

      fprintf(stdout, "\n路线二\n");
      stat_code = DFS(graph, stack, ver1);
      fprintf(stdout, "status: %d\n", stat_code);
      break;
    case 11:
      spath = init_spath_data(graph);
      if (!spath)
        continue;

      fprintf(stdout, "起点: ");
      fscanf(stdin, "%d", &ver1);
      fprintf(stdout, "终点: ");
      fscanf(stdin, "%d", &ver2);
      stat_code = dijkstra(graph, spath, ver1);
      fprintf(stdout, "status: %d\n", stat_code);
      stat_code = show_short_path(graph, spath, ver1, ver2);
      fprintf(stdout, "status: %d\n", stat_code);
      break;
    case 12:
      fprintf(stdout, "景点名称: ");
      fscanf(stdin, "%s", name);
      fprintf(stdout, "景点代码: ");
      fscanf(stdin, "%d", &ver1);
      fprintf(stdout, "景点简介: ");
      fscanf(stdin, "%s", desc);
      stat_code = init_vertex(graph, ver1, name, desc);
      fprintf(stdout, "status: %d", stat_code);
      break;
    case 13:
      fprintf(stdout, "景点代码: ");
      fscanf(stdin, "%d", &ver1);
      fprintf(stdout, "景点代码: ");
      fscanf(stdin, "%d", &ver2);
      fprintf(stdout, "两顶点间距离");
      fscanf(stdin, "%ld", &dist);
      stat_code = add_edge(graph, ver1, ver2, dist);
      fprintf(stdout, "status: %d", stat_code);
      break;
    case 14:
      init_cout = valid_init_vertex_count(graph);
      fprintf(stdout, "系统可初始化顶点个数: %d", init_cout);
      break;
    }
  }

  return 0;
}
