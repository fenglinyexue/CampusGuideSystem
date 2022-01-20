#ifndef ERROR_H
#define ERROR_H 1

typedef enum err {
  VER_OUT_BROUND = -21,     // 顶点下标越界
  SPATH_NULL = -20,         // 球最短路径结构体未分配内存空间
  GRAPH_CAPACITY_OUT = -19, // 图的初始化顶点个数已满
  ELEM_IS_NULL = -18,       // 队列或栈内无元素存在
  STACK_NULL = -17,         // 栈为分配内存空间
  VERIFY_ERROR = -15,       // 用户验证失败
  QUEUE_NULL = -14,         // 队列为分配内存空间
  EDGE_EXIST = -13,         // 路径已存在
  EDGE_NOT_EXIST = -12,     // 路径不存在
  ADJ_VER_NOT_EXIST = -11,  // 相邻景点不存在
  ADJ_VER_EXIST = -10,      // 相邻景点已存在
  ADJ_VER_NULL = -9,        // 无相邻景点
  VER_NOT_CLOSE = -8,       // 景点未关闭
  VER_ALREADY_CLOSE = -7,   // 景点已关闭
  VER_EXIST = -5,           // 景点已存在
  VER_NOT_EXIST = -16,      // 景点不存在
  VER_LIMMIT = -4,          // 超出图中顶点上限
  VER_CODE_ERR = -3,        // 无效景点代码
  LIST_NULL = -2,           // 邻接表为空
  GRAPH_NULL = -1,          // 图为空
  OK = 0,                   // 无异常
  ELEM_NOT_NULL = 1,        // 队列或栈内存在元素
} ERROR;

#endif